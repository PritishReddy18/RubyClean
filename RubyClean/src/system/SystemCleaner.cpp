#include "SystemCleaner.h"

#include <filesystem>
#include <cstdlib>
#include <iostream>

namespace fs = std::filesystem;

static std::string formatSize(uintmax_t bytes)
{
    double size = bytes;

    if(size >= 1024.0 * 1024.0 * 1024.0)
        return std::to_string(size / 1024.0 / 1024.0 / 1024.0) + " GB";

    if(size >= 1024.0 * 1024.0)
        return std::to_string(size / 1024.0 / 1024.0) + " MB";

    if(size >= 1024.0)
        return std::to_string(size / 1024.0) + " KB";

    return std::to_string(bytes) + " B";
}

std::vector<std::string> SystemCleaner::getTargets()
{
    std::vector<std::string> targets;

    const char* temp =
        std::getenv("TEMP");

    if(temp)
    {
        targets.push_back(temp);
    }

    targets.push_back(
        "C:\\Windows\\Temp");

    return targets;
}

uintmax_t SystemCleaner::calculateFolderSize(
    const std::string& path)
{
    uintmax_t total = 0;

    try
    {
        for(const auto& entry :
            fs::recursive_directory_iterator(path))
        {
            if(entry.is_regular_file())
            {
                total += entry.file_size();
            }
        }
    }
    catch(...)
    {
    }

    return total;
}

std::vector<SystemJunkItem>
SystemCleaner::scan()
{
    std::vector<SystemJunkItem> items;

    auto targets =
        getTargets();

    for(const auto& path : targets)
    {
        try
        {
            if(!fs::exists(path))
                continue;

            SystemJunkItem item;

            item.path = path;

            item.size =
                calculateFolderSize(path);

            items.push_back(item);
        }
        catch(...)
        {
        }
    }

    return items;
}

uintmax_t SystemCleaner::getTotalSize(
    const std::vector<SystemJunkItem>& items)
{
    uintmax_t total = 0;

    for(const auto& item : items)
    {
        total += item.size;
    }

    return total;
}

void SystemCleaner::clean(
    const std::vector<SystemJunkItem>& items)
{
    for(const auto& item : items)
    {
        try
        {
            for(const auto& entry :
                fs::directory_iterator(item.path))
            {
                try
                {
                    if(entry.is_directory())
                    {
                        fs::remove_all(
                            entry.path());
                    }
                    else
                    {
                        fs::remove(
                            entry.path());
                    }
                }
                catch(...)
                {
                }
            }
        }
        catch(...)
        {
        }
    }
}