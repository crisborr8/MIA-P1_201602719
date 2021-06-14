#include "../Headers.h"

void Escritura::Esc_INodo(int i){
    inodos.i_mtime = chrono::system_clock::to_time_t(chrono::system_clock::now());
    fseek(archivo, f_start + superbloque.s_inode_start + i*superbloque.s_inode_size, SEEK_SET);
    fwrite(&inodos, sizeof(inodos), 1, archivo);

    fseek(archivo, f_start + superbloque.s_bm_inode_start + i, SEEK_SET);
    fwrite("1", 1, 1, archivo);

    Esc_SuperBloque_INodeCount(1);
}

void Escritura::Esc_BloqueCarpeta(int i){
    fseek(archivo, f_start + superbloque.s_block_start + i*superbloque.s_block_size, SEEK_SET);
    fwrite(&bloques_carpeta, sizeof(bloques_carpeta), 1, archivo);

    fseek(archivo, f_start + superbloque.s_bm_block_start + i, SEEK_SET);
    fwrite("1", 1, 1, archivo);

    Esc_SuperBloque_BlockCount(1);
}

void Escritura::Esc_BloqueArchivo(int i){
    fseek(archivo, f_start + superbloque.s_block_start + i*superbloque.s_block_size, SEEK_SET);
    fwrite(&bloques_archivo, sizeof(bloques_archivo), 1, archivo);

    fseek(archivo, f_start + superbloque.s_bm_block_start + i, SEEK_SET);
    fwrite("1", 1, 1, archivo);

    Esc_SuperBloque_BlockCount(1);
}

void Escritura::Esc_BloqueApuntad(int i){
    fseek(archivo, f_start + superbloque.s_block_start + i*superbloque.s_block_size, SEEK_SET);
    fwrite(&bloques_apuntad, sizeof(bloques_apuntad), 1, archivo);

    fseek(archivo, f_start + superbloque.s_bm_block_start + i, SEEK_SET);
    fwrite("1", 1, 1, archivo);

    Esc_SuperBloque_BlockCount(1);
}

void Escritura::Esc_SuperBloque_BlockCount(int i){
    fseek(archivo, f_start, SEEK_SET);
    fread(&superbloque, sizeof(superbloque), 1, archivo);
    superbloque.s_blocks_count += i;

    char bitmapBloques[superbloque.s_blocks_count];
    fseek(archivo, f_start + superbloque.s_bm_block_start, SEEK_SET);
    fread(&bitmapBloques, sizeof(bitmapBloques), 1, archivo);

    for(i = 0; i < superbloque.s_blocks_count; i++) if(bitmapBloques[i] == '0') break; 
    superbloque.s_first_blo = i;

    fseek(archivo, f_start, SEEK_SET);
    fwrite(&superbloque, sizeof(superbloque), 1, archivo);
}

void Escritura::Esc_SuperBloque_INodeCount(int i){
    fseek(archivo, f_start, SEEK_SET);
    fread(&superbloque, sizeof(superbloque), 1, archivo);
    superbloque.s_inodes_count += i;

    char bitmapINodos[superbloque.s_inodes_count];
    fseek(archivo, f_start + superbloque.s_bm_inode_start, SEEK_SET);
    fread(&bitmapINodos, sizeof(bitmapINodos), 1, archivo);

    for(i = 0; i < superbloque.s_blocks_count; i++) if(bitmapINodos[i] == '0') break; 
    superbloque.s_first_blo = i;

    fseek(archivo, f_start, SEEK_SET);
    fwrite(&superbloque, sizeof(superbloque), 1, archivo);
}

void Escritura::Esc_EscrituraArchivo(){
    string fileName = e_path.substr(e_path.find_last_of('/') + 1, e_path.length());
    e_path = e_path.substr(0, e_path.find_last_of('/') + 1);
    Esc_EscrituraCarpeta();
    //otro codigo aqui....
}

