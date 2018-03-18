//
// Created by Cosmin on 06.03.2018.
//

#include "BigInt.h"
#include <iostream>
#include <cstdlib>
#include <cstring>
#define pozINF "99999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999"
using namespace std;



int lengthOfNr(const unsigned int x);
int lengthOfNr(const int x);
void reversedSeq(int *&newArr, int *oldArr, int len);
//constructors

BigInt::BigInt() {
    length = 1;
    sequence = new int[1];
    sequence[0] = 0;
}

BigInt::BigInt(const unsigned int len,const unsigned int defVal) {
    sequence = new int[len];
    length = len;
    for(unsigned int i = 0; i < length; i++){
        sequence[i] = defVal;
    }
}

BigInt::BigInt(const unsigned int number){
    // obtinem lungimea sirului
    unsigned int nn = number;
    while(nn){
        length += 1;
        nn /= 10;
    }
    nn = number;
    int poz = 0;
    if(!length) length = 1;
    sequence = new int[length];
    while(nn){
        sequence[poz++] = nn % 10;
        nn /= 10;
    }
}

BigInt::BigInt(const string seq) {

    //initializam BigInt-ul cu valoarea 0
    length = 1;
    sequence = new int[1];
    sequence[0] = 0;

    unsigned int counter = 0;
    //determinam lungimea subsirului care incepe de la inceputul sirului initial format doar din cifre
    while(seq[counter] >= '0' && seq[counter++] <= '9' && counter < seq.length());

    if(counter == 0)return;

    length = counter;
    sequence = new int[length];
    //formam numarul din acele cifre

    for(counter = 0; counter < length; counter++){
        sequence[counter] = seq[counter] - '0';
    }

    //ex BigInt a("123aba") --> a=123
}
BigInt::BigInt(const BigInt& number) {
    length = number.length;
    sequence = new int[length];

    for(unsigned int i = 0; i < length; i++)
    {
        sequence[i] = number.sequence[i];
    }
}

//overloading cout<<

ostream &operator<<(ostream &stream, BigInt &number) {
    for(int i = 0; i < number.length; i++)
        stream<<number.sequence[i];
    return stream;
}

//overloading cin>>

istream &operator>>(istream &stream, BigInt &number){
    char c = '0';
    string seq = "";
    //determinam lungimea sirului
    while(stream.get(c) && c >= '0' && c <= '9'){
        seq += c;
    }
    number.length = seq.length();
    number.sequence = new int[number.length];
    for(int i = 0; i < seq.length(); i++){
        number.sequence[i] = seq[i] - '0';
    }
    return stream;
}

bool BigInt::ePar(){
    if(length > 0) {
        if(sequence[length - 1] % 2 == 0)
            return true;
    }
    return false;
}
bool BigInt::ePalindrom(){
    if(length > 0) {
        // 1 2 5 2 3
        for(int i = 0; i < length/2; i++)
            if(sequence[i] != sequence[length - i - 1])
                return false;
        return true;
    }
    return false;
}
long long BigInt::sumaCifre(){
    long long sum = 0;
    for(int i = 0; i < length; i++)
        sum += sequence[i];
    return sum;
}

//operatori > < + - * / =

bool BigInt::operator>(const BigInt &op2) const{
    if(this->length > op2.length)
        return true;
    if(this->length < op2.length)
        return false;
    //ambele sunt negative
    if(this->length > op2.length)
        return false;
    int poz = 0;
    //gasim prima pozitie unde difera cele doua siruri
    while((this->sequence[poz] == op2.sequence[poz]) && (poz < this->length))
        poz++;
    if(poz >= length) return false;
    if(this->sequence[poz] > op2.sequence[poz])
        return true;
    return false;
}
bool BigInt::operator<(const BigInt &op2) const{
    if(!((*this)==op2) && !((*this)>op2))
        return true;
    return false;
}
bool BigInt::operator==(const BigInt &op2) const{
    if(this->length && op2.length)
    {
        int poz = 0;
        while(poz < length)
            if(this->sequence[poz] != op2.sequence[poz])
                return false;
        return true;
    }
    return false;
}
bool BigInt::operator<=(const BigInt &op2) const{
    if((*this) < op2 || (*this) == op2)
        return true;
    return false;
}
bool BigInt::operator>=(const BigInt &op2) const{
    if((*this) > op2 || (*this) == op2)
        return true;
    return false;
}
BigInt BigInt::operator+(const BigInt &op2) const{
    BigInt result;
    //determinam lungimea maxima a sirului suma rezultat

    unsigned int maxLen = this->length > op2.length ? this->length : op2.length;
    maxLen  += 1;

    //declaram vectorul suma si il initialiam cu 0

    int *sum = new int[maxLen];

    for(int i = 0; i <maxLen; i++)
        sum[i] = 0;
    //facem suma de la coada la cap
    //prin urmare vectorul sum o sa reprezinte suma numerelor inversata
    int *term1, *term2;
    reversedSeq(term1, this->sequence, this->length);
    reversedSeq(term2, op2.sequence, op2.length);
    int cPoz = 0, c1=0, c2=0, transport = 0, x, y;    //c1 contorul pentru primul vector, c2 pentru cel de-al doilea vector
    //x - termenul curent din primul vector
    //y - termenul curent din al doilea vector
    x = term1[0];
    y = term2[0];
    while(cPoz < maxLen - 1)
    {
        sum[cPoz] += (x + y + transport)%10;
        transport = (x + y) > 9 ? 1 : 0;
        cPoz++;
        if(c1 < this->length - 1)
            x = term1[++c1];
        else
            x = 0;
        if(c2 < op2.length - 1)
            y = term2[++c2];
        else
            y = 0;
    }
    sum[maxLen - 1] += transport;
    if(sum[maxLen - 1] == 0)
            maxLen--;
    result.length = maxLen;
    reversedSeq(result.sequence, sum, maxLen);

    //eliberam memoria
    delete[]term1;
    delete[]term2;
    delete[]sum;

    return result;
}
BigInt BigInt::operator-(const BigInt &op2) const{
    BigInt result;
    if((*this) <= op2)
    {
        result = 0;
        return result;
    }
    int *term1, *term2, len1 = length, len2 = op2.length;
    term1 = new int[len1];
    term2 = new int[len2];
    reversedSeq(term1, this->sequence, this->length);
    reversedSeq(term2, op2.sequence, op2.length);
    //*term1 -= *term2

    int i,j, t = 0;
    for (i = 0; i < len1 && i < len2; i++)
    {
        if(term1[i] >= term2[i])
            term1[i] -= term2[i];
        else
        {
            j=i+1;
            while(term1[j] == 0)
                term1[j++] = 9;
            term1[j]--;
            term1[i]= 10 + term1[i] - term2[i];
        }
    }
   //sa n-am zerouri nesemnificative
    while(term1[len1-1] == 0)
    {
        len1--;
    }
    reversedSeq(result.sequence, term1, len1);
    result.length = len1;
    delete[]term1;
    delete[]term2;
    return result;
}

