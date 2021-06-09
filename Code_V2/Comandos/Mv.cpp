#include "../Headers.h"

void Mv_::Inicializar(){
    error = false;

    path = "";
    dest = "";

    if(!Ingresar_Datos()) 
        if(Verificar_Datos()) 
            Ejecutar();
}

bool Mv_::Ingresar_Datos(){
    while(comando.length() > 0){
        comando_inicial = e.slower(comando);
        if(comando_inicial.find("-path=") == 0){
            error = i.Ing_PalabraC("-path=");
            if(error) break;
            path = ing_palabra;
        } else if(comando_inicial.find("-dest=") == 0){
            error = i.Ing_PalabraC("-dest=");
            if(error) break;
            dest = ing_palabra;
        }
        else{
            error = i.Ing_Error();
            break;
        } 
    }
    return error;
}

bool Mv_::Verificar_Datos(){
    error = true;
    if(v.Ver_Path2()) error = false;
    if(!v.Ver_Dest()) error = true;
    return !error;
}

void Mv_::Ejecutar(){
    
}