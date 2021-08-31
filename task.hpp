#pragma once

#include <mutex>
#include <condition_variable>
#include <string>
#include <tuple>
#include <optional>
#include "menu/menu_done.hpp"
#include "rpx_patches/rpx_backup_strategy.hpp"

//todo: atomics? on a std::string?

enum ConfirmationMenu {
    CONFIRMATION_MENU_MIIVERSE,
};

class Task {
public:
    struct State {
        int percent = 0;
        MenuDoneError error = MENU_DONE_NO_ERROR;
        bool done = false;

        std::optional<ConfirmationMenu> confirmation_menu = std::nullopt;
        std::optional<bool> confirmation_result = std::nullopt;

        std::string message;

        BackupState miiverse_backup_state; //bad
    };

    bool DoConfirmationMenu(ConfirmationMenu menu_type, BackupState mv_backup_state /*bad*/) {
        std::unique_lock<std::mutex> lock(task_mtx);
        this->task_st.confirmation_result = std::nullopt;
        this->task_st.confirmation_menu = menu_type;

        this->task_st.miiverse_backup_state = mv_backup_state;

        confirmation_cond.wait(lock, [&]{ return task_st.confirmation_result.has_value(); });
        return *this->task_st.confirmation_result;
    }
    void ConfirmationMenuDone(bool result) {
        {
            const std::lock_guard<std::mutex> lock(task_mtx);
            this->task_st.confirmation_result = result;
            this->task_st.confirmation_menu = std::nullopt;
        }
        confirmation_cond.notify_one();
    }

    void Progress(int percent, const std::string& message) {
        const std::lock_guard<std::mutex> lock(task_mtx);
        this->task_st.percent = percent;
        this->task_st.message = message;
    }
    void SetError(MenuDoneError error, const std::string& message) {
        const std::lock_guard<std::mutex> lock(task_mtx);
        this->task_st.error = error;
        this->task_st.message = message;
    }
    void Done() {
        const std::lock_guard<std::mutex> lock(task_mtx);
        this->task_st.done = true;
    }

    State GetState() {
        const std::lock_guard<std::mutex> lock(task_mtx);
        return task_st;
    }

private:
    std::condition_variable confirmation_cond;
    State task_st;
    std::mutex task_mtx;
};
