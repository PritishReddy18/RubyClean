#pragma once

#include <string>
#include <cstdint>

struct JunkItem
{
    std::string path;
    uintmax_t size = 0;
    bool isFile = false;
};