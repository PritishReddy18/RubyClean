#pragma once

#include "../models/JunkItem.h"

#include <vector>
#include <string>

class Scanner
{
public:
    std::vector<JunkItem> scan(const std::string& rootPath);

private:
    bool isJunkDirectory(const std::string& folderName);
    bool isJunkFile(const std::string& fileName);

    uintmax_t calculateFolderSize(
        const std::string& path);
};