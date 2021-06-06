#include "../Headers.h"

void Chmod::Inicializar(){
    error = false;

    path = "";
    ugo = "";
    r = false;

    if(!Ingresar_Datos()) 
        if(Verificar_Datos()) 
            Ejecutar();
}

bool Chmod::Ingresar_Datos(){
    while(comando.length() > 0){
        comando_inicial = e.slower(comando);
        if(comando_inicial.find("-path=") == 0){
            error = i.Ing_PalabraC("-path=");
            if(error) break;
            path = ing_palabra;
        }
        else if(comando_inicial.find("-ugo=") == 0){
            error = i.Ing_Palabra("-ugo=");
            if(error) break;
            ugo = ing_palabra;
        }
        else if(comando_inicial.find("-r ") == 0){
            error = i.Ing_Comando("-r ");
            if(error) break;
            r = true;
        }
        else{
            error = i.Ing_Error();
            break;
        } 
    }
    return error;
}

bool Chmod::Verificar_Datos(){
    if(v.Ver_Path2())
    if(v.Ver_Ugo())
    return true;
    return false;
}

void Chmod::Ejecutar(){
    
}