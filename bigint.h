#include <iostream>
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
    // arithematic operators (+ - * / %) [end]

    // Math functions (gcd/lcm fibonacci factorial)[start]
    // Math functions (gcd/lcm fibonacci factorial)[start]
};
