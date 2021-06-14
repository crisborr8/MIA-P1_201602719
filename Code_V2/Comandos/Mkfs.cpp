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

        archivo = fopen(m_actual->path.c_str(), "r+b");
        fseek(archivo, f_start, SEEK_SET);
        fwrite(&superbloque, sizeof(superbloque), 1, archivo);
        fseek(archivo, f_start + superbloque.s_bm_inode_start, SEEK_SET);
        fwrite("0", 1, 4*i_aux, archivo);
        if(type == "full"){
            fseek(archivo, f_start + superbloque.s_inode_start, SEEK_SET);
            fwrite("0", 1, sizeof(inodos)*i_aux + sizeof(bloques_carpeta)*3*i_aux, archivo);
        }

        uid = gid = 1; //id user, id grupo
        int id_inodo = es.Esc_GetFreeINodo();
        es.Esc_SetInodos(id_inodo, 0); //actual, padre
        inodos.i_block[0] = es.Esc_GetFreeBlock(); //bloque al que apunta
        es.Esc_INodo(id_inodo); //id - inodo actual
        es.Esc_BloqueCarpeta(inodos.i_block[0]); //id - bloque al que apunta

        e_path = "/user.txt";
        e_fit = m_actual->fit_type;
        e_texto = "1,G,root\n1,U,root,root,123\n";
        es.Esc_EscrituraArchivo();

        fclose(archivo);
        cout << "Formateo realizado con éxito" << endl;
    }
    else cout << "ERROR!! id no existe" << endl;
}