#include "../Headers.h"

void Logout_::Inicializar(){
    if(!Ingresar_Datos()) 
        Ejecutar();
}

bool Logout_::Ingresar_Datos(){
    if (e.trim(comando).length() > 0){
        cout << "ERROR!! este comando no recibe parametros" << endl;
        return true;
    }
    return false;
}

void Logout_::Ejecutar(){
    
}