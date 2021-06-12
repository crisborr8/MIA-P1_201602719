#include "../Headers.h"

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
    if(v.Ver_Path5()) error = false;
    if(!v.Ver_Id()) error = true;
    if(!v.Ver_Name()) error = true;
    return !error;
}

void Rep_::Ejecutar(){
    if(ex.Ex_MonturaId(id)){
        dot = "digraph G{";
        name = e.slower(name);
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
    Str::Montura *m_aux = gs.Get_Mount(id);
    dot += "rankdir=LR;\nnode [shape=plaintext];\n";
    dot += "rep [label=<\n<TABLE BORDER='0' CELLBORDER='0' CELLSPACING='0'>\n";
    dot += "<TR><TD>MBR " + m_aux->path.substr(m_aux->path.find_last_of('/') + 1, m_aux->path.length()) + "</TD></TR>\n<TR><TD>\n";
    dot += "<TABLE BORDER='0' CELLBORDER='1' CELLSPACING='0'>\n";
    dot += "<TR><TD BGCOLOR='cornflowerblue'>Nombre</TD><TD BGCOLOR='cornflowerblue'>Valor</TD></TR>\n";
    
    archivo = fopen(m_aux->path.c_str(), "rb");
    fseek(archivo, 0, SEEK_SET);
    fread(&mbr, sizeof(mbr), 1, archivo);

    dot += "<TR><TD BGCOLOR='lightblue'>mbr_tamaño</TD><TD>" + to_string(mbr.size) + "</TD></TR>\n";
    dot += "<TR><TD BGCOLOR='lightblue'>mbr_fecha_creacion</TD><TD>" + gs.Get_Date(mbr.date) + "</TD></TR>\n";
    dot += "<TR><TD BGCOLOR='lightblue'>mbr_disk_signature</TD><TD>" + to_string(mbr.signature) + "</TD></TR>\n";
    dot += "<TR><TD BGCOLOR='lightblue'>Disk_fit</TD><TD>" + mbr.fit;

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

    fclose(archivo);
    dot += "</TABLE>>];";
    Graficar();
}
void Rep_::Graph_disk(){
    Str::Montura *m_aux = gs.Get_Mount(id);
    dot += "rankdir=LR;\nnode [shape=plaintext];\nlabel=\""+ m_aux->path.substr(m_aux->path.find_last_of('/') + 1, m_aux->path.length()) +"\";\nlabelloc=\"t\";\n";
    dot += "disk [label=<\n<TABLE BORDER='1' CELLBORDER='1' CELLSPACING='4' BGCOLOR='darkolivegreen1'>\n";
    dot += "<TR><TD BGCOLOR='seagreen1'>MBR</TD>\n";

    archivo = fopen(m_aux->path.c_str(), "rb");
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
    fclose(archivo);
    Graficar();
}
void Rep_::Graph_inode(){
    Graficar();
}
void Rep_::Graph_journaling(){
    Graficar();
}
void Rep_::Graph_block(){
    Graficar();
}
void Rep_::Graph_bm_inode(){
    Graficar();
}
void Rep_::Graph_bm_block(){
    Graficar();
}
void Rep_::Graph_tree(){
    Graficar();
}
void Rep_::Graph_sb(){
    Graficar();
}
void Rep_::Graph_file(){
    Graficar();
}
void Rep_::Graph_ls(){
    Graficar();
}
bool Rep_::Graficar(){
    dot += "\n}";
    ofstream dot_file;
    dot_file.open("/home/archivos/dot.dot");
    dot_file << dot;
    dot_file.close();
    dot = "dot /home/archivos/dot.dot -T" + path.substr(path.find_last_of('.') + 1, path.length()) + " -o " + path;
    system(dot.c_str());
    dot = "xdg-open " + path;
    system(dot.c_str());
    return false;
}