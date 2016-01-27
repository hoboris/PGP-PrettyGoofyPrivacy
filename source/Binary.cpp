#include "Binary.h"

Binary::Binary()
{
    number = "";
}

Binary::Binary(Binary& p_binary)
{
    number = p_binary.number;
}

Binary::Binary(string p_number)
{
    number = p_number;
}

Binary::Binary(unsigned long p_length)
{
    random(p_length);
}

Binary::~Binary()
{

}

ostream& operator<< (ostream &out, Binary& p_binary)
{
    out << p_binary.number;
    return out;
}

istream& operator>> (istream &in, Binary& p_binary)
{
    in >> p_binary.number;
    return in;
}

bool Binary::operator== (Binary& p_binary)
{
    return shorten().number.compare(p_binary.shorten().number) == 0;
}

bool Binary::operator!= (Binary& p_binary)
{
    return shorten().number.compare(p_binary.shorten().number) != 0;
}

bool Binary::operator> (Binary& p_binary)
{
    long i = 0;
    Binary* binary1 = new Binary(shorten());
    Binary* binary2 = new Binary(p_binary.shorten());
    long maxLength = max(binary1->number.length(),binary2->number.length());
    if (binary1->number.length() > binary2->number.length()) return true;
    else if (binary1->number.length() < binary2->number.length()) return false;
    while (i < maxLength)
    {
        if (binary1->number[i] == '1' && binary2->number[i] == '0') return true;
        else if (binary1->number[i] == '0' && binary2->number[i] == '1') return false;
        i++;
    }
    return false;
}

bool Binary::operator< (Binary& p_binary)
{
    return !(*this > p_binary) && !(*this == p_binary);
}

bool Binary::operator>= (Binary& p_binary)
{
    return *this > p_binary || *this == p_binary;
}

bool Binary::operator<= (Binary& p_binary)
{
    return *this < p_binary || *this == p_binary;
}

Binary& Binary::operator= (Binary& p_binary)
{
    number = p_binary.number;
    return *this;
}

Binary& Binary::operator+ (Binary& p_binary)
{
    unsigned long maxLength = max(number.length(), p_binary.number.length());
    bool remainder = false;
    Binary* binary_result;
    string result = "";
    for (unsigned long i = 0; i <= maxLength; i++)
    {
        if (i >= number.length() && i >= p_binary.number.length())
        {
            if (remainder == false) result.insert(0,1,'0');
            else result.insert(0,1,'1');
        }
        else if (i >= number.length())
        {
            if (remainder == false) result.insert(0,1,p_binary.number[p_binary.number.length()-1-i]);
            else if (remainder == true && p_binary.number[p_binary.number.length()-1-i] == '0')
            {
                result.insert(0,1,'1');
                remainder = false;
            }
            else if (remainder == true && p_binary.number[p_binary.number.length()-1-i] == '1') result.insert(0,1,'0');
        }
        else if (i >= p_binary.number.length())
        {
            if (remainder == false) result.insert(0,1,number[number.length()-1-i]);
            else if (remainder == true && number[number.length()-1-i] == '0')
            {
                result.insert(0,1,'1');
                remainder = false;
            }
            else if (remainder == true && number[number.length()-1-i] == '1') result.insert(0,1,'0');
        }
        else if (number[number.length()-1-i] == '0' && p_binary.number[p_binary.number.length()-1-i] == '0')
        {
            if (remainder == false) result.insert(0,1,'0');
            else
            {
                result.insert(0,1,'1');
                remainder = false;
            }
        }
        else if ((number[number.length()-1-i] == '1' && p_binary.number[p_binary.number.length()-1-i] == '0') || (number[number.length()-1-i] == '0' && p_binary.number[p_binary.number.length()-1-i] == '1'))
        {
            if (remainder == false) result.insert(0,1,'1');
            else result.insert(0,1,'0');
        }
        else if (number[number.length()-1-i] == '1' && p_binary.number[p_binary.number.length()-1-i] == '1')
        {
            if (remainder == false)
            {
                result.insert(0,1,'0');
                remainder = true;
            }
            else result.insert(0,1,'1');
        }
        else {
            binary_result = new Binary();
            return *binary_result;
        }
    }
    binary_result = new Binary(result);
    return binary_result->shorten();
}

