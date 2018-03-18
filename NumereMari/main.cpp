#include <iostream>
#include "BigInt.h"

using namespace std;

int main() {
    BigInt a("690"), b("49"), s, d;
    s = a + b;
    cout<<"Numerele sunt : "<<a<<" "<<b;
    cout<<"\nSuma elementelor este "<<s;
    d = a - b;
    cout<<"\nDiferenta elementelor este "<<d;
    BigInt p;
    p = a * b;
    cout<<"\nProdusul dintre "<<a<<" si "<<b<<" este "<<p;
    BigInt r = a / b;
    cout<<"\nRaportul celor doua numere este " << r;
    return 0;
}
