#pragma once

#include <string>
#include <vector>
#include <cstdint>

struct SystemJunkItem
{
    std::string name;
    std::string path;
    uintmax_t size = 0;
};

class SystemCleaner
{
public:
    std::vector<SystemJunkItem> scan();

    uintmax_t getTotalSize(
        const std::vector<SystemJunkItem>& items);

    void clean(
        const std::vector<SystemJunkItem>& items);

private:
    std::vector<SystemJunkItem> getTargets();

    uintmax_t calculateFolderSize(
        const std::string& path);
};