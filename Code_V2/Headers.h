#ifndef HEADERS_H
#define HEADERS_H
#include "Extras/Strings.cpp"
#include "Extras/Structs.cpp"
#include <fstream>

string comando, comando_inicial;
int ing_numero, i_aux;
string ing_palabra;
Strings e;

int _case;
bool r, p;
int size, add;
string f, u, type, delet, path, name, id, fs, usr, pwd, grp, ugo, cont, dest, ruta;

int f_start, f_sizeMax;

FILE *archivo;
Str::Montura *montura;
Str::MBR mbr;
Str::EBR ebr;
Str::Particion part;
Str::Inodos inodos;
Str::Superbloque superbloque;
Str::Journaling journaling;
Str::Bloques_carpeta bloques_carpeta;
Str::Bloques_archivo bloques_archivo;
Str::Bloques_apuntad bloques_apuntad;
Str::Bloques_content bloques_content;

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
        bool Ver_Path5();
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
        bool Ex_Montura(string name, string path);
        bool Ex_MonturaId(string id);
};
class Get_Set{
    public:
        int Get_esp_dispPE(int start);
        int Get_esp_dispL(int start);
        string Get_Date(time_t fecha);
        void Ordernar_MBR();
        void SetMBR();
        void SetSuperBloque(int partition_size, int filesystem_type);
        Str::Montura* Get_Mount(string id);
};

class Comandos{
    protected:
        bool error;
        Get_Set gs;
        Existe ex;
        Ingresar i;
        Verificar v;
};

class Cat_: public Comandos{
    private:
        Str::Files *file_n;
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
        string dot;
        void Ejecutar();
        bool Ingresar_Datos();
        bool Verificar_Datos();
        void Graph_mbr();
        void Graph_disk();
        void Graph_inode();
        void Graph_journaling();
        void Graph_block();
        void Graph_bm_inode();
        void Graph_bm_block();
        void Graph_tree();
        void Graph_sb();
        void Graph_file();
        void Graph_ls();
        bool Graficar();
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