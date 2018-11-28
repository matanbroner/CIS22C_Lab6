/*
 Person class
 ============
 This class serves to mimic a person with a name and birthdate.
 It has the ability to compare based on name and birth dates using a boolean variable that must be changed when needed.
 */
#ifndef Person_h
#define Person_h

#include <iostream>
#include <fstream>
#include "Date.h"

class Person;
std::ofstream& operator<<(std::ofstream& outputFile, Person&);
std::ostream& operator<<(std::ostream& output, Person&);

class Person
{
private:
    static bool byName; // determines if comparison between two Person's will be by birthdate or by name
    std::string name;
    Date birthDate;
public:
    Person();
    Person(std::string, Date);
    Person(std::string);
    std::string getName();
    std::string getBirthday();
    
    
    void setName(std::string);
    void setDate(Date&);
    
    void operator=(Person);
    bool operator<(Person);
    bool operator==(Person);
    static void sortByName();
    static void sortByDate();
    
};

bool Person::byName = true;

Person::Person()
{
    this->name = "";
}

Person::Person(std::string name)
{
    this->name = name;
}

Person::Person(std::string name, Date date)
{
    this->name = name;
    this->birthDate = date;
}

std::string Person::getName(){return this->name;}
std::string Person::getBirthday()
{
    return this->birthDate.formatDateToPrint();
}

void Person::setName(std::string newName){this->name = newName;}
void Person::setDate(Date &newDate){this->birthDate = newDate;}

std::ofstream& operator<<(std::ofstream& outputFile, Person& person)
{
    outputFile << person.getName() << "\t" << person.getBirthday();
    return outputFile;
}

std::ostream& operator<<(std::ostream& output, Person& person)
{
    output << person.getName();
    return output;
}

bool Person::operator<(Person otherPerson)
{
    if (byName)
    {
        return (this->name < otherPerson.name);
    }
    else
    {
        return (this->birthDate < otherPerson.birthDate);
    }
}

void Person::operator=(Person otherPerson)
{
    this->name = otherPerson.name;
    this->birthDate = otherPerson.birthDate;
}

bool Person::operator==(Person otherPerson)
{
    if (byName)
        return (this->name == otherPerson.getName());
    else
        return (this->birthDate.formatDateToPrint() == otherPerson.getBirthday());
}

void Person::sortByName(){byName = true;}
void Person::sortByDate(){byName = false;}

#endif /* Person_h */
