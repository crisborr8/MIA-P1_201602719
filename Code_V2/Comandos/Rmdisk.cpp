#include "../Headers.h"

void Rmdisk_::Inicializar(){
    error = false;
    
    path = "";

    if(!Ingresar_Datos()) 
        if(Verificar_Datos()) 
            Ejecutar();
}

bool Rmdisk_::Ingresar_Datos(){
    while(comando.length() > 0){
        comando_inicial = e.slower(comando);
        if(comando_inicial.find("-path=") == 0){
            error = i.Ing_PalabraC("-path=");
            if(error) break;
            path = ing_palabra;
        }
        else{
            error = i.Ing_Error();
            break;
        }
    }
    return error;
}

bool Rmdisk_::Verificar_Datos(){
    error = true;
    if(v.Ver_Path()) error = false;
    return !error;
}

void Rmdisk_::Ejecutar(){
    if(ex.Ex_Path_File(path)){
        remove(path.c_str());
        cout << "Removido con éxito" << endl;
    }
    else cout << "ERROR!! Archivo no existe" << endl;
}