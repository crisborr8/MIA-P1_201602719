#include "../Headers.h"

void Chown_::Inicializar(){
    error = false;

    path = "";
    r = false;
    usr = "";

    if(!Ingresar_Datos()) 
        if(Verificar_Datos()) 
            Ejecutar();
}

bool Chown_::Ingresar_Datos(){
    while(comando.length() > 0){
        comando_inicial = e.slower(comando);
        if(comando_inicial.find("-path=") == 0){
            error = i.Ing_PalabraC("-path=");
            if(error) break;
            path = ing_palabra;
        }
        else if(comando_inicial.find("-usr=") == 0){
            error = i.Ing_PalabraC("-usr=");
            if(error) break;
            path = ing_palabra;
        }
        else if(comando_inicial.find("-r ") == 0){
            error = i.Ing_Comando("-r ");
            if(error) break;
            r = true;
        }
        else{
            error = i.Ing_Error();
            break;
        } 
    }
    return error;
}

bool Chown_::Verificar_Datos(){
    error = true;
    if(v.Ver_Path2()) error = false;
    if(!v.Ver_Usr()) error = true;
    return !error;
}

void Chown_::Ejecutar(){
    
}