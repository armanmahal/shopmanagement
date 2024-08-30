#include <iostream>
#include <string>
#include <filesystem>

#include "screenUtil.h"
#include "admin.h"
#include "inventory.h"
#include "cart.h"
// #include "errorHandling.h"

using namespace std;

void adminDashboard()
{
    ScreenClear();

    // AUTHENTICATING ADMIN
    Admin admin;
    try
    {
        admin.authenticate();
        ScreenClear();
        cout << endl;
        textGreen("Success!");
        textAnimate("Loading...", 60);
    }
    catch (customError e)
    {
        e.what();
        return;
    }

    // INITIALISING INVENTORY FROM DATABASE:
    Inventory i;
    InventoryFileHandling inventoryFile("db/inventory.txt");
    inventoryFile.loadInventory(i);
    textGreen("Inventory database Loaded!");
    ScreenWaitMilliSec(500);

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

        // variables to store any user input:
        string name;
        int quantity, price;

        switch (choice)
        {

        case '1':
            try
            {
                i.display();
                textBlink("Type 0 to Dismiss -> ", false);
                string s;
                cin >> s;
            }
            catch (customError e)
            {
                e.what();
            }
            break;

        case '2':
            // getting details of the items to add:
            cout << "Name: ";
            cin >> name;
            cout << "Price: $";
            cin >> price;
            cout << "Quantity: ";
            cin >> quantity;
            try
            {
                i.addItem(name, quantity, price);
                textGreen("Item SuccessFully Added.");
                ScreenWaitMilliSec(700);
            }
            catch (customError e)
            {
                e.what();
            }

            break;

        case '3':
            cout << "Enter the Name of Item: ";
            cin >> name;
            cout << "Enter the Quantity to Add: ";
            cin >> quantity;
            try
            {
                i.addToExisting(name, quantity);
                textGreen("Item Successfully Updated!");
                ScreenWaitMilliSec(700);
            }
            catch (customError e)
            {
                e.what();
            }

            break;

        case '4':
            cout << "Enter the Name of Item: ";
            cin >> name;
            cout << "Enter the New Price: ";
            cin >> price;
            try
            {
                i.updatePrice(name, price);
                textGreen("Price Successfully Updated!");
                ScreenWaitMilliSec(700);
            }
            catch (customError e)
            {
                e.what();
            }

            break;

        case '5':
            cout << "Enter the Name of Item to Delete: ";
            cin >> name;
            try
            {
                i.removeItem(name);
                textGreen("Item Successfully Deleted!");
                ScreenWaitMilliSec(700);
            }
            catch (customError e)
            {
                e.what();
            }

            break;

        case '6':
            try
            {
                b.displayAllBills();
            }
            catch (customError e)
            {
                e.what();
            }

            break;

        case '7':
            try
            {
                admin.displayDetails();

                string temp;
                cout << endl
                     << "Type 0 to return: ";
                cin >> temp;
            }
            catch (customError e)
            {
                e.what();
            }
            
            break;

        case '8':
            // Save the updated inventory back to the file
            try
            {
                inventoryFile.saveInventory(i);
            }
            catch (customError e)
            {
                e.what();
            }

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

    // INITALISING AN INVENTORY OBJECT WITH ITEMS FROM DATABASE:
    Inventory i;
    InventoryFileHandling inventoryFile("db/inventory.txt");
    inventoryFile.loadInventory(i);
    textGreen("Inventory database Loaded!");
    ScreenWaitMilliSec(500);

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
            i.display();
            break;
        case '2':
            cart.display();
            break;
        case '3':
            cart.addItem(i);
            break;
        case '4':
            cart.deleteItem();
            break;
        case '5':
            cart.createBill(i);
            // Save the updated inventory back to the file
            inventoryFile.saveInventory(i);
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