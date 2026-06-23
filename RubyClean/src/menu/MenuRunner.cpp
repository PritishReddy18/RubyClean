#include "MenuRunner.h"
#include "Menu.h"

#include "../system/SystemCleaner.h"

#include <iostream>
#include <vector>

static std::string formatSize(uintmax_t bytes)
{
    double size = bytes;

    if(size >= 1024.0 * 1024.0 * 1024.0)
        return std::to_string(size / 1024.0 / 1024.0 / 1024.0) + " GB";

    if(size >= 1024.0 * 1024.0)
        return std::to_string(size / 1024.0 / 1024.0) + " MB";

    if(size >= 1024.0)
        return std::to_string(size / 1024.0) + " KB";

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
                    << "\nSystem Junk Locations\n\n";

                for(const auto& item : items)
                {
                    std::cout
                        << item.path
                        << "\n";
                }

                    std::cout
                        << "\nRecoverable Space: "
                        << formatSize(total)
                        << "\n";

                char confirm;

                std::cout
                    << "\nDelete all files? (y/n): ";

                std::cin
                    >> confirm;

                if(confirm == 'y' ||
                   confirm == 'Y')
                {
                    cleaner.clean(items);

                    std::cout
                        << "\nCleanup completed.\n";
                }

                break;
            }

            case 6:
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