/*
 Hash Table Manager Class
 This class intends to allow a user to a user to provide an input file, which will be parsed to create Person type objects, which will be entered into a Hash Table instance present in the class. The class allows users to search for entreis based on a key value, view the table, and view table stats.
 */

#ifndef HashTableManager_h
#define HashTableManager_h

#include "HashTable.h"
#include <fstream>

template <typename T>
class HashTableManager
{
private:
    std::string inputFileAddress;
    HashTable<T> personTable; // data table being read into
    bool readFromInputFile(); // reads from the user given inout file
    bool getInputFile(); // ensures input file is open-able
    void clearInput(); // removes illegal input for cin.fail()
    bool searchAgain(); // prompts user if to continue searching for entries
    void innerMenu(int); // proccesses menu option chosen
    void pressEnterToContinue();
public:
    void menu(); // menu with functionality
    void enterBirthday(); // prompts user for birthdates to search for
};

template <typename T>
void HashTableManager<T>::menu()
{
    if(getInputFile()) // if file valid and readable (does not guarantee file has correct data)
        {
            int choice = 0;
            std::cout << "=======================" << std::endl;
            std::cout << "Hash Table Manager Menu" << std::endl;
            std::cout << "=======================\n" << std::endl;
            while (choice != 4)
            {
                std::cout << "[1] - Search for entries" << std::endl;
                std::cout << "[2] - See Table Statistics" << std::endl;
                std::cout << "[3] - Display Table With Collision Info" << std::endl;
                std::cout << "[4] - Exit\n--> ";
                std::cin >> choice;
                while (std::cin.fail() || choice < 1 || choice > 4)
                {
                    clearInput();
                    std::cout << "*** invalid input***\n--> ";
                    std::cin >> choice;
                }
                innerMenu(choice);
                pressEnterToContinue();
            }
        }
    else std::cout << "*** INPUT FILE ERROR ***" << std::endl;
}

template <typename T>
bool HashTableManager<T>::getInputFile()
{
    std::cout << "Please provide a COMPLETE input file address [this includes the name of the file]" << std::endl;
    std::cout << "--> ";
    getline(std::cin, this->inputFileAddress);
    if (this->readFromInputFile()) // if valid input file given
        return true;
    else return false;
}
template <typename T>
void HashTableManager<T>::enterBirthday()
{
    std::string input;
    do
    {
        std::cin.ignore();
        std::cout << "Enter date in [yyyy-mm-dd] format: ";
        getline(std::cin, input);
        if (isValidInputForDate(input))
        {
            Date temp;
            temp.updateDate(input);
            int search = this->personTable.search(input);
            if (search != -1)
                std::cout << "Found at resultant index [" << search << "] - {" << input << ", " << this->personTable[search] << "}";
            else std::cout << "No entry with birthdate [" << input << "] found in this data table";
            std::cout << std::endl;
        }
        else std::cout << "*** invalid input - please use [yyyy/mm/dd] format ***" << std::endl;
    }
    while (searchAgain());
}

template <typename T>
bool HashTableManager<T>::readFromInputFile()
{
    std::ifstream inputFile;
    inputFile.open(this->inputFileAddress);
    if (inputFile)
    {
        while (!inputFile.eof())
        {
            std::string name, y, m, d;
            getline(inputFile, name);
            getline(inputFile, y, '-');
            getline(inputFile, m, '-');
            getline(inputFile, d);
            Date temp(y, m, d);
            Person newPerson(name, temp); // creates new Person for each file entry
            this->personTable.insert(newPerson, temp.formatDateToPrint());
        }
        inputFile.close();
        return true;
    }
    return false;
}

template <typename T>
void HashTableManager<T>::clearInput()
{
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // removes illegal value
}

template <typename T>
bool HashTableManager<T>::searchAgain()
{
    int choice;
    std::cout << "\nSearch for another entry?\n[1] - YES\n[2] - NO\n--> ";
    std::cin >> choice;
    while (std::cin.fail() || (choice != 1 && choice != 2))
    {
        clearInput();
        std::cout << "*** invalid input ***" << std::endl;
        return searchAgain();
    }
    if (choice == 1) return true;
    else return false;
}

template <typename T>
void HashTableManager<T>::innerMenu(int choice)
{
    switch (choice)
    {
        case 1: enterBirthday();
            std::cin.ignore(); break;
        case 2:
            std::cin.ignore();
            this->personTable.stats(); break;
        case 3:
            std::cin.ignore();
            this->personTable.displayTable(); break;
        case 4:
            std::cin.ignore();
            std::cout << "Goodbye!" << std::endl; break;
    }
}

template <typename T>
void HashTableManager<T>::pressEnterToContinue()
{
    std::cout << "Press ENTER to continue...";
    std::cin.get();
    system("clear");
}



#endif /* HashTableManager_h */
