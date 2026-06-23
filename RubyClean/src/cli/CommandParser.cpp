#include "CommandParser.h"

Command CommandParser::parse(int argc, char* argv[])
{
    Command cmd;

    if(argc >= 2)
        cmd.action = argv[1];

    if(argc >= 3)
        cmd.path = argv[2];

    if(argc >= 4)
    {
        if(std::string(argv[3]) == "export")
            cmd.exportReport = true;
    }

    return cmd;
}