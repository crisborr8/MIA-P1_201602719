#include "../Headers.h"

void Rmusr_::Inicializar(){
    error = false;

    usr = "";

    if(!Ingresar_Datos()) 
        if(Verificar_Datos()) 
            Ejecutar();
}

bool Rmusr_::Ingresar_Datos(){
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

bool Rmusr_::Verificar_Datos(){
    error = true;
    if(v.Ver_Usr()) error = false;
    return !error;
}

void Rmusr_::Ejecutar(){
    
}