#include "../Headers.h"

void Escritura::Esc_SetNew_INodo(){
    inodos = Str::Inodos();
    inodos.i_uid = uid;
    inodos.i_gid = gid;
    inodos.i_size = 0;
    inodos.i_atime = chrono::system_clock::to_time_t(chrono::system_clock::now());
    inodos.i_ctime = chrono::system_clock::to_time_t(chrono::system_clock::now());
    inodos.i_mtime = chrono::system_clock::to_time_t(chrono::system_clock::now());
    for(int i = 0; i < 15; i++) inodos.i_block[i] = -1;
    inodos.i_type = type_inodo;
    inodos.i_perm = 770;
}
void Escritura::Esc_SetNew_BloqueCarpeta(){
    bloques_content = Str::Bloques_content();
    strcpy(bloques_content.b_name, "");
    bloques_content.b_inodo = -1;
    bloques_carpeta = Str::Bloques_carpeta();
    for(int i = 0; i < 4; i++) bloques_carpeta.b_content[i] = bloques_content;
}
void Escritura::Esc_SetNew_BloqueApuntad(){
    bloques_apuntad = Str::Bloques_apuntad();
    for(int i = 0; i < 16; i++) bloques_apuntad.b_pointer[i] = -1;
}
void Escritura::Esc_SetNew_BloqueArchivo(){
    bloques_archivo = Str::Bloques_archivo();
    for(int k = 0; k < 64; k++) bloques_archivo.b_content[k] = 0;
}

