#ifndef EDIT_H
#define EDIT_H

#include <iostream>
#include <string.h>
using namespace std;

class Edit{
    public:
        string trim(string s);
        string trimL(string s);
        string trimR(string s);

        string slower(string s);
        char clower(char c);
};

#endif