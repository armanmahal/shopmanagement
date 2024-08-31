#include <iostream>
#include <fstream>
#include <iomanip>
using namespace std;

class Bill
{
private:
    int amount;
    string buyer;
    string contact;

public:
    // default constructor:
    Bill() {}

    // constructor:
    Bill(int amount, string buyer, string contact)
    {
        this->amount = amount;
        this->buyer = buyer;
        this->contact = contact;
    }

    friend class BillsFileHandling;
};

class AllBills
{
private:
    vector<vector<string>> bills;

public:
    // displaying all bills :
    void displayAllBills()
    {
        // if no bill found:
        if (bills.empty())
        {
            customError e("No Bills Found!");
            throw e;
        }

        cout << endl;
        cout << left; // text align left
        cout << setw(20) << "Buyer" << setw(10) << "Amount" << setw(10) << "Contact" << endl;

        for (auto bill : bills)
        {
            cout << left;
            cout
                << setw(20) << setfill('_') << bill[0] << setw(10) << '$' + bill[1] << setw(10) << setfill(' ') << bill[2] << endl;
        }

        cout << right; // reset text align
        cout << endl;
        textBlink("Type 0 to Dismiss -> ", false);
        string s;
        cin >> s;
    }

    friend class BillsFileHandling;
};

class BillsFileHandling
{
private:
    string fileLocation;

    // function to check iffile exists or not:
    bool fileExists()
    {
        ifstream file(fileLocation);
        return file.good(); // Checks if the file stream is in a good state (i.e., file exists)
    }

public:
    // constructor:
    BillsFileHandling(string s)
    {
        fileLocation = s;
    }

    // loading all bills from file:
    void loadAllBills(AllBills &b)
    {
        // if not exists:
        if (!fileExists())
        {
            return;
        }

        // clearing the former billsList to add new:
        b.bills.clear();
        // reading bills from file:

        ifstream billsFile(fileLocation);
        bool skip = true;
        while (billsFile.eof() == false)
        {

            string line = "", s1 = "", s2 = "", s3 = "";
            getline(billsFile, line);

            // skipping first line to print
            if (skip)
            {
                skip = false;
                continue;
            }

            int index = 0;
            for (auto i : line)
            {
                if (i == ':')
                {
                    index++;
                    continue;
                }
                if (index == 0)
                {
                    s1 += i;
                }
                else if (index == 1)
                {
                    s2 += i;
                }
                else
                {
                    s3 += i;
                }
            }
            vector<string> temp = {s1, s2, s3};
            b.bills.push_back(temp);
        }
    }

    // saving a bill to file:
    void saveBill(Bill b)
    {
        // create bill file if not exists:
        if (!fileExists())
        {
            ofstream file(fileLocation);
            file << "Buyer:Amount:Contact:";
            file.close();
        }

        // adding to db:
        ofstream file(fileLocation, ios::app); // opening in append mode
        file << '\n' + b.buyer + ':' + to_string(b.amount) + ':' + b.contact + ':';
        file.close();
    }
};