void Escritura::Esc_Crear_INodo(int pos_inodo, int padre){
    if(!esArchivo){
        if(pos_inodo == padre) type_inodo = 0;
        Esc_SetNew_INodo();
        int pos_bloque = Esc_GetFree_Bloque();
        inodos.i_block[0] = pos_bloque;
        Esc_Updt_INodo(pos_inodo);
        Esc_Bitmap_INodo(pos_inodo, 1);
        Esc_Crear_BloqueCarpeta(pos_bloque);
        strcpy(bloques_carpeta.b_content[0].b_name, ".");
        bloques_carpeta.b_content[0].b_inodo = pos_inodo;
        strcpy(bloques_carpeta.b_content[1].b_name, "..");
        bloques_carpeta.b_content[1].b_inodo = padre;
        Esc_Updt_BloqueCarpeta(pos_bloque);
    }
    else{
        Esc_Crear_INodoArchivo(pos_inodo);
        Esc_FitSize(inodos.i_size ,padre);
    }
}
void Escritura::Esc_Crear_INodoArchivo(int pos_inodo){
    type_inodo = 1;
    Esc_SetNew_INodo();
    Esc_Updt_INodo(pos_inodo);
    Esc_Bitmap_INodo(pos_inodo, 1);
    while(e_texto.length() > 0){
        for(int i = 0; i < 15; i++){
            if(inodos.i_block[i] == -1){
                inodos.i_block[i] = Esc_GetFree_Bloque();
                Esc_Updt_INodo(pos_inodo);
                if(i < 12) Esc_Crear_BloqueArchivo(inodos.i_block[i]);
                else if(i == 12) Esc_Crear_BloqueApuntad_1(inodos.i_block[i]);
                else if(i == 13) Esc_Crear_BloqueApuntad_2(inodos.i_block[i]);
                else Esc_Crear_BloqueApuntad_3(inodos.i_block[i]);
            }
            else if(i >= 12){
                Esc_Read_BloqueApuntad(inodos.i_block[i]);
                if(i == 12){
                    for(int ba_1 = 0; ba_1 < 16; ba_1++){
                        if(bloques_apuntad.b_pointer[ba_1] == -1){
                            bloques_apuntad.b_pointer[ba_1] = Esc_GetFree_Bloque();
                            Esc_Updt_BloqueApuntad(inodos.i_block[i]);
                            Esc_Crear_BloqueArchivo(bloques_apuntad.b_pointer[ba_1]);
                        }
                        if(e_texto.length() > 0) break;
                    }
                }
                else if(i == 13){
                    Str::Bloques_apuntad bloques_apuntad2 = bloques_apuntad;
                    for(int ba_2 = 0; ba_2 < 16; ba_2++){
                        if(bloques_apuntad2.b_pointer[ba_2] == -1){
                            bloques_apuntad.b_pointer[ba_2] = Esc_GetFree_Bloque();
                            Esc_Updt_BloqueApuntad(inodos.i_block[i]);
                            Esc_Crear_BloqueApuntad_1(bloques_apuntad.b_pointer[ba_2]);
                        }
                        else {
                            Esc_Read_BloqueApuntad(bloques_apuntad2.b_pointer[ba_2]);
                            for(int ba_1 = 0; ba_1 < 16; ba_1++){
                                if(bloques_apuntad.b_pointer[ba_1] == -1){
                                    bloques_apuntad.b_pointer[ba_1] = Esc_GetFree_Bloque();
                                    Esc_Updt_BloqueApuntad(inodos.i_block[i]);
                                    Esc_Crear_BloqueArchivo(bloques_apuntad.b_pointer[ba_1]);
                                }
                                if(e_texto.length() > 0) break;
                            }
                        }
                        if(e_texto.length() > 0) break;
                    }
                }
                else{
                    Str::Bloques_apuntad bloques_apuntad3 = bloques_apuntad;
                    Str::Bloques_apuntad bloques_apuntad2;
                    for(int ba_3 = 0; ba_3 < 16; ba_3++){
                        if(bloques_apuntad3.b_pointer[ba_3] == -1){
                            bloques_apuntad.b_pointer[ba_3] = Esc_GetFree_Bloque();
                            Esc_Updt_BloqueApuntad(inodos.i_block[i]);
                            Esc_Crear_BloqueApuntad_2(bloques_apuntad.b_pointer[ba_3]);
                        }
                        else{
                            Esc_Read_BloqueApuntad(bloques_apuntad3.b_pointer[ba_3]);
                            bloques_apuntad2 = bloques_apuntad;
                            for(int ba_2 = 0; ba_2 < 16; ba_2++){
                                if(bloques_apuntad2.b_pointer[ba_2] == -1){
                                    bloques_apuntad.b_pointer[ba_2] = Esc_GetFree_Bloque();
                                    Esc_Updt_BloqueApuntad(inodos.i_block[i]);
                                    Esc_Crear_BloqueApuntad_1(bloques_apuntad.b_pointer[ba_2]);
                                }
                                else {
                                    Esc_Read_BloqueApuntad(bloques_apuntad2.b_pointer[ba_2]);
                                    for(int ba_1 = 0; ba_1 < 16; ba_1++){
                                        if(bloques_apuntad.b_pointer[ba_1] == -1){
                                            bloques_apuntad.b_pointer[ba_1] = Esc_GetFree_Bloque();
                                            Esc_Updt_BloqueApuntad(inodos.i_block[i]);
                                            Esc_Crear_BloqueArchivo(bloques_apuntad.b_pointer[ba_1]);
                                        }
                                        if(e_texto.length() > 0) break;
                                    }
                                }
                                if(e_texto.length() > 0) break;
                            }
                        }
                        if(e_texto.length() > 0) break;
                    }
                }
            }
            if(e_texto.length() > 0) break;
        }
    }
    Esc_Updt_INodo(pos_inodo);
    type_inodo = 0;
}
void Escritura::Esc_Crear_BloqueArchivo(int pos_arch){
    Esc_SetNew_BloqueArchivo();
    Esc_Updt_BloqueArchivo(pos_arch);
    Esc_Bitmap_Bloque(pos_arch, 1);

    int i = 0;
    for(; i < sizeof(bloques_archivo); i++){
        if(e_texto.length() == 0) break;
        bloques_archivo.b_content[i] = e_texto[0];
        e_texto = e_texto.substr(1, e_texto.length());
    }
    inodos.i_size += i;
    Esc_Updt_BloqueArchivo(pos_arch);
}
void Escritura::Esc_Crear_BloqueCarpeta(int pos_carp){
    Esc_SetNew_BloqueCarpeta();
    Esc_Updt_BloqueCarpeta(pos_carp);
    Esc_Bitmap_Bloque(pos_carp, 1);
}
void Escritura::Esc_Crear_BloqueApuntad_1(int pos_apt1){
    Esc_SetNew_BloqueApuntad();
    int pos_bloque = Esc_GetFree_Bloque();
    bloques_apuntad.b_pointer[0] = pos_bloque;
    Esc_Updt_BloqueApuntad(pos_apt1);
    Esc_Bitmap_Bloque(pos_apt1, 1);

    if(type_inodo == 0) Esc_Crear_BloqueCarpeta(pos_bloque);
    else Esc_Crear_BloqueArchivo(pos_bloque);
}
void Escritura::Esc_Crear_BloqueApuntad_2(int pos_apt2){
    Esc_SetNew_BloqueApuntad();
    int pos_bloque = Esc_GetFree_Bloque();
    bloques_apuntad.b_pointer[0] = pos_bloque;
    Esc_Updt_BloqueApuntad(pos_apt2);
    Esc_Bitmap_Bloque(pos_apt2, 1);

    Esc_Crear_BloqueApuntad_1(pos_bloque);
}
void Escritura::Esc_Crear_BloqueApuntad_3(int pos_apt3){
    Esc_SetNew_BloqueApuntad();
    int pos_bloque = Esc_GetFree_Bloque();
    bloques_apuntad.b_pointer[0] = pos_bloque;
    Esc_Updt_BloqueApuntad(pos_apt3);
    Esc_Bitmap_Bloque(pos_apt3, 1);

    Esc_Crear_BloqueApuntad_2(pos_bloque);
}

