#include "../Headers.h"

void Cp::Inicializar(){
    error = false;

    path = "";
    dest = "";

    if(!Ingresar_Datos()) 
        if(Verificar_Datos()) 
            Ejecutar();
}

bool Cp::Ingresar_Datos(){
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

bool Cp::Verificar_Datos(){
    if(v.Ver_Path2())
    if(v.Ver_Dest())
    return true;
    return false;
}

void Cp::Ejecutar(){
    
}