void Escritura::Esc_EscrituraCarpeta(){
    e_path = e_path.substr(e_path.find_first_of('/') + 1, e_path.length());
    string pth;
    bool ingresado;
    int pos = 0, new_pos = 0, padre = 0;;
    while(e_path.length() > 0){
        pth = e_path.substr(0, e_path.find_first_of('/'));
        e_path = e_path.substr(e_path.find_first_of('/') + 1, e_path.length());
        new_pos = Esc_GetINodoPos(pth, pos);
        if(new_pos == -1){

            fseek(archivo, f_start + superbloque.s_inode_start + pos*superbloque.s_inode_size, SEEK_SET);
            fread(&inodos, sizeof(inodos), 1, archivo);
            ingresado = false;
        
            for(int a = 0; a < 15; a++){
                if(a == 0){
                    fseek(archivo, f_start + superbloque.s_block_start + inodos.i_block[a]*superbloque.s_block_size, SEEK_SET);
                    fread(&bloques_carpeta, sizeof(bloques_carpeta), 1, archivo);
                    for(int b = 2; b < 4; b++){
                        if(bloques_carpeta.b_content[b].b_inodo == -1){
                            new_pos = Esc_GetFreeINodo();
                            fseek(archivo, f_start + superbloque.s_block_start + inodos.i_block[a]*superbloque.s_block_size, SEEK_SET);
                            bloques_carpeta.b_content[b].b_inodo = new_pos;
                            strcpy(bloques_carpeta.b_content[b].b_name, pth.c_str());
                            fwrite(&bloques_carpeta, sizeof(bloques_carpeta), 1, archivo);
                            ingresado = true;
                            break;
                        }
                    }
                }
                else if(a < 12){
                    if(inodos.i_block[a] == -1){
                        inodos.i_block[a] = Esc_GetFreeBlock(); 
                        Esc_SetBloqueCarpeta();
                        new_pos = Esc_GetFreeINodo();
                        bloques_carpeta.b_content[0].b_inodo = new_pos;
                        strcpy(bloques_carpeta.b_content[0].b_name, pth.c_str());
                        Esc_BloqueCarpeta(inodos.i_block[a]);
                        ingresado = true;
                    }
                    else{
                        fseek(archivo, f_start + superbloque.s_block_start + inodos.i_block[a]*superbloque.s_block_size, SEEK_SET);
                        fread(&bloques_carpeta, sizeof(bloques_carpeta), 1, archivo);
                        for(int b = 0; b < 4; b++){
                            if(bloques_carpeta.b_content[b].b_inodo == -1){
                                new_pos = Esc_GetFreeINodo();
                                fseek(archivo, f_start + superbloque.s_block_start + inodos.i_block[a]*superbloque.s_block_size, SEEK_SET);
                                bloques_carpeta.b_content[b].b_inodo = new_pos;
                                strcpy(bloques_carpeta.b_content[b].b_name, pth.c_str());
                                fwrite(&bloques_carpeta, sizeof(bloques_carpeta), 1, archivo);
                                ingresado = true;
                                break;
                            }
                        }
                    }
                }
                else if(a == 12){
                    if(inodos.i_block[a] == -1){
                        inodos.i_block[a] = Esc_GetFreeBlock(); 
                        Esc_SetBloqueApuntad();
                        new_pos = Esc_GetFreeBlock();
                        bloques_apuntad.b_pointer[0] = new_pos;
                        Esc_BloqueApuntad(inodos.i_block[a]);
                            Esc_SetBloqueCarpeta();
                            new_pos = Esc_GetFreeINodo();
                            bloques_carpeta.b_content[0].b_inodo = new_pos;
                            strcpy(bloques_carpeta.b_content[0].b_name, pth.c_str());
                            Esc_BloqueCarpeta(bloques_apuntad.b_pointer[0]);
                        ingresado = true;
                    }
                    else{
                        fseek(archivo, f_start + superbloque.s_block_start + inodos.i_block[a]*superbloque.s_block_size, SEEK_SET);
                        fread(&bloques_apuntad, sizeof(bloques_apuntad), 1, archivo);
                        for(int a_i1 = 0; a_i1 < 16; a_i1++){
                            if(bloques_apuntad.b_pointer[a_i1] != -1){
                                fseek(archivo, f_start + superbloque.s_block_start + bloques_apuntad.b_pointer[a_i1]*superbloque.s_block_size, SEEK_SET);
                                fread(&bloques_carpeta, sizeof(bloques_carpeta), 1, archivo);
                                for(int b = 0; b < 4; b++){
                                    if(bloques_carpeta.b_content[b].b_inodo == -1){
                                        new_pos = Esc_GetFreeINodo();
                                        fseek(archivo, f_start + superbloque.s_block_start + inodos.i_block[a]*superbloque.s_block_size, SEEK_SET);
                                        bloques_carpeta.b_content[b].b_inodo = new_pos;
                                        strcpy(bloques_carpeta.b_content[b].b_name, pth.c_str());
                                        fwrite(&bloques_carpeta, sizeof(bloques_carpeta), 1, archivo);
                                        ingresado = true;
                                        break;
                                    }
                                }
                                if(ingresado) break;
                            }
                        }
                    }
                }
                else if(a == 13){
                    if(inodos.i_block[a] == -1){

                    }
                    else{
                        
                    }
                }
                else{
                    if(inodos.i_block[a] == -1){

                    }
                    else{
                        
                    }
                }
                if(ingresado) break;
            }
    
            fseek(archivo, f_start + superbloque.s_inode_start + pos*superbloque.s_inode_size, SEEK_SET);
            fread(&inodos, sizeof(inodos), 1, archivo);
            inodos.i_mtime = chrono::system_clock::to_time_t(chrono::system_clock::now());
            fwrite(&inodos, sizeof(inodos), 1, archivo);

            Esc_SetInodos(new_pos, 0); //actual, padre
            inodos.i_block[0] = Esc_GetFreeBlock(); //bloque al que apunta
            Esc_INodo(new_pos); //id - inodo actual
            Esc_BloqueCarpeta(inodos.i_block[0]); //id - bloque al que apunta

        }
        padre = pos = new_pos;
    }
}


