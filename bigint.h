#include <iostream>
#include <algorithm>
using namespace std;

class bigint
{

private:
    // data members [start]
    string num;
    // data members [end]

public:
    // constructors [start]
    bigint() // default constructor
    {
        this->num = "";
    }
    bigint(const bigint &b) // copy constructor
    {
        this->num = b.num;
    }
    bigint(string num) // parameterised constructor
    {
        this->num = num;
    }
    // constructors [end]

    // input/output operators (>> <<) [start]
    friend istream &operator>>(istream &input, bigint &b)
    {
        input >> b.num;
        return input;
    }
    friend ostream &operator<<(ostream &output, const bigint &b)
    {
        output << b.num;
        return output;
    }
    // input/output operators (>> <<) [end]

    // assignment operator [start]
    void operator=(const bigint &b)
    {
        this->num = b.num;
    }
    void operator=(const string &num)
    {
        this->num = num;
    }
    // assignment operator [end]

    // arithematic operators (+ - * / %) [start]
    bigint operator+(const bigint &b)
    {
        bigint result;
        result.num = add(this->num, b.num);
        return result;
    }
    bigint operator-(const bigint &b)
    {
        bigint result;
        result.num = subtract(this->num, b.num);
        return result;
    }
    bigint operator*(const bigint &b)
    {
        bigint result;
        result.num = multiply(this->num, b.num);
        return result;
    }
    bigint operator/(const bigint &b)
    {
        bigint result;
        result.num = divide(this->num, b.num);
        return result;
    }
    bigint operator%(const bigint &b)
    {
        bigint result;
        result.num = modulo(this->num, b.num);
        return result;
    }
    // arithematic operators (+ - * / %) [end]

private:
    // arithematic operations performed using string [start]
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
    string subtract(const string &a, const string &b)
    {
    }
    string multiply(const string &a, const string &b)
    {
    }
    string divide(const string &a, const string &b)
    {
    }
    string modulo(const string &a, const string &b)
    {
    }
    // arithematic operations performed using string [end]
};

// Math functions (gcd/lcm fibonacci factorial)[start]
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
// Math functions (gcd/lcm fibonacci factorial)[end]
