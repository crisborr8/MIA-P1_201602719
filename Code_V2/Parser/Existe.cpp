#include "../Headers.h"

bool Existe::Ex_Path_File(string path){
    if(FILE* f = fopen(path.c_str(), "rb")){
        fclose(f);
        return true;
    }
    return false;
}
bool Existe::Ex_Path_Folder(string path){
    return false;
}

bool Existe::Ex_Name(string name, string path){
    archivo = fopen(path.c_str(), "rb");
    mbr = MBR();
    fseek(archivo, 0, SEEK_SET);
    fread(&mbr, sizeof(mbr), 1, archivo);
    fclose(archivo);
    for(i_aux = 0; i_aux < 4; i_aux++){
        part = mbr.p[i_aux];
        if(part.status == 'A'){
            if(part.type == 'p'){
                if(strcmp(part.name, name.c_str())) return true;
            }
            else{
                archivo = fopen(path.c_str(), "rb");
                f_start = part.start;
                do{
                    ebr = EBR();
                    fseek(archivo, f_start, SEEK_SET);
                    fread(&ebr, sizeof(ebr), 1, archivo);
                    if(ebr.status == 'A'){
                        if(strcmp(ebr.name, name.c_str())){
                            fclose(archivo);
                            return true;
                        }
                    }
                    f_start = ebr.next;
                }while(ebr.next != -1);
                fclose(archivo);
            }
        }
    }
    return false;
}