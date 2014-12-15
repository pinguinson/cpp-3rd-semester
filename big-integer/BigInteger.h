#ifndef MYBIGINTEGER_H
#define MYBIGINTEGER_H

#include <vector>
#include <string>
#include <iostream>

using namespace std;

class BigInteger
{
private:
    std::vector<char> value;
    bool sign;
public:
    BigInteger();
    BigInteger(int number);
    BigInteger(std::string number);
    BigInteger(BigInteger const &copy);

    const BigInteger & operator =  (BigInteger const& other);
    const BigInteger & operator += (BigInteger const& rhs);
    const BigInteger & operator -= (BigInteger const& rhs);
    const BigInteger & operator *= (BigInteger const& rhs);

    void setSign(bool s);
    const bool &getSign();
    friend std::string to_string(BigInteger const &a);
    friend bool operator==(BigInteger const& a, BigInteger const& b);
    friend bool operator< (BigInteger const& a, BigInteger const& b);
    
    //abs(a)
    const BigInteger absolute();
    /*
      a < b : -1
      a = b : 0
      a > b : 1
     */
    friend int absoluteComparator(BigInteger const& a, BigInteger const& b);
    bool isZero();

private:
    bool equals (BigInteger a, BigInteger b);
    bool less   (BigInteger a, BigInteger b);
    bool greater(BigInteger a, BigInteger b);

    BigInteger add(BigInteger const& rhs);
    BigInteger sub(BigInteger const&b);
};

BigInteger operator +(BigInteger a, BigInteger const& b);
BigInteger operator -(BigInteger a, BigInteger const& b);
BigInteger operator *(BigInteger a, BigInteger const& b);

bool operator == (BigInteger const& a, BigInteger const& b);
bool operator <  (BigInteger const& a, BigInteger const& b);
bool operator != (BigInteger const& a, BigInteger const& b);
bool operator >  (BigInteger const& a, BigInteger const& b);
bool operator >= (BigInteger const& a, BigInteger const& b);
bool operator <= (BigInteger const& a, BigInteger const& b);

std::string to_string(BigInteger const &a);
std::ostream& operator<<(std::ostream& s, BigInteger const& a);
std::istream& operator>>(std::istream& s, BigInteger &a);

#endif