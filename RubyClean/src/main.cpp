#include <iostream>
#include <iomanip>
#include <algorithm>
#include <filesystem>

#include "cli/CommandParser.h"
#include "scanner/Scanner.h"

namespace fs = std::filesystem;

std::string formatSize(uintmax_t bytes)
{
    double size = bytes;

    if (size >= 1024.0 * 1024.0 * 1024.0)
    {
        return std::to_string(size / 1024.0 / 1024.0 / 1024.0)
               + " GB";
    }

    if (size >= 1024.0 * 1024.0)
    {
        return std::to_string(size / 1024.0 / 1024.0)
               + " MB";
    }

    if (size >= 1024.0)
    {
        return std::to_string(size / 1024.0)
               + " KB";
    }

    return std::to_string(bytes) + " B";
}

int main(int argc, char* argv[])
{
    CommandParser parser;

    Command cmd =
        parser.parse(argc, argv);

    if (cmd.action != "scan" &&
        cmd.action != "clean")
    {
        std::cout
            << "\nRubyClean\n\n"
            << "Usage:\n"
            << "RubyClean scan .\n"
            << "RubyClean clean .\n";

        return 0;
    }

    Scanner scanner;

    auto junk =
        scanner.scan(cmd.path);

    std::sort(
        junk.begin(),
        junk.end(),
        [](const JunkItem& a,
           const JunkItem& b)
        {
            return a.size > b.size;
        });

    uintmax_t total = 0;

    std::cout
        << "\n=====================================\n"
        << "        RubyClean Report\n"
        << "=====================================\n\n";

    std::cout
        << std::left
        << std::setw(40)
        << "Path"
        << "Size\n";

    std::cout
        << "----------------------------------------------------------\n";

    for (const auto& item : junk)
    {
        std::cout
            << std::left
            << std::setw(40)
            << item.path
            << formatSize(item.size)
            << "\n";

        total += item.size;
    }

    std::cout
        << "----------------------------------------------------------\n";

    std::cout
        << "Total Recoverable: "
        << formatSize(total)
        << "\n";

    if (cmd.action == "clean")
    {
        std::cout
            << "\nDelete all junk folders? (y/n): ";

        char choice;
        std::cin >> choice;

        if (choice == 'y' ||
            choice == 'Y')
        {
            for (const auto& item : junk)
            {
                try
                {
                    fs::remove_all(item.path);
                }
                catch (...)
                {
                }
            }

            std::cout
                << "\nCleanup completed.\n";
        }
    }

    return 0;
}