#ifndef STRINGS_H
#define STRINGS_H

#include <iostream>
#include <string.h>
using namespace std;

class Strings{
    public:
        string trim(string s);
        string trimL(string s);
        string trimR(string s);

        string slower(string s);
        char clower(char c);
};

#endif