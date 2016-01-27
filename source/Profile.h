#ifndef PROFILE_H
#define PROFILE_H

#include <string>
#include <stdlib.h>
#include <iostream>
#include <utility>
#include <sstream>
#include "Binary.h"
#include <QDebug>

#define DEFAULT_KEYSIZE 8

using namespace std;

class Profile
{

    public:
        string name;
        unsigned long keySize;
        pair<Binary*,Binary*> publicKey;
        pair<Binary*,Binary*> privateKey;
        Profile();
        Profile(string p_name, unsigned long p_keySize);
        Profile(string p_name, unsigned long p_keySize, pair<Binary*,Binary*> p_publicKey);
        Profile(string p_name, unsigned long p_keySize, pair<Binary*,Binary*> p_publicKey, pair<Binary*,Binary*> p_privateKey);
        virtual ~Profile();
        void createKeys();
        string encryptText(string p_text);
        string decryptText(string p_text);
        Binary* P;
        Binary* Q;
        Binary* N;
        Binary* M;
        Binary* C;
        Binary* U;
        void createPublicKey();
        void createPrivateKey();
    protected:
    private:

};

#endif // PROFILE_H
