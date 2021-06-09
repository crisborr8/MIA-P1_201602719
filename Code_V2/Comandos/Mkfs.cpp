#include "../Headers.h"

void Mkfs_::Inicializar(){
    error = false;

    id = "";
    type = "full";
    fs = "2fs";

    if(!Ingresar_Datos()) 
        if(Verificar_Datos()) 
            Ejecutar();
}

bool Mkfs_::Ingresar_Datos(){
    while(comando.length() > 0){
        comando_inicial = e.slower(comando);
        if(comando_inicial.find("-id=") == 0){
            error = i.Ing_Palabra("-id=");
            if(error) break;
            id = ing_palabra;
        }
        else if(comando_inicial.find("-type=") == 0){
            error = i.Ing_Palabra("-type=");
            if(error) break;
            type = ing_palabra;
        }
        else if(comando_inicial.find("-fs=") == 0){
            error = i.Ing_Palabra("-fs=");
            if(error) break;
            fs = ing_palabra;
        }
        else{
            error = i.Ing_Error();
            break;
        } 
    }
    return error;
}

bool Mkfs_::Verificar_Datos(){
    error = true;
    if(v.Ver_Id()) error = false;
    if(!v.Ver_Fs()) error = true;
    if(!v.Ver_Type2()) error = true;
    return !error;
}

void Mkfs_::Ejecutar(){
    
}