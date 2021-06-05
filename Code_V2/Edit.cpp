#include "Edit.h"

string Edit::trim(string s){
    return trimL(trimR(s));
}
string Edit::trimL(string s){
    while(s.length() > 0){
        if(s[0] == ' ' || s[0] == '\t' ||s[0] == '\f' ||s[0] == '\v' ||s[0] == '\n' ||s[0] == '\r')
            s = s.substr(1, s.length());
        else break;
    }
    return s;
}
string Edit::trimR(string s){
    int i;
    while(s.length() > 0){
        i = s.length() - 1;
        if(s[i] == ' ' || s[i] == '\t' ||s[i] == '\f' ||s[i] == '\v' ||s[i] == '\n' ||s[i] == '\r')
            s = s.substr(0, i);
        else break;
    }
    return s;
}

string Edit::slower(string s){
    for(int i = 0; i < s.length(); i++)
        s[i] = clower(s[i]);
    return s;
}
char Edit::clower(char c){
    if(c <='Z' && c >= 'A')
        return c - ('Z' - 'z');
    return c;
}