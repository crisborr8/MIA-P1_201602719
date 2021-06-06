#include "../Headers.h"

void Rem::Inicializar(){
    error = false;

    path = "";

    if(!Ingresar_Datos()) 
        if(Verificar_Datos()) 
            Ejecutar();
}

bool Rem::Ingresar_Datos(){
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

bool Rem::Verificar_Datos(){
    if(v.Ver_Path2())
    return false;
}

void Rem::Ejecutar(){
    
}