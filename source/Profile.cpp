#include "Profile.h"

Profile::Profile()
{
    //ctor
    name = "";
    keySize = DEFAULT_KEYSIZE;
    publicKey.first = new Binary();
    publicKey.second = new Binary();
    privateKey.first = new Binary();
    privateKey.second = new Binary();
    P = new Binary();
    Q = new Binary();
    N = new Binary();
    M = new Binary();
    C = new Binary();
    U = new Binary();
}

Profile::Profile(string p_name, unsigned long p_keySize)
{
    //ctor
    name = p_name;
    keySize = p_keySize;
    publicKey.first = new Binary();
    publicKey.second = new Binary();
    privateKey.first = new Binary();
    privateKey.second = new Binary();
    P = new Binary();
    Q = new Binary();
    N = new Binary();
    M = new Binary();
    C = new Binary();
    U = new Binary();
}

Profile::Profile(string p_name, unsigned long p_keySize, pair<Binary*,Binary*> p_publicKey)
{
    //ctor
    name = p_name;
    keySize = p_keySize;
    publicKey.first = new Binary();
    publicKey.second = new Binary();
    privateKey.first = new Binary();
    privateKey.second = new Binary();
    P = new Binary();
    Q = new Binary();
    N = new Binary();
    M = new Binary();
    C = new Binary();
    U = new Binary();
    *publicKey.first = *p_publicKey.first;
    *publicKey.second = *p_publicKey.second;
}

Profile::Profile(string p_name, unsigned long p_keySize, pair<Binary*,Binary*> p_publicKey, pair<Binary*,Binary*> p_privateKey)
{
    //ctor
    name = p_name;
    keySize = p_keySize;
    publicKey.first = new Binary();
    publicKey.second = new Binary();
    privateKey.first = new Binary();
    privateKey.second = new Binary();
    P = new Binary();
    Q = new Binary();
    N = new Binary();
    M = new Binary();
    C = new Binary();
    U = new Binary();
    *publicKey.first = *p_publicKey.first;
    *publicKey.second = *p_publicKey.second;
    *privateKey.first = *p_privateKey.first;
    *privateKey.second = *p_privateKey.second;
}

Profile::~Profile()
{
    //dtor
}

void Profile::createKeys(){
    createPublicKey();
    createPrivateKey();
}

void Profile::createPublicKey()
{
    Binary* one = new Binary("1");
    do{
        P->random_odd(keySize);
    } while (P->millerRabin(max(2.0,floor(keySize/8))) == false || P->fermat(max(2.0,floor(keySize/8))) == false);
    do{
        Q->random_odd(keySize);
    } while (Q->millerRabin(max(2.0,floor(keySize/8))) == false || Q->fermat(max(2.0,floor(keySize/8))) == false);
    *N = *P * *Q;
    *M = (*P - *one) * (*Q - *one);
    do{
        C->random_odd(keySize);
    } while (C->pgcd(*M) != *one);
    *publicKey.first = *C;
    *publicKey.second = *N;
}

void Profile::createPrivateKey()
{
    *U = C->bezout_u(*M);
    *privateKey.first = *U;
    *privateKey.second = *N;
}

string Profile::encryptText(string p_text)
{
    string encryptedText = "";
    for (unsigned long i = 0; i < p_text.length(); i++){
        Binary* character = new Binary();
        *character = Binary::toBinary((int)p_text[i]);
        *character = character->exp_mod(*publicKey.first,*publicKey.second);
        encryptedText += character->number + "-";
    }
    encryptedText.erase(encryptedText.length()-1,1);
    return encryptedText;
}

string Profile::decryptText(string p_text)
{
    string decryptedText = "";
    string char_number;
    stringstream ss(p_text);
    while(getline(ss, char_number,'-')){
        Binary* character = new Binary(char_number);
        *character = character->exp_mod(*privateKey.first,*privateKey.second);
        int decimal = 0;
        for (unsigned int i = 0; i < character->number.length(); i++){
            if (character->number[character->number.length()-1-i] == '1') decimal += pow(2,i);
        }
        decryptedText += (char)decimal;
    }
    return decryptedText;
}
