#include <iostream>
#include <fstream>
#include <iomanip>
using namespace std;

class Bills
{
private:
    int total;
    string person;
    string phone;
    string billsLocation = "db/bills.txt";

    // function to check if a file exists or not:
    bool fileExists(string fileName)
    {
        ifstream file(fileName);
        return file.good(); // Checks if the file stream is in a good state (i.e., file exists)
    }

public:
    // default constructor:
    Bills() {}
    // constructor:
    Bills(int total, string person, string phone)
    {
        this->total = total;
        this->person = person;
        this->phone = phone;
    }

    // displaying all bills from db file:
    void displayAllBills()
    {

        // if not exists:
        if (!fileExists(billsLocation))
        {
            cout << endl
                 << "\t\t   ";
            textRed("No Bills Found!");
            ScreenWaitMilliSec(700);
            return;
        }

        ifstream file(billsLocation);

        // displaying board:
        cout << endl;
        cout << left; // text align left
        cout << setw(20) << "Buyer" << setw(10) << "Amount" << setw(10) << "Contact" << endl;

        bool skip = true;
        while (file.eof() == false)
        {

            string line = "", s1 = "", s2 = "", s3 = "";
            getline(file, line);

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
            cout << left;
            cout
                << setw(20) << setfill('_') << s1 << setw(10) << '$' + s2 << setw(10) << setfill(' ') << s3 << endl;
        }

        cout << right; // reset text align
        cout << endl;
        textBlink("Type 0 to Dismiss -> ", false);
        string s;
        cin >> s;
    }

    void addBillToDb()
    {
        // checking if file exists:
        if (!fileExists(billsLocation))
        {
            ofstream file(billsLocation);
            file << "Buyer:Amount:Contact:";
            file.close();
        }

        // adding to db:
        ofstream file(billsLocation, ios::app); // opening in append mode
        file << '\n' + person + ':' + to_string(total) + ':' + phone + ':';
        file.close();
    }
};