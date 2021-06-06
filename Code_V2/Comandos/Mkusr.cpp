#include "../Headers.h"

void Mkusr::Inicializar(){
    error = false;

    usr = "";
    pwd = "";
    grp = "";

    if(!Ingresar_Datos()) 
        if(Verificar_Datos()) 
            Ejecutar();
}

bool Mkusr::Ingresar_Datos(){
    while(comando.length() > 0){
        comando_inicial = e.slower(comando);
        if(comando_inicial.find("-usr=") == 0){
            error = i.Ing_PalabraC("-usr=");
            if(error) break;
            usr = ing_palabra;
        }
        else if(comando_inicial.find("-pwd=") == 0){
            error = i.Ing_PalabraC("-pwd=");
            if(error) break;
            pwd = ing_palabra;
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

bool Mkusr::Verificar_Datos(){
    if(v.Ver_Usr2())
    if(v.Ver_Pwd2())
    if(v.Ver_Grp())
    return true;
    return false;
}

void Mkusr::Ejecutar(){
    
}