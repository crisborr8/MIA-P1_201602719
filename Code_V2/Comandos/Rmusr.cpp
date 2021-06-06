#include "../Headers.h"

void Rmusr::Inicializar(){
    error = false;

    usr = "";

    if(!Ingresar_Datos()) 
        if(Verificar_Datos()) 
            Ejecutar();
}

bool Rmusr::Ingresar_Datos(){
    while(comando.length() > 0){
        comando_inicial = e.slower(comando);
        if(comando_inicial.find("-usr=") == 0){
            error = i.Ing_PalabraC("-usr=");
            if(error) break;
            usr = ing_palabra;
        }
        else{
            error = i.Ing_Error();
            break;
        } 
    }
    return error;
}

bool Rmusr::Verificar_Datos(){
    if(v.Ver_Usr())
    return true;
    return false;
}

void Rmusr::Ejecutar(){
    
}