#include "../Headers.h"

void Unmount_::Inicializar(){
    error = false;

    id = "";

    if(!Ingresar_Datos()) 
        if(Verificar_Datos()) 
            Ejecutar();
}

bool Unmount_::Ingresar_Datos(){
    while(comando.length() > 0){
        comando_inicial = e.slower(comando);
        if(comando_inicial.find("-id=") == 0){
            error = i.Ing_Palabra("-id=");
            if(error) break;
            id = ing_palabra;
        }
        else{
            error = i.Ing_Error();
            break;
        } 
    }
    return error;
}

bool Unmount_::Verificar_Datos(){
    error = true;
    if(v.Ver_Id()) error = false;
    return !error;
}

void Unmount_::Ejecutar(){
    if(ex.Ex_MonturaId(id)){
        Str::Montura* m_aux = montura;
        Str::Montura* m_ant = montura;
        while(m_aux != nullptr){
            if(id == "19" + to_string(m_aux->numero) + m_aux->letra){
                if(m_ant == m_aux) montura = montura->next;
                else m_ant->next = m_aux->next;
                cout << "Montura eliminada" << endl;
                break;
            }
            m_ant = m_aux;
            m_aux = m_aux->next;
        }

        m_aux = montura;
        while(m_aux != nullptr){
            cout << "Particion: " << m_aux->numero << endl;
            i_aux = m_aux->numero;
            while(m_aux != nullptr){
                cout << "\tLetra: " << m_aux->letra << endl;
                cout << "\t\tName: " << m_aux->name << endl;
                cout << "\t\tPath: " << m_aux->path << endl;
                if(m_aux->next == nullptr) break;
                if(i_aux != m_aux->next->numero) break;
                else m_aux = m_aux->next;
            }
            if(m_aux == nullptr) break;
            m_aux = m_aux->next;
        }
    }
    else cout << "ERROR!! id no existe" << endl;
}