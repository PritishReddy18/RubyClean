#include "Scanner.h"

#include <filesystem>

namespace fs = std::filesystem;

bool Scanner::isJunkDirectory(const std::string& folderName)
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
            if (!entry.is_directory())
                continue;

            std::string folderName =
                entry.path().filename().string();

            if (isJunkDirectory(folderName))
            {
                JunkItem item;

                item.path =
                    entry.path().string();

                item.size =
                    calculateFolderSize(item.path);

                junkItems.push_back(item);
            }
        }
    }
    catch (...)
    {
    }

    return junkItems;
}