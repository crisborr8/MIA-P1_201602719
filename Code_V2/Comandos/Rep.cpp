#include "../Headers.h"

void Rep::Inicializar(){
    error = false;

    name = "";
    path = "";
    id = "";
    ruta = "";

    if(!Ingresar_Datos()) 
        if(Verificar_Datos()) 
            Ejecutar();
}

bool Rep::Ingresar_Datos(){
    while(comando.length() > 0){
        comando_inicial = e.slower(comando);
        if(comando_inicial.find("-path=") == 0){
            error = i.Ing_PalabraC("-path=");
            if(error) break;
            path = ing_palabra;
        } else if(comando_inicial.find("-name=") == 0){
            error = i.Ing_PalabraC("-name=");
            if(error) break;
            name = ing_palabra;
        } else if(comando_inicial.find("-id=") == 0){
            error = i.Ing_Palabra("-id=");
            if(error) break;
            id = ing_palabra;
        } else if(comando_inicial.find("-ruta=") == 0){
            error = i.Ing_PalabraC("-ruta=");
            if(error) break;
            ruta = ing_palabra;
        }
        else{
            error = i.Ing_Error();
            break;
        } 
    }
    return error;
}

bool Rep::Verificar_Datos(){
    if(v.Ver_Path2())
    if(v.Ver_Id())
    if(v.Ver_Name())
    return true;
    return false;
}

void Rep::Ejecutar(){
    
}