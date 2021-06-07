#include "../Headers.h"

void Mkdisk::Inicializar(){
    error = false;
    
    path = "";
    size = 0;
    f = "ff";
    u = "m";

    if(!Ingresar_Datos()) 
        if(Verificar_Datos()) 
            Ejecutar();
}

bool Mkdisk::Ingresar_Datos(){
    while(comando.length() > 0){
        comando_inicial = e.slower(comando);
        if(comando_inicial.find("-f=") == 0){
            error = i.Ing_Palabra("-f=");
            if(error) break;
            f = ing_palabra;
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
        else if(comando_inicial.find("-size=") == 0){
            error = i.Ing_Numero("-size=");
            if(error) break;
            size = ing_numero;
        }
        else{
            error = i.Ing_Error();
            break;
        }
    }
    return error;
}

bool Mkdisk::Verificar_Datos(){
    if(v.Ver_Size())
    if(v.Ver_Path())
    if(v.Ver_F())
    if(v.Ver_U())
    return true;
    return false;
}

void Mkdisk::Ejecutar(){
    if(!ex.Ex_Path_File(path)){
        SetMBR();
        CrearDisco();
    }
    else cout << "ERROR!! Archivo ya existe" << endl;
}
void Mkdisk::SetMBR(){
    mbr = MBR();
    size *= 1000;
    if(u == "m") size *= 1000;
    mbr.size = size - sizeof(mbr);
    mbr.fit = f[0];
    mbr.date = chrono::system_clock::to_time_t(chrono::system_clock::now());
    srand(time(NULL));
    mbr.signature = rand();
    part = Particion();
    part.start = sizeof(mbr);
    part.size = 0;
    part.type = 'p';
    part.status = 'N';
    mbr.p[0] = mbr.p[1] = mbr.p[2] = mbr.p[3] = part;
}
void Mkdisk::CrearDisco(){
    archivo = NULL;
    archivo = fopen(path.c_str(), "w+b");
    fseek(archivo, size, SEEK_SET);
    fputc('\0', archivo);
    fclose(archivo);

    archivo = fopen(path.c_str(), "r+b");
    fseek(archivo, 0, SEEK_SET);
    fwrite(&mbr, sizeof(mbr), 1, archivo);
    fclose(archivo);

    cout << "Disco creado con exito!" << endl;
}