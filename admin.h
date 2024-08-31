#include <iostream>
#include <fstream>
#include <string>

#include "errorHandling.h"

using namespace std;

class Admin
{
private:
    string correctPassword; // correct password
    string userPassword;    // password which user gave as input

    string name, email; // user details

    // Function to hash Password:
    string hashPass(string s)
    {
        unsigned long long int hash = 0;
        for (char c : s)
        {
            hash = (hash * 31) + (unsigned long long int)c;
        }

        string ans = to_string(hash);
        return ans;

        /*
         For each character c in the string, the hash value is updated by multiplying the current
         hash value by a prime number (31 in this case) and adding the ASCII value of the
         character.

        *** Points to Consider ***

        --> Collision Resistance:
        This simple hash function is not designed to be collision-resistant. A good hash
        function minimizes collisions, meaning different inputs should produce different hash
        values as much as possible.

        --> Uniform Distribution:
         A well-designed hash function should distribute hash values uniformly to avoid
         clustering.

        --> Performance:
        In practice, hash functions should be efficient and work well with large datasets.
        */
    }

    // Function to create a New Admin:
    void createAdmin()
    {
        textRed("\t\tNo Prior Admin Found.");
        textGreen("\tEnter details below to become one:");
        cout << "Name: ";
        cin >> name;

        cout << "Email: ";
        cin >> email;

        cout << "Create Password: ";
        cin >> correctPassword;

        // hashing password:
        correctPassword = hashPass(correctPassword);

        textGreen("Congrats!!! You became admin of this store.");
        ScreenWaitMilliSec(800);

        ScreenClear();
    }

public:
    // Function to authenticate Admin:
    void authenticate()
    {
        // getting user input password:
        cout << endl;
        cout << "Enter the Passkey for Admin: ";
        cin >> userPassword;

        // hashing user input password:
        userPassword = hashPass(userPassword);

        // if password entered is incorrect:
        if (correctPassword != userPassword)
        {
            customError e("Wrong Password!");
            throw e;
        }
    }

    // Function to display Details of Admin:
    void displayDetails()
    {
        cout << "\t\tName: " << name << endl;
        cout << "\t\tEmail: " << email << endl;
    }

    friend class AdminFileHandling;
};

class AdminFileHandling
{
private:
    string fileLocation;

    // function to check if a file exists or not:
    bool fileExists()
    {
        ifstream file(fileLocation);
        return file.good(); // Checks if the file stream is in a good state (i.e., file exists)
    }

public:
    // constructor:
    AdminFileHandling(string s)
    {
        fileLocation = s;
    }

    // function to load admin from database:
    void loadAdmin(Admin &admin)
    {
        if (!fileExists())
        {
            // create new file:
            ofstream tempFile(fileLocation);
            tempFile << "name:password:email";
            tempFile.close();
            // create new admin:
            admin.createAdmin();
            // save the admin to file:
            saveAdmin(admin);
            return;
        }

        // getting admin Details From File:
        ifstream adminFile(fileLocation);
        string details = "";
        getline(adminFile, details); // skip this first placeholder line
        getline(adminFile, details); // this line contains details.

        // setting admin Details in variables:
        int index = 0;
        for (auto c : details)
        {
            if (c == ':')
            {
                index++;
            }
            else
            {
                if (index == 0)
                {
                    admin.name += c;
                }
                if (index == 1)
                {
                    admin.correctPassword += c;
                }
                if (index == 2)
                {
                    admin.email += c;
                }
            }
        }
    }

    // function to save admin to database:
    void saveAdmin(Admin admin)
    {
        if (!fileExists())
        {
            customError e("Admin File Not Found in Database!");
            throw e;
        }

        // overwriting the file with changed admin details:
        ofstream tempFile(fileLocation);
        tempFile << "adminname:password:email:";
        // enter new admin details in file:
        tempFile << "\n"
                 << admin.name << ":" << admin.correctPassword << ":" << admin.email << ":";

        // close the file:
        tempFile.close();
    }
};
