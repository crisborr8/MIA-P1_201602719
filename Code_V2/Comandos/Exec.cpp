#include "../Headers.h"

void Exec_::Inicializar(){
    error = false;

    path = "";

    if(!Ingresar_Datos()) 
        if(Verificar_Datos()) 
            Ejecutar();
}

bool Exec_::Ingresar_Datos(){
    while(comando.length() > 0){
        comando_inicial = e.slower(comando);
        if(comando_inicial.find("-path=") == 0){
            error = i.Ing_PalabraC("-path=");
            if(error) break;
            path = ing_palabra;
        }
        else{
            error = i.Ing_Error();
            break;
        } 
    }
    return error;
}

bool Exec_::Verificar_Datos(){
    error = true;
    if(v.Ver_Path4()) error = false;
    return !error;
}

void Exec_::Ejecutar(){
    if(ex.Ex_Path_File(path)){
        comando = "";
        ifstream file(path);
        cout << "Inicia ejecucion del script" << endl;
        while(getline(file, comando)){
            cout << comando << endl;
            getchar();
            comando = comando.substr(0, comando.find_first_of('#'));
            comando = e.trim(comando);
            if (comando.length() > 0) me.Comando();
        }
        cout << "Finalizada ejecucion del script" << endl;
    }
    else cout << "ERROR!! archivo no existe" << endl;
}