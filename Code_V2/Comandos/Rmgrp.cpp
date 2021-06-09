#include "../Headers.h"

void Rmgrp_::Inicializar(){
    error = false;

    name = "";

    if(!Ingresar_Datos()) 
        if(Verificar_Datos()) 
            Ejecutar();
}

bool Rmgrp_::Ingresar_Datos(){
    while(comando.length() > 0){
        comando_inicial = e.slower(comando);
        if(comando_inicial.find("-name=") == 0){
            error = i.Ing_PalabraC("-name=");
            if(error) break;
            name = ing_palabra;
        }
        else{
            error = i.Ing_Error();
            break;
        } 
    }
    return error;
}

bool Rmgrp_::Verificar_Datos(){
    error = true;
    if(v.Ver_Name()) error = false;
    return !error;
}

void Rmgrp_::Ejecutar(){
    
}