#include "../Headers.h"

void Cat::Inicializar(){
    error = false;
    
    file_n = nullptr;

    if(!Ingresar_Datos()) 
        if(Verificar_Datos()) 
            Ejecutar();
}

bool Cat::Ingresar_Datos(){
    while(comando.length() > 0){
        comando_inicial = e.slower(comando);
        if(comando_inicial.find("-file") == 0){
            error = i.Ing_PalabraF("-file");
            if(error) break;
            Add_File();
        }
        else{
            error = i.Ing_Error();
            break;
        } 
    }
    return error;
}

bool Cat::Verificar_Datos(){
    if(file_n != nullptr) 
    return true;
    return false;
}

void Cat::Ejecutar(){
    Files *file_new = file_n;
    while(file_new != nullptr){
        cout << file_new->numero << ": " << file_new->file << endl;
        file_new = file_new->next;
    }
}

void Cat::Add_File(){
    if(file_n == nullptr){
        file_n = new Files;
        file_n->file = ing_palabra;
        file_n->numero = ing_numero;
        file_n->next = nullptr;
    }
    else{
        Files *file_new = file_n;
        while(file_new->next != nullptr) file_new = file_new->next;
        file_new->next = new Files;
        file_new = file_new->next;
        file_new->file = ing_palabra;
        file_new->numero = ing_numero;
        file_new->next = nullptr;
    }
}