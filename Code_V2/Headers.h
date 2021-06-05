#ifndef HEADERS_H
#define HEADERS_H
#include "Edit.cpp"

Edit e;
string blanco = " \t\f\v\n\r";
string comando, comando_inicial, ing_palabra;
int ing_numero, i_aux;
bool error;

int size;
string f, u;
string path;


class Menu{
    private:
        void Mostrar_Menu();
        void Comando();
    public:
        Menu();
};

class Verificar{
    public:
        bool Ver_Size();
        bool Ver_F();
        bool Ver_U();
        bool Ver_Path();
};
class Ingresar{
    public:
        bool Ing_Palabra(string c);
        bool Ing_Numero(string c);
        bool Ing_Char(string c);
        bool Ing_Error();
};

class Comandos{
    protected:
        Ingresar i;
        Verificar v;
};

class Mkdisk: public Comandos{
    public:
        void Inicializar();
    private:
        bool Ingresar_Datos();
        bool Verificar_Datos();
        void Ejecutar();
};

#endif