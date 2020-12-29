#include "util/titles.hpp"
#include "util/iosu_fs.hpp"

std::filesystem::path GetTitlePath(int mcp_handle, MCPAppType app) {
    MCPTitleListType title;
    uint32_t title_count;

    int ret = MCP_TitleListByAppType(mcp_handle, app, &title_count, &title, sizeof(title));
    if (ret != 0 || title_count != 1) {
        return std::filesystem::path();
    }

    return std::filesystem::path(std::string(IOSU_FS_DEVICE ":") + title.path);
}
