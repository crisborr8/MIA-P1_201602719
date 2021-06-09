#include "../Headers.h"

void Mkusr_::Inicializar(){
    error = false;

    usr = "";
    pwd = "";
    grp = "";

    if(!Ingresar_Datos()) 
        if(Verificar_Datos()) 
            Ejecutar();
}

bool Mkusr_::Ingresar_Datos(){
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

bool Mkusr_::Verificar_Datos(){
    error = true;
    if(v.Ver_Usr2()) error = false;
    if(!v.Ver_Pwd2()) error = true;
    if(!v.Ver_Grp()) error = true;
    return !error;
}

void Mkusr_::Ejecutar(){
    
}