#include "../Headers.h"
#include <sstream>


int Get_Set::Get_esp_dispPE(int start){
    for(int i = 0; i < 4; i++){
        if(mbr.p[i].start >= start && mbr.p[i].status == 'A')
            return mbr.p[i].start - start;
    }
    return mbr.size - start;
}
int Get_Set::Get_esp_dispL(int start){
    Str::EBR ebr_aux = Str::EBR();
    fseek(archivo, start, SEEK_SET);
    fread(&ebr_aux, sizeof(ebr_aux), 1, archivo);
    int esp_disp, ebr_esp = 0;
    while(true){
        if(ebr_aux.next == -1){
            esp_disp = f_sizeMax - ebr_esp;
            if(ebr_aux.status == 'A') esp_disp -= ebr_aux.size;
            return esp_disp;
        }
        if(ebr_aux.status == 'A') ebr_esp = ebr_aux.size;
        fseek(archivo, ebr_aux.next, SEEK_SET);
        fread(&ebr_aux, sizeof(ebr_aux), 1, archivo);
        if(ebr_aux.status == 'A') return (ebr_aux.start -sizeof(mbr)) - start - ebr_esp;
    }
    return f_sizeMax;
}

Str::Montura* Get_Set::Get_Mount(string id){
    Str::Montura *m_aux = montura;
    string id_;
    do{
        id_ = "19" + to_string(m_aux->numero);
        id_ = id_ + m_aux->letra;
        if(id_ == id) return m_aux;
        m_aux = m_aux->next;
    }
    while(m_aux != nullptr);
    return nullptr;
}

void Get_Set::Ordernar_MBR(){
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
}
void Get_Set::SetMBR(){
    mbr = Str::MBR();
    size *= 1024;
    if(u == "m") size *= 1024;
    mbr.size = size - sizeof(mbr);
    mbr.fit = f[0];
    mbr.date = chrono::system_clock::to_time_t(chrono::system_clock::now());
    srand(time(NULL));
    mbr.signature = rand();
    part = Str::Particion();
    part.start = sizeof(mbr);
    part.size = 0;
    part.type = 'p';
    part.status = 'N';
    mbr.p[0] = mbr.p[1] = mbr.p[2] = mbr.p[3] = part;
}

int Get_Set::Get_StartPartitionPoint(string path, string name){
    archivo = fopen(path.c_str(), "rb");
    mbr = Str::MBR();
    fseek(archivo, 0, SEEK_SET);
    fread(&mbr, sizeof(mbr), 1, archivo);
    fclose(archivo);
    for(i_aux = 0; i_aux < 4; i_aux++){
        part = mbr.p[i_aux];
        if(part.status == 'A'){
            if(part.type != 'l'){
                if(strcmp(part.name, name.c_str()) == 0){
                    f_sizeMax = part.size;
                    return part.start;
                }
            }
            if(part.type == 'e'){
                archivo = fopen(path.c_str(), "rb");
                f_start = part.start;
                do{
                    fseek(archivo, f_start, SEEK_SET);
                    fread(&ebr, sizeof(ebr), 1, archivo);
                    if(ebr.status == 'A'){
                        if(strcmp(ebr.name, name.c_str()) == 0){
                            fclose(archivo);
                            type = "l";
                            f_sizeMax = ebr.size;
                            return ebr.start;
                        }
                    }
                    f_start = ebr.next;
                }while(ebr.next != -1);
                fclose(archivo);
            }
        }
    }
    return 0;
}


string Get_Set::Get_Date(time_t fecha){
    tm *t = localtime(&fecha);
    stringstream stream;
    stream << t->tm_mday << "/" << 1 + t->tm_mon << "/" << 1900 + t->tm_year << " " << 1 + t->tm_hour << ":" << 1 + t->tm_min << ":" << 1 + t->tm_sec;
    return stream.str();
}

char Get_Set::Get_FitType(string path, string name){
    archivo = fopen(path.c_str(), "rb");
    mbr = Str::MBR();
    fseek(archivo, 0, SEEK_SET);
    fread(&mbr, sizeof(mbr), 1, archivo);
    fclose(archivo);
    for(i_aux = 0; i_aux < 4; i_aux++){
        part = mbr.p[i_aux];
        if(part.status == 'A'){
            if(part.type != 'l'){
                if(strcmp(part.name, name.c_str()) == 0) return part.fit;
            }
            if(part.type == 'e'){
                archivo = fopen(path.c_str(), "rb");
                f_start = part.start;
                do{
                    fseek(archivo, f_start, SEEK_SET);
                    fread(&ebr, sizeof(ebr), 1, archivo);
                    if(ebr.status == 'A'){
                        if(strcmp(ebr.name, name.c_str()) == 0){
                            fclose(archivo);
                            type = "l";
                            return ebr.fit;
                        }
                    }
                    f_start = ebr.next;
                }while(ebr.next != -1);
                fclose(archivo);
            }
        }
    }
    return '0';
}

void Get_Set::Set_SuperBloque(int partition_size, int filesystem_type){
    superbloque = Str::Superbloque();
    if(filesystem_type == 0){
        i_aux = (partition_size - sizeof(superbloque))/(4 + sizeof(inodos) + 3*sizeof(bloques_carpeta));
        superbloque.s_bm_inode_start = sizeof(superbloque);
    }
    else{
        i_aux = (partition_size - sizeof(superbloque))/(4 + sizeof(journaling) + sizeof(inodos) + 3*sizeof(bloques_carpeta));
        superbloque.s_bm_inode_start = sizeof(superbloque) + i_aux*sizeof(journaling);
    }
    superbloque.s_filesystem_type = filesystem_type;
    superbloque.s_inodes_count = i_aux;
    superbloque.s_blocks_count = 3*i_aux;
    superbloque.s_free_blocks_count = 3*i_aux;
    superbloque.s_free_inodes_count = i_aux;
    superbloque.s_mtime = chrono::system_clock::to_time_t(chrono::system_clock::now());
    superbloque.s_umtime = chrono::system_clock::to_time_t(chrono::system_clock::now());
    superbloque.s_mnt_count = 0;
    superbloque.s_magic = 0xEF53;
    superbloque.s_inode_size = sizeof(inodos);
    superbloque.s_block_size = sizeof(bloques_carpeta);
    superbloque.s_first_ino = 0;
    superbloque.s_first_blo = 0;
    superbloque.s_bm_block_start = superbloque.s_bm_inode_start + i_aux;
    superbloque.s_inode_start = superbloque.s_bm_block_start + 3*i_aux;
    superbloque.s_block_start = superbloque.s_inode_start + i_aux*sizeof(inodos);
}
