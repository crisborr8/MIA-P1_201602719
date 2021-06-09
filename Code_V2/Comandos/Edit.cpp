#include "../Headers.h"

void Edit_::Inicializar(){
    error = false;

    path = "";
    cont = "";

    if(!Ingresar_Datos()) 
        if(Verificar_Datos()) 
            Ejecutar();
}

bool Edit_::Ingresar_Datos(){
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

bool Edit_::Verificar_Datos(){
    error = true;
    if(v.Ver_Cont()) error = false;
    if(!v.Ver_Path3()) error = true;
    return !error;
}

void Edit_::Ejecutar(){
    
}