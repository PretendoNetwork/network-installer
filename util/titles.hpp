#pragma once

#include <filesystem>

#include <coreinit/mcp.h>

std::filesystem::path GetTitlePath(int mcp_handle, MCPAppType app);
