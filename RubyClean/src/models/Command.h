#pragma once

#include <string>

struct Command
{
    std::string action;
    std::string path;

    bool exportReport = false;
};