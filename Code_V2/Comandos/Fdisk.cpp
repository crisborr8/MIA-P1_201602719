#include "../Headers.h"

void Fdisk::Inicializar(){
    error = false;

    _case = 0; //0 - Crear particion, 1 Eliminar, 2 Agregar
    type = "p";
    delet = "";
    path = "";
    name = "";
    f = "wf";
    u = "k";
    size = 0;
    add = 0;

    if(!Ingresar_Datos()) 
        if(Verificar_Datos()) 
            Ejecutar();
}

bool Fdisk::Ingresar_Datos(){
    while(comando.length() > 0){
        comando_inicial = e.slower(comando);
        if(comando_inicial.find("-size=") == 0){
            error = i.Ing_Numero("-size=");
            if(error) break;
            size = ing_numero;
        } 
        else if(comando_inicial.find("-u=") == 0){
            error = i.Ing_Palabra("-u=");
            if(error) break;
            u = ing_palabra;
        }
        else if(comando_inicial.find("-path=") == 0){
            error = i.Ing_PalabraC("-path=");
            if(error) break;
            path = ing_palabra;
        }
        else if(comando_inicial.find("-type=") == 0){
            error = i.Ing_Palabra("-type=");
            if(error) break;
            type = ing_palabra;
        }
        else if(comando_inicial.find("-f=") == 0){
            error = i.Ing_Palabra("-f=");
            if(error) break;
            f = ing_palabra;
        }
        else if(comando_inicial.find("-delete=") == 0){
            error = i.Ing_Palabra("-delete=");
            if(error) break;
            delet = ing_palabra;
            if(_case == 0) _case = 1;
        }
        else if(comando_inicial.find("-name=") == 0){
            error = i.Ing_PalabraC("-name=");
            if(error) break;
            name = ing_palabra;
        }
        else if(comando_inicial.find("-add=") == 0){
            error = i.Ing_Numero("-add=");
            if(error) break;
            add = ing_numero;
            if(_case == 0) _case = 2;
        }
        else{
            error = i.Ing_Error();
            break;
        } 
    }
    return error;
}

bool Fdisk::Verificar_Datos(){
    if(v.Ver_F())
    if(v.Ver_U2())
    if(v.Ver_Type())
    if(v.Ver_Name())
    if(v.Ver_Path()){
        if(_case == 0) if(v.Ver_Size()) return true;
        else if(_case == 1) if(v.Ver_Delet()) return true;
        else if(v.Ver_Add()) return true;
    }
    return false;
}

void Fdisk::Ejecutar(){
    
}