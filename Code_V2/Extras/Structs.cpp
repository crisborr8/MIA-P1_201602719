#include "Structs.h"

struct Str::Particion{
    char status;
    char type;
    char fit;
    int start;
    int size;
    char name[16];
};
struct Str::EBR{
    char status;
    char fit;
    int start;
    int size;
    int next;
    char name[16];
};
struct Str::MBR{
    int size;
    time_t date;
    int signature;
    char fit;
    Particion p[4];
};


struct Str::Files{
    int numero;
    string file;
    Files* next;
};
struct Str::Montura{
    char letra;
    int numero;
    string path;
    string name;
    char fit_type;
    Montura* next;
};

struct Str::Journaling{
    char comando[50];
};
struct Str::Superbloque{
    int s_filesystem_type;
    int s_inodes_count;
    int s_blocks_count;
    int s_free_blocks_count;
    int s_free_inodes_count;
    time_t s_mtime;
    time_t s_umtime;
    int s_mnt_count;
    int s_magic;
    int s_inode_size;
    int s_block_size;
    int s_first_ino;
    int s_first_blo;
    int s_bm_inode_start;
    int s_bm_block_start;
    int s_inode_start;
    int s_block_start;
};
struct Str::Inodos{
    int i_uid;
    int i_gid;
    int i_size;
    time_t i_atime;
    time_t i_ctime;
    time_t i_mtime;
    int i_block[15];
    char i_type;
    int i_perm;
};

//Cada Bloque mide 64Bits
struct Str::Bloques_content{ //12*1 + 1*4 = 16
    char b_name[12];
    int b_inodo;
};
struct Str::Bloques_carpeta{//16 * 4 = 64
    Bloques_content b_content[4];
};
struct Str::Bloques_archivo{ //64 * 1 = 64
    char b_content[64];
};
struct Str::Bloques_apuntad{ //16 * 4 = 64
    int b_pointer[16];
};