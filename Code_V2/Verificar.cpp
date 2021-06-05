#include "Headers.h"

bool Verificar::Ver_Size(){
    if(size > 0) return true;
    cout << "ERROR!! -size= debe de ser mayor a 0" << endl;
    return false;
}
bool Verificar::Ver_F(){
    f = e.slower(f);
    if(f == "bf" || f == "ff" || f == "wf") return true;
    cout << "ERROR!! -f= debe ser bf, ff o wf, " << f << endl;
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
bool Verificar::Ver_U(){
    u = e.slower(u);
    if(u == "k" || u == "m") return true;
    cout << "ERROR!! -u= debe ser k o m" << endl;
    return false;
}