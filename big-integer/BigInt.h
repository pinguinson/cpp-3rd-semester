#ifndef MYBIGINTEGER_H
#define MYBIGINTEGER_H

#include <vector>
#include <string>
#include <iostream>

using namespace std;

class BigInt
{
private:
    std::vector<char> value;
    bool sign;
public:
    BigInt();
    BigInt(int number);
    BigInt(std::string number);
    BigInt(BigInt const &copy);

    const BigInt & operator =  (BigInt const& other);
    const BigInt & operator += (BigInt const& rhs);
    const BigInt & operator -= (BigInt const& rhs);
    const BigInt & operator *= (BigInt const& rhs);

    void setSign(bool s);
    const bool &getSign();
    friend std::string to_string(BigInt const &a);
    friend bool operator==(BigInt const& a, BigInt const& b);
    friend bool operator< (BigInt const& a, BigInt const& b);
    
    //abs(a)
    const BigInt absolute();
    /*
      a < b : -1
      a = b : 0
      a > b : 1
     */
    friend int absoluteComparator(BigInt const& a, BigInt const& b);

private:
    bool equals (BigInt a, BigInt b);
    bool less   (BigInt a, BigInt b);
    bool greater(BigInt a, BigInt b);

    BigInt add(BigInt const& rhs);
    BigInt sub(BigInt const&b);
};

BigInt operator +(BigInt a, BigInt const& b);
BigInt operator -(BigInt a, BigInt const& b);
BigInt operator *(BigInt a, BigInt const& b);

bool operator == (BigInt const& a, BigInt const& b);
bool operator <  (BigInt const& a, BigInt const& b);
bool operator != (BigInt const& a, BigInt const& b);
bool operator >  (BigInt const& a, BigInt const& b);
bool operator >= (BigInt const& a, BigInt const& b);
bool operator <= (BigInt const& a, BigInt const& b);

std::string to_string(BigInt const &a);
std::ostream& operator<<(std::ostream& s, BigInt const& a);
std::istream& operator>>(std::istream& s, BigInt &a);

#endif