BigInt BigInt::operator*(const BigInt &op2) const{

    int len1 = length, len2 = op2.length, *term1, *term2;
    term1 = new int[len1];
    term2 = new int[len2];

    reversedSeq(term1, this->sequence, len1);
    reversedSeq(term2, op2.sequence, len2);

    int auxLen = len1 + len2;
    int *aux = new int[auxLen];

    int i,j,t=0;

    //stabilim lungimea rezultatului. S-ar putea modifica
    auxLen = len1 + len2 - 1;
    //initializez vectorul aux
    for(i = 0; i < auxLen + 1; i++)
        aux[i] = 0;
    //calculez produsele intermediare, impreuna cu suma intermediara
    for(i = 0 ; i < len1; i++)
        for(j = 0; j < len2; j++)
            aux[i + j] += term1[i] * term2[j];
    //corectez sumele intermediare
    int init;
    for(i = 0; i < auxLen; i++)
    {
        init = aux[i] + t;
        aux[i] = (aux[i] + t)%10;
        t = init / 10;
    }
    if(t) {
        aux[auxLen] = t;
        auxLen ++;
    }
    for (; auxLen && !aux[auxLen - 1]; auxLen--); // sa n-am zerouri nesemnificative
    BigInt result;
    result.length = auxLen;
    result.sequence = new int[result.length];
    reversedSeq(result.sequence, aux, auxLen);
    return result;
}

BigInt BigInt::operator/(const BigInt &op2) const{
    BigInt result("0"), zero("0");
    /*if(*this == op2)
    {
        result = 1;
        return result;
    }
    if(*this < op2 || (*this) == zero)
    {
        result = 0;
        return result;
    }
    if(op2 == zero)
    {
        result = 0;
        return result;
    }*/
    //
    BigInt dCopy(*this), opCopy(op2);
    result = 0;
    cout<<"\nCopia este "<<dCopy;
    cout<<endl<<"opCopy este "<<opCopy;
    BigInt contor("0"), incrementor("1");
    while(dCopy > opCopy)
    {
        cout<<endl<<"dCopy "<<dCopy<<" si opCopy este "<<opCopy<<" si result este "<<result<<" si incrementor este "<<incrementor;
        result = result + incrementor;
        dCopy -= opCopy;
        cout<<endl<<"Dupa operatiile din while dCopy "<<dCopy<<" si opCopy este "<<opCopy<<" si result este "<<result;
    }
    cout<<"\nLungimea rezultatului este "<<result.length;
    return result;
}
&BigInt::operator=(const BigInt &op2){
    this->length = op2.length;
    this->sequence = new int[this->length];
    for(int i = 0; i < this->length; i++)
        this->sequence[i] = op2.sequence[i];

}
&BigInt::operator=(const unsigned int number){
    if(number >= 0)
        {
            length = lengthOfNr(number);
            unsigned int nr = number;
            int *temp = new int[length];
            unsigned cont = 0;
            while(nr)
            {
                temp[cont++] = number%10;
                nr /= 10;
            }
            reversedSeq(sequence, temp, length);
            delete []temp;
        }


}
&BigInt::operator=(const int number){
    if(number >= 0)
        {
            length = lengthOfNr(number);
            int nr = number;
            int *temp = new int[length];
            int cont = 0;
            while(nr)
            {
                temp[cont++] = number%10;
                nr /= 10;
            }
            reversedSeq(sequence, temp, length);
            delete []temp;
        }
}
&BigInt::operator=(const string seq){
    if(seq.length() > 0)
        *this = BigInt(seq);
}
BigInt::operator+=(const BigInt &op2){
    *this = (*this) + op2;
}
BigInt::operator-=(const BigInt &op2){
    *this = (*this) - op2;
}

//destructor
BigInt::~BigInt() {
    length = 0;
    delete []sequence;
}

//folosit in adunarea vectorilor
void reversedSeq(int *&newArr, int *oldArr, int len) {
    newArr = new int[len];
    for(int i = 0; i < len; i++) {
        newArr[i] = oldArr[len - i - 1];
    }
}

int lengthOfNr(const unsigned int x)
{
    int len = 0, xx = x;
    while(xx)
    {
        xx /= 10;
        len++;
    }
    return len;
}

int lengthOfNr(const int x)
{
    int len = 0, xx = x;
    while(xx)
    {
        xx /= 10;
        len++;
    }
    return len;
}
