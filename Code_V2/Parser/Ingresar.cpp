#include "../Headers.h"

bool Ingresar::Ing_Numero(string c){
    if(c.length() + 1 >= comando.length()){
        cout << "ERROR!!, " << c << " debe tener un parametro" << endl;
        return true;
    }
    comando = comando.substr(c.length(), comando.length());
    comando_inicial = comando.substr(0, comando.find_first_of(blanco) + 1);
    try{
        ing_numero = stoi(comando_inicial);
    }catch(exception ex){
        cout << "ERROR!!, " << c << " debe ser tipo numerico" << endl;
        return true;
    }
    comando = comando.substr(comando_inicial.length(), comando.length());
    comando = e.trimL(comando);
    return false;
}
bool Ingresar::Ing_Comando(string c){
    comando = comando.substr(c.length(), comando.length());
    return false;
}

bool Ingresar::Ing_PalabraC(string c){
    if(c.length() + 1 >= comando.length()){
        cout << "ERROR!!, " << c << " debe tener un parametro" << endl;
        return true;
    }
    comando = comando.substr(c.length(), comando.length());
    if(comando[0] == '"'){
        comando = comando.substr(1, comando.length());
        i_aux = comando.find_first_of('"');
        if(i_aux == string::npos){
            cout << "ERROR!!, " << c << " si inicia con \" debe terminar con \"" << endl;
            return true;
        }
        else if(i_aux == 0){
            cout << "ERROR!!, " << c << " no debe ser nulo" << endl;
            return true;
        }
        comando_inicial = comando.substr(0, i_aux);
        ing_palabra = e.trim(comando_inicial);
        comando = comando.substr(comando_inicial.length() + 1, comando.length());
    }
    else{
        comando_inicial = comando.substr(0, comando.find_first_of(blanco) + 1);
    ing_palabra = e.trim(comando_inicial);
        comando = comando.substr(comando_inicial.length(), comando.length());
    }
        comando = e.trimL(comando);
    return false;
}

bool Ingresar::Ing_Palabra(string c){
    if(c.length() + 1 >= comando.length()){
        cout << "ERROR!!, " << c << " debe tener un parametro" << endl;
        return true;
    }
    comando = comando.substr(c.length(), comando.length());
    comando_inicial = comando.substr(0, comando.find_first_of(blanco) + 1);
    ing_palabra = e.trim(comando_inicial);
    comando = comando.substr(comando_inicial.length(), comando.length());
    comando = e.trimL(comando);
    return false;
}

bool Ingresar::Ing_PalabraF(string c){
    comando = comando.substr(c.length(), comando.length());
    comando_inicial = comando.substr(0, comando.find_first_of('='));
    try{
        ing_numero = stoi(comando_inicial);
    }catch(exception ex){
        cout << "ERROR!! -file debe seguir con algun numero" << endl;
        return true;
    }
    comando = comando.substr(comando_inicial.length() + 1, comando.length());
    comando_inicial = comando.substr(0, comando.find_first_of(blanco));
    ing_palabra = e.trim(comando_inicial);
    comando = comando.substr(comando_inicial.length(), comando.length());
    comando = e.trimL(comando);
    return false;
}

bool Ingresar::Ing_Error(){
    cout << "ERROR!! comando desconocido: " << 
    comando.substr(0, comando.find_first_of(blanco) + 1) << endl;
    return true;
}