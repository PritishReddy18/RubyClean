#pragma once

#include "../models/Command.h"

class CommandParser
{
public:
    Command parse(int argc, char* argv[]);
};