Binary& Binary::operator- (Binary& p_binary)
{
    bool remainder = false;
	Binary* binary_result;
    string result = "";
    if (*this < p_binary) {
        binary_result = new Binary();
        return *binary_result;
    }
    for (unsigned long i = 0; i < number.length(); i++)
    {
        if (i >= p_binary.number.length())
        {
            if (remainder == false) result.insert(0,1,number[number.length()-1-i]);
            else if (remainder == true && number[number.length()-1-i] == '1')
            {
                result.insert(0,1,'0');
                remainder = false;
            }
            else if (remainder == true && number[number.length()-1-i] == '0')
            {
                result.insert(0,1,'1');
            }
            else
            {
                binary_result = new Binary();
                return *binary_result;
            }
        }
        else if (number[number.length()-1-i] == '0' && p_binary.number[p_binary.number.length()-1-i] == '0')
        {
            if (remainder == false) result.insert(0,1,'0');
            else result.insert(0,1,'1');
        }
        else if (number[number.length()-1-i] == '0' && p_binary.number[p_binary.number.length()-1-i] == '1')
        {
            if (remainder == false)
            {
                result.insert(0,1,'1');
                remainder = true;
            }
            else result.insert(0,1,'0');
        }
        else if (number[number.length()-1-i] == '1' && p_binary.number[p_binary.number.length()-1-i] == '0')
        {
            if (remainder == false) result.insert(0,1,'1');
            else
            {
                result.insert(0,1,'0');
                remainder = false;
            }
        }
        else if (number[number.length()-1-i] == '1' && p_binary.number[p_binary.number.length()-1-i] == '1')
        {
            if (remainder == false) result.insert(0,1,'0');
            else result.insert(0,1,'1');
        }
        else {
            binary_result = new Binary();
            return *binary_result;
        }
    }
    binary_result = new Binary(result);
    return binary_result->shorten();
}

Binary& Binary::operator* (Binary& p_binary)
{
    Binary* binary1 = new Binary(shorten());
    Binary* binary2 = new Binary(p_binary.shorten());
    Binary* binary_result = new Binary("0");
    if (binary1->number == "" || binary2->number == "")
    {
        binary_result->number = "";
        return *binary_result;
    }
    while (binary1->number.length() > 0)
    {
        if (binary1->number[binary1->number.length()-1] == '1') *binary_result = *binary_result + *binary2;
        binary1->number.erase(binary1->number.length()-1,1);
        binary2->number.push_back('0');
    }
    return *binary_result;
}

Binary& Binary::operator/ (Binary& p_binary)
{
    Binary* binary_dividend = new Binary(shorten());
    Binary* binary_divisor = new Binary(p_binary.shorten());
    Binary* binary_quotient = new Binary("0");
    Binary* binary_remainder = new Binary("0");
    if (binary_divisor->number == "0" || binary_dividend->number == "" || binary_divisor->number == "")
    {
        binary_quotient->number = "";
        binary_remainder->number = "";
        return *binary_quotient;
    }
    else if ( *binary_dividend < *binary_divisor)
    {
        binary_quotient->number = "0";
        binary_remainder->number = binary_dividend->number;
        return *binary_quotient;
    }
    for (unsigned long i = binary_dividend->number.length()-1; i!=-1; i--){
        binary_remainder->number.push_back(binary_dividend->number[binary_dividend->number.length()-1-i]);
        if (*binary_remainder >= *binary_divisor){
            *binary_remainder = *binary_remainder - *binary_divisor;
            binary_quotient->number.push_back('1');
        }
        else binary_quotient->number.push_back('0');
    }
    return *binary_quotient;
}

Binary& Binary::operator% (Binary& p_binary)
{
    Binary* binary_base = new Binary(shorten());
    Binary* binary_mod = new Binary(p_binary.shorten());
    Binary* binary_result = new Binary("0");
    if (binary_base->number == "" || binary_mod->number == "" || binary_mod->number == "0")
    {
        binary_result->number = "";
        return *binary_result;
    }
    else *binary_result = *binary_base - ((*binary_base / *binary_mod) * *binary_mod);
    return *binary_result;
}

Binary& Binary::operator^ (Binary& p_binary)
{
    Binary* binary_base = new Binary(shorten());
    Binary* binary_exp = new Binary(p_binary.shorten());
    Binary* binary_result = new Binary("1");
    Binary* binary_y = new Binary(*binary_base);
    if (binary_base->number == "" || binary_exp->number == ""){
        binary_result->number = "";
        return *binary_result;
    }
    else if (binary_exp->number == "0"){
        binary_result->number = "1";
        return *binary_result;
    }
    else{
        Binary* binary_tmp = new Binary("1");
        while (*binary_exp > *binary_tmp){
            if (binary_exp->number[binary_exp->number.length()-1] == '1')
                *binary_result = *binary_result * *binary_y;
            binary_exp->number.erase(binary_exp->number.length()-1,1);
            *binary_y = *binary_y * *binary_y;
        }
        *binary_result = *binary_result * *binary_y;
        return *binary_result;
    }
}