void Escritura::Esc_Crear_Archivo(){
    //esArchivo = true;
    int pos = Esc_Crear_Carpeta();
    cout << "Puesto el ultimo en: " << pos << endl;
    esArchivo = false;
}
int Escritura::Esc_Crear_Carpeta(){
    string pth;
    e_path += "/";
    bool ingresado;
    type_inodo = 0;
    int pos = 0, pos_aux;
    while(e_path.length() > 0){
        pth = e_path.substr(0, e_path.find_first_of('/'));
        e_path = e_path.substr(e_path.find_first_of('/') + 1, e_path.length());
        Esc_Read_INodo(pos);
        pos_aux = Esc_GetPos_INodo(pth);
        if(pos_aux == -1){
            ingresado = false;
            for(int i = 0; i < 15; i++){
                if(inodos.i_block[i] == -1){
                    inodos.i_block[i] = Esc_GetFree_Bloque();
                    Esc_Updt_INodo(pos);
                    if(i < 12){
                        Esc_Crear_BloqueCarpeta(inodos.i_block[i]);
                        pos_aux = Esc_Crear_Carpeta_BloqueCarpeta(inodos.i_block[i], pos, 0, pth);
                    }
                    else{
                        if(i == 12) Esc_Crear_BloqueApuntad_1(inodos.i_block[i]);
                        else if(i == 13) Esc_Crear_BloqueApuntad_2(inodos.i_block[i]);
                        else Esc_Crear_BloqueApuntad_3(inodos.i_block[i]);
                        pos_aux = Esc_Crear_Carpeta_BloqueCarpeta(bloques_apuntad.b_pointer[0], pos, 0, pth);
                    }
                    break;
                }
                else{
                    if(i == 0){
                        Esc_Read_BloqueCarpeta(inodos.i_block[i]);
                        for(int bc = 2; bc < 4; bc++){
                            if(bloques_carpeta.b_content[bc].b_inodo == -1){
                                pos_aux = Esc_Crear_Carpeta_BloqueCarpeta(inodos.i_block[i], pos, bc, pth);
                                ingresado = true;
                                break;
                            }
                        }
                    }
                    else if(i < 12){
                        Esc_Read_BloqueCarpeta(inodos.i_block[i]);
                        for(int bc = 0; bc < 4; bc++){
                            if(bloques_carpeta.b_content[bc].b_inodo == -1){
                                pos_aux = Esc_Crear_Carpeta_BloqueCarpeta(inodos.i_block[i], pos, bc, pth);
                                ingresado = true;
                                break;
                            }
                        }
                    }
                    else if(i == 12){
                        Esc_Read_BloqueApuntad(inodos.i_block[i]);
                        for(int ba_1 = 0; ba_1 < 16; ba_1++){
                            if(bloques_apuntad.b_pointer[ba_1] == -1){
                                bloques_apuntad.b_pointer[ba_1] = Esc_GetFree_Bloque();
                                Esc_Updt_BloqueApuntad(inodos.i_block[i]);
                                Esc_Crear_BloqueCarpeta(bloques_apuntad.b_pointer[ba_1]);
                                pos_aux = Esc_Crear_Carpeta_BloqueCarpeta(bloques_apuntad.b_pointer[ba_1], pos, 0, pth);
                                ingresado = true;
                                break;
                            }
                            else{
                                Esc_Read_BloqueCarpeta(bloques_apuntad.b_pointer[ba_1]);
                                for(int bc = 0; bc < 4; bc++){
                                    if(bloques_carpeta.b_content[bc].b_inodo == -1){
                                        pos_aux = Esc_Crear_Carpeta_BloqueCarpeta(bloques_apuntad.b_pointer[ba_1], pos, bc, pth);
                                        ingresado = true;
                                        break;
                                    }
                                }
                            }
                            if(ingresado) break;
                        }
                    }
                    else if(i == 13){
                        Esc_Read_BloqueApuntad(inodos.i_block[i]);
                        Str::Bloques_apuntad bloques_apuntad2 = bloques_apuntad;
                        for(int ba_2 = 0; ba_2 < 16; ba_2++){
                            if(bloques_apuntad2.b_pointer[ba_2] == -1){
                                bloques_apuntad.b_pointer[ba_2] = Esc_GetFree_Bloque();
                                Esc_Updt_BloqueApuntad(inodos.i_block[i]);
                                Esc_Crear_BloqueApuntad_1(bloques_apuntad.b_pointer[ba_2]);
                                pos_aux = Esc_Crear_Carpeta_BloqueCarpeta(bloques_apuntad.b_pointer[0], pos, 0, pth);
                                ingresado = true;
                                break;
                            }
                            else {
                                Esc_Read_BloqueApuntad(bloques_apuntad2.b_pointer[ba_2]);
                                for(int ba_1 = 0; ba_1 < 16; ba_1++){
                                    if(bloques_apuntad.b_pointer[ba_1] == -1){
                                        bloques_apuntad.b_pointer[ba_1] = Esc_GetFree_Bloque();
                                        Esc_Updt_BloqueApuntad(bloques_apuntad2.b_pointer[ba_2]);
                                        Esc_Crear_BloqueCarpeta(bloques_apuntad.b_pointer[ba_1]);
                                        pos_aux = Esc_Crear_Carpeta_BloqueCarpeta(bloques_apuntad.b_pointer[ba_1], pos, 0, pth);
                                        ingresado = true;
                                        break;
                                    }
                                    else{
                                        Esc_Read_BloqueCarpeta(bloques_apuntad.b_pointer[ba_1]);
                                        for(int bc = 0; bc < 4; bc++){
                                            if(bloques_carpeta.b_content[bc].b_inodo == -1){
                                                pos_aux = Esc_Crear_Carpeta_BloqueCarpeta(bloques_apuntad.b_pointer[ba_1], pos, bc, pth);
                                                ingresado = true;
                                                break;
                                            }
                                        }
                                    }
                                    if(ingresado) break;
                                }
                            }
                            if(ingresado) break;
                        }
                    }
                    else{
                        Esc_Read_BloqueApuntad(inodos.i_block[i]);
                        Str::Bloques_apuntad bloques_apuntad3 = bloques_apuntad;
                        Str::Bloques_apuntad bloques_apuntad2;
                        for(int ba_3 = 0; ba_3 < 16; ba_3++){
                            if(bloques_apuntad3.b_pointer[ba_3] == -1){
                                bloques_apuntad.b_pointer[ba_3] = Esc_GetFree_Bloque();
                                Esc_Updt_BloqueApuntad(inodos.i_block[i]);
                                Esc_Crear_BloqueApuntad_2(bloques_apuntad.b_pointer[ba_3]);
                                pos_aux = Esc_Crear_Carpeta_BloqueCarpeta(bloques_apuntad.b_pointer[0], pos, 0, pth);
                                ingresado = true;
                                break;
                            }
                            else{
                                Esc_Read_BloqueApuntad(bloques_apuntad3.b_pointer[ba_3]);
                                bloques_apuntad2 = bloques_apuntad;
                                for(int ba_2 = 0; ba_2 < 16; ba_2++){
                                    if(bloques_apuntad2.b_pointer[ba_2] == -1){
                                        bloques_apuntad.b_pointer[ba_2] = Esc_GetFree_Bloque();
                                        Esc_Updt_BloqueApuntad(bloques_apuntad3.b_pointer[ba_3]);
                                        Esc_Crear_BloqueApuntad_1(bloques_apuntad.b_pointer[ba_2]);
                                        pos_aux = Esc_Crear_Carpeta_BloqueCarpeta(bloques_apuntad.b_pointer[0], pos, 0, pth);
                                        ingresado = true;
                                        break;
                                    }
                                    else {
                                        Esc_Read_BloqueApuntad(bloques_apuntad2.b_pointer[ba_2]);
                                        for(int ba_1 = 0; ba_1 < 16; ba_1++){
                                            if(bloques_apuntad.b_pointer[ba_1] == -1){
                                                bloques_apuntad.b_pointer[ba_1] = Esc_GetFree_Bloque();
                                                Esc_Updt_BloqueApuntad(bloques_apuntad2.b_pointer[ba_2]);
                                                Esc_Crear_BloqueCarpeta(bloques_apuntad.b_pointer[ba_1]);
                                                pos_aux = Esc_Crear_Carpeta_BloqueCarpeta(bloques_apuntad.b_pointer[ba_1], pos, 0, pth);
                                                ingresado = true;
                                                break;
                                            }
                                            else{
                                                Esc_Read_BloqueCarpeta(bloques_apuntad.b_pointer[ba_1]);
                                                for(int bc = 0; bc < 4; bc++){
                                                    if(bloques_carpeta.b_content[bc].b_inodo == -1){
                                                        pos_aux = Esc_Crear_Carpeta_BloqueCarpeta(bloques_apuntad.b_pointer[ba_1], pos, bc, pth);
                                                        ingresado = true;
                                                        break;
                                                    }
                                                }
                                            }
                                            if(ingresado) break;
                                        }
                                    }
                                    if(ingresado) break;
                                }
                            }
                            if(ingresado) break;
                        }
                    }
                }
                if(ingresado) break;
            }
        }
        pos = pos_aux;
    }
    return pos;
}
int Escritura::Esc_Crear_Carpeta_BloqueCarpeta(int updt_bc, int pos, int bc, string pth){
    int newpos = Esc_GetFree_INodo();
    bloques_carpeta.b_content[bc].b_inodo = newpos;
    strcpy(bloques_carpeta.b_content[bc].b_name, pth.c_str());
    Esc_Updt_BloqueCarpeta(updt_bc);
    Esc_Crear_INodo(newpos, pos);
    cout << "-------------------" << endl;
    cout << "ID inodo: " << newpos << endl;
    cout << "ID apt: " << inodos.i_block[0] << endl;
    return newpos;
}

