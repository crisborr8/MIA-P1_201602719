#ifndef HEADERS_H
#define HEADERS_H
#include "Extras/Strings.cpp"
#include <ctime>
#include <chrono>
#include <fstream>

string comando, comando_inicial;
int ing_numero, i_aux;
string ing_palabra;
Strings e;

int _case;
int size, add;
string f, u, type, delet, path, name, id, fs, usr, pwd, grp, ugo, cont, dest, ruta;
bool r, p;

int f_start, f_sizeMax;

struct Files{
    int numero;
    string file;
    Files* next;
};
struct Particion{
    char status;
    char type;
    char fit;
    int start;
    int size;
    char name[16];
};
struct EBR{
    char status;
    char fit;
    int start;
    int size;
    int next;
    char name[16];
};
struct MBR{
    int size;
    time_t date;
    int signature;
    char fit;
    Particion p[4];
};

FILE *archivo;
struct MBR mbr;
struct EBR ebr;
struct Particion part;

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
        bool Ver_Grp();
        bool Ver_Ugo();
        bool Ver_Usr();
        bool Ver_Pwd();
        bool Ver_Usr2();
        bool Ver_Pwd2();
        bool Ver_Cont();
        bool Ver_Dest();
        bool Ver_Name();
        bool Ver_Size();
        bool Ver_Path();
        bool Ver_Type();
        bool Ver_Type2();
        bool Ver_Delet();
        bool Ver_Size2();
        bool Ver_Path2();
        bool Ver_Path3();
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
class Existe{
    public:
        bool Ex_Path_File(string path);
        bool Ex_Path_Folder(string path);
        bool Ex_Name(string name, string path);
};

class Comandos{
    protected:
        bool error;
        Existe ex;
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
        void Crear();
        void Crear_Particion();
        void Crear_VerEspacio();
        void Eliminar();
        void Agregar();
        int Get_esp_dispPE(int start);
        int Get_esp_dispL(int start);
        void testing();

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

        void SetMBR();
        void CrearDisco();
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