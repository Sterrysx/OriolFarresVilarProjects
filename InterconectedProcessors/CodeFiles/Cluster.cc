#include "Cluster.hh"

    //Constructoras:
Cluster::Cluster() 
{ 
    arbol = BinTree<string>(); 
    mapa_string_procesador = map<string, Procesador>(); 
}


    //Lectoras:
void Cluster::configurar_cluster() 
{ 
    mapa_string_procesador.clear();
    i_configurar_cluster(arbol, mapa_string_procesador);
}

void Cluster::i_configurar_cluster(BinTree<string>& a, map<string, Procesador>& mapa) 
{ 
    string idp; //idp = id del procesador
    cin >> idp;
    if (idp != "*") {
        Procesador p;
        p.read_procesador(idp);

        mapa[idp] = p;
        BinTree<string> left;
        i_configurar_cluster(left, mapa);
        BinTree<string> right;
        i_configurar_cluster(right, mapa);

        a = BinTree<string>(idp, left, right); //árbol pasa a tener idp como nodo, left como hijo izquierdo y right como hijo derecho
    }
}


    //Escritoras:
void Cluster::imprimir_procesador(string& id_procesador) 
{ 
    map<string, Procesador>::iterator it = mapa_string_procesador.find(id_procesador);
    if (it == mapa_string_procesador.end()) cout << "error: no existe procesador" << endl;
    else (it->second).imprimir_procesador();
}

void Cluster::imprimir_procesadores_cluster() 
{ 
    map<string, Procesador>::iterator it, itend;
    it = mapa_string_procesador.begin();
    itend = mapa_string_procesador.end();
    while (it != itend) {
        cout << it->first << endl;
        it->second.imprimir_procesador();
        ++it;
    }
} 

void Cluster::imprimir_estructura_cluster() 
{ 
    BinTree<string> a = arbol; 
    i_imprimir_estructura_cluster(a);
    cout << endl;
}

void Cluster::i_imprimir_estructura_cluster(BinTree<string>& a) 
{ 
    if (not a.empty()) {
        cout << '(' << a.value();
        BinTree<string> left = a.left();
        i_imprimir_estructura_cluster(left);
        BinTree<string> right = a.right();
        i_imprimir_estructura_cluster(right);
        cout << ')';
    }
    else cout << ' ';
}


    //Modificadoras:
void Cluster::avanzar_tiempo(const unsigned int& t) 
{
    map<string, Procesador>::iterator it = mapa_string_procesador.begin(), itend = mapa_string_procesador.end();
    while (it != itend) {
        it->second.avanzar_tiempo(t);
        ++it;
    } 
}

void Cluster::alta_proceso_procesador(string& id_procesador, Proceso& p) 
{ 
    map<string, Procesador>::iterator it = mapa_string_procesador.find(id_procesador);
    if (it == mapa_string_procesador.end()) cout << "error: no existe procesador" << endl;
    else it->second.colocar_proceso(p);
    //si existe el procesador falta ver si ya contiene un proceso con el mismo identificador o el proceso no se puede colocar en el procesador
}

void Cluster::baja_proceso_procesador(string& id_procesador, int& id_proceso) 
{ 
    map<string, Procesador>::iterator it = mapa_string_procesador.find(id_procesador);
    if (it == mapa_string_procesador.end()) cout << "error: no existe procesador" << endl;
    else it->second.baja_proceso_procesador(id_proceso);
}

void Cluster::modificar_cluster(Cluster& c2, const string& id_procesador) 
{
    map<string, Procesador>::iterator it = mapa_string_procesador.find(id_procesador);
    if (it == mapa_string_procesador.end()) cout << "error: no existe procesador" << endl; 
    else if (it->second.contiene_procesos()) cout << "error: procesador con procesos" << endl;
    else {
        bool found = false; //nos servirá para ver si ha encontrado ya el proceso y evitar hacer el recorrido de la derecha (más óptimo). 
        modificar_bintree(c2, id_procesador, arbol, found);
    }
} 

