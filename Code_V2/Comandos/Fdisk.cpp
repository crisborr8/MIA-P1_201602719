#include "../Headers.h"

void Fdisk_::Inicializar(){
    error = false;

    _case = 0; //0 - Crear particion, 1 Eliminar, 2 Agregar
    type = "p";
    delet = "";
    path = "";
    name = "";
    f = "wf";
    u = "k";
    size = 0;
    add = 0;

    if(!Ingresar_Datos()) 
        if(Verificar_Datos()) 
            Ejecutar();
}

bool Fdisk_::Ingresar_Datos(){
    while(comando.length() > 0){
        comando_inicial = e.slower(comando);
        if(comando_inicial.find("-size=") == 0){
            error = i.Ing_Numero("-size=");
            if(error) break;
            size = ing_numero;
        } 
        else if(comando_inicial.find("-u=") == 0){
            error = i.Ing_Palabra("-u=");
            if(error) break;
            u = ing_palabra;
        }
        else if(comando_inicial.find("-path=") == 0){
            error = i.Ing_PalabraC("-path=");
            if(error) break;
            path = ing_palabra;
        }
        else if(comando_inicial.find("-type=") == 0){
            error = i.Ing_Palabra("-type=");
            if(error) break;
            type = ing_palabra;
        }
        else if(comando_inicial.find("-f=") == 0){
            error = i.Ing_Palabra("-f=");
            if(error) break;
            f = ing_palabra;
        }
        else if(comando_inicial.find("-delete=") == 0){
            error = i.Ing_Palabra("-delete=");
            if(error) break;
            delet = ing_palabra;
            if(_case == 0) _case = 1;
        }
        else if(comando_inicial.find("-name=") == 0){
            error = i.Ing_PalabraC("-name=");
            if(error) break;
            name = ing_palabra;
        }
        else if(comando_inicial.find("-add=") == 0){
            error = i.Ing_Numero("-add=");
            if(error) break;
            add = ing_numero;
            if(_case == 0) _case = 2;
        }
        else{
            error = i.Ing_Error();
            break;
        } 
    }
    return error;
}
bool Fdisk_::Verificar_Datos(){
    error = true;
    if(v.Ver_F()) error = false;
    if(!v.Ver_U2()) error = true;
    if(!v.Ver_Type()) error = true;
    if(!v.Ver_Name()) error = true;
    if(!v.Ver_Path()){
        if(_case == 0){ if(!v.Ver_Size()) error = true; }
        else if(_case == 1){ if(!v.Ver_Delet()) error = true; }
        else if(!v.Ver_Add()) error = true;
    }
    return !error;
}
void Fdisk_::Ejecutar(){
    if(ex.Ex_Path_File(path)){
        switch (_case)
        {
        case 0: Crear(); break;
        case 1: Eliminar(); break;
        case 2: Agregar(); break;
        }
    }
    else cout << "ERROR!! el archivo no existe" << endl;
}

