#include "../Headers.h"
#include <stack>

void Rep_::Inicializar(){
    error = false;

    name = "";
    path = "";
    id = "";
    ruta = "";

    if(!Ingresar_Datos()) 
        if(Verificar_Datos()) 
            Ejecutar();
}

bool Rep_::Ingresar_Datos(){
    while(comando.length() > 0){
        comando_inicial = e.slower(comando);
        if(comando_inicial.find("-path=") == 0){
            error = i.Ing_PalabraC("-path=");
            if(error) break;
            path = ing_palabra;
        } else if(comando_inicial.find("-name=") == 0){
            error = i.Ing_PalabraC("-name=");
            if(error) break;
            name = ing_palabra;
        } else if(comando_inicial.find("-id=") == 0){
            error = i.Ing_Palabra("-id=");
            if(error) break;
            id = ing_palabra;
        } else if(comando_inicial.find("-ruta=") == 0){
            error = i.Ing_PalabraC("-ruta=");
            if(error) break;
            ruta = ing_palabra;
        }
        else{
            error = i.Ing_Error();
            break;
        } 
    }
    return error;
}

bool Rep_::Verificar_Datos(){
    error = true;
    if(v.Ver_Path3()) error = false;
    if(!v.Ver_Id()) error = true;
    if(!v.Ver_Name()) error = true;
    return !error;
}

void Rep_::Ejecutar(){
    if(ex.Ex_MonturaId(id)){
        dot = "digraph G{";
        name = e.slower(name);
        m_actual = gs.Get_Mount(id);
        if(name == "mbr") Graph_mbr();
        else if(name == "disk") Graph_disk();
        else if(name == "inode") Graph_inode();
        else if(name == "journaling") Graph_journaling();
        else if(name == "block") Graph_block();
        else if(name == "bm_inode") Graph_bm_inode();
        else if(name == "bm_block") Graph_bm_block();
        else if(name == "tree") Graph_tree();
        else if(name == "sb") Graph_sb();
        else if(name == "file") Graph_file();
        else if(name == "ls") Graph_ls();
        else cout << "ERROR!! -name debe ser mbr, disk, inode, journaling, block, bm_inode, " <<
                "bm_block, tree, sb, file o ls" << endl;
    }
    else cout << "ERROR!! -id= no existe" << endl;
}

