#include <iostream>
using namespace std;

#include "admin.h"
#include "inventory.h"
#include "cart.h"

class Shop
{
private:
    string inventoryFileLocation = "db/inventory.txt";
    string adminFileLocation = "db/admin.txt";
    string billsFileLocation = "db/bills.txt";

    Inventory inventory;
    Admin admin;
    AllBills bills;
    Cart cart;

    AdminFileHandling adminFile = AdminFileHandling(adminFileLocation);
    /*
        declaration like this:
            AdminFileHandling adminFile(adminFileLocation);
        only works inside a function or method.
    */
    InventoryFileHandling inventoryFile = InventoryFileHandling(inventoryFileLocation);
    BillsFileHandling billFile = BillsFileHandling(billsFileLocation);

public:
    void adminDashboard()
    {
        ScreenClear();

        // AUTHENTICATING ADMIN

        adminFile.loadAdmin(admin);
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

        inventoryFile.loadInventory(inventory);
        textGreen("Inventory database Loaded!");
        ScreenWaitMilliSec(500);

        // LOADING ALL BILLS FROM DATABASE:

        billFile.loadAllBills(bills);

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
                    inventory.display();
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
                    inventory.addItem(name, quantity, price);
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
                    inventory.addToExisting(name, quantity);
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
                    inventory.updatePrice(name, price);
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
                    inventory.removeItem(name);
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
                    bills.displayAllBills();
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
                // Save the updated inventory + admindetails back to the file
                try
                {
                    inventoryFile.saveInventory(inventory);
                    adminFile.saveAdmin(admin);
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
    
    void store()
    {

        // INITALISING AN INVENTORY OBJECT WITH ITEMS FROM DATABASE:

        inventoryFile.loadInventory(inventory);
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

            // variables to store any user input:
            string name;
            int quantity;

            switch (choice)
            {

            case '1':
                try
                {
                    inventory.display();
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
                try
                {
                    cart.display();
                    textBlink("Type 0 to Dismiss -> ", false);
                    string s;
                    cin >> s;
                }
                catch (customError e)
                {
                    e.what();
                }

                break;

            case '3':
                cout << "Item to Buy: ";
                cin >> name;
                cout << "Quantity: ";
                cin >> quantity;
                try
                {
                    cart.addItem(inventory, name, quantity);
                    textGreen("Item Added to Cart.");
                    ScreenWaitMilliSec(500);
                }
                catch (customError e)
                {
                    e.what();
                }

                break;

            case '4':
                cout << "Item to Delete from Cart: ";
                cin >> name;
                try
                {
                    cart.deleteItem(name);
                    textGreen("Item Removed from Cart.");
                    ScreenWaitMilliSec(500);
                }
                catch (customError e)
                {
                    e.what();
                }

                break;

            case '5':
                try
                {
                    cart.createBill(inventory);
                    // Save the updated inventory back to the file
                    inventoryFile.saveInventory(inventory);

                    // clearing cart:
                    cart.clear();

                    cout << endl;
                    textGreen("Purchase Successful!");
                    cout << endl;
                    textInBox("Thanks for shopping " + name, 2);
                    textBlink("Redirecting to Home page...");
                    ScreenWaitMilliSec(2000);
                    return;
                }
                catch (customError e)
                {
                    e.what();
                    break;
                }

            case '6':
                cart.clear();
                return;

            default:
                textRed("Please Enter A Valid Choice!");
                ScreenWaitMilliSec(500);
                break;
            }
        }
    }
};