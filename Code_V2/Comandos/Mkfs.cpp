#include "../Headers.h"

void Mkfs_::Inicializar(){
    error = false;

    id = "";
    type = "full";
    fs = "2fs";

    if(!Ingresar_Datos()) 
        if(Verificar_Datos()) 
            Ejecutar();
}

bool Mkfs_::Ingresar_Datos(){
    while(comando.length() > 0){
        comando_inicial = e.slower(comando);
        if(comando_inicial.find("-id=") == 0){
            error = i.Ing_Palabra("-id=");
            if(error) break;
            id = ing_palabra;
        }
        else if(comando_inicial.find("-type=") == 0){
            error = i.Ing_Palabra("-type=");
            if(error) break;
            type = ing_palabra;
        }
        else if(comando_inicial.find("-fs=") == 0){
            error = i.Ing_Palabra("-fs=");
            if(error) break;
            fs = ing_palabra;
        }
        else{
            error = i.Ing_Error();
            break;
        } 
    }
    return error;
}

bool Mkfs_::Verificar_Datos(){
    error = true;
    if(v.Ver_Id()) error = false;
    if(!v.Ver_Fs()) error = true;
    if(!v.Ver_Type2()) error = true;
    return !error;
}

void Mkfs_::Ejecutar(){
    if(ex.Ex_MonturaId(id)){
        m_actual = gs.Get_Mount(id);
        f_start = gs.Get_StartPartitionPoint(m_actual->path, m_actual->name);

        if(fs == "2fs") gs.Set_SuperBloque(f_sizeMax, 0);
        else gs.Set_SuperBloque(f_sizeMax, 1);

        fseek(archivo, f_start, SEEK_SET);
        fwrite(&superbloque, sizeof(superbloque), 1, archivo);

        char zero1[superbloque.s_inodes_count] { '0' };
        fseek(archivo, f_start + superbloque.s_bm_inode_start, SEEK_SET);
        fwrite(&zero1, sizeof(zero1), 1, archivo);
        char zero2[superbloque.s_blocks_count] { '0' };
        fseek(archivo, f_start + superbloque.s_bm_block_start, SEEK_SET);
        fwrite(&zero2, sizeof(zero2), 1, archivo);
        if(type == "full"){
            char zero3[superbloque.s_inodes_count*superbloque.s_inode_size + superbloque.s_blocks_count*superbloque.s_block_size] = {0};
            fseek(archivo, f_start + superbloque.s_inode_start, SEEK_SET);
            fwrite(&zero3, sizeof(zero3), 1, archivo);
        }

        uid = gid = 1; //id user, id grupo
        es.Esc_Crear_INodo(0, 0);

        e_path = "/e/f/user.txt";
        e_fit = m_actual->fit_type;
        e_texto = "1,G,root\n1,U,root,root,123\n";
        es.Esc_Crear_Archivo();
        e_path = "/a/b/user.txt";
        es.Esc_Crear_Archivo();
        e_path = "/e/b/user.txt";
        es.Esc_Crear_Archivo();

        fclose(archivo);
        cout << "Formateo realizado con éxito" << endl;
    }
    else cout << "ERROR!! id no existe" << endl;
}