int Escritura::Esc_GetFreeBlock(){
    char bitmapBloques[superbloque.s_blocks_count];
    fseek(archivo, f_start + superbloque.s_bm_block_start, SEEK_SET);
    fread(&bitmapBloques, sizeof(bitmapBloques), 1, archivo);

    int i_pref = 0, esp_pref = 0;
    int i_act = 0, esp_act = 0;
    if(e_fit == 'b') esp_pref =superbloque.s_blocks_count;
    for(int i = 0; i < superbloque.s_blocks_count; i++){
        if(bitmapBloques[i] == '0'){
            if(e_fit == 'f') return i;
            esp_act++;
            if(e_fit == 'w'){
                if(esp_act > esp_pref) i_pref = i_act;
            }
            else{
                if(esp_act < esp_pref) i_pref = i_act;
            }
        }
        else{
            i_act = i;
            esp_act = 0;
        }
    }

    return i_pref;
}

int Escritura::Esc_GetFreeINodo(){
    char bitmapINodos[superbloque.s_inodes_count];
    fseek(archivo, f_start + superbloque.s_bm_inode_start, SEEK_SET);
    fread(&bitmapINodos, sizeof(bitmapINodos), 1, archivo);

    int i_pref = 0, esp_pref = 0;
    int i_act = 0, esp_act = 0;
    if(e_fit == 'b') esp_pref =superbloque.s_inodes_count;
    for(int i = 0; i < superbloque.s_inodes_count; i++){
        if(bitmapINodos[i] == '0'){
            if(e_fit == 'f') return i;
            esp_act++;
            if(e_fit == 'w'){
                if(esp_act > esp_pref) i_pref = i_act;
            }
            else{
                if(esp_act < esp_pref) i_pref = i_act;
            }
        }
        else{
            i_act = i;
            esp_act = 0;
        }
    }

    return i_pref;
}

