/*
 String Assistant Class
 This class is used for hashing a date of type string.
 The three functions present in the class allow the same functionality but with different input:
    Date, Person, or string
 */
#ifndef StringAssistant_h
#define StringAssistant_h

#include "Date.h"
#include "Person.h"

class StringAssistant
{
public:
    static int hashBirthdate(Date&); // hashes a date of a given Date object type
    static int hashPersonUsingBirthdate(Person&); // hashes a date of a given Person type
    static int hashStringBirthdate(std::string); // hashes a date of string type
};

/*
 All three functions in the class work the same:
 1. Pull the date of string type out for use, method depends on which version used
 2. For each numerical character in the string, add it to a sum
 3. If sum less than 9, return it
 4. If not, convert sum back into a string, and repeat step 2
 5. Repeat steps 2-4 until sum is less than 9 and can be returned
 */

int StringAssistant::hashBirthdate(Date &date)
{
    int sum = 0;
    for (char c : date.formatDateToPrint())
    {
        if (isdigit(c))
            sum += (c - '0');
    }
    if (sum > 9)
    {
        std::string tempSum = std::to_string(sum);
        while (sum > 9)
        {
            sum = 0;
            for (char c : tempSum)
                sum += (c - '0');
            tempSum = std::to_string(sum);
        }
    }
    return sum;
}

int StringAssistant::hashStringBirthdate(std::string date)
{
    int sum = 0;
    for (char c : date)
    {
        if (isdigit(c))
            sum += (c - '0');
    }
    if (sum > 9)
    {
        std::string tempSum = std::to_string(sum);
        while (sum > 9)
        {
            sum = 0;
            for (char c : tempSum)
                sum += (c - '0');
            tempSum = std::to_string(sum);
        }
    }
    return sum;
}

int StringAssistant::hashPersonUsingBirthdate(Person &person)
{
    Date temp;
    temp.updateDate(person.getBirthday());
    return hashBirthdate(temp);
}

#endif /* StringAssistant_h */