void Fdisk_::Crear(){
    if(!ex.Ex_Name(name, path)){
        archivo = fopen(path.c_str(), "rb");
        mbr = Str::MBR();
        fseek(archivo, 0, SEEK_SET);
        fread(&mbr, sizeof(mbr), 1, archivo);
        fclose(archivo);
        i_aux = 0;
        for(int i = 0; i < 4; i++){
            part = mbr.p[i];
            if(part.type == 'e'){
                if(part.status == 'A'){
                    if(type == "l") break;
                    if(type == "e"){
                        i_aux = 5;
                        break;
                    }
                    else i_aux++;
                }
            }
            else if (part.status == 'A') i_aux++;
            if(i == 3 && type == "l") i_aux = 6;
        }
        if(i_aux == 4 && type == "l") i_aux = 6;
        switch (i_aux)
        {
            case 4:
                cout << "ERROR!! cantidad permitida de particiones primarias y extendidas superada" << endl;
                break;
            case 5:
                cout << "ERROR!! ya existe una particion extendida" << endl;
                break;
            case 6:
                cout << "ERROR!! debe existir una particion extendida para crear una logica" << endl;
                break;
            default:
                Crear_Particion();
                break;
        }
    }
    else cout << "ERROR!! el nombre ya existe en esta particion" << endl;
}
void Fdisk_::Crear_Particion(){
    if(u != "b") size *= 1024;
    if(u == "m") size *= 1024;

    Crear_VerEspacio();

    if(f_start != 0){
        if(type == "l"){
            archivo = fopen(path.c_str(), "r+b");
            fseek(archivo, f_start, SEEK_SET);
            fread(&ebr, sizeof(ebr), 1, archivo);
            if(ebr.status == 'A'){
                if(ebr.next == -1){
                    i_aux = ebr.start + ebr.size;
                    ebr.next = i_aux;
                    fseek(archivo, f_start, SEEK_SET);
                    fwrite(&ebr, sizeof(ebr), 1, archivo);
                    ebr.next = -1;
                }else{
                    i_aux = ebr.next;
                    ebr.next = ebr.start + ebr.size;
                    fseek(archivo, f_start, SEEK_SET);
                    fwrite(&ebr, sizeof(ebr), 1, archivo);
                    ebr.next = i_aux;
                }
                f_start = i_aux;
                ebr.start = f_start + sizeof(ebr);
            }
            ebr.fit = f[0];
            strcpy(ebr.name, name.c_str());
            ebr.size = size - sizeof(ebr);
            ebr.status = 'A';

            fseek(archivo, f_start, SEEK_SET);
            fwrite(&ebr, sizeof(ebr), 1, archivo);
        }
        else{
            part.fit = f[0];
            strcpy(part.name, name.c_str());
            part.size = size;
            part.start = f_start;
            part.status = 'A';
            part.type = type[0];
            mbr.p[3] = part;

            gs.Ordernar_MBR();

            archivo = fopen(path.c_str(), "r+b");
            fseek(archivo, 0, SEEK_SET);
            fwrite(&mbr, sizeof(mbr), 1, archivo);

            if(type == "e"){
                ebr = Str::EBR();
                ebr.status = 'N';
                ebr.next = -1;
                ebr.start = f_start + sizeof(ebr);
                fseek(archivo, f_start, SEEK_SET);
                fwrite(&ebr, sizeof(ebr), 1, archivo);
            }
        }
        fclose(archivo);
        cout << "Particion creada con exito" << endl;
    }
    else cout << "ERROR!! espacio insuficiente" << endl;
}
void Fdisk_::Crear_VerEspacio(){
    int esp_disp, esp_dispAnt;
    if(mbr.fit == 'b') esp_dispAnt = mbr.size;
    else esp_dispAnt = 0;
    i_aux = 0;
    
    if(type == "l"){
        for(; i_aux < 4; i_aux++){
            if(mbr.p[i_aux].type == 'e'){
                archivo = fopen(path.c_str(), "rb");
                part = mbr.p[i_aux];
                f_sizeMax = part.size;
                f_start = part.start;
                i_aux = 0;
                do{
                    ebr = Str::EBR();
                    fseek(archivo, f_start, SEEK_SET);
                    fread(&ebr, sizeof(ebr), 1, archivo);
                    esp_disp = gs.Get_esp_dispL(f_start) - sizeof(ebr);

                    if(mbr.fit == 'b'){
                        if(esp_disp < esp_dispAnt && esp_disp >= size){ 
                            esp_dispAnt = esp_disp;
                            i_aux = f_start;
                        }
                    }
                    else if(esp_disp > esp_dispAnt && esp_disp >= size){ 
                        esp_dispAnt = esp_disp;
                        i_aux = f_start;
                        if(mbr.fit == 'f') break;
                    }

                    f_start = ebr.next;
                }while(ebr.next != -1);
                fclose(archivo);
                break;
            }
        }
    }
    else{
        for(int i = -1; i < 4; i++){
            part = mbr.p[i];
            if(i == -1 || part.status == 'A'){
                if(i == -1) f_start = sizeof(mbr);
                else if(part.status == 'A') f_start = mbr.p[i].size + mbr.p[i].start;
                esp_disp = gs.Get_esp_dispPE(f_start);

                if(mbr.fit == 'b'){
                    if(esp_disp < esp_dispAnt && esp_disp >= size){
                        esp_dispAnt = esp_disp;
                        i_aux = f_start;
                    }
                } else if(esp_disp > esp_dispAnt && esp_disp >= size){
                    esp_dispAnt = esp_disp;
                    i_aux = f_start;
                    if(mbr.fit == 'f') break;
                }
            }
            else break;
        }
    }
    f_start = i_aux;
}

