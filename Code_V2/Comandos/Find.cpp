#include "../Headers.h"

void Find::Inicializar(){
    error = false;

    path = "";
    name = "";

    if(!Ingresar_Datos()) 
        if(Verificar_Datos()) 
            Ejecutar();
}

bool Find::Ingresar_Datos(){
    while(comando.length() > 0){
        comando_inicial = e.slower(comando);
        if(comando_inicial.find("-path=") == 0){
            error = i.Ing_PalabraC("-path=");
            if(error) break;
            path = ing_palabra;
        } else if(comando_inicial.find("-name=") == 0){
            error = i.Ing_PalabraC("-name=");
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

bool Find::Verificar_Datos(){
    if(v.Ver_Path2())
    if(v.Ver_Name())
    return true;
    return false;
}

void Find::Ejecutar(){
    
}