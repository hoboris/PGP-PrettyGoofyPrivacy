#ifndef BINARY_H
#define BINARY_H

#include <string>
#include <stdlib.h>
#include <iostream>
#include <math.h>
#include <QDebug>

using namespace std;

class Binary
{

    public:
        string number;
        Binary();
        Binary(Binary& p_binary);
        Binary(string p_number);
        Binary(unsigned long p_length);
        virtual ~Binary();
        friend ostream& operator<< (ostream &out, Binary& p_binary);
        friend istream& operator>> (istream& in, Binary& p_binary);
        bool operator== (Binary& p_binary);
        bool operator!= (Binary& p_binary);
        bool operator> (Binary& p_binary);
        bool operator< (Binary& p_binary);
        bool operator>= (Binary& p_binary);
        bool operator<= (Binary& p_binary);
        Binary& operator= (Binary& p_binary);
        Binary& operator+ (Binary &p_binary);
        Binary& operator- (Binary &p_binary);
        Binary& operator* (Binary &p_binary);
        Binary& operator/ (Binary &p_binary);
        Binary& operator% (Binary &p_binary);
        Binary& operator^ (Binary &p_binary);
        Binary& exp_mod (Binary& p_binary_exp, Binary& p_binary_mod);
        Binary& shorten();
        Binary& pgcd(Binary& p_binary);
        void bezout(Binary& p_binary, Binary& u, Binary& v, Binary& r, int* p_u_sign, int* p_v_sign, int* p_r_sign);
        Binary& bezout_u(Binary& p_binary);
        bool fermat(unsigned long k);
        bool millerRabin(unsigned long k);
        void random (unsigned long p_length);
        void random_odd (unsigned long p_length);
        bool isBinary();
        static Binary& toBinary(int p_decimal);

    protected:
    private:
};

#endif // BINARY_H
