#include "../Headers.h"

void Unmount_::Inicializar(){
    error = false;

    id = "";

    if(!Ingresar_Datos()) 
        if(Verificar_Datos()) 
            Ejecutar();
}

bool Unmount_::Ingresar_Datos(){
    while(comando.length() > 0){
        comando_inicial = e.slower(comando);
        if(comando_inicial.find("-id=") == 0){
            error = i.Ing_Palabra("-id=");
            if(error) break;
            id = ing_palabra;
        }
        else{
            error = i.Ing_Error();
            break;
        } 
    }
    return error;
}

bool Unmount_::Verificar_Datos(){
    error = true;
    if(v.Ver_Id()) error = false;
    return !error;
}

void Unmount_::Ejecutar(){
    
}