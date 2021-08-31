#include "juxt.hpp"
#include "task.hpp"

#include "cert_patches/cert_backup_strategy.hpp"
#include "cert_patches/cert_backup.hpp"
#include "cert_patches/cert_hashes.hpp"
#include "rpx_patches/rpx_backup_strategy.hpp"
#include "rpx_patches/rpx_backup.hpp"
#include "rpx_patches/rpx_hashes.hpp"
#include "rpx_patches/rpx_patch.hpp"
#include "util/copy_file.hpp"

static constexpr int task_percent(int task) { return (task*100)/17; };

void JuxtPermaPatch(Task& task, std::filesystem::path miiverse_path) {
    bool bret;
    int progress = 0;

    //goal: get a state together; ready to show a menu or something
    //https://marcan.st/2011/01/safe-hacking/

    std::filesystem::path wave_path = miiverse_path/"code/wave.rpx";
    std::filesystem::path wave_bak_path = miiverse_path/"code/wave.rpx.orig";
    std::filesystem::path wave_patched_path = miiverse_path/"code/wave.rpx.patched";

    std::filesystem::path pn_olv_path = miiverse_path/"code/pn_olv.rpl";
    std::filesystem::path nn_olv_path = "iosu:/vol/system_slc/title/00050010/1000400a/code/nn_olv.rpl";
    std::filesystem::path pn_olv_patched_path = miiverse_path/"code/pn_olv.rpl.patched";

    std::filesystem::path cert_path = "iosu:/vol/storage_mlc01/sys/title/0005001b/10054000/content/scerts/THAWTE_PREMIUM_SERVER_CA.der";
    std::filesystem::path cert_bak_path = "iosu:/vol/storage_mlc01/sys/title/0005001b/10054000/content/scerts/THAWTE_PREMIUM_SERVER_CA.der.orig";
    std::filesystem::path cert_patched_path = "resin:/dstrootx3.der";

    std::error_code fserr;

    task.Progress(task_percent(progress++), "Examining current Miiverse state... (wave.rpx)");

    BackupState wave_state = GetBackupStrategy(wave_path, wave_bak_path);
    if (!wave_state.strategy) {
        //couldn't come up with a way to continue
        task.SetError(MENU_DONE_NO_BACKUP, "Could not find a suitable backup strategy!");
        return;
    }
    BackupStrategy wave_strategy = *wave_state.strategy;

    task.Progress(task_percent(progress++), "Examining current Miiverse state... (nn_olv.rpl)");

    //we can be a bit less careful with nn_olv, since we always have the stock file on hand
    //if the stock file is bad, the patcher should catch it
    BackupStrategy olv_strategy = {
        .need_confirmation = false,
        .backup_action = B_DO_NOTHING,
        .patch_action = P_PATCH_FROM_BACKUP,
    };

    task.Progress(task_percent(progress++), "Examining current Miiverse state... (NSSL cert)");

    //certs use a different strategy, since we're always overwriting from resin
    auto cert_strategy_o = GetCertBackupStrategy(cert_path, cert_bak_path);
    if (!cert_strategy_o) {
        //couldn't continue
        task.SetError(MENU_DONE_NO_CERT_BACKUP, "Could not find a suitable certificate backup strategy!");
        return;
    }
    BackupStrategy cert_strategy = *cert_strategy_o;

    bool confirmed = task.DoConfirmationMenu(CONFIRMATION_MENU_MIIVERSE, wave_state);
    if (!confirmed) return;

    task.Progress(task_percent(progress++), "Creating Miiverse backup... (wave.rpx)");

    bret = backup_rpx(wave_strategy.backup_action, wave_path, wave_bak_path);
    if (!bret) {
        wave_strategy.patch_action = P_DO_NOTHING;
        task.SetError(MENU_DONE_BACKUP_FAIL, "Failed to backup wave!");
        return;
    }

    task.Progress(task_percent(progress++), "Creating Miiverse backup... (pn_olv.rpl)");

    bret = backup_rpx(olv_strategy.backup_action, pn_olv_path, nn_olv_path);
    if (!bret) {
        olv_strategy.patch_action = P_DO_NOTHING;
        task.SetError(MENU_DONE_BACKUP_FAIL, "Failed to backup olv!");
        return;
    }

    task.Progress(task_percent(progress++), "Creating Miiverse backup... (NSSL cert)");

    bret = backup_cert(cert_strategy.backup_action, cert_path, cert_bak_path);
    if (!bret) {
        cert_strategy.patch_action = P_DO_NOTHING;
        task.SetError(MENU_DONE_BACKUP_FAIL, "Failed to backup cert!");
        return;
    }

    task.Progress(task_percent(progress++), "Applying Miiverse patches... (wave.rpx)");

    bret = patch_rpx(wave_strategy.patch_action, wave_path, wave_bak_path, wave_patched_path, "resin:/patches/wave.d.v113.p1.bps");
    if (!bret) {
        task.SetError(MENU_DONE_PATCH_FAIL, "Failed to patch wave!");
        return;
    }

    task.Progress(task_percent(progress++), "Applying Miiverse patches... (nn_olv.rpl)");

    //DANGER: getting argument order wrong here could cause brickable writes to OSv10!
    bret = patch_rpx(olv_strategy.patch_action, pn_olv_path, nn_olv_path, pn_olv_patched_path, "resin:/patches/nn_olv.d.v15072.p1.bps");
    if (!bret) {
        task.SetError(MENU_DONE_PATCH_FAIL, "Failed to patch nn_olv.rpl!");
        return;
    }

    task.Progress(task_percent(progress++), "Verifying patched files... (wave.rpx)");

    {
        std::ifstream is(wave_patched_path, std::ios::binary);
        auto hash = rpx_hash(is);
        if (hash.id != CURRENT_PRETENDO_WAVE) {
            task.SetError(MENU_DONE_PATCH_BAD, "Patcher made a corrupt file!");
            return;
        }
    }

    task.Progress(task_percent(progress++), "Verifying patched files... (nn_olv.rpl)");

    {
        std::ifstream is(pn_olv_patched_path, std::ios::binary);
        auto hash = rpx_hash(is);
        if (hash.id != CURRENT_PRETENDO_NN_OLV) {
            task.SetError(MENU_DONE_PATCH_BAD, "Patcher made a corrupt file!");
            return;
        }
    }

    task.Progress(task_percent(progress++), "Verifying patched files... (NSSL cert)");

    {
        std::ifstream is(cert_patched_path, std::ios::binary);
        auto hash = cert_hash(is);
        if (hash.id != CURRENT_PRETENDO_CERT) {
            task.SetError(MENU_DONE_PATCH_BAD, "New SSL certificate is corrupt");
            return;
        }
    }

    //the point of no return
    task.Progress(task_percent(progress++), "Committing changes... (wave.rpx)");

    bret = fast_copy_file(wave_patched_path, wave_path);
    if (!bret) {
        printf("Final file copy failed!\n");
        //the next step is verification. on the off chance the copy 100% failed
        //and the stock wave is still there, we could still quit gracefully, so
        //we don't hard-fail here.
    }

    task.Progress(task_percent(progress++), "Committing changes... (nn_olv.rpl)");

    bret = fast_copy_file(pn_olv_patched_path, pn_olv_path);
    if (!bret) {
        printf("Final olv file copy failed!\n");
    }

    task.Progress(task_percent(progress++), "Committing changes... (NSSL cert)");

    bret = fast_copy_file(cert_patched_path, cert_path);
    if (!bret) {
        printf("Final olv file copy failed!\n");
    }

    task.Progress(task_percent(progress++), "Verifying final patches... (wave.rpx)");

    {
        std::ifstream is(wave_path, std::ios::binary);
        auto hash = rpx_hash(is);
        if (hash.patch == RPX_PATCH_STATE_STOCK) {
            task.SetError(MENU_DONE_PATCH_FAIL, "Failed to commit patches - stock wave in place");
            return;
        } else if (hash.id != CURRENT_PRETENDO_WAVE) {
            task.SetError(MENU_DONE_PATCH_FAIL_DANGEROUS, "Failed to commit patches - wave corrupt!");
            return;
        }
    }

    task.Progress(task_percent(progress++), "Verifying final patches... (nn_olv.rpl)");

    {
        std::ifstream is(pn_olv_path, std::ios::binary);
        auto hash = rpx_hash(is);
        if (hash.id != CURRENT_PRETENDO_NN_OLV) {
            //we've already modified wave, so this is always dangerous
            task.SetError(MENU_DONE_PATCH_FAIL_DANGEROUS, "Failed to commit patches - pn_olv corrupt!");
            return;
        }
    }

    task.Progress(task_percent(progress++), "Verifying final patches... (NSSL cert)");

    {
        std::ifstream is(cert_path, std::ios::binary);
        auto hash = cert_hash(is);
        if (hash.id != CURRENT_PRETENDO_CERT) {
            //we've already modified wave, so this is always dangerous
            printf("Failed to commit patches - nssl cert corrupt!\n");
            //oh shit, this could brick - restore backup
            bret = fast_copy_file(cert_bak_path, cert_path);
            if (!bret) {
                task.SetError(MENU_DONE_PATCH_FAIL_CERT_BRICK, "Reverting nssl patches failed!");
                return;
            }

            std::ifstream is2(cert_path, std::ios::binary);
            auto hash2 = cert_hash(is2);
            if (hash2.patch != CERT_PATCH_STATE_STOCK) {
                task.SetError(MENU_DONE_PATCH_FAIL_CERT_BRICK, "Reverting nssl patches failed!");
                return;
            } else if (hash2.id != CURRENT_SACRIFICIAL_CERT) {
                task.SetError(MENU_DONE_PATCH_FAIL_DANGEROUS, "Reverting NSSL cert resulted in the wrong cert?");
                return;
            }

            task.SetError(MENU_DONE_PATCH_FAIL_DANGEROUS, "NSSL cert copy failed, applet modified");
            return;
        }
    }

    task.Done();

    //todo: flush volume on supported CFWs
}
