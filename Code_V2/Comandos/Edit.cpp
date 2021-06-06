#include "../Headers.h"

void Edit::Inicializar(){
    error = false;

    path = "";
    cont = "";

    if(!Ingresar_Datos()) 
        if(Verificar_Datos()) 
            Ejecutar();
}

bool Edit::Ingresar_Datos(){
    while(comando.length() > 0){
        comando_inicial = e.slower(comando);
        if(comando_inicial.find("-path=") == 0){
            error = i.Ing_PalabraC("-path=");
            if(error) break;
            path = ing_palabra;
        }
        else if(comando_inicial.find("-cont=") == 0){
            error = i.Ing_PalabraC("-cont=");
            if(error) break;
            cont = ing_palabra;
        }
        else{
            error = i.Ing_Error();
            break;
        } 
    }
    return error;
}

bool Edit::Verificar_Datos(){
    if(v.Ver_Cont())
    if(v.Ver_Path3())
    return true;
    return false;
}

void Edit::Ejecutar(){
    
}