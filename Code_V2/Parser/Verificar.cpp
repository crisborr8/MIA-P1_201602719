#include "../Headers.h"

bool Verificar::Ver_F(){
    f = e.slower(f);
    if(f == "bf" || f == "ff" || f == "wf") return true;
    cout << "ERROR!! -f= debe ser bf, ff o wf, " << f << endl;
    return false;
}
bool Verificar::Ver_U(){
    u = e.slower(u);
    if(u == "k" || u == "m") return true;
    cout << "ERROR!! -u= debe ser k o m" << endl;
    return false;
}
bool Verificar::Ver_U2(){
    u = e.slower(u);
    if(u == "k" || u == "m" || u == "b") return true;
    cout << "ERROR!! -u= debe ser k, m o u" << endl;
    return false;
}
bool Verificar::Ver_Id(){
    if(e.trim(id).length() > 0) return true;
    cout << "ERROR!! -id= debe existir" << endl;
    return false;
}
bool Verificar::Ver_Fs(){
    fs = e.slower(fs);
    if(fs == "2fs" || fs == "3fs") return true;
    cout << "ERROR!! -fs= debe ser 2fs o 3fs" << endl;
    return false;
}
bool Verificar::Ver_Add(){
    if(size != 0) return true;
    cout << "ERROR!! -add= debe de ser distinto a 0" << endl;
    return false;
}
bool Verificar::Ver_Usr(){
    if(e.trim(usr).length() > 0) return true;
    cout << "ERROR!! -usr= debe existir" << endl;
    return false;
}
bool Verificar::Ver_Usr2(){
    if(Ver_Usr()){
        if(e.trim(usr).length() < 11) return true;
        cout << "ERROR!! -usr= debe tener maximo 10 caracteres" << endl;
    }
    return false;
}
bool Verificar::Ver_Pwd2(){
    if(Ver_Pwd()){
        if(e.trim(pwd).length() < 11) return true;
        cout << "ERROR!! -pwd= debe tener maximo 10 caracteres" << endl;
    }
    return false;
}
bool Verificar::Ver_Grp(){
    if(e.trim(grp).length() > 0){
        if(e.trim(grp).length() < 11) return true;
        cout << "ERROR!! -grp= debe tener maximo 10 caracteres" << endl;
    }
    cout << "ERROR!! -grp= debe existir" << endl;
    return false;
}
bool Verificar::Ver_Pwd(){
    if(e.trim(pwd).length() > 0) return true;
    cout << "ERROR!! -pwd= debe existir" << endl;
    return false;
}
bool Verificar::Ver_Size(){
    if(size > 0) return true;
    cout << "ERROR!! -size= debe de ser mayor a 0" << endl;
    return false;
}
bool Verificar::Ver_Size2(){
    if(size >= 0) return true;
    cout << "ERROR!! -size= debe de ser mayor o igual a 0" << endl;
    return false;
}
bool Verificar::Ver_Ugo(){
    try{
        ing_numero = stoi(ugo);
    }catch(exception ex){
        cout << "ERROR!!, -ugo debe ser tipo numerico" << endl;
        return true;
    }
    if(ugo.length() == 3)
    if(0 <= ing_numero && ing_numero <= 777) return true;
    cout << "ERROR!! -ugo= debe de ser entre 000 y 777" << endl;
    return false;
}
bool Verificar::Ver_Name(){
    if(e.trim(name).length() > 0) return true;
    cout << "ERROR!! -name= debe existir" << endl;
    return false;
}
bool Verificar::Ver_Path(){
    i_aux = path.find_last_of(".");
    if(i_aux > 0){
        if(i_aux > 1){
            if(e.slower(path.substr(i_aux, path.length())) == ".dk") return true;
            cout << "ERROR!! -path= debe terminar en .dk" << endl;
        }
        else cout << "ERROR!! -path= debe ser una ruta valida" << endl;
    }
    else cout << "ERROR!! -path= debe terminar en .dk" << endl;
    return false;
}
bool Verificar::Ver_Path4(){
    i_aux = path.find_last_of(".");
    if(i_aux > 0){
        if(i_aux > 1){
            if(e.slower(path.substr(i_aux, path.length())) == ".script") return true;
            cout << "ERROR!! -path= debe terminar en .script" << endl;
        }
        else cout << "ERROR!! -path= debe ser una ruta valida" << endl;
    }
    else cout << "ERROR!! -path= debe terminar en .script" << endl;
    return false;
}
bool Verificar::Ver_Path2(){
    if(e.trim(path).length() < 1) return true;
    cout << "ERROR!! -path= debe ser una ruta valida" << endl;
    return false;
}
bool Verificar::Ver_Dest(){
    if(e.trim(dest).length() < 1) return true;
    cout << "ERROR!! -dest= debe ser una ruta valida" << endl;
    return false;
}
bool Verificar::Ver_Path3(){
    i_aux = path.find_last_of(".");
    if(i_aux > 0){
        if(i_aux > 1 && i_aux < path.length() - 1) return true;
        else cout << "ERROR!! -path= debe ser una ruta valida" << endl;
    }
    else cout << "ERROR!! -path= debe tener alguna extencion" << endl;
    return false;
}
bool Verificar::Ver_Cont(){
    if(cont.length() == 0) return true;
    i_aux = cont.find_last_of(".");
    if(i_aux > 0){
        if(i_aux > 1 && i_aux < cont.length() - 1) return true;
        else cout << "ERROR!! -cont= debe ser una ruta valida" << endl;
    }
    else cout << "ERROR!! -cont= debe tener alguna extencion" << endl;
    return false;
}
bool Verificar::Ver_Type(){
    type = e.slower(type);
    if(type == "p" || type == "e" || type == "l") return true;
    cout << "ERROR!! -type= debe ser p, e o l" << endl;
    return false;
}
bool Verificar::Ver_Type2(){
    type = e.slower(type);
    if(type == "fast" || type == "full") return true;
    cout << "ERROR!! -type= debe ser fast o full" << endl;
    return false;
}
bool Verificar::Ver_Delet(){
    delet = e.slower(delet);
    if(delet == "fast" || delet == "full") return true;
    cout << "ERROR!! -delet= debe ser fast o full" << endl;
    return false;
}