void Cluster::modificar_bintree(Cluster& c2, const string& id_procesador, BinTree<string>& a, bool& found) 
{
    if (not a.empty() and (a.value() != id_procesador)) {
        BinTree<string> left = a.left();
        BinTree<string> right = a.right();
        modificar_bintree(c2, id_procesador, left, found);
        if (not found) modificar_bintree(c2, id_procesador, right, found); 
        a = BinTree<string> (a.value(), left, right);
    }
    else if (not a.empty()) {
        found = true;
        BinTree<string> left = a.left();
        BinTree<string> right = a.right();
        if (left.empty() and right.empty()) {
            a = c2.arbol;
            map<string, Procesador>::iterator it = mapa_string_procesador.find(id_procesador);
            mapa_string_procesador.erase(it);
            add_procesadores(c2.arbol, c2.mapa_string_procesador);
        }
        else cout << "error: procesador con auxiliares" << endl;
    }
}

void Cluster::add_procesadores(BinTree<string>& a, map<string, Procesador>& mapa) 
{
    if (not a.empty()) {
        map<string, Procesador>::iterator it = mapa.find(a.value());
        mapa_string_procesador[it->first] = it->second;
        BinTree<string> left = a.left();
        BinTree<string> right = a.right();
        add_procesadores(left, mapa);
        add_procesadores(right, mapa);
    }
}

void Cluster::compactar_memoria_cluster() 
{
    map<string, Procesador>:: iterator it = mapa_string_procesador.begin(), itend = mapa_string_procesador.end();
    while (it != itend) {
        it->second.compactar_memoria_procesador();
        ++it;
    }
} 

void Cluster::compactar_memoria_procesador(string& id_procesador) 
{
    map<string, Procesador>:: iterator it = mapa_string_procesador.find(id_procesador);
    if (it == mapa_string_procesador.end()) cout << "error: no existe procesador" << endl;
    else it->second.compactar_memoria_procesador();
} 

bool Cluster::i_BFS(Proceso& p, BinTree<string>& a) 
{  
    map<string, Procesador>::iterator it = mapa_string_procesador.end();
    if(not a.empty()){
        int hueco_max = 0, hueco = 0;
        queue <BinTree<string>> q;
        q.push(a);
        while(not q.empty()){
            BinTree<string> aux(q.front());
            //comparaciones
            //1-Si un proceso se puede colocar en más de un procesador, se elige el que disponga de un hueco más ajustado respecto a tal proceso y ya nb está colocado dicho proceso
            map<string, Procesador>::iterator itm = mapa_string_procesador.find(aux.value());          
            //if (it != mapa_string_procesador.end() and itm != mapa_string_procesador.end())cout << it->first << ' ' << itm->first << endl;
            if ((itm->second.hay_espacio(hueco, p.consultar_memoria())) and (not itm->second.tiene_proceso(p.consultar_id()))) { //itm->second = procesador al que apunta itm
                //cout << "ifif" << endl;
                //si es la 1a iteración si es la 2da o > iteración
                if (it == mapa_string_procesador.end() or hueco_max > hueco) {
                   // cout << "if" << endl;
                    hueco_max = hueco;
                    it = itm;
                }
                //En caso de empate entre varios procesadores, se designa el que quede con más memoria libre. 
                else if (hueco == hueco_max and itm->second.consultar_memoria_libre() > it->second.consultar_memoria_libre()) {
                   // cout << "else if" << endl;
                    it = itm;
                }
            }   
            //estructura del bfs
            if (not aux.left().empty()) q.push(aux.left());
            if (not aux.right().empty()) q.push(aux.right());
            q.pop();
        }
        if (it != mapa_string_procesador.end()) {
            it->second.colocar_proceso(p); //podria hacerse con cabe proceso
            return true;
        }
        return false;
    }
    return false;
}

bool Cluster::puedo_enviar_proceso_cluster(Proceso& p) 
{
    return i_BFS(p, arbol);
}
