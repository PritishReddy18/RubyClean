#include "Scanner.h"
#include <iostream>
#include <filesystem>
#include <algorithm>
#include <fstream>

namespace fs = std::filesystem;

std::vector<std::string> Scanner::loadIgnoreRules()
{
    std::vector<std::string> rules;

    std::ifstream file(".rubycleanignore");

    if (!file.is_open())
        return rules;

    std::string line;

    while (std::getline(file, line))
    {
        if (!line.empty() && line.back() == '\r')
        {
            line.pop_back();
        }

        if (!line.empty())
        {
            rules.push_back(line);
        }
    }

    return rules;
}

bool Scanner::isIgnored(
    const std::string& path,
    const std::vector<std::string>& ignoreRules)
{
    for (const auto& rule : ignoreRules)
    {
        if (path.find(rule) != std::string::npos)
        {
            return true;
        }
    }

    return false;
}

bool Scanner::isJunkDirectory(
    const std::string& folderName)
{
    return
        folderName == "cmake-build-debug" ||
        folderName == "cmake-build-release" ||
        folderName == "__pycache__" ||
        folderName == "build" ||
        folderName == "node_modules" ||
        folderName == ".next" ||
        folderName == "dist" ||
        folderName == "out" ||
        folderName == "bin" ||
        folderName == "obj";
}

bool Scanner::isJunkFile(
    const std::string& fileName)
{
    fs::path p(fileName);

    std::string ext =
        p.extension().string();

    return
        ext == ".log" ||
        ext == ".tmp" ||
        ext == ".temp";
}

uintmax_t Scanner::calculateFolderSize(
    const std::string& path)
{
    uintmax_t total = 0;

    try
    {
        for (const auto& entry :
             fs::recursive_directory_iterator(path))
        {
            if (entry.is_regular_file())
            {
                total += entry.file_size();
            }
        }
    }
    catch (...)
    {
    }

    return total;
}

std::vector<JunkItem> Scanner::scan(
    const std::string& rootPath)
{
    std::vector<JunkItem> junkItems;

    auto ignoreRules =
        loadIgnoreRules();

    try
    {
        for (const auto& entry :
             fs::recursive_directory_iterator(rootPath))
        {
            std::string fullPath =
                entry.path().string();

            if (isIgnored(fullPath, ignoreRules))
                continue;

            if (entry.is_directory())
            {
                std::string folderName =
                    entry.path().filename().string();

                if (isJunkDirectory(folderName))
                {
                    JunkItem item;

                    item.path = fullPath;

                    item.size =
                        calculateFolderSize(item.path);

                    item.isFile = false;

                    junkItems.push_back(item);
                }
            }
            else if (entry.is_regular_file())
            {
                std::string fileName =
                    entry.path().filename().string();

                if (isJunkFile(fileName))
                {
                    JunkItem item;

                    item.path = fullPath;

                    item.size =
                        entry.file_size();

                    item.isFile = true;

                    junkItems.push_back(item);
                }
            }
        }
    }
    catch (...)
    {
    }

    return junkItems;
}

std::vector<FolderInfo> Scanner::getLargestFolders(
    const std::string& rootPath)
{
    std::vector<FolderInfo> folders;

    auto ignoreRules =
        loadIgnoreRules();

    try
    {
        for (const auto& entry :
             fs::directory_iterator(rootPath))
        {
            std::string fullPath =
                entry.path().string();

            if (isIgnored(fullPath, ignoreRules))
                continue;

            if (entry.is_directory())
            {
                FolderInfo info;

                info.path = fullPath;

                info.size =
                    calculateFolderSize(fullPath);

                folders.push_back(info);
            }
        }
    }
    catch (...)
    {
    }

    std::sort(
        folders.begin(),
        folders.end(),
        [](const FolderInfo& a,
           const FolderInfo& b)
        {
            return a.size > b.size;
        });

    return folders;
}

ScanStats Scanner::getStats(
    const std::string& rootPath)
{
    ScanStats stats;

    auto ignoreRules =
        loadIgnoreRules();

    try
    {
        for (const auto& entry :
             fs::recursive_directory_iterator(rootPath))
        {
            std::string fullPath =
                entry.path().string();

            if (isIgnored(fullPath, ignoreRules))
                continue;

            if (entry.is_directory())
            {
                stats.foldersScanned++;

                uintmax_t size =
                    calculateFolderSize(fullPath);

                if (size >
                    stats.largestFolderSize)
                {
                    stats.largestFolderSize =
                        size;

                    stats.largestFolder =
                        fullPath;
                }

                if (isJunkDirectory(
                    entry.path().filename().string()))
                {
                    stats.junkFolders++;
                }
            }
            else if (entry.is_regular_file())
            {
                stats.filesScanned++;

                uintmax_t size =
                    entry.file_size();

                if (size >
                    stats.largestFileSize)
                {
                    stats.largestFileSize =
                        size;

                    stats.largestFile =
                        fullPath;
                }

                if (isJunkFile(
                    entry.path().filename().string()))
                {
                    stats.junkFiles++;
                }
            }
        }
    }
    catch (...)
    {
    }

    return stats;
}