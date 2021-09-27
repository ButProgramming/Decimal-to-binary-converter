#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <bitset>
#include <iomanip>
using namespace std;

bool castHasNotBeenSuccessfully(double number, string readLine);
bool numberIsAnIntegerValue(double number, string readLine);
template <typename T>
string getBinary(const T t);

int main()
{
    long long decimalIntegerNumber = 0;
    double decimalRealNumber = 0;
    double number = 0;
    string readLine;
    stringstream ss;
    ifstream input{ "/dec.txt" };
    ofstream output{ "/bin.txt" };

    if (!input)
    {
        cout << "The input file cannot be founded" << endl;
        return 1;
    }

    if (!output)
    {
        cout << "Output file cannot be founded" << endl;
        return 1;
    }

    // read and write
    while (input)
    {
        bool valueIsAnInteger = false; // for convinience

        getline(input, readLine);

        if (!input)
            break;

        ss.str("");
        ss.clear();
        ss << readLine;
        ss >> number;

        if (castHasNotBeenSuccessfully(number, readLine))
        {
            output << "The value \"" << readLine << "\" cannot be converted to the binary number " << endl;
            continue;
        }

        if (numberIsAnIntegerValue(number, readLine))
        {
            decimalIntegerNumber = (int)number; //because of 3.00000000101
            number = 0;
            valueIsAnInteger = true;
            if (decimalIntegerNumber == LONG_MIN)
            {
                if (to_string(decimalIntegerNumber) != readLine)
                {
                    output << "The value \"" << readLine << "\" is not supported (your value must be >= " << LONG_MIN << " and <= " << LONG_MAX << ")" << endl;
                    continue;
                }
            }
        }
        else
        {
            decimalRealNumber = number;
        }


        if (valueIsAnInteger)
        {
            output <<"Integer dec: "<< decimalIntegerNumber <<" | " << " bin: " << getBinary(decimalIntegerNumber) <<endl;
        }
        else
        {
            output << setprecision(numeric_limits<long double>::digits10 + 1) << "Real dec: " <<
                decimalRealNumber << " | " << " bin: " << getBinary(decimalRealNumber) << endl;
        }
   
    }

    return 0;

}

// when numberIsNull = false then that means the cast
// to a number type was not successfully
bool numberIsNull(double number, string line)
{
    string numberStr = to_string(number);
    if (numberStr != line)
    {
        return false;
    }
    return true;
}

bool castHasNotBeenSuccessfully(double number, string readLine)
{
    if (number == 0 && readLine != "0")
    {
        return true;
    }
    return false;
}

bool numberIsAnIntegerValue(double number, string readLine)
{
    // == the cast has been done successfully
    if (numberIsNull(number, readLine))
    {
        return true;
    }
    else {
        size_t found = readLine.find('.');
        if (found == string::npos)
        {
            return true;
        }
    }
    return false;
}

template <typename T>
string getBinary(const T t)
{
    stringstream ss;
    string binary;
    ss << bitset<64>(*reinterpret_cast<const uint64_t*>(&t)) << endl;
    ss >> binary;
    for (int i = binary.length() - 1; i >= 0; i--)
    {
        if (i % 4 == 0)
        {
            binary.insert(i, 1, ' ');
        }
    }
    return binary;
}
