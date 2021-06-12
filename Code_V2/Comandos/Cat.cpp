#include "../Headers.h"

void Cat_::Inicializar(){
    error = false;
    
    file_n = nullptr;

    if(!Ingresar_Datos()) 
        if(Verificar_Datos()) 
            Ejecutar();
}

bool Cat_::Ingresar_Datos(){
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

bool Cat_::Verificar_Datos(){
    error = true;
    if(file_n != nullptr) error = false;
    return !error;
}

void Cat_::Ejecutar(){
    Str::Files *file_new = file_n;
    while(file_new != nullptr){
        cout << file_new->numero << ": " << file_new->file << endl;
        file_new = file_new->next;
    }
}

void Cat_::Add_File(){
    if(file_n == nullptr){
        file_n = new Str::Files;
        file_n->file = ing_palabra;
        file_n->numero = ing_numero;
        file_n->next = nullptr;
    }
    else{
        Str::Files *file_new = file_n;
        while(file_new->next != nullptr) file_new = file_new->next;
        file_new->next = new Str::Files;
        file_new = file_new->next;
        file_new->file = ing_palabra;
        file_new->numero = ing_numero;
        file_new->next = nullptr;
    }
}