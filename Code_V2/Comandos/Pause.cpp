#include "../Headers.h"

void Pause_::Inicializar(){
    if(!Ingresar_Datos()) 
        Ejecutar();
}

bool Pause_::Ingresar_Datos(){
    if (e.trim(comando).length() > 0){
        cout << "ERROR!! este comando no recibe parametros" << endl;
        return true;
    }
    return false;
}

void Pause_::Ejecutar(){
    cout << "Ingrese cualquier tecla para continuar..." << endl;
    getchar();
}