int Escritura::Esc_GetINodoPos(string pth, int pos){
    fseek(archivo, f_start + superbloque.s_inode_start + pos*superbloque.s_inode_size, SEEK_SET);
    fread(&inodos, sizeof(inodos), 1, archivo);
    inodos.i_atime = chrono::system_clock::to_time_t(chrono::system_clock::now());
    fwrite(&inodos, sizeof(inodos), 1, archivo);
    if(inodos.i_type == 0){
        for(int a = 0; a < 15; a++){
            if(inodos.i_block[a] != -1){
                if(a == 0){
                    fseek(archivo, f_start + superbloque.s_block_start + inodos.i_block[a]*superbloque.s_block_size, SEEK_SET);
                    fread(&bloques_carpeta, sizeof(bloques_carpeta), 1, archivo);
                    for(int b = 2; b < 4; b++){
                        if(bloques_carpeta.b_content[b].b_inodo != -1)
                            if(strcmp(bloques_carpeta.b_content[b].b_name, pth.c_str()) == 0)
                                return bloques_carpeta.b_content[b].b_inodo;
                    }
                }
                else if(a < 12){
                    fseek(archivo, f_start + superbloque.s_block_start + inodos.i_block[a]*superbloque.s_block_size, SEEK_SET);
                    fread(&bloques_carpeta, sizeof(bloques_carpeta), 1, archivo);
                    for(int b = 0; b < 4; b++){
                        if(bloques_carpeta.b_content[b].b_inodo != -1)
                            if(strcmp(bloques_carpeta.b_content[b].b_name, pth.c_str()) == 0)
                                return bloques_carpeta.b_content[b].b_inodo;
                    }
                }
                else if(a == 12){
                    fseek(archivo, f_start + superbloque.s_block_start + inodos.i_block[a]*superbloque.s_block_size, SEEK_SET);
                    fread(&bloques_apuntad, sizeof(bloques_apuntad), 1, archivo);
                    for(int a_i1 = 0; a_i1 < 16; a_i1++){
                        if(bloques_apuntad.b_pointer[a_i1] != -1){
                            fseek(archivo, f_start + superbloque.s_block_start + bloques_apuntad.b_pointer[a_i1]*superbloque.s_block_size, SEEK_SET);
                            fread(&bloques_carpeta, sizeof(bloques_carpeta), 1, archivo);
                            for(int b = 0; b < 4; b++){
                                if(bloques_carpeta.b_content[b].b_inodo != -1)
                                    if(strcmp(bloques_carpeta.b_content[b].b_name, pth.c_str()) == 0)
                                        return bloques_carpeta.b_content[b].b_inodo;
                            }
                        }
                    }
                }
                else if(a == 13){
                    Str::Bloques_apuntad bloques_apuntad2 = Str::Bloques_apuntad();
                    fseek(archivo, f_start + superbloque.s_block_start + inodos.i_block[a]*superbloque.s_block_size, SEEK_SET);
                    fread(&bloques_apuntad2, sizeof(bloques_apuntad2), 1, archivo);
                    for(int a_i2 = 0; a_i2 < 16; a_i2++){
                        if(bloques_apuntad2.b_pointer[a_i2] != -1){
                            fseek(archivo, f_start + superbloque.s_block_start + bloques_apuntad2.b_pointer[a_i2]*superbloque.s_block_size, SEEK_SET);
                            fread(&bloques_apuntad, sizeof(bloques_apuntad), 1, archivo);
                            for(int a_i1 = 0; a_i1 < 16; a_i1++){
                                if(bloques_apuntad.b_pointer[a_i1] != -1){
                                    fseek(archivo, f_start + superbloque.s_block_start + bloques_apuntad.b_pointer[a_i1]*superbloque.s_block_size, SEEK_SET);
                                    fread(&bloques_carpeta, sizeof(bloques_carpeta), 1, archivo);
                                    for(int b = 0; b < 4; b++){
                                        if(bloques_carpeta.b_content[b].b_inodo != -1)
                                            if(strcmp(bloques_carpeta.b_content[b].b_name, pth.c_str()) == 0)
                                                return bloques_carpeta.b_content[b].b_inodo;
                                    }
                                }
                            }
                        }
                    }
                }
                else{
                    Str::Bloques_apuntad bloques_apuntad3 = Str::Bloques_apuntad();
                    Str::Bloques_apuntad bloques_apuntad2 = Str::Bloques_apuntad();
                    fseek(archivo, f_start + superbloque.s_block_start + inodos.i_block[a]*superbloque.s_block_size, SEEK_SET);
                    fread(&bloques_apuntad3, sizeof(bloques_apuntad3), 1, archivo);
                    for(int a_i3 = 0; a_i3 < 16; a_i3++){
                        if(bloques_apuntad3.b_pointer[a_i3] != -1){
                            fseek(archivo, f_start + superbloque.s_block_start + bloques_apuntad3.b_pointer[a_i3]*superbloque.s_block_size, SEEK_SET);
                            fread(&bloques_apuntad2, sizeof(bloques_apuntad2), 1, archivo);
                            for(int a_i2 = 0; a_i2 < 16; a_i2++){
                                if(bloques_apuntad2.b_pointer[a_i2] != -1){
                                    fseek(archivo, f_start + superbloque.s_block_start + bloques_apuntad2.b_pointer[a_i2]*superbloque.s_block_size, SEEK_SET);
                                    fread(&bloques_apuntad, sizeof(bloques_apuntad), 1, archivo);
                                    for(int a_i1 = 0; a_i1 < 16; a_i1++){
                                        if(bloques_apuntad.b_pointer[a_i1] != -1){
                                            fseek(archivo, f_start + superbloque.s_block_start + bloques_apuntad.b_pointer[a_i1]*superbloque.s_block_size, SEEK_SET);
                                            fread(&bloques_carpeta, sizeof(bloques_carpeta), 1, archivo);
                                            for(int b = 0; b < 4; b++){
                                                if(bloques_carpeta.b_content[b].b_inodo != -1)
                                                    if(strcmp(bloques_carpeta.b_content[b].b_name, pth.c_str()) == 0)
                                                        return bloques_carpeta.b_content[b].b_inodo;
                                            }
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
    }
    return -1;
}


void Escritura::Esc_SetInodos(int actual, int padre){
    inodos = Str::Inodos();
    inodos.i_uid = uid;
    inodos.i_gid = gid;
    inodos.i_size = 0;
    inodos.i_atime = chrono::system_clock::to_time_t(chrono::system_clock::now());
    inodos.i_ctime = chrono::system_clock::to_time_t(chrono::system_clock::now());
    inodos.i_mtime = chrono::system_clock::to_time_t(chrono::system_clock::now());
    for(int i = 0; i < 15; i++) inodos.i_block[i] = -1;
    inodos.i_type = 0;
    inodos.i_perm = 770;

    Esc_SetBloqueCarpetaInicial(actual, padre);
}

void Escritura::Esc_SetBloqueCarpetaInicial(int actual, int padre){
    Esc_SetBloqueCarpeta();
    strcpy(bloques_carpeta.b_content[0].b_name, ".");
    bloques_carpeta.b_content[0].b_inodo = actual;
    strcpy(bloques_carpeta.b_content[1].b_name, "..");
    bloques_carpeta.b_content[1].b_inodo = padre;
}
void Escritura::Esc_SetBloqueCarpeta(){
    bloques_content = Str::Bloques_content();
    strcpy(bloques_content.b_name, "");
    bloques_content.b_inodo = -1;
    bloques_carpeta = Str::Bloques_carpeta();
    for(int i = 0; i < 4; i++) bloques_carpeta.b_content[i] = bloques_content;
}

void Escritura::Esc_SetBloqueApuntad(){
    bloques_apuntad = Str::Bloques_apuntad();
    for(int i = 0; i < 16; i++) bloques_apuntad.b_pointer[i] = -1;
}




