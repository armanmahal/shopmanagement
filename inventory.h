#include <iostream>
#include <fstream>
#include <string>
#include <unordered_map>
#include <iomanip>

using namespace std;

class Inventory
{
private:
    unordered_map<string, pair<int, int>> items; // name , (quantity,price)

    // function to check if a file exists or not:
    bool fileExists(string fileName)
    {
        ifstream file(fileName);
        return file.good(); // Checks if the file stream is in a good state (i.e., file exists)
    }

    // location of file:
    string fileLocation = "db/inventory.txt";

public:
    Inventory() {}

    // LOADING DATA FROM INVENTORY->DB TO UNORDERED_MAP->ITEMS
    bool initialize()
    {
        // IF FILE NOT FOUND , create it
        if (!fileExists(fileLocation))
        {
            ofstream file(fileLocation);
            file << "itemname:itemquantity:itemprice:";
            file.close();
        }

        // OPENING FILE in read mode:
        ifstream inventoryData(fileLocation);

        // SETTING THE INVENTORY FROM DATA INTO THE UNORDERED_MAP:
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

            // breaking each line of items into its three components:
            // name,quantity,price
            // and inserting them to a pair p
            pair<string, pair<int, int>> p;

            string temp = "";
            int count = 0;

            for (auto i : s)
            {
                if (i == ':')
                {
                    count++;
                    if (count == 1)
                    {
                        p.first = temp;
                    }
                    else if (count == 2)
                    {
                        int toNumber = stoi(temp);
                        p.second.first = toNumber;
                    }
                    else
                    {
                        int toNumber = stoi(temp);
                        p.second.second = toNumber;
                    }
                    temp = "";
                    continue;
                }
                temp = temp + i;
            }

            // inserting the currently created pair of items into the inventory's map:
            items.insert(p);
        }
        inventoryData.close();
        textGreen("Inventory database Loaded!");
        ScreenWaitMilliSec(500);

        return true;
    }

    // DISPLAYING DATA IN TABULAR FORM.
    void display()
    {
        // if empty:
        if (items.empty())
        {
            textRed("No Items In Inventory.");
            ScreenWaitMilliSec(1000);
            return;
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
        textBlink("Type 0 to Dismiss -> ", false);
        string s;
        cin >> s;
    }

    // ADDING A NEW ITEM TO INVENTORY:
    void addItem()
    {
        // getting details of the items to add:
        string name, quantity, price;

        cout << "Name: ";
        cin >> name;
        cout << "Price: $";
        cin >> price;
        cout << "Quantity: ";
        cin >> quantity;

        // Opening file i.e. inventory database:
        ofstream inventoryData(fileLocation, ios::app); // ios::app -> for appending

        // inserting to inventory database:
        string lineToInsert = '\n' + name + ':' + quantity + ':' + price + ':';
        inventoryData << lineToInsert;

        // inserting to unordered_map->items:
        items[name] = make_pair(stoi(quantity), stoi(price));

        textGreen("Item SuccessFully Added.");
        ScreenWaitMilliSec(700);
    }

    // ADDING STOCK TO EXISTING ITEM:
    void addToExisting()
    {
        string name;
        int quantity;

        cout << "Enter the Name of Item: ";
        cin >> name;
        cout << "Enter the Quantity to Add: ";
        cin >> quantity;

        // if item doesnt exists:
        if (items.find(name) == items.end())
        {
            textRed("No Such Items Found!");
            ScreenWaitMilliSec(800);
            return;
        }

        // updating in the unordered_map of items:
        items[name].first += quantity;

        // updating in the inventory Database:
        // overwriting the existing inventory...

        ofstream inventoryData(fileLocation, ios::out); // opening in write, if already exists it will overwrite.
        inventoryData << "itemname:itemquantity:itemprice:";
        for (auto i : items)
        {
            string lineToInsert = '\n' + i.first + ':' + to_string(i.second.first) + ':' + to_string(i.second.second) + ':';
            inventoryData << lineToInsert;
        }

        // printing success message:
        textGreen("Item Successfully Updated!");
        ScreenWaitMilliSec(700);
    }

    // UPDATE PRICE OF AN EXISTING ITEM:
    void updatePrice()
    {
        string name;
        int newPrice;

        cout << "Enter the Name of Item: ";
        cin >> name;
        cout << "Enter the New Price: ";
        cin >> newPrice;

        // if item doesnt exists:
        if (items.find(name) == items.end())
        {
            textRed("No Such Items Found!");
            ScreenWaitMilliSec(800);
            return;
        }

        // updating in the unordered_map of items:
        items[name].second = newPrice;

        // updating in the inventory Database:
        // overwriting the existing inventory...

        ofstream inventoryData(fileLocation, ios::out); // opening in write, if already exists it will overwrite.
        inventoryData << "itemname:itemquantity:itemprice:";
        for (auto i : items)
        {
            string lineToInsert = '\n' + i.first + ':' + to_string(i.second.first) + ':' + to_string(i.second.second) + ':';
            inventoryData << lineToInsert;
        }

        // printing success message:
        textGreen("Price Successfully Updated!");
        ScreenWaitMilliSec(700);
    }

    // REMOVING AN ITEM:
    void removeItem()
    {
        string name;

        cout << "Enter the Name of Item to Delete: ";
        cin >> name;

        // if item doesnt exists:
        if (items.find(name) == items.end())
        {
            textRed("No Such Items Found!");
            ScreenWaitMilliSec(800);
            return;
        }

        // deleting in the unordered_map of items:
        items.erase(name);

        // delelting in the inventory Database:
        // overwriting the existing inventory...

        ofstream inventoryData(fileLocation, ios::out); // opening in write, if already exists it will overwrite.
        inventoryData << "itemname:itemquantity:itemprice:";
        for (auto i : items)
        {
            string lineToInsert = '\n' + i.first + ':' + to_string(i.second.first) + ':' + to_string(i.second.second) + ':';
            inventoryData << lineToInsert;
        }

        // printing success message:
        textGreen("Item Successfully Deleted!");
        ScreenWaitMilliSec(700);
    }

    // GETTING VALUE OF AN ITEM
    int getPrice(string s)
    {
        return items[s].second;
    }

    // GETTING QUANTITY OF AN ITEM
    int getQuantity(string s)
    {
        return items[s].first;
    }

    // CHECKING IF ITEM EXITST:
    bool checkIfExists(string s)
    {
        if (items.find(s) == items.end())
        {
            return false;
        }
        return true;
    }

    // DECREASE QUANTITY AFTER BILLING:
    void decreaseQuantity(string s, int x)
    {
        // updating in unordered_map:
        items[s].first -= x;

        // updating in db
        ofstream inventoryData(fileLocation, ios::out); // opening in write, if already exists it will overwrite.
        inventoryData << "itemname:itemquantity:itemprice:";
        for (auto i : items)
        {
            string lineToInsert = '\n' + i.first + ':' + to_string(i.second.first) + ':' + to_string(i.second.second) + ':';
            inventoryData << lineToInsert;
        }
    }
};