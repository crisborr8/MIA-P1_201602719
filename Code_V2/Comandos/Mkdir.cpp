#include "../Headers.h"

void Mkdir_::Inicializar(){
    error = false;

    path = "";
    p = false;

    if(!Ingresar_Datos()) 
        if(Verificar_Datos()) 
            Ejecutar();
}

bool Mkdir_::Ingresar_Datos(){
    while(comando.length() > 0){
        comando_inicial = e.slower(comando);
        if(comando_inicial.find("-path=") == 0){
            error = i.Ing_PalabraC("-path=");
            if(error) break;
            path = ing_palabra;
        }
        else if(comando_inicial.find("-p ") == 0){
            error = i.Ing_Comando("-p ");
            if(error) break;
            p = true;
        }
        else{
            error = i.Ing_Error();
            break;
        } 
    }
    return error;
}

bool Mkdir_::Verificar_Datos(){
    error = true;
    if(v.Ver_Path2()) error = false;
    return !error;
}

void Mkdir_::Ejecutar(){
    
}