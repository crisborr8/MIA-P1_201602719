#include "../Headers.h"

void Mount_::Inicializar(){
    error = false;

    path = "";
    name = "";

    if(!Ingresar_Datos()) 
        if(Verificar_Datos()) 
            Ejecutar();
}

bool Mount_::Ingresar_Datos(){
    while(comando.length() > 0){
        comando_inicial = e.slower(comando);
        if(comando_inicial.find("-name=") == 0){
            error = i.Ing_PalabraC("-name=");
            if(error) break;
            name = ing_palabra;
        }
        else if(comando_inicial.find("-path=") == 0){
            error = i.Ing_PalabraC("-path=");
            if(error) break;
            path = ing_palabra;
        }
        else{
            error = i.Ing_Error();
            break;
        } 
    }
    return error;
}

bool Mount_::Verificar_Datos(){
    error = true;
    if(v.Ver_Path()) error = false;
    if(!v.Ver_Name()) error = true;
    return !error;
}

void Mount_::Ejecutar(){
    if(ex.Ex_Path_File(path)){
        if(ex.Ex_Name(name, path)){
            if(!ex.Ex_Montura(name, path)){
                Str::Montura* m_aux = montura;
                int numero = 1;
                char letra = 'a';
                if(montura != nullptr){
                    i_aux = 0;
                    do{
                        if(m_aux->path == path){
                            numero = m_aux->numero;
                            do{
                                if(m_aux->numero != numero) break;
                                if(letra != m_aux->letra) break;
                                else letra = m_aux->letra + 1;
                                m_aux = m_aux->next;

                            }while(m_aux != nullptr);
                            break;
                        }
                        else if(numero + 1 > m_aux->numero) numero = m_aux->numero + 1;
                        m_aux = m_aux->next;
                    }while(m_aux != nullptr);
                }
                Str::Montura* m_new = new Str::Montura;
                m_new->name = name;
                m_new->path = path;
                m_new->letra = letra;
                m_new->next = montura;
                m_new->numero = numero;
                m_new->fit_type = gs.Get_FitType(path, name);
                if(montura != nullptr) m_new->next = montura;
                else m_new->next = nullptr;
                montura = m_new;

                while(m_new->next != nullptr){
                    if(m_new->numero > m_new->next->numero){
                        if(m_new == montura){
                            montura = m_new->next;
                            m_new->next = montura->next;
                            montura->next = m_new;
                            m_new = montura;
                        }
                        else{
                            m_aux->next = m_new->next;
                            m_aux = m_new->next;
                            m_new->next = m_aux->next;
                            m_aux->next = m_new;
                            m_new = m_aux;
                        }
                    }
                    else{
                        while(m_new->next != nullptr){
                            if(m_new->numero < m_new->next->numero) break;
                            if(m_new->letra > m_new->next->letra){
                                if(m_new == montura){
                                    montura = m_new->next;
                                    m_new->next = montura->next;
                                    montura->next = m_new;
                                    m_new = montura;
                                }
                                else{
                                    m_aux->next = m_new->next;
                                    m_aux = m_new->next;
                                    m_new->next = m_aux->next;
                                    m_aux->next = m_new;
                                    m_new = m_aux;
                                }
                            }
                            else break;
                            m_aux = m_new;
                            m_new = m_new->next;
                        }
                        break;
                    }
                    m_aux = m_new;
                    m_new = m_new->next;
                }
                cout << "Montura creada con id = " << 19 << to_string(numero) << letra << endl;
            } 
            else cout << "ERROR!! Particion ya esta montada" << endl;
        }
        else cout << "ERROR!! El nombre de la particion no existe" << endl;
    }
    else cout << "ERROR!! El archivo no existe" << endl;
}
