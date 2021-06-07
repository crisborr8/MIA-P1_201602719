#include "../Headers.h"

void Fdisk::Inicializar(){
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

bool Fdisk::Ingresar_Datos(){
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
bool Fdisk::Verificar_Datos(){
    if(v.Ver_F())
    if(v.Ver_U2())
    if(v.Ver_Type())
    if(v.Ver_Name())
    if(v.Ver_Path()){
        if(_case == 0) if(v.Ver_Size()) return true;
        else if(_case == 1) if(v.Ver_Delet()) return true;
        else if(v.Ver_Add()) return true;
    }
    return false;
}
void Fdisk::Ejecutar(){
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

void Fdisk::Crear(){
    if(!ex.Ex_Name(name, path)){
        archivo = fopen(path.c_str(), "rb");
        mbr = MBR();
        fseek(archivo, 0, SEEK_SET);
        fread(&mbr, sizeof(mbr), 1, archivo);
        fclose(archivo);
        i_aux = 0;
        for(int i = 0; i < 4; i++){
            part = mbr.p[i];
            if(part.type == 'e'){
                if(part.status == 'A'){
                    if(type == "e"){
                        i_aux = 5;
                        break;
                    }
                    else i_aux++;
                }
                if(type == "l") break;
            }
            else if (part.status == 'A') i_aux++;
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
                testing();
                break;
        }
    }
    else cout << "ERROR!! el nombre ya existe en esta particion" << endl;
}
void Fdisk::Crear_Particion(){
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

            for(int i = 0; i < 4; i++){
                if(mbr.p[i].status == 'N'){
                    for(int j = i + 1; j < 4; j++){
                        part = mbr.p[i];
                        mbr.p[i] = mbr.p[j];
                        mbr.p[j] = part;
                    }
                }
            }
            for(int i = 0; i < 4; i++){
                if(mbr.p[i].status == 'A'){
                    for(int j = i + 1; j < 4; j++){
                        if(mbr.p[j].status == 'N') break;
                        if(mbr.p[j].start < mbr.p[i].start){
                            part = mbr.p[i];
                            mbr.p[i] = mbr.p[j];
                            mbr.p[j] = part;
                        }
                    }
                }
                else break;
            }

            archivo = fopen(path.c_str(), "r+b");
            fseek(archivo, 0, SEEK_SET);
            fwrite(&mbr, sizeof(mbr), 1, archivo);

            if(type == "e"){
                ebr = EBR();
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
void Fdisk::Crear_VerEspacio(){
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
                    ebr = EBR();
                    fseek(archivo, f_start, SEEK_SET);
                    fread(&ebr, sizeof(ebr), 1, archivo);
                    esp_disp = Get_esp_dispL(f_start) - (f_start + sizeof(ebr));

                    if(mbr.fit == 'b'){
                        if(esp_disp < esp_dispAnt){ 
                            esp_dispAnt = esp_disp;
                            i_aux = f_start;
                        }
                    }
                    else if(esp_disp > esp_dispAnt){ 
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
                esp_disp = Get_esp_dispPE(f_start);

                if(mbr.fit == 'b'){
                    if(esp_disp < esp_dispAnt){
                        esp_dispAnt = esp_disp;
                        i_aux = f_start;
                    }
                } else if(esp_disp > esp_dispAnt){
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

void Fdisk::Eliminar(){
    if(ex.Ex_Name(name, path)){

    }
    else cout << "ERROR!! el nombre no existe en esta particion" << endl;
}

void Fdisk::Agregar(){
    if(ex.Ex_Name(name, path)){

    }
    else cout << "ERROR!! el nombre no existe en esta particion" << endl;
}

void Fdisk::testing(){

    archivo = fopen(path.c_str(), "rb");
    fseek(archivo, 0, SEEK_SET);
    fread(&mbr, sizeof(mbr), 1, archivo);
    cout << "MBR:" << endl;
    cout << "Size: " << mbr.size << endl;
    cout << "Fit: " << mbr.fit << endl;

    for(int i = 0; i < 4; i++){
        part = mbr.p[i];
        cout << "Particion " << i + 1 << ":" << endl;
        cout << "\tNombre: " << part.name << endl;
        cout << "\tStatus: " << part.status << endl;
        cout << "\tType: " << part.type << endl;
        cout << "\tFit: " << part.fit << endl;
        cout << "\tStart: " << part.start << endl; 
        cout << "\tSize: " << part.size << endl;
        if(part.type == 'e'){
            f_start = part.start;
            i_aux = 1;
            do{
                fseek(archivo, f_start, SEEK_SET);
                fread(&ebr, sizeof(ebr), 1, archivo);
                cout << "\tParticion logica " << i_aux << ":" << endl;
                cout << "\t\tNombre: " << ebr.name << endl;
                cout << "\t\tStatus: " << ebr.status << endl;
                cout << "\t\tFit: " << ebr.fit << endl;
                cout << "\t\tStart: " << ebr.start << endl;
                cout << "\t\tSize: " << ebr.size << endl;
                f_start = ebr.next;
                i_aux++;
            }while(ebr.next != -1);
        }
    }

    fclose(archivo);

}
int Fdisk::Get_esp_dispPE(int start){
    for(int i = 0; i < 4; i++){
        if(mbr.p[i].start >= start && mbr.p[i].status == 'A')
            return mbr.p[i].start - start;
    }
    return mbr.size - start;
}
int Fdisk::Get_esp_dispL(int start){
    EBR ebr_aux = EBR();
    fseek(archivo, start, SEEK_SET);
    fread(&ebr_aux, sizeof(ebr_aux), 1, archivo);
    int ebr_next = start, esp_disp, ebr_esp = 0;
    while(true){
        if(ebr_aux.next == -1){
            esp_disp = f_sizeMax - ebr_esp;
            if(ebr_aux.status == 'A') esp_disp -= ebr_aux.size;
            return esp_disp;
        }
        if(ebr_aux.status == 'A') ebr_esp = ebr_aux.size;
        ebr_next = ebr_aux.next;
        fseek(archivo, ebr_next, SEEK_SET);
        fread(&ebr_aux, sizeof(ebr_aux), 1, archivo);
        if(ebr_aux.status == 'A') return ebr_next - ebr_esp;
    }
    return f_sizeMax;
}
