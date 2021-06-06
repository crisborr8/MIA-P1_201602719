#include "../Headers.h"

void Mkfile::Inicializar(){
    error = false;

    path = "";
    r = false;
    size = 0;
    cont = "";

    if(!Ingresar_Datos()) 
        if(Verificar_Datos()) 
            Ejecutar();
}

bool Mkfile::Ingresar_Datos(){
    while(comando.length() > 0){
        comando_inicial = e.slower(comando);
        if(comando_inicial.find("-path=") == 0){
            error = i.Ing_PalabraC("-path=");
            if(error) break;
            path = ing_palabra;
        }
        else if(comando_inicial.find("-size=") == 0){
            error = i.Ing_Numero("-size=");
            if(error) break;
            size = ing_numero;
        }
        else if(comando_inicial.find("-r ") == 0){
            error = i.Ing_Comando("-r ");
            if(error) break;
            r = true;
        }
        else if(comando_inicial.find("-cont=") == 0){
            error = i.Ing_PalabraC("-cont=");
            if(error) break;
            path = ing_palabra;
        }
        else{
            error = i.Ing_Error();
            break;
        } 
    }
    return error;
}

bool Mkfile::Verificar_Datos(){
    if(v.Ver_Path3())
    if(v.Ver_Size2())
    if(v.Ver_Cont())
    return true;
    return false;
}

void Mkfile::Ejecutar(){
    
}