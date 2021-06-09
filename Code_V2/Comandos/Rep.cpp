#include "../Headers.h"

void Rep_::Inicializar(){
    error = false;

    name = "";
    path = "";
    id = "";
    ruta = "";

    if(!Ingresar_Datos()) 
        if(Verificar_Datos()) 
            Ejecutar();
}

bool Rep_::Ingresar_Datos(){
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

bool Rep_::Verificar_Datos(){
    error = true;
    if(v.Ver_Path2()) error = false;
    if(!v.Ver_Id()) error = true;
    if(!v.Ver_Name()) error = true;
    return !error;
}

void Rep_::Ejecutar(){
    
}