#include "Extras/Includes.cpp"

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

    if(comando_inicial == "cat") cat.Inicializar();
    else if(comando_inicial == "chgrp") chgrp.Inicializar();
    else if(comando_inicial == "chmod") chmod.Inicializar();
    else if(comando_inicial == "chown") chown.Inicializar();
    else if(comando_inicial == "cp") cp.Inicializar();
    else if(comando_inicial == "edit") edit.Inicializar();
    else if(comando_inicial == "exec") exec.Inicializar();
    else if(comando_inicial == "fdisk") fdisk.Inicializar();
    else if(comando_inicial == "find") find_.Inicializar();
    else if(comando_inicial == "login") login.Inicializar();
    else if(comando_inicial == "logut") logout.Inicializar();
    else if(comando_inicial == "mkdir") mkdir.Inicializar();
    else if(comando_inicial == "mkdisk") mkdisk.Inicializar();
    else if(comando_inicial == "mkfile") mkfile.Inicializar();
    else if(comando_inicial == "mkfs") mkfs.Inicializar();
    else if(comando_inicial == "mkgrp") mkgrp.Inicializar();
    else if(comando_inicial == "mkusr") mkusr.Inicializar();
    else if(comando_inicial == "mount") mount.Inicializar();
    else if(comando_inicial == "mv") mv.Inicializar();
    else if(comando_inicial == "pause") pause.Inicializar();
    else if(comando_inicial == "rem") rem.Inicializar();
    else if(comando_inicial == "ren") ren.Inicializar();
    else if(comando_inicial == "rep") rep.Inicializar();
    else if(comando_inicial == "rmdisk") rmdisk.Inicializar();
    else if(comando_inicial == "rmgrp") rmgrp.Inicializar();
    else if(comando_inicial == "rmusr") rmusr.Inicializar();
    else if(comando_inicial == "unmount") unmount.Inicializar();
    else if(comando_inicial != "exit")
        cout << "ERROR!! INGRESE UN COMANDO VALIDO" << endl;
}

int main()
{
    Menu();
}