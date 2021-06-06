#include "../Headers.h"

void Chgrp::Inicializar(){
    error = false;

    usr = "";
    grp = "";

    if(!Ingresar_Datos()) 
        if(Verificar_Datos()) 
            Ejecutar();
}

bool Chgrp::Ingresar_Datos(){
    while(comando.length() > 0){
        comando_inicial = e.slower(comando);
        if(comando_inicial.find("-path=") == 0){
            error = i.Ing_PalabraC("-path=");
            if(error) break;
            path = ing_palabra;
        }
        else if(comando_inicial.find("-grp=") == 0){
            error = i.Ing_PalabraC("-grp=");
            if(error) break;
            grp = ing_palabra;
        }
        else{
            error = i.Ing_Error();
            break;
        } 
    }
    return error;
}

bool Chgrp::Verificar_Datos(){
    if(v.Ver_Usr())
    if(v.Ver_Grp())
    return true;
    return false;
}

void Chgrp::Ejecutar(){
    
}