#include <string>
#include "BigInt.h"
#include <cmath>
#include "exception.cpp"

BigInt::BigInt() {
    value.clear();
    value.push_back(0);
    sign = true;
}

BigInt::BigInt(int a) {
    long long number = a;
    sign = number > 0;
    value.clear();
    long long buffer;
    if (sign) {
        buffer = number;
    } else {
        buffer = -number;
    }

    while (buffer > 0) {
        value.push_back((char) (buffer % 10));
        buffer /= 10;
    }
}

std::string to_string(BigInt const &a) {
    unsigned int length = a.value.size() + !a.sign;
    char number[a.value.size() + !a.sign];
    int cur = 0;
    if (!a.sign) {
        number[cur] = '-';
        cur++;
    }
    for (int i = a.value.size() - 1; i >= 0; i--) {
        number[cur] = (char) (48 + a.value[i]);
        cur++;
    }
    std::string ans = number;
    return ans.substr(0, length);
}

BigInt::BigInt(std::string number) {
    if (number.size() == 0)
        throw parse_exception("Empty string");
    int end = 0;
    sign = true;
    value.clear();
    if (number[0] == '-') {
        sign = false;
        end = 1;
    }
    for (int i = end; i < number.length(); i++) {
        char currentChar = number[i];
        if (!isdigit(currentChar))
            throw parse_exception("Invalid string");
    }
    for (int i = number.length() - 1; i >= end; i--) {
        value.push_back((char) (number[i] - 48));
    }
}

BigInt::BigInt(BigInt const &copy) {
    value = copy.value;
    sign = copy.sign;
}

void BigInt::setSign(bool s) {
    sign = s;
}

const bool &BigInt::getSign() {
    return sign;
}

const BigInt& BigInt::operator = (BigInt const& other) {
    value = other.value;
    sign = other.sign;
    return *this;
}

const BigInt& BigInt::operator+=(BigInt const& rhs) {
    if (sign == rhs.sign) {
        add(rhs);
        return *this;
    }
    if (absoluteComparator(*this, rhs) == 1) {
        sub(rhs);
        return *this;
    }
    BigInt buff = rhs;
    buff.sub(*this);
    *this = buff;
    return *this;
}

const BigInt& BigInt::operator-=(BigInt const& rhs) {
    BigInt r = rhs;
    r.setSign(!r.getSign());
    return (*this) += r;
}

const BigInt& BigInt::operator*=(BigInt const& rhs) {
    bool newSign = (sign == rhs.sign);
    BigInt result = BigInt();
    for (int i = 0; i < rhs.value.size(); ++i) {
        vector<char> current;
        for (int j = 0; j < i; ++j) {
            current.push_back(0);
        }
        char carry = 0;
        for (int k = 0; k < value.size(); ++k) {
            int newValue = rhs.value[i] * value[k] + carry;
            current.push_back((char) (newValue % 10));
            carry = (char) (newValue / 10);
        }
        if (carry > 0) {
            current.push_back(carry);
        }
        BigInt buff = BigInt();
        buff.value = current;
        result += buff;
    }
    result.setSign(newSign);
    *this = result;
    return *this;
}

bool operator ==(BigInt const& a, BigInt const& b) {
    bool sign1 = a.sign;
    bool sign2 = b.sign;

    if (sign1 != sign2) {
        return false;
    }

    if (a.value.size() != b.value.size()) {
        return false;
    }

    for (int i = a.value.size() - 1; i >= 0; i--) {
        if (a.value[i] != b.value[i]) {
            return false;
        }
    }

    return true;
}

bool operator <=(BigInt const& a, BigInt const& b) {
    return ((a < b) || (a == b));
}

bool operator < (BigInt const& a, BigInt const& b) {
    return (absoluteComparator(a, b) == -1);
}

bool operator >=(BigInt const& a, BigInt const& b) {
    return ((a > b) || (a == b));
}

bool operator > (BigInt const& a, BigInt const& b) {
    return ((a != b) && !(a < b));
}

bool operator !=(BigInt const& a, BigInt const& b) {
    return !(a == b);
}

const BigInt BigInt::absolute() {
    BigInt result = *this;
    result.setSign(true);
    return result;
}

bool BigInt::greater(BigInt a, BigInt b) {
    bool sign1 = a.getSign();
    bool sign2 = b.getSign();

    if (!sign1 && sign2)
        return false;

    if (sign1 && !sign2)
        return true;

    if (sign1) {
        if (a.value.size() < b.value.size())
            return false;
        if (a.value.size() > b.value.size())
            return true;
        for (int i = a.value.size() - 1; i >= 0; i--) {
            if (a.value[i] < b.value[i]) {
                return false;
            }
            if (a.value[i] > b.value[i]) {
                return true;
            }

        }
    } else {
        if (a.value.size() > b.value.size())
            return true;
        if (a.value.size() < b.value.size())
            return false;
        for (int i = a.value.size() - 1; i >= 0; i--) {
            if (a.value[i] < b.value[i]) {
                return true;
            }
            if (a.value[i] > b.value[i]) {
                return false;
            }
        }
    }
    return false;
}

BigInt operator+(BigInt a, BigInt const& b) {
    return a += b;
}

BigInt operator-(BigInt a, BigInt const& b) {
    return a -= b;
}

BigInt operator*(BigInt a, BigInt const& b) {
    return a *= b;
}

std::istream& operator>>(std::istream &s, BigInt &a) {
    std::string tmp;
    s >> tmp;
    a = BigInt(tmp);
    return s;
}

std::ostream& operator<<(std::ostream &s, BigInt const& a) {
    return s << to_string(a);
}

int absoluteComparator(BigInt const& a, BigInt const& b) {
    if (a.value.size() > b.value.size()) {
        return 1;
    } else if (a.value.size() < b.value.size()) {
        return -1;
    } else {
        for (int i = a.value.size() - 1; i >= 0; i--) {
            if (a.value[i] > b.value[i]) {
                return 1;
            } else if (a.value[i] < b.value[i]) {
                return -1;
            }
        }
    }
    return 0;
}

BigInt BigInt::add(BigInt const &rhs) {
    char carry = 0;
    int index = 0;
    if (value.size() >= rhs.value.size()) {
        //case A: a >= b
        while (index < rhs.value.size()) {
            int newValue = value[index] + rhs.value[index] + carry;
            carry = (char) (newValue / 10);
            value[index] = (char) (newValue % 10);
            index++;
        }
        while (index < value.size()) {
            int newValue = value[index] + carry;
            carry = (char) (newValue / 10);
            value[index] = (char) (newValue % 10);
            index++;
        }
    } else {
        //case B: a < b
        while (index < value.size()) {
            int newValue = value[index] + rhs.value[index] + carry;
            carry = (char) (newValue / 10);
            value[index] = (char) (newValue % 10);
            index++;
        }
        while (index < rhs.value.size()) {
            int newValue = rhs.value[index] + carry;
            carry = (char) (newValue / 10);
            value.push_back((char) (newValue % 10));
            index++;
        }
    }

    if (carry > 0) {
        value.push_back(carry);
    }

    return *this;
}

BigInt BigInt::sub(BigInt const &rhs) {
    //a >> b
    BigInt b = rhs;
    for (int i = b.value.size(); i < value.size(); ++i) {
        b.value.push_back(0);
    }

    for (int i = 0; i < value.size(); ++i) {
        if (value[i] < b.value[i]) {
            value[i] += 10;
            value[i + 1]--;
        }
        value[i] -= b.value[i];
    }

    while (value[value.size() - 1] == 0) {
        value.pop_back();
    }
    return *this;
}
