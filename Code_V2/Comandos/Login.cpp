#include "../Headers.h"

void Login_::Inicializar(){
    error = false;

    usr = "";
    pwd = "";
    id = "";

    if(!Ingresar_Datos()) 
        if(Verificar_Datos()) 
            Ejecutar();
}

bool Login_::Ingresar_Datos(){
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
        else if(comando_inicial.find("-id=") == 0){
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

bool Login_::Verificar_Datos(){
    error = true;
    if(v.Ver_Usr()) error = false;
    if(!v.Ver_Pwd()) error = true;
    if(!v.Ver_Id()) error = true;
    return !error;
}

void Login_::Ejecutar(){
    
}