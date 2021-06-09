#include "../Headers.h"

void Rem_::Inicializar(){
    error = false;

    path = "";

    if(!Ingresar_Datos()) 
        if(Verificar_Datos()) 
            Ejecutar();
}

bool Rem_::Ingresar_Datos(){
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

bool Rem_::Verificar_Datos(){
    error = true;
    if(v.Ver_Path2()) error = false;
    return !error;
}

void Rem_::Ejecutar(){
    
}