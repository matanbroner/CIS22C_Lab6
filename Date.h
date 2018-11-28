/*
 Date class
 ==========
 This class serves to mimic a date in the format yyyy/mm/dd.
 It allows updating and intial assigning in the constructor.
 It has methods to ensue that dates given are valid based on leap years and number of days in months.
 Dates can be compared and copied over.
 */

#ifndef Date_h
#define Date_h

#include <stdlib.h>
#include <string>
#include <iostream>
#include <fstream>

enum MONTHS{
    JAN_MAR_MAY_JUL_AUG_OCT_DEC = 31, APR_JUN_SEP_NOV = 30, FEBRUARY = 28, FEBRUARY_LEAP = 29
};

class Date;
std::ofstream& operator<<(std::ofstream&, Date&);
std::ostream& operator<<(std::ostream&, Date&);
static bool isValidInputForDate(std::string); // determines if a string is in yyyy/mm/dd format

class Date
{
private:
    MONTHS legalNumberOfDays; // number of max days a month can have
    std::string year;
    std::string month;
    std::string day;
    int toNumber(std::string); // changes string to number [renaming of std::stoi for readability]
    bool isLeapYear(); // determines if a year is a leap year (ie. February has 29 days)
    bool isValidNumber(std::string, int); // determines if string is a number based on given number of expected digits
public:
    Date(std::string, std::string, std::string);
    Date();
    std::string formatDateToPrint(); // returns a date in format yyyy/mm/dd
    bool operator<(Date);
    bool operator==(Date);
    void operator=(Date&);
    
    void determineDaysInMonth(); // determines the number of maximum dates in a month
    void updateDate(std::string); // updates the object based on string IF the input is valid, throws exception otherwise
};

/*
 Public Functions
 */

Date::Date()
{
    this->year = this->month = this->day = "";
}

Date::Date(std::string y, std::string m, std::string d)
{
    if (toNumber(y) >= 0)
        this->year = y;
    
    if (isValidNumber(m, 2))
    {
        this->month = m;
        determineDaysInMonth(); // determine the number of days in the month
    }
    else
    {
        this->month = "01"; // if not valid set default month value
        determineDaysInMonth(); // determine the number of days in the month
    }
    
    if (isValidNumber(d, 2) && toNumber(d) <= this->legalNumberOfDays && toNumber(d) >= 1)
    {
        this->day = d;
    }
    else
    {
        this->day = "01"; // if invalid number set default day value;
    }
    
}

std::string Date::formatDateToPrint()
{
    std::string dateToPrint = "";
    dateToPrint += this->year + "-" + this->month + "-" + this->day;
    return dateToPrint;
}


bool Date::operator<(Date otherDate) // checks year, then month, then day (larger is actually smaller as in 2015 is younger than 1975)
{
    if (toNumber(this->year) > toNumber(otherDate.year))
        return true;
    else if (toNumber(this->year) == toNumber(otherDate.year))
    {
        if (toNumber(this->month) > toNumber(otherDate.month))
            return true;
        else if (toNumber(this->month) == toNumber(otherDate.month))
            return (toNumber(this->day) > toNumber(otherDate.day));
        else return false;
    }
    else return false;
}

bool Date::operator==(Date otherDate)
{
    if (this->formatDateToPrint() == otherDate.formatDateToPrint())
        return true;
    else return false;
}

std::ofstream& operator<<(std::ofstream& outputFile, Date& date)
{
    outputFile << date.formatDateToPrint();
    return outputFile;
}

std::ostream& operator<<(std::ostream& output, Date& date)
{
    output << date.formatDateToPrint();
    return output;
}


void Date::operator=(Date &otherDate)
{
    this->legalNumberOfDays = otherDate.legalNumberOfDays;
    this->year = otherDate.year;
    this->month = otherDate.month;
    this->day = otherDate.day;
}

void Date::updateDate(std::string newDate)
{
    if (isValidInputForDate(newDate))
    {
        this->year = newDate.substr(0,4);
        this->month = newDate.substr(5,2);
        this->determineDaysInMonth();
        this->day = newDate.substr(8,2);
        if (toNumber(this->day) > this->legalNumberOfDays)
            this->day = "01";
    }
    else
        throw ("[invalid input given for date]");
}

void Date::determineDaysInMonth()
{
    switch(toNumber(this->month))
    {
        case 1:
        case 3:
        case 5:
        case 7:
        case 8:
        case 10:
        case 12:
            this->legalNumberOfDays = JAN_MAR_MAY_JUL_AUG_OCT_DEC;
            break;
        case 4:
        case 6:
        case 9:
        case 11:
            this->legalNumberOfDays = APR_JUN_SEP_NOV;
            break;
        case 2:
            if (isLeapYear())
                this->legalNumberOfDays = FEBRUARY_LEAP;
            else this->legalNumberOfDays = FEBRUARY;
            break;
        default:
            this->month = "01";
            determineDaysInMonth();
    }
}

/*
 Private Functions
 */

bool Date::isLeapYear()
{
    if(std::stoi(this->year) % 4 == 0)
    {
        if (std::stoi(this->year) % 100 == 0)
        {
            if (std::stoi(this->year) % 400 == 0)
                return true;
            else return false;
        }
        else return true;
    }
    else return false;
}

int Date::toNumber(std::string num)
{
    return std::stoi(num);
}


bool Date::isValidNumber(std::string number, int expectedLength)
{
    if (number.length() == expectedLength)
    {
        for (char c : number)
        {
            if (!isdigit(c)) // ensure every char is in fact a number
                return false;
        }
        return true;
    }
    return false;
}


bool isValidInputForDate(std::string date)
{
    if (date.length() == 10) //  must be in yyyy/mm/dd format
    {
        if (date[4] == '-' && date[7] == '-') // checks for slashes (/)
        {
            for (int index = 0; index < 10; index++)
            {
                if (index == 4 || index == 7) // skips slashes
                    continue;
                else if (!isdigit(date[index])) // ensures every other index is a number
                    return false;
            }
            return true;
        }
        else return false;
    }
    return false;
}

#endif /* Date_h */