void Rep_::Graph_mbr(){
    dot += "rankdir=LR;\nnode [shape=plaintext];\n";
    dot += "rep [label=<\n<TABLE BORDER='0' CELLBORDER='0' CELLSPACING='0'>\n";
    dot += "<TR><TD>MBR " + m_actual->path.substr(m_actual->path.find_last_of('/') + 1, m_actual->path.length()) + "</TD></TR>\n<TR><TD>\n";
    dot += "<TABLE BORDER='0' CELLBORDER='1' CELLSPACING='0'>\n";
    dot += "<TR><TD BGCOLOR='cornflowerblue'>Nombre</TD><TD BGCOLOR='cornflowerblue'>Valor</TD></TR>\n";
    
    archivo = fopen(m_actual->path.c_str(), "rb");
    fseek(archivo, 0, SEEK_SET);
    fread(&mbr, sizeof(mbr), 1, archivo);

    dot += "<TR><TD BGCOLOR='lightblue'>mbr_tamaño</TD><TD>" + to_string(mbr.size) + "</TD></TR>\n";
    dot += "<TR><TD BGCOLOR='lightblue'>mbr_fecha_creacion</TD><TD>" + gs.Get_Date(mbr.date) + "</TD></TR>\n";
    dot += "<TR><TD BGCOLOR='lightblue'>Disk_fit</TD><TD>";
    dot += mbr.fit;
    dot += "</TD></TR>\n";
    dot += "<TR><TD BGCOLOR='lightblue'>mbr_disk_signature</TD><TD>" + to_string(mbr.signature) + "</TD></TR>\n";
    for(int i = 0; i < 4; i++){
        part = mbr.p[i];
        if(part.status == 'A'){
            i++;
            dot += "<TR><TD BGCOLOR='lightblue'>part_status_" + to_string(i) + "</TD><TD>" + part.status + "</TD></TR>\n";
            dot += "<TR><TD BGCOLOR='lightblue'>part_type_" + to_string(i) + "</TD><TD>" + part.type + "</TD></TR>\n";
            dot += "<TR><TD BGCOLOR='lightblue'>part_fit_" + to_string(i) + "</TD><TD>" + part.fit + "</TD></TR>\n";
            dot += "<TR><TD BGCOLOR='lightblue'>part_start_" + to_string(i) + "</TD><TD>" + to_string(part.start) + "</TD></TR>\n";
            dot += "<TR><TD BGCOLOR='lightblue'>part_size_" + to_string(i) + "</TD><TD>" + to_string(part.size) + "</TD></TR>\n";
            dot += "<TR><TD BGCOLOR='lightblue'>part_name_" + to_string(i) + "</TD><TD>" + part.name + "</TD></TR>\n";
            i--;
        }
    }
    dot += "</TABLE></TD></TR>\n";

    for(int i = 0; i < 4; i++){
        part = mbr.p[i];
        if(part.type == 'e' && part.status == 'A'){
            f_start = part.start;
            i_aux = 1;
            do{
                fseek(archivo, f_start, SEEK_SET);
                fread(&ebr, sizeof(ebr), 1, archivo);

                dot += "<TR><TD>-------------------------------</TD></TR>\n";
                dot += "<TR><TD>EBR_" + to_string(i_aux) + "</TD></TR>\n";
                dot += "<TR><TD>\n";
                dot += "<TABLE BORDER='0' CELLBORDER='1' CELLSPACING='0'>\n";
                dot += "<TR><TD BGCOLOR='indianred2'>Nombre</TD><TD BGCOLOR='indianred2'>Valor</TD></TR>\n";
                dot += "<TR><TD BGCOLOR='lightpink1'>part_status_" + to_string(i_aux) + "</TD><TD>" + ebr.status + "</TD></TR>\n";
                dot += "<TR><TD BGCOLOR='lightpink1'>part_fit_" + to_string(i_aux) + "</TD><TD>" + ebr.fit + "</TD></TR>\n";
                dot += "<TR><TD BGCOLOR='lightpink1'>part_start_" + to_string(i_aux) + "</TD><TD>" + to_string(ebr.start) + "</TD></TR>\n";
                dot += "<TR><TD BGCOLOR='lightpink1'>part_size_" + to_string(i_aux) + "</TD><TD>" + to_string(ebr.size) + "</TD></TR>\n";
                dot += "<TR><TD BGCOLOR='lightpink1'>part_next_" + to_string(i_aux) + "</TD><TD>" + to_string(ebr.next) + "</TD></TR>\n";
                dot += "<TR><TD BGCOLOR='lightpink1'>part_name_" + to_string(i_aux) + "</TD><TD>" + ebr.name + "</TD></TR>\n";
                dot += "</TABLE>\n";
                dot += "</TD></TR>\n";

                f_start = ebr.next;
                i_aux++;
            }while(ebr.next != -1);
        }
    }
    dot += "</TABLE>>];";
    Graficar();
}
void Rep_::Graph_disk(){
    dot += "rankdir=LR;\nnode [shape=plaintext];\nlabel=\""+ m_actual->path.substr(m_actual->path.find_last_of('/') + 1, m_actual->path.length()) +"\";\nlabelloc=\"t\";\n";
    dot += "disk [label=<\n<TABLE BORDER='1' CELLBORDER='1' CELLSPACING='4' BGCOLOR='darkolivegreen1'>\n";
    dot += "<TR><TD BGCOLOR='seagreen1'>MBR</TD>\n";

    archivo = fopen(m_actual->path.c_str(), "rb");
    fseek(archivo, 0, SEEK_SET);
    fread(&mbr, sizeof(mbr), 1, archivo);

    f_start = sizeof(mbr);
    for(int i = 0; i < 4; i++){
        part = mbr.p[i];
        if(part.status == 'A'){
            if(f_start < part.start){
                dot += "<TD BGCOLOR='paleturquoise1'><TABLE BORDER='0' CELLBORDER='0' CELLSPACING='0'>\n";
                dot += "<TR><TD>LIBRE</TD></TR>\n";
                dot += "<TR><TD><FONT POINT-SIZE='8.5' FACE='times:italic'>" + to_string(100 * (part.start - f_start) / mbr.size) + "% DEL DISCO</FONT></TD></TR>\n";
                dot += "</TABLE></TD>\n";
            }

            if(part.type == 'e'){
                dot += "<TD BGCOLOR='seagreen3'><TABLE BORDER='0' CELLBORDER='0' CELLSPACING='0'>\n";
                dot += "<TR><TD>EXTENDIDA</TD></TR>\n";
                dot += "<TR><TD>\n";
                dot += "<TABLE BORDER='0' CELLBORDER='1' CELLSPACING='0'><TR>\n";
                f_start = part.start;
                i_aux = 0;
                do{
                    fseek(archivo, f_start, SEEK_SET);
                    fread(&ebr, sizeof(ebr), 1, archivo);

                    dot += "<TD BGCOLOR='springgreen3'>EBR</TD>\n";
                    if(ebr.status == 'A'){
                        dot += "<TD BGCOLOR='palegreen1'><TABLE BORDER='0' CELLBORDER='0' CELLSPACING='0'>\n";
                        dot += "<TR><TD>LOGICA</TD></TR>\n";
                        dot += "<TR><TD><FONT POINT-SIZE='8.5' FACE='times:italic'>" + to_string(100 * ebr.size / mbr.size) + "% DEL DISCO</FONT></TD></TR>\n";
                        dot += "</TABLE></TD>\n";
                        if(ebr.next == -1 && ebr.size + ebr.start < part.start + part.size){
                            dot += "<TD BGCOLOR='paleturquoise1'><TABLE BORDER='0' CELLBORDER='0' CELLSPACING='0'>\n";
                            dot += "<TR><TD>LIBRE</TD></TR>\n";
                            dot += "<TR><TD><FONT POINT-SIZE='8.5' FACE='times:italic'>" + to_string(100 * (part.size + part.start - (ebr.start + ebr.size)) / mbr.size) + "% DEL DISCO</FONT></TD></TR>\n";
                            dot += "</TABLE></TD>\n";
                        }
                    }
                    else{
                        dot += "<TD BGCOLOR='paleturquoise1'><TABLE BORDER='0' CELLBORDER='0' CELLSPACING='0'>\n";
                        dot += "<TR><TD>LIBRE</TD></TR>\n";
                        if(ebr.next == -1) dot += "<TR><TD><FONT POINT-SIZE='8.5' FACE='times:italic'>" + to_string(100 * (part.size + part.start - ebr.start) / mbr.size) + "% DEL DISCO</FONT></TD></TR>\n";
                        else dot += "<TR><TD><FONT POINT-SIZE='8.5' FACE='times:italic'>" + to_string(100 * (ebr.next - ebr.start) / mbr.size) + "% DEL DISCO</FONT></TD></TR>\n";
                        dot += "</TABLE></TD>\n";
                    }

                    f_start = ebr.next;
                }while(ebr.next != -1);
                dot += "</TR></TABLE></TD></TR>\n";
                dot += "</TABLE></TD>\n";
                f_start = part.start + part.size;
            }
            else {
                dot += "<TD BGCOLOR='springgreen1'><TABLE BORDER='0' CELLBORDER='0' CELLSPACING='0'>\n";
                dot += "<TR><TD>PRIMARIA</TD></TR>\n";
                dot += "<TR><TD><FONT POINT-SIZE='8.5' FACE='times:italic'>" + to_string(100 * part.size / mbr.size) + "% DEL DISCO</FONT></TD></TR>\n";
                dot += "</TABLE></TD>\n";
            }

            f_start = part.start + part.size;
        }
        else{
            if(f_start == sizeof(mbr)) f_start = 0;
            dot += "<TD BGCOLOR='paleturquoise1'><TABLE BORDER='0' CELLBORDER='0' CELLSPACING='0'>\n";
            dot += "<TR><TD>LIBRE</TD></TR>\n";
            dot += "<TR><TD><FONT POINT-SIZE='8.5' FACE='times:italic'>" + to_string(100 * (mbr.size - f_start) / mbr.size) + "% DEL DISCO</FONT></TD></TR>\n";
            dot += "</TABLE></TD>\n";
        }
    }
    dot += "</TR></TABLE>>];";
    Graficar();
}
void Rep_::Graph_inode(){
    dot += "rankdir=LR;\nnode [shape=plaintext];\nlabel=\"INodos " + m_actual->name + " en "+ m_actual->path.substr(m_actual->path.find_last_of('/') + 1, m_actual->path.length()) +"\";\nlabelloc=\"t\";\n";
    f_start = gs.Get_StartPartitionPoint(m_actual->path, m_actual->name);
    es.Esc_Read_Superbloque();
    Graph_inodeRec(0);
    Graficar();
}
void Rep_::Graph_inodeRec(int pos){
    es.Esc_Read_INodo(pos);
    dot += "inodo_" + to_string(pos) + "[label=<<TABLE BORDER='1' CELLBORDER='0' CELLSPACING='0' BGCOLOR='darkgoldenrod1'>\n";
    dot += "<TR><TD>INODO " + to_string(pos) + "</TD></TR>\n<TR><TD>\n";
    dot += "<TABLE BORDER='0' CELLBORDER='1' CELLSPACING='0' BGCOLOR='khaki1'>\n";
    dot += "<TR><TD>i_uid</TD><TD>" + to_string(inodos.i_uid) + "</TD></TR>\n";
    dot += "<TR><TD>i_gid</TD><TD>" + to_string(inodos.i_gid) + "</TD></TR>\n";
    dot += "<TR><TD>i_size</TD><TD>" + to_string(inodos.i_size) + "</TD></TR>\n";
    dot += "<TR><TD>i_atime</TD><TD>" + gs.Get_Date(inodos.i_atime) + "</TD></TR>\n";
    dot += "<TR><TD>i_ctime</TD><TD>" + gs.Get_Date(inodos.i_ctime) + "</TD></TR>\n";
    dot += "<TR><TD>i_mtime</TD><TD>" + gs.Get_Date(inodos.i_mtime) + "</TD></TR>\n";
    for(int i = 0; i < 15; i++){
        if(i < 12) dot += "<TR><TD>i_block_" + to_string(i) + "</TD><TD>" + to_string(inodos.i_block[i]) + "</TD></TR>\n";
        else  dot += "<TR><TD>i_block_apt" + to_string(i - 11) + "</TD><TD>" + to_string(inodos.i_block[i]) + "</TD></TR>\n";
    }
    dot += "<TR><TD>i_type</TD><TD>" + to_string(inodos.i_type) + "</TD></TR>\n";
    if(inodos.i_perm < 10) dot += "<TR><TD>i_perm</TD><TD>00" + to_string(inodos.i_perm) + "</TD></TR>\n";
    else if(inodos.i_perm < 100) dot += "<TR><TD>i_perm</TD><TD>0" + to_string(inodos.i_perm) + "</TD></TR>\n";
    else dot += "<TR><TD>i_perm</TD><TD>" + to_string(inodos.i_perm) + "</TD></TR>\n";
    dot += "</TABLE></TD></TR>\n</TABLE>>];\n";

    cout << "---------Aqui con " << pos << endl;
    if(inodos.i_type == 0){
        stack<int> stack;
        for(int i = 0; i < 15; i++){
            if(inodos.i_block[i] != -1){
                if(i == 0){
                    es.Esc_Read_BloqueCarpeta(inodos.i_block[i]);
                    for(int bc = 2; bc < 4; bc++){
                        if(bloques_carpeta.b_content[bc].b_inodo != -1)
                            stack.push(bloques_carpeta.b_content[bc].b_inodo);
                    }
                }
                else if(i < 12){
                    es.Esc_Read_BloqueCarpeta(inodos.i_block[i]);
                    for(int bc = 0; bc < 4; bc++){
                        if(bloques_carpeta.b_content[bc].b_inodo != -1)
                            stack.push(bloques_carpeta.b_content[bc].b_inodo);
                    }
                }
                else if(i == 12){
                    es.Esc_Read_BloqueApuntad(inodos.i_block[i]);
                    for(int ba_1 = 0; ba_1 < 16; ba_1++){
                        if(bloques_apuntad.b_pointer[ba_1] != -1){
                            es.Esc_Read_BloqueCarpeta(bloques_apuntad.b_pointer[ba_1]);
                            for(int bc = 0; bc < 4; bc++){
                                if(bloques_carpeta.b_content[bc].b_inodo != -1)
                                    stack.push(bloques_carpeta.b_content[bc].b_inodo);
                            }
                        }
                    }
                }
                else if(i == 13){
                    es.Esc_Read_BloqueApuntad(inodos.i_block[i]);
                    Str::Bloques_apuntad bloques_apuntad2 = bloques_apuntad;
                    for(int ba_2 = 0; ba_2 < 16; ba_2++){
                        if(bloques_apuntad2.b_pointer[ba_2] != -1){
                            es.Esc_Read_BloqueApuntad(bloques_apuntad2.b_pointer[ba_2]);
                            for(int ba_1 = 0; ba_1 < 16; ba_1++){
                                if(bloques_apuntad.b_pointer[ba_1] != -1){
                                    es.Esc_Read_BloqueCarpeta(bloques_apuntad.b_pointer[ba_1]);
                                    for(int bc = 0; bc < 4; bc++){
                                        if(bloques_carpeta.b_content[bc].b_inodo != -1)
                                            stack.push(bloques_carpeta.b_content[bc].b_inodo);
                                    }
                                }
                            }
                        }
                    }
                }
                else{
                    es.Esc_Read_BloqueApuntad(inodos.i_block[i]);
                    Str::Bloques_apuntad bloques_apuntad3 = bloques_apuntad;
                    Str::Bloques_apuntad bloques_apuntad2;
                    for(int ba_3 = 0; ba_3 < 16; ba_3++){
                        if(bloques_apuntad3.b_pointer[ba_3] != -1){
                            es.Esc_Read_BloqueApuntad(bloques_apuntad3.b_pointer[ba_3]);
                            bloques_apuntad2 = bloques_apuntad;
                            for(int ba_2 = 0; ba_2 < 16; ba_2++){
                                if(bloques_apuntad2.b_pointer[ba_2] != -1){
                                    es.Esc_Read_BloqueApuntad(bloques_apuntad2.b_pointer[ba_2]);
                                    for(int ba_1 = 0; ba_1 < 16; ba_1++){
                                        if(bloques_apuntad.b_pointer[ba_1] != -1){
                                            es.Esc_Read_BloqueCarpeta(bloques_apuntad.b_pointer[ba_1]);
                                            for(int bc = 0; bc < 4; bc++){
                                                if(bloques_carpeta.b_content[bc].b_inodo != -1)
                                                    stack.push(bloques_carpeta.b_content[bc].b_inodo);
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
        
        cout << "Finalizado:-----" << endl;
        while(!stack.empty()){
            i_aux = stack.top();
            dot += "inodo_" + to_string(pos) + "->inodo_" + to_string(i_aux) + "\n;";
            cout << "----->Stack: " << i_aux << endl;
            stack.pop();
            if(i_aux != pos) Graph_inodeRec(i_aux);
        }
    }
}
void Rep_::Graph_journaling(){
    Graficar();
}
void Rep_::Graph_block(){
    Graficar_Txt();
}
void Rep_::Graph_bm_inode(){
    dot = "";
    f_start = gs.Get_StartPartitionPoint(m_actual->path, m_actual->name);
    es.Esc_Read_Superbloque();

    fseek(archivo, f_start + superbloque.s_bm_inode_start, SEEK_SET);
    unsigned char bitmapINodos [superbloque.s_inodes_count];
    fread(bitmapINodos, sizeof(bitmapINodos), 1, archivo);
    fclose(archivo);

    cout << bitmapINodos[0] << endl;
    int k = 0;
    for(int i = 0; i < superbloque.s_inodes_count; i++){
        if(k == 20){
            dot += "\n";
            k = 0;
        }
        k++;
        if(bitmapINodos[i] == '1') dot += "1 ";
        else dot += "0 ";
    }
    Graficar_Txt();
}
void Rep_::Graph_bm_block(){
    dot = "";
    f_start = gs.Get_StartPartitionPoint(m_actual->path, m_actual->name);
    es.Esc_Read_Superbloque();

    fseek(archivo, f_start + superbloque.s_bm_block_start, SEEK_SET);
    unsigned char bitmapBloques [superbloque.s_blocks_count];
    fread(bitmapBloques, sizeof(bitmapBloques), 1, archivo);
    fclose(archivo);

    cout << bitmapBloques[0] << endl;
    int k = 0;
    for(int i = 0; i < superbloque.s_blocks_count; i++){
        if(k == 20){
            dot += "\n";
            k = 0;
        }
        k++;
        if(bitmapBloques[i] == '1') dot += "1 ";
        else dot += "0 ";
    }
    Graficar_Txt();
}
void Rep_::Graph_tree(){

    Graficar();
}
void Rep_::Graph_sb(){
    dot += "rankdir=LR;\nnode [shape=plaintext];\n";
    dot += "rep [label=<\n<TABLE BORDER='0' CELLBORDER='0' CELLSPACING='0'>\n";
    dot += "<TR><TD>SuperBloque "+ m_actual->name + " en " + m_actual->path.substr(m_actual->path.find_last_of('/') + 1, m_actual->path.length()) + "</TD></TR>\n<TR><TD>\n";
    dot += "<TABLE BORDER='0' CELLBORDER='1' CELLSPACING='0'>\n";
    dot += "<TR><TD BGCOLOR='lightsalmon2'>Nombre</TD><TD BGCOLOR='lightsalmon2'>Valor</TD></TR>\n";
    
    f_start = gs.Get_StartPartitionPoint(m_actual->path, m_actual->name);
    es.Esc_Read_Superbloque();

    dot += "<TR><TD BGCOLOR='lightsalmon'>s_inodes_count</TD><TD>" + to_string(superbloque.s_inodes_count) + "</TD></TR>\n";
    dot += "<TR><TD BGCOLOR='lightsalmon'>s_blocks_count</TD><TD>" + to_string(superbloque.s_blocks_count) + "</TD></TR>\n";
    dot += "<TR><TD BGCOLOR='lightsalmon'>s_free_blocks_count</TD><TD>" + to_string(superbloque.s_free_blocks_count) + "</TD></TR>\n";
    dot += "<TR><TD BGCOLOR='lightsalmon'>s_free_inodes_count</TD><TD>" + to_string(superbloque.s_free_inodes_count) + "</TD></TR>\n";
    dot += "<TR><TD BGCOLOR='lightsalmon'>s_mtime</TD><TD>" + gs.Get_Date(superbloque.s_mtime) + "</TD></TR>\n";
    dot += "<TR><TD BGCOLOR='lightsalmon'>s_umtime</TD><TD>" + gs.Get_Date(superbloque.s_umtime) + "</TD></TR>\n";
    dot += "<TR><TD BGCOLOR='lightsalmon'>s_mnt_count</TD><TD>" + to_string(superbloque.s_magic) + "</TD></TR>\n";
    dot += "<TR><TD BGCOLOR='lightsalmon'>s_magic</TD><TD>" + to_string(superbloque.s_mnt_count) + "xEF53</TD></TR>\n";
    dot += "<TR><TD BGCOLOR='lightsalmon'>s_inode_size</TD><TD>" + to_string(superbloque.s_inode_size) + "</TD></TR>\n";
    dot += "<TR><TD BGCOLOR='lightsalmon'>s_block_size</TD><TD>" + to_string(superbloque.s_block_size) + "</TD></TR>\n";
    dot += "<TR><TD BGCOLOR='lightsalmon'>s_first_ino</TD><TD>" + to_string(superbloque.s_first_ino) + "</TD></TR>\n";
    dot += "<TR><TD BGCOLOR='lightsalmon'>s_first_blo</TD><TD>" + to_string(superbloque.s_first_blo) + "</TD></TR>\n";
    dot += "<TR><TD BGCOLOR='lightsalmon'>s_bm_inode_start</TD><TD>" + to_string(superbloque.s_bm_inode_start) + "</TD></TR>\n";
    dot += "<TR><TD BGCOLOR='lightsalmon'>s_bm_block_start</TD><TD>" + to_string(superbloque.s_bm_block_start) + "</TD></TR>\n";
    dot += "<TR><TD BGCOLOR='lightsalmon'>s_inode_start</TD><TD>" + to_string(superbloque.s_inode_start) + "</TD></TR>\n";
    dot += "<TR><TD BGCOLOR='lightsalmon'>s_block_start</TD><TD>" + to_string(superbloque.s_block_start) + "</TD></TR>\n";

    dot += "</TABLE></TD></TR>\n";

    dot += "</TABLE>>];";
    Graficar();
}
void Rep_::Graph_file(){
    Graficar();
}
void Rep_::Graph_ls(){
    Graficar();
}
void Rep_::Graficar(){
    dot += "\n}";
    ofstream dot_file;
    mkdir(path.substr(0, path.find_last_of('/')).c_str(), 0777);
    dot_file.open("/home/archivos/dot.dot");
    dot_file << dot;
    dot_file.close();
    dot = "dot /home/archivos/dot.dot -T" + path.substr(path.find_last_of('.') + 1, path.length()) + " -o " + path;
    system(dot.c_str());
    dot = "xdg-open " + path;
    system(dot.c_str());
    cout << "Reporte " << name << " generado con exito" << endl;
    fclose(archivo);
}
void Rep_::Graficar_Txt(){
    ofstream dot_file;
    mkdir(path.substr(0, path.find_last_of('/')).c_str(), 0777);
    dot_file.open(path);
    dot_file << dot;
    dot_file.close();
    dot = "xdg-open " + path;
    system(dot.c_str());
    cout << "Reporte " << name << " generado con exito" << endl;
}