void Escritura::Esc_Updt_INodo(int pos){
    inodos.i_mtime = chrono::system_clock::to_time_t(chrono::system_clock::now());
    fseek(archivo, f_start + superbloque.s_inode_start + pos*superbloque.s_inode_size, SEEK_SET);
    fwrite(&inodos, sizeof(inodos), 1, archivo);
}
void Escritura::Esc_Updt_BloqueArchivo(int pos){
    fseek(archivo, f_start + superbloque.s_block_start + pos*superbloque.s_block_size, SEEK_SET);
    fwrite(&bloques_archivo, sizeof(bloques_archivo), 1, archivo);
}
void Escritura::Esc_Updt_BloqueApuntad(int pos){
    fseek(archivo, f_start + superbloque.s_block_start + pos*superbloque.s_block_size, SEEK_SET);
    fwrite(&bloques_apuntad, sizeof(bloques_apuntad), 1, archivo);
}
void Escritura::Esc_Updt_BloqueCarpeta(int pos){
    fseek(archivo, f_start + superbloque.s_block_start + pos*superbloque.s_block_size, SEEK_SET);
    fwrite(&bloques_carpeta, sizeof(bloques_carpeta), 1, archivo);
}

void Escritura::Esc_Read_Superbloque(){
    fseek(archivo, f_start, SEEK_SET);
    fread(&superbloque, sizeof(superbloque), 1, archivo);
}
void Escritura::Esc_Read_INodo(int pos){
    fseek(archivo, f_start + superbloque.s_inode_start + pos*superbloque.s_inode_size, SEEK_SET);
    fread(&inodos, sizeof(inodos), 1, archivo);
    inodos.i_atime = chrono::system_clock::to_time_t(chrono::system_clock::now());
    fwrite(&inodos, sizeof(inodos), 1, archivo);
}
void Escritura::Esc_Read_BloqueApuntad(int pos){
    fseek(archivo, f_start + superbloque.s_block_start + pos*superbloque.s_block_size, SEEK_SET);
    fread(&bloques_apuntad, sizeof(bloques_apuntad), 1, archivo);
}
void Escritura::Esc_Read_BloqueArchivo(int pos){
    fseek(archivo, f_start + superbloque.s_block_start + pos*superbloque.s_block_size, SEEK_SET);
    fread(&bloques_archivo, sizeof(bloques_archivo), 1, archivo);
}
void Escritura::Esc_Read_BloqueCarpeta(int pos){
    fseek(archivo, f_start + superbloque.s_block_start + pos*superbloque.s_block_size, SEEK_SET);
    fread(&bloques_carpeta, sizeof(bloques_carpeta), 1, archivo);
}