Binary& Binary::exp_mod (Binary& p_binary_exp, Binary& p_binary_mod)
{
    Binary* binary_base = new Binary(shorten());
    Binary* binary_exp = new Binary(p_binary_exp.shorten());
    Binary* binary_mod = new Binary(p_binary_mod.shorten());
    Binary* binary_result = new Binary("1");
    Binary* binary_y = new Binary(*binary_base);
    if (binary_base->number == "" || binary_exp->number == ""){
        binary_result->number = "";
        return *binary_result;
    }
    else if (binary_exp->number == "0"){
        binary_result->number = "1";
        return *binary_result;
    }
    else{
        Binary* binary_tmp = new Binary("1");
        while (*binary_exp > *binary_tmp){
            if (binary_exp->number[binary_exp->number.length()-1] == '1')
                *binary_result = (*binary_result * *binary_y) % *binary_mod;
            binary_exp->number.erase(binary_exp->number.length()-1,1);
            *binary_y = (*binary_y * *binary_y) % *binary_mod;
        }
        *binary_result = (*binary_result * *binary_y) % *binary_mod;
        return *binary_result;
    }
}

Binary& Binary::pgcd(Binary& p_binary)
{
    Binary* binary1 = new Binary(shorten());
    Binary* binary2 = new Binary(p_binary.shorten());
    if (binary1->number == "0") return *binary2;
    else if (binary2->number == "0") return *binary1;
    unsigned long shift = 0;
    while (binary1->number[binary1->number.length()-1] == '0' && binary2->number[binary2->number.length()-1] == '0'){
        binary1->number.erase(binary1->number.length()-1,1);
        binary2->number.erase(binary2->number.length()-1,1);
        shift++;
    }
    while (binary1->number[binary1->number.length()-1] == '0')
        binary1->number.erase(binary1->number.length()-1,1);
    do{
        while (binary2->number[binary2->number.length()-1] == '0')
            binary2->number.erase(binary2->number.length()-1,1);
        if (*binary1 > *binary2){
            Binary* binary_tmp = new Binary(*binary2);
            *binary2 = *binary1;
            *binary1 = *binary_tmp;
        }
        *binary2 = *binary2 - *binary1;
    } while (binary2->number != "0");
    for (unsigned long i = 0; i < shift; i++)
        binary1->number.push_back('0');
    return *binary1;
}

void Binary::bezout(Binary& p_binary, Binary& p_u, Binary& p_v, Binary& p_r, int* p_u_sign, int* p_v_sign, int* p_r_sign)
{
    Binary* binary1 = new Binary(shorten());
    Binary* binary2 = new Binary(p_binary.shorten());
    Binary* r = new Binary(*binary1);
    Binary* u = new Binary("1");
    Binary* v = new Binary("0");
    Binary* r2 = new Binary(*binary2);
    Binary* u2 = new Binary("0");
    Binary* v2 = new Binary("1");
    Binary* q = new Binary();
    Binary* rs = new Binary();
    Binary* us = new Binary();
    Binary* vs = new Binary();
    Binary* qr2 = new Binary();
    Binary* qu2 = new Binary();
    Binary* qv2 = new Binary();
    bool q_sign, u_sign, v_sign, r_sign, us_sign, vs_sign, rs_sign, u2_sign, v2_sign, r2_sign, qu2_sign, qv2_sign, qr2_sign;
    q_sign = true; u_sign = true; v_sign = true; r_sign = true; us_sign = true; vs_sign = true; rs_sign = true; u2_sign = true; v2_sign = true; r2_sign = true; qu2_sign = true; qv2_sign = true; qr2_sign = true;
    while (r2->number != "0"){
        *q = *r / *r2; q_sign = (r_sign == r2_sign);
        *rs = *r; rs_sign = r_sign;
        *us = *u; us_sign = u_sign;
        *vs = *v; vs_sign = v_sign;
        *r = *r2; r_sign = r2_sign;
        *u = *u2; u_sign = u2_sign;
        *v = *v2; v_sign = v2_sign;
        *qr2 = *q * *r2; qr2_sign = (q_sign == r2_sign);
        *qu2 = *q * *u2; qu2_sign = (q_sign == u2_sign);
        *qv2 = *q * *v2; qv2_sign = (q_sign == v2_sign);

        if (rs_sign != qr2_sign){
            *r2 = *rs + *qr2;
            r2_sign = rs_sign;
        }
        else{
            r2_sign = (*rs >= *qr2) == rs_sign;
            if (*rs >= *qr2)
                *r2 = *rs - *qr2;
            else
                *r2 = *qr2 - *rs;
        }

        if (us_sign != qu2_sign){
            *u2 = *us + *qu2;
            u2_sign = us_sign;
        }
        else{
            u2_sign = (*us >= *qu2) == us_sign;
            if (*us >= *qu2)
                *u2 = *us - *qu2;
            else
                *u2 = *qu2 - *us;
        }

        if (vs_sign != qv2_sign){
            *v2 = *vs + *qv2;
            v2_sign = vs_sign;
        }
        else{
            v2_sign = (*vs >= *qv2) == vs_sign;
            if (*vs >= *qv2)
                *v2 = *vs - *qv2;
            else
                *v2 = *qv2 - *vs;
        }
    }
    if (u_sign) *p_u_sign = 1;
    else *p_u_sign = -1;
    if (v_sign) *p_v_sign = 1;
    else *p_v_sign = -1;
    if (r_sign) *p_r_sign = 1;
    else *p_r_sign = -1;
    p_u = *u;
    p_v = *v;
    p_r = *r;
}

