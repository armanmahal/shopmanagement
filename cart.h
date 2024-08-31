#include <iostream>
#include <unordered_map>
#include <iomanip>
#include "bills.h"

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
            customError e("No Items In Cart.");
            throw e;
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
    }

    void addItem(Inventory i, string name, int quantity)
    {
        // if item doesnt exists:
        if (!i.checkIfExists(name))
        {
            customError e("No such Item Exists.");
            throw e;
        }

        // if out of stock :
        if (i.getQuantity(name) == 0)
        {
            customError e("Out of Stock!");
            throw e;
        }

        // if quantity exceeds availability:
        if (i.getQuantity(name) < quantity)
        {
            customError e("Select a lower Quantity!");
            throw e;
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
    }

    void deleteItem(string name)
    {
        // if not exists:
        if (items.find(name) == items.end())
        {
            customError e("No Such Item Exists in Cart.");
            throw e;
        }

        // if exists:
        items.erase(name);
    }

    void createBill(Inventory &inventory)
    {
        // if cart empty:
        if (items.empty())
        {
            customError e("Cart is Empty");
            throw e;
        }

        // displaying the cart:
        display();

        // calculating total
        int total = 0;
        for (auto i : items)
        {
            total += i.second.second;
        }

        cout << endl;
        cout << "Total Value of Bill is ---> $" << total << endl
             << endl;

        // getting buyer details:
        cout << "GIVE YOUR DETAILS:" << endl;
        string name;
        cout << "Name: ";
        cin >> name;
        string phone;
        cout << "Phone: ";
        cin >> phone;

        try
        {
            // creating the bill and adding to db:
            Bill b(total, name, phone);
            BillsFileHandling billFile("db/bills.txt");
            billFile.saveBill(b);
        }
        catch (customError e)
        {
            throw e;
        }

        // updating inventory after billing:
        for (auto i : items)
        {
            inventory.decreaseQuantity(i.first, i.second.first);
        }
    }
};