void Escritura::Esc_Bitmap_INodo(int pos, int i){
    fseek(archivo, f_start + superbloque.s_bm_inode_start + pos, SEEK_SET);
    fwrite(to_string(i).c_str(), 1, 1, archivo);

    superbloque.s_free_inodes_count -= i;

    fseek(archivo, f_start + superbloque.s_bm_inode_start, SEEK_SET);
    unsigned char bitmapINodos [superbloque.s_inodes_count];
    fread(bitmapINodos, sizeof(bitmapINodos), 1, archivo);

    for(i = 0; i < superbloque.s_inodes_count; i++) if(bitmapINodos[i] != '1') break; 
    superbloque.s_first_blo = i;
    fseek(archivo, f_start, SEEK_SET);
    fwrite(&superbloque, sizeof(superbloque), 1, archivo);
}
void Escritura::Esc_Bitmap_Bloque(int pos, int i){
    fseek(archivo, f_start + superbloque.s_bm_block_start + pos, SEEK_SET);
    fwrite(to_string(i).c_str(), 1, 1, archivo);

    superbloque.s_free_blocks_count -= i;
    
    fseek(archivo, f_start + superbloque.s_bm_block_start, SEEK_SET);
    unsigned char bitmapBloques [superbloque.s_blocks_count];
    fread(bitmapBloques, sizeof(bitmapBloques), 1, archivo);

    for(i = 0; i < superbloque.s_blocks_count; i++) if(bitmapBloques[i] != '1') break; 
    superbloque.s_first_blo = i;
    fseek(archivo, f_start, SEEK_SET);
    fwrite(&superbloque, sizeof(superbloque), 1, archivo);
}

