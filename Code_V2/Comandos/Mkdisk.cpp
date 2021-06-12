#include "../Headers.h"
#include <sys/stat.h> 

void Mkdisk_::Inicializar(){
    error = false;
    
    path = "";
    size = 0;
    f = "ff";
    u = "m";

    if(!Ingresar_Datos()) 
        if(Verificar_Datos()) 
            Ejecutar();
}

bool Mkdisk_::Ingresar_Datos(){
    while(comando.length() > 0){
        comando_inicial = e.slower(comando);
        if(comando_inicial.find("-f=") == 0){
            error = i.Ing_Palabra("-f=");
            if(error) break;
            f = ing_palabra;
        } 
        else if(comando_inicial.find("-u=") == 0){
            error = i.Ing_Palabra("-u=");
            if(error) break;
            u = ing_palabra;
        }
        else if(comando_inicial.find("-path=") == 0){
            error = i.Ing_PalabraC("-path=");
            if(error) break;
            path = ing_palabra;
        }
        else if(comando_inicial.find("-size=") == 0){
            error = i.Ing_Numero("-size=");
            if(error) break;
            size = ing_numero;
        }
        else{
            error = i.Ing_Error();
            break;
        }
    }
    return error;
}

bool Mkdisk_::Verificar_Datos(){
    error = true;
    if(v.Ver_Size()) error = false;
    if(!v.Ver_Path()) error = true;
    if(!v.Ver_F()) error = true;
    if(!v.Ver_U()) error = true;
    return !error;
}

void Mkdisk_::Ejecutar(){
    if(!ex.Ex_Path_File(path)){
        mkdir(path.substr(0, path.find_last_of('/')).c_str(), 0777);
        gs.SetMBR();
        CrearDisco();
    }
    else cout << "ERROR!! Archivo ya existe" << endl;
}

void Mkdisk_::CrearDisco(){
    archivo = NULL;
    archivo = fopen(path.c_str(), "w+b");
    fseek(archivo, size, SEEK_SET);
    fputc('\0', archivo);
    fclose(archivo);

    archivo = fopen(path.c_str(), "r+b");
    fseek(archivo, 0, SEEK_SET);
    fwrite(&mbr, sizeof(mbr), 1, archivo);
    fclose(archivo);

    cout << "Disco creado con exito!" << endl;
}