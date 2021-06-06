#include "../Headers.h"

void Mkdir::Inicializar(){
    error = false;

    path = "";
    p = false;

    if(!Ingresar_Datos()) 
        if(Verificar_Datos()) 
            Ejecutar();
}

bool Mkdir::Ingresar_Datos(){
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

bool Mkdir::Verificar_Datos(){
    if(v.Ver_Path2())
    return true;
    return false;
}

void Mkdir::Ejecutar(){
    
}