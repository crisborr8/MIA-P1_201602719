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
struct Monunts{

};

FILE *archivo;
struct MBR mbr;
struct EBR ebr;
struct Particion part;

class Menu{
    private:
        void Mostrar_Menu();
    public:
        void Comando();
        void Menu_Principal();
}me;

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

class Cat_: public Comandos{
    private:
        Files *file_n;
        void Ejecutar();
        bool Ingresar_Datos();
        bool Verificar_Datos();
        void Add_File();
    public:
        void Inicializar();
};
class Chgrp_: public Comandos{
    private:
        void Ejecutar();
        bool Ingresar_Datos();
        bool Verificar_Datos();
    public:
        void Inicializar();
};
class Chmod_: public Comandos{
    private:
        void Ejecutar();
        bool Ingresar_Datos();
        bool Verificar_Datos();
    public:
        void Inicializar();
};
class Chown_: public Comandos{
    private:
        void Ejecutar();
        bool Ingresar_Datos();
        bool Verificar_Datos();
    public:
        void Inicializar();
};
class Cp_: public Comandos{
    private:
        void Ejecutar();
        bool Ingresar_Datos();
        bool Verificar_Datos();
    public:
        void Inicializar();
};
class Edit_: public Comandos{
    private:
        void Ejecutar();
        bool Ingresar_Datos();
        bool Verificar_Datos();
    public:
        void Inicializar();
};
class Exec_: public Comandos{
    private:
        void Ejecutar();
        bool Ingresar_Datos();
        bool Verificar_Datos();
    public:
        void Inicializar();
};
class Fdisk_: public Comandos{
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
        void Ordernar_MBR();
        void testing();

    public:
        void Inicializar();
};
class Find_: public Comandos{
    private:
        void Ejecutar();
        bool Ingresar_Datos();
        bool Verificar_Datos();
    public:
        void Inicializar();
};
class Login_: public Comandos{
    private:
        void Ejecutar();
        bool Ingresar_Datos();
        bool Verificar_Datos();
    public:
        void Inicializar();
};
class Logout_: public Comandos{
    private:
        void Ejecutar();
        bool Ingresar_Datos();
        bool Verificar_Datos();
    public:
        void Inicializar();
};
class Mkdir_: public Comandos{
    private:
        void Ejecutar();
        bool Ingresar_Datos();
        bool Verificar_Datos();
    public:
        void Inicializar();
};
class Mkdisk_: public Comandos{
    private:
        void Ejecutar();
        bool Ingresar_Datos();
        bool Verificar_Datos();

        void SetMBR();
        void CrearDisco();
    public:
        void Inicializar();
};
class Mkfile_: public Comandos{
    private:
        void Ejecutar();
        bool Ingresar_Datos();
        bool Verificar_Datos();
    public:
        void Inicializar();
};
class Mkfs_: public Comandos{
    private:
        void Ejecutar();
        bool Ingresar_Datos();
        bool Verificar_Datos();
    public:
        void Inicializar();
};
class Mkgrp_: public Comandos{
    private:
        void Ejecutar();
        bool Ingresar_Datos();
        bool Verificar_Datos();
    public:
        void Inicializar();
};
class Mkusr_: public Comandos{
    private:
        void Ejecutar();
        bool Ingresar_Datos();
        bool Verificar_Datos();
    public:
        void Inicializar();
};
class Mount_: public Comandos{
    private:
        void Ejecutar();
        bool Ingresar_Datos();
        bool Verificar_Datos();
    public:
        void Inicializar();
};
class Mv_: public Comandos{
    private:
        void Ejecutar();
        bool Ingresar_Datos();
        bool Verificar_Datos();
    public:
        void Inicializar();
};
class Pause_: public Comandos{
    private:
        void Ejecutar();
        bool Ingresar_Datos();
        bool Verificar_Datos();
    public:
        void Inicializar();
};
class Rem_: public Comandos{
    private:
        void Ejecutar();
        bool Ingresar_Datos();
        bool Verificar_Datos();
    public:
        void Inicializar();
};
class Ren_: public Comandos{
    private:
        void Ejecutar();
        bool Ingresar_Datos();
        bool Verificar_Datos();
    public:
        void Inicializar();
};
class Rep_: public Comandos{
    private:
        void Ejecutar();
        bool Ingresar_Datos();
        bool Verificar_Datos();
    public:
        void Inicializar();
};
class Rmdisk_: public Comandos{
    private:
        void Ejecutar();
        bool Ingresar_Datos();
        bool Verificar_Datos();
    public:
        void Inicializar();
};
class Rmgrp_: public Comandos{
    private:
        void Ejecutar();
        bool Ingresar_Datos();
        bool Verificar_Datos();
    public:
        void Inicializar();
};
class Rmusr_: public Comandos{
    private:
        void Ejecutar();
        bool Ingresar_Datos();
        bool Verificar_Datos();
    public:
        void Inicializar();
};
class Unmount_: public Comandos{
    private:
        void Ejecutar();
        bool Ingresar_Datos();
        bool Verificar_Datos();
    public:
        void Inicializar();
};

#endif