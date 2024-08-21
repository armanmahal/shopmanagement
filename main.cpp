#include <iostream>
#include <string>
#include <filesystem>

#include "screenUtil.h"
#include "auth.h"
#include "inventory.h"
#include "cart.h"

using namespace std;

void adminDashboard()
{
    ScreenClear();

    // AUTHENTICATING ADMIN
    Admin admin;
    bool auth = admin.authenticate();
    if (!auth)
        return;

    // INITIALISING INVENTORY:
    Inventory i;
    i.initialize();

    Bills b;

    while (true)
    {
        ScreenClear();

        textInBox("Admin Dashboard", 3);

        char choice;
        cout << R"(
                      1. View Stock
                      2. Add New Item to Store
                      3. Add Stock to Existing Item
                      4. Update Price of an Existing Item
                      5. Delete Item from Store
                      6. View Billing History
                      7. Admin Details
                      8. Go to Main Menu
                
        )";
        cout << "\t      ";
        textBgWhite(">>>>>", false);
        cout << " ";
        cin >> choice;

        switch (choice)
        {
        case '1':
            i.display();
            break;
        case '2':
            i.addItem();
            break;
        case '3':
            i.addToExisting();
            break;
        case '4':
            i.updatePrice();
            break;
        case '5':
            i.removeItem();
            break;
        case '6':
            b.displayAllBills();
            break;
        case '7':
            admin.displayDetails();
            return;
        case '8':
            return;
        default:
            textRed("Please Enter A Valid Choice!");
            ScreenWaitMilliSec(500);
            break;
        }
    }
}

void shop()
{
    Cart cart;

    Inventory inventory;
    inventory.initialize();

    while (true)
    {
        ScreenClear();

        textInBox("Shop", 4);

        char choice;
        cout << R"(
                      1. View Available Items
                      2. View Cart
                      3. Add item to Cart
                      4. Delete item from Cart
                      5. Proceed to billing
                      6. Go to Main Menu
                
        )";
        cout << "\t      ";
        textBgWhite(">>>>>", false);
        cout << " ";
        cin >> choice;

        switch (choice)
        {
        case '1':
            inventory.display();
            break;
        case '2':
            cart.display();
            break;
        case '3':
            cart.addItem(inventory);
            break;
        case '4':
            cart.deleteItem();
            break;
        case '5':
            cart.createBill(inventory);
            return;
        case '6':
            return;
        default:
            textRed("Please Enter A Valid Choice!");
            ScreenWaitMilliSec(500);
            break;
        }
    }
}

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

    while (1)
    {
        ScreenClear();

        char choice;
        textInBox("Main Menu", 3);
        cout << R"(
            Welcome To Super Market Billing System
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
            adminDashboard();
            break;
        case '2':
            shop();
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