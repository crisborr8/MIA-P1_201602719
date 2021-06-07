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
                else if(type == "l"){
                    i_aux = 6;
                    break;
                }
            }
            else if (part.status == 'A') i_aux++;
        }
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
                Crear_();
                break;
        }
    }
    else cout << "ERROR!! el nombre ya existe en esta particion" << endl;
}
void Fdisk::Crear_(){
    i_aux = -1;
    f_size = 0;
    f_start = 0;
    f_next = -1;

    if(mbr.fit == 'b') Crear_Bf();
    else if(mbr.fit == 'f') Crear_FF();
    else Crear_Wf();

    if(i_aux != -1){
        archivo = fopen(path.c_str(), "r+b");
        if(type == "l"){
            ebr.fit = f[0];
            strcpy(ebr.name, name.c_str());
            ebr.next = f_next;
            ebr.size = size;
            ebr.start = f_start;
            ebr.status = 'A';
            fseek(archivo, ebr.start - sizeof(ebr), SEEK_SET);
            fwrite(&ebr, sizeof(ebr), 1, archivo);
        }
        else{
            part.fit = f[0];
            strcpy(part.name, name.c_str());
            part.size = size;
            part.start = f_start;
            part.status = 'A';
            part.type = type[0];
            mbr.p[i_aux] = part;
            fseek(archivo, 0, SEEK_SET);
            fwrite(&mbr, sizeof(mbr), 1, archivo);
        }
        fclose(archivo);
        cout << "Particion creada con exito" << endl;
    }
    else cout << "ERROR!! no existe espacio suficiente para la particion" << endl;
}
void Fdisk::Crear_Bf(){
    for(int i = 0; i < 4; i++){
        part = mbr.p[i];
        if(type == "l"){
            if(part.type == 'e'){
                archivo = fopen(path.c_str(), "rb");
                f_start = part.start;
                do{
                    ebr = EBR();
                    fseek(archivo, f_start, SEEK_SET);
                    fread(&ebr, sizeof(ebr), 1, archivo);
                    


                    f_start = ebr.next;
                }while(ebr.next != -1);
                fclose(archivo);
                break;
            }
        }
        else{

        }
    }
}
void Fdisk::Crear_FF(){
    for(int i = 0; i < 4; i++){
        part = mbr.p[i];
        if(type == "l"){
            if(part.type == 'e'){
                archivo = fopen(path.c_str(), "rb");
                f_start = part.start;
                do{
                    ebr = EBR();
                    fseek(archivo, f_start, SEEK_SET);
                    fread(&ebr, sizeof(ebr), 1, archivo);
                    


                    f_start = ebr.next;
                }while(ebr.next != -1);
                fclose(archivo);
                break;
            }
        }
        else{

        }
    }
}
void Fdisk::Crear_Wf(){
    for(int i = 0; i < 4; i++){
        part = mbr.p[i];
        if(type == "l"){
            if(part.type == 'e'){
                archivo = fopen(path.c_str(), "rb");
                f_start = part.start;
                do{
                    ebr = EBR();
                    fseek(archivo, f_start, SEEK_SET);
                    fread(&ebr, sizeof(ebr), 1, archivo);
                    
                    

                    f_start = ebr.next;
                }while(ebr.next != -1);
                fclose(archivo);
                break;
            }
        }
        else{

        }
    }
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