Binary& Binary::bezout_u(Binary& p_binary)
{
    Binary* binary2 = new Binary(p_binary.shorten());
    Binary* u = new Binary();
    Binary* v = new Binary();
    Binary* r = new Binary();
    int u_sign;
    int v_sign;
    int r_sign;
    bezout(p_binary,*u,*v,*r,&u_sign,&v_sign,&r_sign);
    if (u_sign == 1)
        return *u;
    else{
        Binary* k = new Binary("1");
        Binary* one = new Binary("1");
        while (*u > (*k * *binary2)) *k = *k + *one;
        *u = (*k * *binary2) - *u;
        return *u;
    }
}

bool Binary::fermat(unsigned long k)
{
    Binary* n = new Binary(shorten());
    if (n->number == "0" || n->number == "1") return false;
    Binary* one = new Binary("1");
    for (unsigned long i = 0; i < k; i++){
        Binary* a = new Binary(n->number.length());
        while (a->number == "0" || *a >= *n) a->random(n->number.length());
        if ( a->exp_mod(*n - *one, *n) != *one ) return false;
    }
    return true;
}

bool Binary::millerRabin(unsigned long k)
{
    Binary* n = new Binary(shorten());
    Binary* one = new Binary("1");
    Binary* two = new Binary("10");
    Binary* n_mod_two = new Binary(*n % *two);
    if (n->number == "0" || n->number == "1") return false;
    else if (n->number == "10" || n->number == "11") return true;
    else if (n_mod_two->number == "0") return false;
    Binary* s = new Binary("0");
    Binary* d = new Binary(*n - *one);
    while (d->number[d->number.length()-1] == '0'){
        *s = *s + *one;
        d->number.erase(d->number.length()-1,1);
    }
    for (unsigned long i = 0; i < k; i++){
        Binary* a = new Binary(n->number.length());
        while (a->number == "0" || *a >= *n) a->random(n->number.length());
        Binary* x = new Binary(a->exp_mod(*d,*n));
        if (*x == *one || *x == (*n - *one))
            continue;
        bool iteration = true;
        for (Binary* r = new Binary("1"); *r < *s; *r = *r + *one){
            *x = x->exp_mod(*two,*n);
            if (*x == *one)
                return false;
            if (*x == (*n - *one)){
                iteration = false;
                break;
            }
        }
        if (iteration) return false;
    }
    return true;
}

Binary& Binary::shorten()
{
    unsigned long counter = 0;
    while (number.length()-counter>1 && number[counter] == '0') counter++;
    Binary* shortened = new Binary(number.substr(counter));
    return *shortened;
}

void Binary::random(unsigned long p_length)
{
    number = "0";
    for (unsigned long i = 0; i < p_length; i++)
        if (rand()%2 == 0) number += '0';
        else number += '1';
    number = shorten().number;
}

void Binary::random_odd(unsigned long p_length)
{
    random(p_length);
    number[number.length()-1] = '1';
}

bool Binary::isBinary()
{
    for (unsigned long i = 0; i < number.length(); i++)
        if (number[i] != '0' && number[i] != '1') return false;
    return true;
}

Binary& Binary::toBinary(int p_decimal)
{
    Binary* binary = new Binary();
    binary->number = "";
    while (p_decimal != 0){
        if (p_decimal%2 == 0) binary->number = "0" + binary->number;
        else binary->number = "1" + binary->number;
        p_decimal = floor(p_decimal/2);
    }
    *binary = binary->shorten();
    return *binary;
}
