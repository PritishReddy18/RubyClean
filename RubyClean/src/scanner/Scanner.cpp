#include "Scanner.h"

#include <filesystem>
#include <algorithm>

namespace fs = std::filesystem;

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

    try
    {
        for (const auto& entry :
             fs::recursive_directory_iterator(rootPath))
        {
            if (entry.is_directory())
            {
                std::string folderName =
                    entry.path().filename().string();

                if (isJunkDirectory(folderName))
                {
                    JunkItem item;

                    item.path =
                        entry.path().string();

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

                    item.path =
                        entry.path().string();

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

    try
    {
        for (const auto& entry :
             fs::directory_iterator(rootPath))
        {
            if (entry.is_directory())
            {
                FolderInfo info;

                info.path =
                    entry.path().string();

                info.size =
                    calculateFolderSize(info.path);

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

    try
    {
        for (const auto& entry :
             fs::recursive_directory_iterator(rootPath))
        {
            if (entry.is_directory())
            {
                stats.foldersScanned++;

                uintmax_t size =
                    calculateFolderSize(
                        entry.path().string());

                if (size >
                    stats.largestFolderSize)
                {
                    stats.largestFolderSize =
                        size;

                    stats.largestFolder =
                        entry.path().string();
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
                        entry.path().string();
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