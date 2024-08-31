#include <iostream>
#include <string>
#include <filesystem>

#include "screenUtil.h"
#include "shop.h"

using namespace std;

void exit()
{
    ScreenClear();
    cout << endl
         << endl;
    textInBox("Thanks For Shopping!", 2);
    cout << endl
         << endl;

    ScreenWaitSec(1);
}

int main()
{
    // if db folder doesn't exists, create one:
    if (!std::filesystem::exists("db"))
    {
        std::filesystem::create_directory("db");
    }

    Shop s;

    while (1)
    {
        ScreenClear();

        char choice;
        textInBox("Main Menu", 3);
        cout << R"(
            Welcome To Shop Management System
            **************************************

                      1. Admin Access.
                      2. Shop.
                      3. Exit.

        )";
        cout << "\t      ";
        textBgWhite(">>>>>", false);
        cout << " ";
        cin >> choice;

        switch (choice)
        {
        case '1':
            s.adminDashboard();
            break;
        case '2':
            s.store();
            break;
        case '3':
            exit();
            return 0;
        default:
            textRed("Please Enter A Valid Choice!");
            ScreenWaitMilliSec(500);
            break;
        }
    }
}