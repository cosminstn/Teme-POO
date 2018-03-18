//
// Created by Cosmin on 06.03.2018.
//

#ifndef NUMEREMARI_BIGINT_H
#define NUMEREMARI_BIGINT_H
#include <string>
#include <iostream>

using namespace std;

class BigInt {
    int *sequence;
    unsigned int length;

public:
    //constructor
    BigInt();
    BigInt(const string seq);
    BigInt(const unsigned int len,const unsigned int defVal);                        //initializez the sequence to have "len" values each being equal to "defVal"
    BigInt(const BigInt& number);                              //copy constructor
    BigInt(const unsigned int number);


    bool ePar();
    bool ePalindrom();
    long long sumaCifre();

    BigInt operator+(const BigInt &op2) const;
    BigInt operator-(const BigInt &op2) const;
    BigInt operator*(const BigInt &op2) const;
    BigInt operator/(const BigInt &op2) const;
    BigInt operator^(const BigInt &op2) const;
    operator+=(const BigInt &op2);
    operator-=(const BigInt &op2);

    bool operator>(const BigInt &op2) const;
    bool operator<(const BigInt &op2) const;
    bool operator==(const BigInt &op2) const;
    bool operator<=(const BigInt &op2) const;
    bool operator>=(const BigInt &op2) const;

    &operator=(const BigInt &op2);
    &operator=(const unsigned int number);
    &operator=(const int number);
    &operator=(const string seq);
    friend ostream &operator<<(ostream& stream, BigInt &number);
    friend istream &operator>>(istream& stream, BigInt &number);
    //destructor
    ~BigInt();
};


#endif //NUMEREMARI_BIGINT_H
