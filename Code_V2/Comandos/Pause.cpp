#include "../Headers.h"

void Pause::Inicializar(){
    if(!Ingresar_Datos()) 
        Ejecutar();
}

bool Pause::Ingresar_Datos(){
    if (e.trim(comando).length() > 0){
        cout << "ERROR!! este comando no recibe parametros" << endl;
        return true;
    }
    return false;
}

void Pause::Ejecutar(){
    
}