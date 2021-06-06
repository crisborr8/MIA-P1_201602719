#include "../Headers.h"

void Mkgrp::Inicializar(){
    error = false;

    name = "";

    if(!Ingresar_Datos()) 
        if(Verificar_Datos()) 
            Ejecutar();
}

bool Mkgrp::Ingresar_Datos(){
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

bool Mkgrp::Verificar_Datos(){
    if(v.Ver_Name())
    return true;
    return false;
}

void Mkgrp::Ejecutar(){
    
}