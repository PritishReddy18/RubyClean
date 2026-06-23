#include "MenuRunner.h"
#include "Menu.h"

#include "../system/SystemCleaner.h"

#include <iostream>
#include <vector>

#include <sstream>
#include <iomanip>

static std::string formatSize(uintmax_t bytes)
{
    std::stringstream ss;

    double size = static_cast<double>(bytes);

    if(size >= 1024.0 * 1024.0 * 1024.0)
    {
        ss << std::fixed
           << std::setprecision(2)
           << size / 1024.0 / 1024.0 / 1024.0
           << " GB";

        return ss.str();
    }

    if(size >= 1024.0 * 1024.0)
    {
        ss << std::fixed
           << std::setprecision(2)
           << size / 1024.0 / 1024.0
           << " MB";

        return ss.str();
    }

    if(size >= 1024.0)
    {
        ss << std::fixed
           << std::setprecision(2)
           << size / 1024.0
           << " KB";

        return ss.str();
    }

    return std::to_string(bytes) + " B";
}

void MenuRunner::run()
{
    Menu menu;

    while(true)
    {
        int choice =
            menu.show();

        switch(choice)
        {
            case 1:
            {
                std::string path;

                std::cout
                    << "\nEnter project path: ";

                std::cin >> path;

                std::cout
                    << "\nProject Scan coming in v1.4.1\n";

                break;
            }

            case 2:
            {
                std::string path;

                std::cout
                    << "\nEnter project path: ";

                std::cin >> path;

                std::cout
                    << "\nProject Clean coming in v1.4.1\n";

                break;
            }

            case 3:
            {
                std::string path;

                std::cout
                    << "\nEnter project path: ";

                std::cin >> path;

                std::cout
                    << "\nLargest Junk coming in v1.4.1\n";

                break;
            }

            case 4:
            {
                std::string path;

                std::cout
                    << "\nEnter project path: ";

                std::cin >> path;

                std::cout
                    << "\nStatistics coming in v1.4.1\n";

                break;
            }

            case 5:
            {
                SystemCleaner cleaner;

                auto items =
                    cleaner.scan();

                auto total =
                    cleaner.getTotalSize(items);

                std::cout
                    << "\n==================================================\n"
                    << "                System Junk Report\n"
                    << "==================================================\n\n";

                std::cout
                    << "Name                     Size\n"
                    << "--------------------------------------------------\n";

                for(const auto& item : items)
                {
                    std::cout
                        << item.name;

                    int spaces =
                        25 - static_cast<int>(item.name.length());

                    while(spaces-- > 0)
                        std::cout << ' ';

                    std::cout
                        << formatSize(item.size)
                        << "\n";
                }

                std::cout
                    << "--------------------------------------------------\n"
                    << "Total Recoverable: "
                    << formatSize(total)
                    << "\n\n";

                std::cout
                    << "Locations\n"
                    << "--------------------------------------------------\n";

                for(const auto& item : items)
                {
                    std::cout
                        << item.name
                        << "\n"
                        << item.path
                        << "\n\n";
                }

                char confirm;

                std::cout
                    << "Delete all files? (y/n): ";

                std::cin
                    >> confirm;

                if(confirm == 'y' ||
                confirm == 'Y')
                {
                    cleaner.clean(items);

                    std::cout
                        << "\n==================================================\n"
                        << "Cleanup completed.\n"
                        << "Recovered Space: "
                        << formatSize(total)
                        << "\n"
                        << "Locations Cleaned: "
                        << items.size()
                        << "\n"
                        << "==================================================\n";
                }

                break;
            }

            case 6:
            {
                std::cout
                    << "\n=====================================\n"
                    << "         RubyClean v1.5.0\n"
                    << "=====================================\n\n"
                    << "Open Source C++ Cleanup Utility\n\n"
                    << "Author:\n"
                    << "PritishReddy18\n\n"
                    << "GitHub:\n"
                    << "https://github.com/PritishReddy18/RubyClean\n";

                break;
            }

            case 7:
            {
                return;
            }

            default:
            {
                std::cout
                    << "\nInvalid choice.\n";
            }
        }
    }
}