void Fdisk_::Eliminar(){
    if(ex.Ex_Name(name, path)){
        cout << "¿Desea eliminar la particion " << name << " del disco?" << endl;
        cout << "si/no" << endl;
        comando = "";
        getline(cin, comando);
        if(e.slower(e.trim(comando)) == "si"){
            archivo = fopen(path.c_str(), "r+b");
            fseek(archivo, 0, SEEK_SET);
            fread(&mbr, sizeof(mbr), 1, archivo);

            if(type == "l"){
                for(int i = 0; i < 4; i++){
                    if(mbr.p[i].type == 'e'){
                        f_start = mbr.p[i].start;
                        i_aux = f_start;
                        do{
                            fseek(archivo, f_start, SEEK_SET);
                            fread(&ebr, sizeof(ebr), 1, archivo);
                            if(strcmp(ebr.name, name.c_str()) == 0){
                                ebr.status = 'N';
                                strcpy(ebr.name, "");
                                if(i_aux != f_start){ //No es el primero
                                    Str::EBR ebr_aux = Str::EBR();
                                    fseek(archivo, i_aux, SEEK_SET);
                                    fread(&ebr_aux, sizeof(ebr_aux), 1, archivo);
                                    ebr_aux.next = ebr.next;
                                    fseek(archivo, i_aux, SEEK_SET);
                                    fwrite(&ebr_aux, sizeof(ebr_aux), 1, archivo);
                                }
                                if(delet == "full"){
                                    fseek(archivo, ebr.start, SEEK_SET);
                                    char zero[ebr.size] = {'0'};
                                    fwrite(&zero, sizeof(zero), 1, archivo);
                                }
                                fseek(archivo, f_start, SEEK_SET);
                                fwrite(&ebr, sizeof(ebr), 1, archivo);
                                break;
                            }
                            i_aux = f_start;
                            f_start = ebr.next;
                        }while(ebr.next != -1);
                        break;
                    }
                }
            }
            else{
                for(int i = 0; i < 4; i++){
                    if(strcmp(mbr.p[i].name, name.c_str())  == 0){
                        cout << "---->Start: " << mbr.p[i].start << endl;
                        mbr.p[i].status = 'N';
                        mbr.p[i].type = 'p';
                        strcpy(mbr.p[i].name, "");
                        if(delet == "full") {
                            fseek(archivo, mbr.p[i].start, SEEK_SET);
                            char zero[mbr.p[i].size] = {'0'};
                            fwrite(&zero, sizeof(zero), 1, archivo);
                        }
                        gs.Ordernar_MBR();
                        fseek(archivo, 0, SEEK_SET);
                        fwrite(&mbr, sizeof(mbr), 1, archivo);
                        break;
                    }
                }
            }
            fclose(archivo);
            cout << "Particion eliminada" << endl;
        }
        else cout << "...Redireccionando al menu" << endl;
    }
    else cout << "ERROR!! el nombre no existe en esta particion" << endl;
}

void Fdisk_::Agregar(){
    if(ex.Ex_Name(name, path)){
        if(u != "b") add *= 1024;
        if(u == "m") add *= 1024;
        archivo = fopen(path.c_str(), "r+b");
        fseek(archivo, 0, SEEK_SET);
        fread(&mbr, sizeof(mbr), 1, archivo);

        if(type == "l"){
            for(int i = 0; i < 4; i++){
                if(mbr.p[i].type == 'e'){
                    f_start = mbr.p[i].start;
                    do{
                        fseek(archivo, f_start, SEEK_SET);
                        fread(&ebr, sizeof(ebr), 1, archivo);
                        if(ebr.status == 'A'){
                            if(strcmp(ebr.name, name.c_str()) == 0){
                                if(add > 0){
                                    i_aux = gs.Get_esp_dispL(f_start + 1) + 1;
                                    if(i_aux > add) cout << "ERROR!! Espacio insuficiente" << endl;
                                    else ebr.size += add;
                                }
                                else{
                                    i_aux = ebr.size;
                                    if(i_aux + add < 0) cout << "ERROR!! Espacio a quitar demasiado grande" << endl;
                                    else ebr.size += add;
                                }
                                fseek(archivo, f_start, SEEK_SET);
                                fwrite(&ebr, sizeof(ebr), 1, archivo);
                                break;
                            }
                        }
                        f_start = ebr.next;
                    }while(ebr.next != -1);
                    break;
                }
            }
        }
        else{
            for(int i = 0; i < 4; i++){
                if(strcmp(mbr.p[i].name, name.c_str()) == 0){
                    part = mbr.p[i];
                    if(add > 0){
                        i_aux = gs.Get_esp_dispPE(part.start + 1) + 1;
                        if(i_aux >= add){
                            mbr.p[i].size += add;
                            fseek(archivo, 0, SEEK_SET);
                            fwrite(&mbr, sizeof(mbr), 1, archivo);
                            cout << "Espacio agregado" << endl;
                        }
                        else cout << "ERROR!! espacio insuficiente" << endl;
                    }
                    else{
                        if(part.type == 'p'){
                            i_aux = part.size;
                            if(i_aux + add < 0) cout << "ERROR!! Espacio a quitar demasiado grande" << endl;
                            else {
                                mbr.p[i].size += add;
                                fseek(archivo, 0, SEEK_SET);
                                fwrite(&mbr, sizeof(mbr), 1, archivo);
                                cout << "Espacio agregado" << endl;
                            }
                        }
                        else{
                            f_start = part.start;
                            do{
                                fseek(archivo, f_start, SEEK_SET);
                                fread(&ebr, sizeof(ebr), 1, archivo);
                                f_start = ebr.next;
                            }while(ebr.next != -1);
                            i_aux = part.start + part.size - ebr.start;
                            if(ebr.status == 'A') i_aux -= ebr.size;
                            if(i_aux + add < 0) cout << "ERROR!! Espacio a quitar demasiado grande" << endl;
                            else {
                                mbr.p[i].size += add;
                                fseek(archivo, 0, SEEK_SET);
                                fwrite(&mbr, sizeof(mbr), 1, archivo);
                                cout << "Espacio agregado" << endl;
                            }
                        }
                    }
                    break;
                }
            }
        }
        fclose(archivo);
    }
    else cout << "ERROR!! el nombre no existe en esta particion" << endl;
}
