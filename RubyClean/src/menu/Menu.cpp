#include "Menu.h"

#include <iostream>

int Menu::show()
{
    int choice;

    std::cout
        << "\n=================================\n"
        << "           RubyClean\n"
        << "=================================\n\n"
        << "1. Project Scan\n"
        << "2. Project Clean\n"
        << "3. Largest Junk\n"
        << "4. Statistics\n"
        << "5. System Clean\n"
        << "6. Exit\n\n"
        << "Choice: ";

    std::cin >> choice;

    return choice;
}