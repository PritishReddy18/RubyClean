#include "SystemCleaner.h"

#include <filesystem>
#include <cstdlib>
#include <iostream>

namespace fs = std::filesystem;

std::vector<SystemJunkItem>
SystemCleaner::getTargets()
{
    std::vector<SystemJunkItem> targets;

    const char* temp =
        std::getenv("TEMP");

    if(temp)
    {
        targets.push_back({
            "User Temp",
            temp,
            0
        });
    }

    targets.push_back({
        "Windows Temp",
        "C:\\Windows\\Temp",
        0
    });

    const char* local =
        std::getenv("LOCALAPPDATA");

    if(local)
    {
        std::string localPath =
            local;

        targets.push_back({
            "Crash Dumps",
            localPath + "\\CrashDumps",
            0
        });

        targets.push_back({
            "Internet Cache",
            localPath +
            "\\Microsoft\\Windows\\INetCache",
            0
        });

        targets.push_back({
            "Thumbnail Cache",
            localPath +
            "\\Microsoft\\Windows\\Explorer",
            0
        });

        targets.push_back({
            "DirectX Shader Cache",
            localPath + "\\D3DSCache",
            0
        });

        targets.push_back({
            "Windows Error Reports",
            localPath +
            "\\Microsoft\\Windows\\WER",
            0
        });
    }

    const char* appData =
    std::getenv("APPDATA");

    if(appData)
    {
        targets.push_back({
            "Recent Files",
            std::string(appData) +
            "\\Microsoft\\Windows\\Recent",
            0
        });
    }

    targets.push_back({
        "Windows Update Cache",
        "C:\\Windows\\SoftwareDistribution\\Download",
        0
    });

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
    auto items =
        getTargets();

    for(auto& item : items)
    {
        try
        {
            if(fs::exists(item.path))
            {
                item.size =
                    calculateFolderSize(
                        item.path);
            }
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
        std::cout
            << "Cleaning "
            << item.name
            << "...\n";

        try
        {
            if(!fs::exists(item.path))
                continue;

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