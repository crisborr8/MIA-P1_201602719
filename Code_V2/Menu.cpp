#include "Headers.h"
#include "Comandos/Mkdisk.cpp"
Mkdisk mkdisk;

Menu::Menu(){
    comando_inicial = "";
    while(comando_inicial!= "exit"){
        Mostrar_Menu();
        Comando();
    }
    cout << "ADIOS!!!" << endl;
}

void Menu::Mostrar_Menu(){
    cout << "****************************" << endl;
    cout << "****************************" << endl;
    cout << "**                        **" << endl;
    cout << "**    MIA - PROYECTO 1    **" << endl;
    cout << "**                        **" << endl;
    cout << "****************************" << endl;
    cout << "****************************" << endl;
    cout << "\n\tIngrese un comando:" << endl;

    comando = "";
    getline(cin, comando);   
}
void Menu::Comando(){
    comando = e.trim(comando);
    comando_inicial = comando.substr(0, comando.find(' '));
    comando_inicial = e.slower(comando_inicial);

    comando = comando.substr(comando_inicial.length(), comando.length());
    comando = e.trimL(comando);
    if(comando.length() > 0) comando += " ";

    if(comando_inicial == "mkdisk") mkdisk.Inicializar();
    else if(comando_inicial != "exit")
        cout << "ERROR!! INGRESE UN COMANDO VALIDO" << endl;
}