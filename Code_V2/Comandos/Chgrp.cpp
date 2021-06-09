#include "../Headers.h"

void Chgrp_::Inicializar(){
    error = false;

    usr = "";
    grp = "";

    if(!Ingresar_Datos()) 
        if(Verificar_Datos()) 
            Ejecutar();
}

bool Chgrp_::Ingresar_Datos(){
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

bool Chgrp_::Verificar_Datos(){
    error = true;
    if(v.Ver_Usr()) error = false;
    if(!v.Ver_Grp()) error = true;
    return !error;
}

void Chgrp_::Ejecutar(){
    
}