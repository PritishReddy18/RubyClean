#include <iostream>
#include <iomanip>
#include <algorithm>
#include <filesystem>
#include <fstream>

#include "cli/CommandParser.h"
#include "scanner/Scanner.h"

namespace fs = std::filesystem;

std::string formatSize(uintmax_t bytes)
{
    double size = bytes;

    if (size >= 1024.0 * 1024.0 * 1024.0)
        return std::to_string(size / 1024.0 / 1024.0 / 1024.0) + " GB";

    if (size >= 1024.0 * 1024.0)
        return std::to_string(size / 1024.0 / 1024.0) + " MB";

    if (size >= 1024.0)
        return std::to_string(size / 1024.0) + " KB";

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
            << "RubyClean scan . export\n"
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

    uintmax_t totalSize = 0;

    int totalFiles = 0;
    int totalFolders = 0;

    std::ofstream report;

    if (cmd.exportReport)
    {
        report.open("report.txt");
    }

    std::cout
        << "\n=========================================\n"
        << "           RubyClean Report\n"
        << "=========================================\n\n";

    std::cout
        << std::left
        << std::setw(10)
        << "Type"
        << std::setw(45)
        << "Path"
        << "Size\n";

    std::cout
        << "---------------------------------------------------------------------\n";

    if (cmd.exportReport)
    {
        report
            << "RubyClean Report\n\n";
    }

    for (const auto& item : junk)
    {
        std::string type =
            item.isFile ? "FILE" : "FOLDER";

        std::cout
            << std::left
            << std::setw(10)
            << type
            << std::setw(45)
            << item.path
            << formatSize(item.size)
            << "\n";

        if (cmd.exportReport)
        {
            report
                << type
                << " | "
                << item.path
                << " | "
                << formatSize(item.size)
                << "\n";
        }

        totalSize += item.size;

        if (item.isFile)
            totalFiles++;
        else
            totalFolders++;
    }

    int totalItems =
        totalFiles + totalFolders;

    std::cout
        << "\n---------------------------------------------------------------------\n";

    std::cout
        << "Folders : "
        << totalFolders
        << "\n";

    std::cout
        << "Files   : "
        << totalFiles
        << "\n";

    std::cout
        << "Items   : "
        << totalItems
        << "\n";

    std::cout
        << "Recover : "
        << formatSize(totalSize)
        << "\n";

    if (cmd.exportReport)
    {
        report
            << "\nFolders : "
            << totalFolders
            << "\n";

        report
            << "Files   : "
            << totalFiles
            << "\n";

        report
            << "Items   : "
            << totalItems
            << "\n";

        report
            << "Recover : "
            << formatSize(totalSize)
            << "\n";

        report.close();

        std::cout
            << "\nReport exported to report.txt\n";
    }

    if (cmd.action == "clean")
    {
        std::cout
            << "\nDelete all detected junk? (y/n): ";

        char choice;
        std::cin >> choice;

        if (choice == 'y' ||
            choice == 'Y')
        {
            for (const auto& item : junk)
            {
                try
                {
                    if (item.isFile)
                    {
                        fs::remove(item.path);
                    }
                    else
                    {
                        fs::remove_all(item.path);
                    }
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