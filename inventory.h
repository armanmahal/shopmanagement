#include <iostream>
#include <fstream>
#include <string>
#include <unordered_map>
#include <iomanip>

#include "errorHandling.h"

using namespace std;

class Inventory
{
private:
    unordered_map<string, pair<int, int>> items; // name , (quantity,price)

public:
    // TO GET ITEMS OF INVENTORY:
    unordered_map<string, pair<int, int>> getItems()
    {
        return items;
    }

    // DISPLAYING DATA IN TABULAR FORM.
    void display()
    {
        // if empty:
        if (items.empty())
        {
            customError e("No Items In Inventory.");
            throw e;
        }

        cout << endl;
        cout << left; // text align left
        cout << setw(20) << "Item" << setw(10) << "Quantity" << setw(10) << "Price" << endl;
        for (auto i : items)
        {
            cout << setw(20) << setfill('_') << i.first << setw(10) << i.second.first << '$' << setw(10) << setfill(' ') << i.second.second << endl;
        }
        cout << right; // reset text align
        cout << endl;
    }

    // ADDING A NEW ITEM TO INVENTORY:
    void addItem(string name, int quantity, int price)
    {
        // inserting to unordered_map->items:
        items[name] = make_pair(quantity, price);
    }

    // ADDING STOCK TO EXISTING ITEM:
    void addToExisting(string name, int quantity)
    {
        // if item doesnt exists:
        if (items.find(name) == items.end())
        {
            customError e("No Such Items Found!");
            throw e;
        }

        // updating in the unordered_map of items:
        items[name].first += quantity;
    }

    // UPDATE PRICE OF AN EXISTING ITEM:
    void updatePrice(string name, int newPrice)
    {
        // if item doesnt exists:
        if (items.find(name) == items.end())
        {
            customError e("No Such Items Found!");
            throw e;
        }

        // updating in the unordered_map of items:
        items[name].second = newPrice;
    }

    // REMOVING AN ITEM:
    void removeItem(string name)
    {
        // if item doesnt exists:
        if (items.find(name) == items.end())
        {
            customError e("No Such Items Found!");
            throw e;
        }

        // deleting in the unordered_map of items:
        items.erase(name);
    }

    // GETTING VALUE OF AN ITEM
    int getPrice(string name)
    {
        // if item doesnt exists:
        if (items.find(name) == items.end())
        {
            customError e("No Such Items Found!");
            throw e;
        }

        // else return the price of item:
        return items[name].second;
    }

    // GETTING QUANTITY OF AN ITEM
    int getQuantity(string name)
    {
        // if item doesnt exists:
        if (items.find(name) == items.end())
        {
            customError e("No Such Items Found!");
            throw e;
        }

        // else return the quantity of item:
        return items[name].first;
    }

    // CHECKING IF ITEM EXITST:
    bool checkIfExists(string name)
    {
        if (items.find(name) == items.end())
        {
            return false;
        }
        return true;
    }

    // DECREASE QUANTITY AFTER BILLING:
    void decreaseQuantity(string name, int x)
    {
        // if item doesnt exists:
        if (items.find(name) == items.end())
        {
            customError e("No Such Items Found!");
            throw e;
        }

        // updating in unordered_map:
        items[name].first -= x;
    }
};

class InventoryFileHandling
{
private:
    // location of file:
    string fileLocation;

    // function to check if a file exists or not:
    bool fileExists()
    {
        ifstream file(fileLocation);
        return file.good(); // Checks if the file stream is in a good state (i.e., file exists)
    }

public:
    // constructor to initialize the location of database:
    InventoryFileHandling(string s)
    {
        fileLocation = s;
    }

    // function to load the inventory from database:
    void loadInventory(Inventory &inventory)
    {
        // IF FILE NOT FOUND , create it
        if (!fileExists())
        {
            ofstream file(fileLocation);
            file << "itemname:itemquantity:itemprice:";
            file.close();
        }

        // OPENING FILE in read mode:
        ifstream inventoryData(fileLocation);

        // SETTING THE INVENTORY FROM DATABASE TO LOCAL INVENTORY OBJECT:
        int i = 0;
        while (inventoryData.eof() == false)
        {
            // GETTING THE CURRENT LINE:
            string s;
            getline(inventoryData, s);

            // skipping the first line as it contains headings only:
            if (i == 0)
            {
                i++;
                continue;
            }

            string name;
            int quantity, price;

            string temp = "";
            int count = 0;

            for (auto i : s)
            {
                if (i == ':')
                {
                    count++;
                    if (count == 1)
                    {
                        name = temp;
                    }
                    else if (count == 2)
                    {
                        int toNumber = stoi(temp);
                        quantity = toNumber;
                    }
                    else
                    {
                        int toNumber = stoi(temp);
                        price = toNumber;
                    }
                    temp = "";
                    continue;
                }
                temp = temp + i;
            }

            // inserting the currently item to the local inventory object:
            inventory.addItem(name, quantity, price);
        }

        // closing the file:
        inventoryData.close();
    }

    // function to save the inventory to database:
    void saveInventory(Inventory inventory)
    {
        // checking if file exists:
        if (!fileExists())
        {
            customError e("Could not find inventory database file!");
            throw e;
        }

        // Overwrite the file
        ofstream inventoryData(fileLocation, ios::out);

        inventoryData << "itemname:itemquantity:itemprice:";
        for (auto item : inventory.getItems())
        {
            inventoryData << '\n'
                          << item.first << ':' << item.second.first << ':' << item.second.second << ':';
        }
        inventoryData.close();
    }
};