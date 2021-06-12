#include "Extras/Includes.cpp"
#include <stdlib.h> 

void Menu::Menu_Principal(){
    comando_inicial = "";
    montura = nullptr;
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
//rep -path=/home/archivos/b.pdf -id=191a -name=disk
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

    if(comando_inicial == "cat") cat_.Inicializar();
    else if(comando_inicial == "chgrp") chgrp_.Inicializar();
    else if(comando_inicial == "chmod") chmod_.Inicializar();
    else if(comando_inicial == "chown") chown_.Inicializar();
    else if(comando_inicial == "cp") cp_.Inicializar();
    else if(comando_inicial == "edit") edit_.Inicializar();
    else if(comando_inicial == "exec") exec_.Inicializar();
    else if(comando_inicial == "fdisk") fdisk_.Inicializar();
    else if(comando_inicial == "find") find_.Inicializar();
    else if(comando_inicial == "login") login_.Inicializar();
    else if(comando_inicial == "logut") logout_.Inicializar();
    else if(comando_inicial == "mkdir") mkdir_.Inicializar();
    else if(comando_inicial == "mkdisk") mkdisk_.Inicializar();
    else if(comando_inicial == "mkfile") mkfile_.Inicializar();
    else if(comando_inicial == "mkfs") mkfs_.Inicializar();
    else if(comando_inicial == "mkgrp") mkgrp_.Inicializar();
    else if(comando_inicial == "mkusr") mkusr_.Inicializar();
    else if(comando_inicial == "mount") mount_.Inicializar();
    else if(comando_inicial == "mv") mv_.Inicializar();
    else if(comando_inicial == "pause") pause_.Inicializar();
    else if(comando_inicial == "rem") rem_.Inicializar();
    else if(comando_inicial == "ren") ren_.Inicializar();
    else if(comando_inicial == "rep") rep_.Inicializar();
    else if(comando_inicial == "rmdisk") rmdisk_.Inicializar();
    else if(comando_inicial == "rmgrp") rmgrp_.Inicializar();
    else if(comando_inicial == "rmusr") rmusr_.Inicializar();
    else if(comando_inicial == "unmount") unmount_.Inicializar();
    else if(comando_inicial != "exit")
        cout << "ERROR!! INGRESE UN COMANDO VALIDO" << endl;
}

int main()
{
    Menu m;
    m.Menu_Principal();
}

//exec -path="/home/criss/Escritorio/Criss/MIA_P1_201602719/Tests/basico.script"