#include "../Headers.h"

void Chown::Inicializar(){
    error = false;

    path = "";
    r = false;
    usr = "";

    if(!Ingresar_Datos()) 
        if(Verificar_Datos()) 
            Ejecutar();
}

bool Chown::Ingresar_Datos(){
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

bool Chown::Verificar_Datos(){
    if(v.Ver_Path2())
    if(v.Ver_Usr())
    return true;
    return false;
}

void Chown::Ejecutar(){
    
}