#include "../Headers.h"

void Mkdisk::Inicializar(){
    error = false;
    
    path = "";
    size = 0;
    f = "ff";
    u = "m";

    if(!Ingresar_Datos()) 
        if(Verificar_Datos()) 
            Ejecutar();
}

bool Mkdisk::Ingresar_Datos(){
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

bool Mkdisk::Verificar_Datos(){
    if(v.Ver_Size())
    if(v.Ver_Path())
    if(v.Ver_F())
    if(v.Ver_U())
    return true;
    return false;
}

void Mkdisk::Ejecutar(){
    cout << "ejecutando" << endl;
    cout << "f: " << f << endl;
    cout << "u: " << u << endl;
    cout << "path: " << path << endl;
    cout << "size: " << size << endl;
}