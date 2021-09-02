#include <iostream>
#include <algorithm>
#include <assert.h>

using namespace std;

class bigint
{

private:
    //-----------------------------DATA MEMBERS-------------------------------//

    string num = "0";
    bool isNeg = false;

    //-----------------------------------------------------------------------//

    //-------------------------VALIDITY AND CONVERSION-----------------------//

    bool isDigit(char ch)
    {
        return '0' <= ch and ch <= '9';
    }

    bool isValid(string num)
    {
        switch (num[0])
        {
        case '+':
            break;
        case '-':
            break;
        default:
            if (!isDigit(num[0]))
                return false;
        }
        int i = 1;
        while (i < num.length())
        {
            if (!isDigit(num[i]))
                return false;
            i++;
        }
        return true;
    }

    bigint convert(string num)
    {

        bigint b;
        b.isNeg = (num[0] == '-');

        int i = num[0] == '-' or num[0] == '+';

        while (i < num.length() and num[i] == '0')
            i++;

        b.num = num.substr(i);

        if (b.num == "")
            b.num += '0';

        return b;
    }
    //-----------------------------------------------------------------------//

public:
    //-----------------------------CONSTRUCTORS-------------------------------//
    bigint()
    {
        this->num = "";
        this->isNeg = false;
    }
    bigint(string num)
    {
        assert(isValid(num));

        *this = convert(num);
    }
    //------------------------------------------------------------------------//

    //-------------------------INPUT/OUTPUT OPERATORS-------------------------//
    friend istream &operator>>(istream &input, bigint &b)
    {
        string s;
        input >> s;
        assert(b.isValid(s));
        b = b.convert(s);
        return input;
    }
    friend ostream &operator<<(ostream &output, const bigint &b)
    {
        if (b.isNeg)
            output << "-" << b.num;
        else
            output << b.num;
        return output;
    }
    //------------------------------------------------------------------------//

    //-------------------------ASSIGNMENT OPERATORS--------------------------//
    void operator=(const bigint &b)
    {
        this->num = b.num;
        this->isNeg = b.isNeg;
    }
    void operator=(const string &num)
    {
        assert(isValid(num));
        *this = convert(num);
    }
    //------------------------------------------------------------------------//

    //-------------------------ARITHEMATIC OPERATORS--------------------------//
    bigint operator+(const bigint &b)
    {
        bool differentSigns = (b.isNeg ^ this->isNeg);
        bigint result;

        if (differentSigns)
        {
            if (b.isNeg)
                result = convert(subtract(this->num, b.num));
            else
                result = convert(subtract(b.num, this->num));
        }
        else
        {
            result = convert(add(this->num, b.num));
            result.isNeg = (this->isNeg and b.isNeg);
            return result;
        }
    }
    bigint operator-(const bigint &b)
    {
        bool differentSigns = (b.isNeg ^ this->isNeg);
        bigint result;

        if (differentSigns)
        {
            if (b.isNeg)
                result = convert(add(this->num, b.num));
            else
            {
                result = convert(add(b.num, this->num));
                result.isNeg = true;
            }
        }
        else
        {
            if (!this->isNeg and !b.isNeg)
                result = convert(subtract(this->num, b.num));
            else
                result = convert(subtract(b.num, this->num));
            return result;
        }
    }
    bigint operator*(const bigint &b)
    {
        bigint result;
        result = convert(multiply(this->num, b.num));
        result.isNeg = this->isNeg ^ b.isNeg;
        return result;
    }
    bigint operator/(const bigint &b)
    {
        bigint result;
        result = convert(divide(this->num, b.num));
        return result;
    }
    bigint operator%(const bigint &b)
    {
        bigint result;
        result = convert(modulo(this->num, b.num));
        return result;
    }
    //------------------------------------------------------------------------//

private:
    //-----------------------------DIGIT X STRING-----------------------------//
    string digitCrossString(int digit, const string &s, int placeValue)
    {
        string res = "";
        int current = 0;
        int carry = 0;
        for (int i = (int)s.length() - 1; i >= 0; i--)
        {
            int strDigit = s[i] - '0';
            current = (strDigit * digit) + carry;
            res += ((current % 10) + '0');
            carry = current / 10;
        }
        if (carry != 0)
            res += (carry + '0');

        reverse(res.begin(), res.end());

        while (placeValue--)
            res += '0';
        return res;
    }
    //-----------------------------ADDITION-----------------------------------//
    string add(const string &a, const string &b)
    {
        string res = "";
        int length1 = a.length();
        int length2 = b.length();
        int carry = 0;

        while (length1 > 0 or length2 > 0 or carry > 0)
        {
            int currentDigit1 = (length1 > 0) ? a[length1 - 1] - '0' : 0;
            int currentDigit2 = (length2 > 0) ? b[length2 - 1] - '0' : 0;

            int currentDigit = currentDigit1 + currentDigit2 + carry;

            carry = currentDigit / 10;
            currentDigit %= 10;

            res += (char)(currentDigit + '0');

            length1--;
            length2--;
        }
        reverse(res.begin(), res.end());

        return res;
    }
    //-----------------------------------------------------------------------//

    //-----------------------------SUBTRACTION-------------------------------//
    string subtract(string a, string b)
    {
        if (a.length() < b.length() or (a.length() == b.length() and a < b))
        {
            return '-' + subtract(b, a);
        }

        string res = "";

        int length1 = a.length();
        int length2 = b.length();

        while (length1 > 0 or length2 > 0)
        {
            int currentDigit1 = a[length1 - 1] - '0';
            int currentDigit2 = (length2 > 0) ? b[length2 - 1] - '0' : 0;

            if (currentDigit2 > currentDigit1)
            {
                int i = length1 - 2;
                while (i >= 0 and a[i] == '0')
                {
                    a[i] = '9';
                    i--;
                }
                if (i >= 0)
                    a[i]--;
                currentDigit1 += 10;
            }

            int currentDigit = currentDigit1 - currentDigit2;
            res += (char)(currentDigit + '0');

            length1--;
            length2--;
        }
        reverse(res.begin(), res.end());
        return res;
    }
    //-----------------------------------------------------------------------//
    string multiply(const string &a, const string &b)
    {
        bigint res;
        for (int i = 0; i < a.length(); i++)
            res = res + digitCrossString(a[i] - '0', b, (int)a.length() - i - 1);

        return res.num;
    }
    string divide(const string &a, const string &b)
    {
    }
    string modulo(const string &a, const string &b)
    {
    }
};

//----------------------MATH FUNCTIONS-----------------------------------//
namespace MathFunctions
{

    bigint fibbnacci(int n)
    {
        bigint res;

        switch (n)
        {
        case 0:
            res = "0";
            break;
        case 1:
            res = "1";
            break;
        default:
            bigint t1;
            bigint t2;
            t1 = "0";
            t2 = "1";
            res = "1";
            int currentTerm = 1;
            while (currentTerm < n)
            {
                res = t1 + t2;
                t2 = t1;
                t1 = res;
                currentTerm++;
            }
        }

        return res;
    }

}
//-----------------------------------------------------------------------//