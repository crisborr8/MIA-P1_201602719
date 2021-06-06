#ifndef HEADERS_H
#define HEADERS_H
#include "Extras/Strings.cpp"

string comando, comando_inicial;
int ing_numero, i_aux;
string ing_palabra;
Strings e;

int _case;
int size, add;
string f, u, type, delet, path, name, id, fs, usr, pwd, grp, ugo, cont, dest, ruta;
bool r, p;

class Menu{
    private:
        void Mostrar_Menu();
        void Comando();
    public:
        Menu();
};

class Verificar{
    public:
        bool Ver_F();
        bool Ver_U();
        bool Ver_U2();
        bool Ver_Fs();
        bool Ver_Id();
        bool Ver_Add();
        bool Ver_Usr();
        bool Ver_Pwd();
        bool Ver_Name();
        bool Ver_Size();
        bool Ver_Path();
        bool Ver_Type();
        bool Ver_Type2();
        bool Ver_Delet();

        bool Ver_Usr2();
        bool Ver_Pwd2();
        bool Ver_Grp();
        bool Ver_Path2();
        bool Ver_Ugo();
        bool Ver_Path3();
        bool Ver_Size2();
        bool Ver_Cont();
        bool Ver_Dest();
        bool Ver_Path4();
};
class Ingresar{
    private:
        string blanco = " \t\f\v\n\r";
    public:
        bool Ing_Numero(string c);
        bool Ing_Comando(string c);
        bool Ing_Palabra(string c);
        bool Ing_PalabraC(string c);
        bool Ing_PalabraF(string c);
        bool Ing_Error();
};

struct Files{
    int numero;
    string file;
    Files* next;
};

class Comandos{
    protected:
        bool error;
        Ingresar i;
        Verificar v;
};

class Cat: public Comandos{
    private:
        Files *file_n;
        void Ejecutar();
        bool Ingresar_Datos();
        bool Verificar_Datos();
        void Add_File();
    public:
        void Inicializar();
};
class Chgrp: public Comandos{
    private:
        void Ejecutar();
        bool Ingresar_Datos();
        bool Verificar_Datos();
    public:
        void Inicializar();
};
class Chmod: public Comandos{
    private:
        void Ejecutar();
        bool Ingresar_Datos();
        bool Verificar_Datos();
    public:
        void Inicializar();
};
class Chown: public Comandos{
    private:
        void Ejecutar();
        bool Ingresar_Datos();
        bool Verificar_Datos();
    public:
        void Inicializar();
};
class Cp: public Comandos{
    private:
        void Ejecutar();
        bool Ingresar_Datos();
        bool Verificar_Datos();
    public:
        void Inicializar();
};
class Edit: public Comandos{
    private:
        void Ejecutar();
        bool Ingresar_Datos();
        bool Verificar_Datos();
    public:
        void Inicializar();
};
class Exec: public Comandos{
    private:
        void Ejecutar();
        bool Ingresar_Datos();
        bool Verificar_Datos();
    public:
        void Inicializar();
};
class Fdisk: public Comandos{
    private:
        void Ejecutar();
        bool Ingresar_Datos();
        bool Verificar_Datos();
    public:
        void Inicializar();
};
class Find: public Comandos{
    private:
        void Ejecutar();
        bool Ingresar_Datos();
        bool Verificar_Datos();
    public:
        void Inicializar();
};
class Login: public Comandos{
    private:
        void Ejecutar();
        bool Ingresar_Datos();
        bool Verificar_Datos();
    public:
        void Inicializar();
};
class Logout: public Comandos{
    private:
        void Ejecutar();
        bool Ingresar_Datos();
        bool Verificar_Datos();
    public:
        void Inicializar();
};
class Mkdir: public Comandos{
    private:
        void Ejecutar();
        bool Ingresar_Datos();
        bool Verificar_Datos();
    public:
        void Inicializar();
};
class Mkdisk: public Comandos{
    private:
        void Ejecutar();
        bool Ingresar_Datos();
        bool Verificar_Datos();
    public:
        void Inicializar();
};
class Mkfile: public Comandos{
    private:
        void Ejecutar();
        bool Ingresar_Datos();
        bool Verificar_Datos();
    public:
        void Inicializar();
};
class Mkfs: public Comandos{
    private:
        void Ejecutar();
        bool Ingresar_Datos();
        bool Verificar_Datos();
    public:
        void Inicializar();
};
class Mkgrp: public Comandos{
    private:
        void Ejecutar();
        bool Ingresar_Datos();
        bool Verificar_Datos();
    public:
        void Inicializar();
};
class Mkusr: public Comandos{
    private:
        void Ejecutar();
        bool Ingresar_Datos();
        bool Verificar_Datos();
    public:
        void Inicializar();
};
class Mount: public Comandos{
    private:
        void Ejecutar();
        bool Ingresar_Datos();
        bool Verificar_Datos();
    public:
        void Inicializar();
};
class Mv: public Comandos{
    private:
        void Ejecutar();
        bool Ingresar_Datos();
        bool Verificar_Datos();
    public:
        void Inicializar();
};
class Pause: public Comandos{
    private:
        void Ejecutar();
        bool Ingresar_Datos();
        bool Verificar_Datos();
    public:
        void Inicializar();
};
class Rem: public Comandos{
    private:
        void Ejecutar();
        bool Ingresar_Datos();
        bool Verificar_Datos();
    public:
        void Inicializar();
};
class Ren: public Comandos{
    private:
        void Ejecutar();
        bool Ingresar_Datos();
        bool Verificar_Datos();
    public:
        void Inicializar();
};
class Rep: public Comandos{
    private:
        void Ejecutar();
        bool Ingresar_Datos();
        bool Verificar_Datos();
    public:
        void Inicializar();
};
class Rmdisk: public Comandos{
    private:
        void Ejecutar();
        bool Ingresar_Datos();
        bool Verificar_Datos();
    public:
        void Inicializar();
};
class Rmgrp: public Comandos{
    private:
        void Ejecutar();
        bool Ingresar_Datos();
        bool Verificar_Datos();
    public:
        void Inicializar();
};
class Rmusr: public Comandos{
    private:
        void Ejecutar();
        bool Ingresar_Datos();
        bool Verificar_Datos();
    public:
        void Inicializar();
};
class Unmount: public Comandos{
    private:
        void Ejecutar();
        bool Ingresar_Datos();
        bool Verificar_Datos();
    public:
        void Inicializar();
};

#endif