int Escritura::Esc_GetFree_INodo(){
    fseek(archivo, f_start + superbloque.s_bm_inode_start, SEEK_SET);
    unsigned char bitmapINodos [superbloque.s_inodes_count];
    fread(bitmapINodos, sizeof(bitmapINodos), 1, archivo);

    if(e_fit == 'f'){
        for(int i = 0; i < superbloque.s_inodes_count; i++) 
            if(bitmapINodos[i] != '1') return i;
    }

    int esp_act = 0, esp_pref = 0;
    int i_act = 0, i_ant = -1, i_pref = -1;
    if(e_fit == 'b') esp_pref =superbloque.s_inodes_count;
    for(int i = 0; i < superbloque.s_inodes_count; i++){
        if(bitmapINodos[i] == '0'){
            if(esp_act == 0) i_ant = i;
            esp_act++;
        }
        else{
            if(esp_act != 0){
                if(e_fit == 'w'){ if(esp_act > esp_pref) i_pref = i_ant; }
                else if(esp_act < esp_pref && esp_act != 0) i_pref = i_ant;
            }
            i_act = i;
            esp_act = 0;
        }
    }
    if(i_pref == -1 && i_ant != -1) return i_ant;
    return i_pref;
}
int Escritura::Esc_GetFree_Bloque(){
    fseek(archivo, f_start + superbloque.s_bm_block_start, SEEK_SET);
    unsigned char bitmapBloques [superbloque.s_blocks_count];
    fread(bitmapBloques, sizeof(bitmapBloques), 1, archivo);

   if(e_fit == 'f'){
        for(int i = 0; i < superbloque.s_blocks_count; i++) 
            if(bitmapBloques[i] != '1') return i;
    }

    int esp_act = 0, esp_pref = 0;
    int i_act = 0, i_ant = -1, i_pref = -1;
    if(e_fit == 'b') esp_pref =superbloque.s_blocks_count;
    for(int i = 0; i < superbloque.s_blocks_count; i++){
        if(bitmapBloques[i] == '0'){
            if(esp_act == 0) i_ant = i;
            esp_act++;
        }
        else{
            if(esp_act != 0){
                if(e_fit == 'w'){ if(esp_act > esp_pref) i_pref = i_ant; }
                else if(esp_act < esp_pref && esp_act != 0) i_pref = i_ant;
            }
            i_act = i;
            esp_act = 0;
        }
    }
    if(i_pref == -1 && i_ant != -1) return i_ant;
    return i_pref;
}

