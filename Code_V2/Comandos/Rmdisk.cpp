#include "../Headers.h"

void Rmdisk::Inicializar(){
    error = false;
    
    path = "";

    if(!Ingresar_Datos()) 
        if(Verificar_Datos()) 
            Ejecutar();
}

bool Rmdisk::Ingresar_Datos(){
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

bool Rmdisk::Verificar_Datos(){
    if(v.Ver_Path())
    return true;
    return false;
}

void Rmdisk::Ejecutar(){
    cout << "ejecutando rmdisk" << endl;
    cout << "path: " << path << endl;
}