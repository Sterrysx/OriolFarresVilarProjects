#include "Process_Area.hh"

    //Constructoras:
Process_Area::Process_Area() 
{ 
    priority p;
        p.npc = 0;
        p.npr = 0;
        p.l = list<Proceso>();
        p.id_proceso = set<int>();
    mapa_string_priority = map<string, priority>();
}


    //Consultoras:
bool Process_Area::existe_proceso(const Proceso& p, const string& id_priority) const 
{ 
    map<string, priority>::const_iterator it = mapa_string_priority.find(id_priority);
    //it apunta --> proceso en el área de espera con id_priority que buscamos
    set<int>::iterator itset = it->second.id_proceso.find(p.consultar_id()); 
    if (itset == it->second.id_proceso.end()) return false; //itset apunta --> end si no existe ningún id_proceso
    else return true; //itset apunta al id del proceso --> ya existe un proceso con este id_proceso
}


    //Lectoras:
void Process_Area::read_process_area() 
{ 
    string id;
    priority p;
    list<Proceso> lista;
    int n; //donde n es el número de prioridades
    cin >> n;
    for (int i = 0; i < n; ++i) {
        cin >> id;
        p.l = lista;
        p.npc = 0;
        p.npr = 0;
        mapa_string_priority[id] = p;
    }
}


    //Escritoras:
void Process_Area::imprimir_area_espera() 
{ 
    map<string, priority>::iterator it = mapa_string_priority.begin(), itend = mapa_string_priority.end();
    while (it != itend) {
        //Imprimide el identificador de prioridad
        cout << it->first << endl;
        list<Proceso>::iterator itlista = it->second.l.begin(); 
        imprimir_procesos_lista(it, itlista);
        ++it;
    }
}

void Process_Area::imprimir_prioridad(string& id_priority) 
{ 
    map<string, priority>::iterator it = mapa_string_priority.find(id_priority);
    if (it == mapa_string_priority.end()) cout << "error: no existe prioridad" << endl;
    else {
        list<Proceso>::iterator itlista = it->second.l.begin();
        imprimir_procesos_lista(it, itlista);
    }
}

void Process_Area::imprimir_procesos_lista(map<string, priority>::iterator& it, list<Proceso>::iterator& itlista) 
{
    while (itlista != it->second.l.end()) {
        (*itlista).imprimir_proceso();
        ++itlista;
    }
    cout << it->second.npc << ' ' << it->second.npr << endl;
}


    //Modificadoras:
void Process_Area::alta_prioridad(string& id_priority) 
{ 
    //Si no hay error, añade la prioridad al área de espera
    map<string, priority>::iterator it = mapa_string_priority.find(id_priority);
    if (it == mapa_string_priority.end()) anadir_prioridad_a_area_espera(id_priority); 
    else cout << "error: ya existe prioridad" << endl; //ha encontrado en el área de espera una prioridad con el mismo id de prioridad
}

void Process_Area::anadir_prioridad_a_area_espera(string& id_priority) 
{ 
    priority p;
    list<Proceso> lista;
    p.l = lista;
    p.npc = 0;
    p.npr = 0;
    mapa_string_priority[id_priority] = p;
}

void Process_Area::baja_prioridad(string& id_priority) 
{ 
    //Si no hay error, elimina la prioridad del área de espera
    map<string, priority>::iterator it = mapa_string_priority.find(id_priority);
    if (it == mapa_string_priority.end()) cout << "error: no existe prioridad" << endl;
    else {
        if (it->second.l.empty())mapa_string_priority.erase(it); //elimina prioridad del area de espera
        else cout << "error: prioridad con procesos" << endl;
    }
}

void Process_Area::alta_proceso_espera(const Proceso& p, const string& id_priority) 
{ 
    map<string, priority>::iterator it = mapa_string_priority.find(id_priority);
    if(it == mapa_string_priority.end()) cout <<  "error: no existe prioridad" << endl; 
    else {
        if (existe_proceso(p, id_priority)) cout << "error: ya existe proceso" << endl;
        else {
            it->second.l.insert(it->second.l.end(), p);
            it->second.id_proceso.insert(p.consultar_id());
        }
    }
}

void Process_Area::enviar_procesos_cluster(int unsigned& n, Cluster& c) 
{
    map<string, priority>::iterator it = mapa_string_priority.begin(), itend = mapa_string_priority.end();
    while (it != itend and n > 0) {
        list<Proceso>::iterator itl = it->second.l.begin(), itlend = it->second.l.end();
        bool rechazado = false;
        while (itl != itlend and n > 0) {
            //si se puede enviar proceso cluster (++procesos aceptados)
            Proceso p = *itl;
            if (c.puedo_enviar_proceso_cluster(p)) {
                ++it->second.npc;
                it->second.id_proceso.erase(p.consultar_id()); //eliminar el proceso del set de procesos
                --n;
            }
            //si no se puede enviar proceso cluster (++procesos rechazados)
            else {
                ++it->second.npr;
                it->second.l.push_back(p); //pongo el proceso en el final de la lista
                if(not rechazado) {
                    //cuando entre el primer rechazado restaremos un al itlend para apuntar al primer rechazado de la prioridad
                    --itlend;
                    rechazado = true;
                }
            }
            itl = it->second.l.erase(itl); //eliminar el proceso de la lista de procesos y itl apunta al siguiente
        }
        ++it;
    }
} 