int Escritura::Esc_GetPos_INodo(string pth){
    for(int i = 0; i < 15; i++){
        if(inodos.i_block[i] != -1){
            if(i == 0){
                Esc_Read_BloqueCarpeta(inodos.i_block[i]);
                for(int bc = 2; bc < 4; bc++){
                    if(bloques_carpeta.b_content[bc].b_inodo != -1){
                        if(strcmp(bloques_carpeta.b_content[bc].b_name, pth.c_str()) == 0)
                            return bloques_carpeta.b_content[bc].b_inodo;
                    }
                }
            }
            else if(i < 12){
                Esc_Read_BloqueCarpeta(inodos.i_block[i]);
                for(int bc = 0; bc < 4; bc++){
                    if(bloques_carpeta.b_content[bc].b_inodo != -1){
                        if(strcmp(bloques_carpeta.b_content[bc].b_name, pth.c_str()) == 0)
                            return bloques_carpeta.b_content[bc].b_inodo;
                    }
                }
            }
            else if(i == 12){
                Esc_Read_BloqueApuntad(inodos.i_block[i]);
                for(int ba_1 = 0; ba_1 < 16; ba_1++){
                    if(bloques_apuntad.b_pointer[ba_1] != -1){
                        Esc_Read_BloqueCarpeta(bloques_apuntad.b_pointer[ba_1]);
                        for(int bc = 0; bc < 4; bc++){
                            if(bloques_carpeta.b_content[bc].b_inodo != -1){
                                if(strcmp(bloques_carpeta.b_content[bc].b_name, pth.c_str()) == 0)
                                    return bloques_carpeta.b_content[bc].b_inodo;
                            }
                        }
                    }
                }
            }
            else if(i == 13){
                Esc_Read_BloqueApuntad(inodos.i_block[i]);
                Str::Bloques_apuntad bloques_apuntad2 = bloques_apuntad;
                for(int ba_2 = 0; ba_2 < 16; ba_2++){
                    if(bloques_apuntad2.b_pointer[ba_2] != -1){
                        Esc_Read_BloqueApuntad(bloques_apuntad2.b_pointer[ba_2]);
                        for(int ba_1 = 0; ba_1 < 16; ba_1++){
                            if(bloques_apuntad.b_pointer[ba_1] != -1){
                                Esc_Read_BloqueCarpeta(bloques_apuntad.b_pointer[ba_1]);
                                for(int bc = 0; bc < 4; bc++){
                                    if(bloques_carpeta.b_content[bc].b_inodo != -1){
                                        if(strcmp(bloques_carpeta.b_content[bc].b_name, pth.c_str()) == 0)
                                            return bloques_carpeta.b_content[bc].b_inodo;
                                    }
                                }
                            }
                        }
                    }
                }
            }
            else{
                Esc_Read_BloqueApuntad(inodos.i_block[i]);
                Str::Bloques_apuntad bloques_apuntad3 = bloques_apuntad;
                Str::Bloques_apuntad bloques_apuntad2;
                for(int ba_3 = 0; ba_3 < 16; ba_3++){
                    if(bloques_apuntad3.b_pointer[ba_3] != -1){
                        Esc_Read_BloqueApuntad(bloques_apuntad3.b_pointer[ba_3]);
                        bloques_apuntad2 = bloques_apuntad;
                        for(int ba_2 = 0; ba_2 < 16; ba_2++){
                            if(bloques_apuntad2.b_pointer[ba_2] != -1){
                                Esc_Read_BloqueApuntad(bloques_apuntad2.b_pointer[ba_2]);
                                for(int ba_1 = 0; ba_1 < 16; ba_1++){
                                    if(bloques_apuntad.b_pointer[ba_1] != -1){
                                        Esc_Read_BloqueCarpeta(bloques_apuntad.b_pointer[ba_1]);
                                        for(int bc = 0; bc < 4; bc++){
                                            if(bloques_carpeta.b_content[bc].b_inodo != -1){
                                                if(strcmp(bloques_carpeta.b_content[bc].b_name, pth.c_str()) == 0)
                                                    return bloques_carpeta.b_content[bc].b_inodo;
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

void Escritura::Esc_FitSize(int size, int padre){
    while(padre != 0){
        Esc_Read_INodo(padre);
        inodos.i_size += size;
        Esc_Updt_INodo(padre);
        Esc_Read_BloqueCarpeta(inodos.i_block[0]);
        padre = bloques_carpeta.b_content[1].b_inodo;
    }
    Esc_Read_INodo(padre);
    inodos.i_size += size;
    Esc_Updt_INodo(padre);
}