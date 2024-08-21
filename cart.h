#include <iostream>
#include <unordered_map>
#include <iomanip>
#include "bill.h"

using namespace std;

class Cart
{
private:
    unordered_map<string, pair<int, int>> items; // name , (quantity, Totalprice)

public:
    void display()
    {
        // if empty:
        if (items.empty())
        {
            textRed("No Items In Cart.");
            ScreenWaitMilliSec(1000);
            return;
        }

        cout << endl;
        cout << left; // text align left
        cout << setw(20) << "Item" << setw(10) << "Quantity" << setw(10) << "Total" << endl;
        for (auto i : items)
        {
            cout << setw(20) << setfill('_') << i.first << setw(10) << i.second.first << '$' << setw(10) << setfill(' ') << i.second.second << endl;
        }
        cout << right; // reset text align
        cout << endl;
        textBlink("Type 0 to Dismiss -> ", false);
        string s;
        cin >> s;
    }

    void addItem(Inventory i)
    {
        string name;
        int quantity;

        cout << "Item to Buy: ";
        cin >> name;
        cout << "Quantity: ";
        cin >> quantity;

        // if item doesnt exists:
        if (!i.checkIfExists(name))
        {
            textRed("No such Item Exists.");
            ScreenWaitMilliSec(800);
            return;
        }

        // if out of stock :
        if (i.getQuantity(name) == 0)
        {
            textRed("Out of Stock!");
            ScreenWaitMilliSec(800);
            return;
        }

        // if quantity exceeds availability:
        if (i.getQuantity(name) < quantity)
        {
            textRed("Select a lower Quantity!");
            ScreenWaitMilliSec(800);
            return;
        }

        // if item already exits in cart
        if (items.find(name) != items.end())
        {
            items[name].first += quantity;
            items[name].second += quantity * i.getPrice(name);
            return;
        }

        // adding it to cart:
        items[name] = make_pair(quantity, quantity * i.getPrice(name));

        textGreen("Item Added to Cart.");
        ScreenWaitMilliSec(500);
    }

    void deleteItem()
    {
        string name;

        cout << "Item to Delete from Cart: ";
        cin >> name;

        // if not exists:
        if (items.find(name) == items.end())
        {
            textRed("No Such Item Exists in Cart.");
            ScreenWaitMilliSec(800);
        }

        // if exists:
        items.erase(name);
        textGreen("Item Removed from Cart.");
        ScreenWaitMilliSec(500);
    }

    void createBill(Inventory inventory)
    {
        // if cart empty:
        if (items.empty())
        {
            textRed("Cart is Empty");
            ScreenWaitMilliSec(800);
        }

        ScreenClear();

        // printing cart:
        textInBox("Cart", 3);
        cout << endl;
        cout << left; // text align left
        cout << setw(20) << "Item" << setw(10) << "Quantity" << setw(10) << "Total" << endl;
        for (auto i : items)
        {
            cout << setw(20) << setfill('_') << i.first << setw(10) << i.second.first << '$' << setw(10) << setfill(' ') << i.second.second << endl;
        }
        cout << right; // reset text align
        cout << endl;


        // calculating total
        int total = 0;
        for (auto i : items)
        {
            total += i.second.second;
        }

        cout << endl;
        textBold("Total Value of Bill is ---> ", false);
        cout << '$' << total << endl;


        // getting buyer details:
        cout << "GIVE YOUR DETAILS:" << endl;
        string name;
        cout << "Name: ";
        cin >> name;
        string phone;
        cout << "Phone: ";
        cin >> phone;


        // updating inventory after billing:
        for (auto i : items)
        {
            inventory.decreaseQuantity(i.first, i.second.first);
        }


        // creating the bill and adding to db:
        Bills b1(total, name, phone);
        b1.addBillToDb();


        cout << endl;
        textGreen("Purchase Successful!");
        cout << endl;
        textInBox("Thanks for shopping " + name, 2);
        textBlink("Redirecting to Home page...");
        ScreenWaitMilliSec(2000);
    }
};