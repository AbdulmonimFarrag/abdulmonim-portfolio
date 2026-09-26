#include <iostream>
#include <string>
using namespace std;

int GetDigits(const int number);
int SumOddNums(const string& cardnumber);
int SumEvenNums(const string& cardnumber);
string GetCardType(const string& cardnumber);
bool IsNumeric(const string& s);
string RemoveSpaces(const string& input);

int main()
{
    string cardnumber;

    cout << "Enter your credit card number:\n";
    getline(cin, cardnumber);

    cardnumber = RemoveSpaces(cardnumber);

    if (cardnumber.empty())
    {
        cout << "Input cannot be empty.\n";
        return 1;
    }

    if (!IsNumeric(cardnumber))
    {
        cout << "Invalid input: card number must contain digits only.\n";
        return 1;
    }

    int result = SumEvenNums(cardnumber) + SumOddNums(cardnumber);

    if (result % 10 == 0)
    {
        cout << "This credit card number is valid\n";
        cout << GetCardType(cardnumber) << "\n";
    }
    else
    {
        cout << "This credit card number is not valid\n";
    }

    return 0;
}

int GetDigits(const int number)
{
    return number % 10 + (number / 10 % 10);
}

int SumOddNums(const string& cardnumber)
{
    int sum = 0;
    for (int i = cardnumber.size() - 1; i >= 0; i -= 2)
    {
        sum += cardnumber[i] - '0';
    }
    return sum;
}

int SumEvenNums(const string& cardnumber)
{
    int sum = 0;
    for (int i = cardnumber.size() - 2; i >= 0; i -= 2)
    {
        sum += GetDigits((cardnumber[i] - '0') * 2);
    }
    return sum;
}

string GetCardType(const string& cardnumber)
{
    if (cardnumber[0] == '4')
    {
        return "This card number is a VISA credit card";
    }
    else if (cardnumber.substr(0, 2) == "34" || cardnumber.substr(0, 2) == "37")
    {
        return "This card number is an American Express credit card";
    }
    else if (cardnumber.substr(0, 2) >= "51" && cardnumber.substr(0, 2) <= "55")
    {
        return "This card number is a Mastercard credit card";
    }
    else if (cardnumber.substr(0, 4) == "6011")
    {
        return "This card number is a Discover credit card";
    }
    else
    {
        return "Unknown credit card type";
    }
}

bool IsNumeric(const string& s)
{
    for (char c : s)
    {
        if (!isdigit(c))
            return false;
    }
    return true;
}

string RemoveSpaces(const string& input)
{
    string output;
    for (char c : input)
    {
        if (c != ' ')
            output += c;
    }
    return output;
}
