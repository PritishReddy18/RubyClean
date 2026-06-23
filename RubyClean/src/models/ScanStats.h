#pragma once

#include <string>
#include <cstdint>

struct ScanStats
{
    int foldersScanned = 0;
    int filesScanned = 0;

    int junkFolders = 0;
    int junkFiles = 0;

    std::string largestFolder;
    uintmax_t largestFolderSize = 0;

    std::string largestFile;
    uintmax_t largestFileSize = 0;
};