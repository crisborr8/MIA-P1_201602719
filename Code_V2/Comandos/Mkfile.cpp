#include "../Headers.h"

void Mkfile_::Inicializar(){
    error = false;

    path = "";
    r = false;
    size = 0;
    cont = "";

    if(!Ingresar_Datos()) 
        if(Verificar_Datos()) 
            Ejecutar();
}

bool Mkfile_::Ingresar_Datos(){
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

bool Mkfile_::Verificar_Datos(){
    error = true;
    if(v.Ver_Path3()) error = false;
    if(!v.Ver_Size2()) error = true;
    if(!v.Ver_Cont()) error = true;
    return !error;
}

void Mkfile_::Ejecutar(){
    
}