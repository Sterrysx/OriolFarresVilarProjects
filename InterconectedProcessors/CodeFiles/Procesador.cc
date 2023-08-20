#include "Procesador.hh"

    //Constructoras:
Procesador::Procesador() 
{ 
    mapa_int_proceso = map<int, Proceso>();
    mapa_donde_esta_proceso = map<int, int>();
    mapa_size_position = map<int, set<int>>();
    id_procesador = "";
    memoria_total = 0;
    memoria_disponible = memoria_total;
}

Procesador::Procesador(string& id, const int& m) 
{ 
    mapa_int_proceso = map<int, Proceso>();
    mapa_donde_esta_proceso = map<int, int>();
    mapa_size_position = map<int, set<int>>();
    id_procesador = id;
    memoria_total = m;
    memoria_disponible = m;
}


    //Consultoras:
string Procesador::consultar_id() const 
{ 
    return id_procesador;
}

int Procesador::consultar_memoria() const
{ 
    return memoria_total;
}

int Procesador::consultar_memoria_libre() const 
{
    return memoria_disponible;
}

bool Procesador::contiene_procesos() const 
{
    if (mapa_int_proceso.size() == 0) return false;
    return true; 
}

bool Procesador::tiene_proceso(const int& id_proceso) const 
{ 
   map<int, int>::const_iterator it = mapa_donde_esta_proceso.find(id_proceso);
   if (it == mapa_donde_esta_proceso.end()) return false;
   else return true;
}

int Procesador::consultar_hueco_mas_grande() const 
{
    map<int, set<int>>::const_iterator it = mapa_size_position.end();
    --it;
    return it->first;
}

bool Procesador::hueco_izquierdo(const int& id_proceso) const 
{
    map<int, int>::const_iterator it = mapa_donde_esta_proceso.find(id_proceso);
    int posi = it->second; //posi = posicion inicial del proceso
    //si está a la izquierda del todo:
    if (posi == 0) return false;
    else {
        //no hay más procesos a la izquierda
        map<int, Proceso>::const_iterator itaux = mapa_int_proceso.find(posi);
        if (not hay_mas_procesos_izquierda(itaux)) return true;
        //hay más procesos a la izquierda
        else {
            map<int, Proceso>::const_iterator pre_it = mapa_int_proceso.find(posi);
            --pre_it; //pre_it apunta al proceso anterior
            int pre_posi = pre_it->first; //pre_posi = posicion inicial del proceso previo
            int pre_size = pre_it->second.consultar_memoria(); //pre_size = tamaño del proceso previo
            if (pre_posi + pre_size == posi) return false;
            return true;
        }
    }
}

bool Procesador::hueco_derecho(const int& id_proceso) const 
{
    map<int, int>::const_iterator it = mapa_donde_esta_proceso.find(id_proceso);
    int posi = it->second; //posi = posicion inicial del proceso
    map<int, Proceso>::const_iterator itp = mapa_int_proceso.find(posi); //apunta al proceso con posicion inicial posi
    int size_proceso = itp->second.consultar_memoria();
    //si está a la derecha del todo:
    if (posi + size_proceso == consultar_memoria()) return false;
    else {
        ////si está a la derecha del todo pero no llega al final:
        if (not hay_mas_procesos_derecha(itp)) return true;
        //hay más procesos a la derecha
        else {
            ++itp;
            int post_posi = itp->first; //post_posi = posicion inicial del proceso posterior
            if (posi + size_proceso == post_posi) return false;
            return true;
        }
    }
}

bool Procesador::hay_mas_procesos_izquierda(const map<int, Proceso>::const_iterator& it) const
{
    if (it == mapa_int_proceso.begin()) return false;
    return true;
}

bool Procesador::hay_mas_procesos_derecha(const map<int, Proceso>::const_iterator& it) const
{
    map<int, Proceso>::const_iterator itaux = it;
    ++itaux;
    if (itaux == mapa_int_proceso.end()) return false;
    return true; 
}


    //Lectoras:
void Procesador::read_procesador(string& idp) 
{ 
    id_procesador = idp;
    cin >> memoria_total;
    memoria_disponible = memoria_total;
    set<int> s;
    s.insert(0);
    mapa_size_position[memoria_total] = s;
}


    //Escritoras:
void Procesador::imprimir_procesador() 
{ 
    map<int, Proceso>::iterator it, itend;
    itend = mapa_int_proceso.end();
    for (it = mapa_int_proceso.begin(); it != itend; ++it) {
        cout << it->first << ' ';
        it->second.imprimir_proceso();
    }
}


    //Modificadoras:
void Procesador::avanzar_tiempo(const unsigned int& t) 
{ 
    map<int, Proceso>::iterator it = mapa_int_proceso.begin(), itend = mapa_int_proceso.end();
    while (it != itend) {
        it->second.modificar_tiempo(t);
        if (it->second.consultar_tiempo() <= 0) {
            map<int, Proceso>::iterator safe = it;
            ++it;
            baja_proceso_procesador(safe->second.consultar_id());
         }
        else ++it;
    }
} 

void Procesador::compactar_memoria_procesador() 
{
    mapa_size_position.clear(); //elimina  todos los huecos del procesador
    map<int, Proceso>::iterator it = mapa_int_proceso.begin(),  itend = mapa_int_proceso.end();
    int posiciones_desplazadas = 0; //tamaño a retrasar (tamaño de los anteriores huecos sumados)
    int posi = 0; //posicion inicial del proceso al que apunta it
    int pre_posif = 0; //posicion final del proceso anterior
    while (it != itend) {
        posi = it->first;
        Proceso p = it->second;
        if (pre_posif != posi) { //hay hueco izquierda (no está compactado)
            //modificar mapa int proceso
            it = mapa_int_proceso.erase(it);
            mapa_int_proceso[pre_posif] = p;
            mapa_donde_esta_proceso[p.consultar_id()] = pre_posif;
            //compactar memoria
            posiciones_desplazadas += (posi - pre_posif);
        }
        else ++it;
        pre_posif += p.consultar_memoria();
    }
    //si hay más huecos detrás del último proceso:
    if (pre_posif != consultar_memoria()) posiciones_desplazadas = consultar_memoria() - pre_posif;
    //crear hueco a la derecha del procesador de tamaño = Σ(huecos)
    crear_hueco(posiciones_desplazadas, pre_posif);
}


int Procesador::metodo_hueco_izquierda(int& posi, map<int, Proceso>::iterator& itpl) 
{
    //busco tamaño y posicion inicial del hueco de la izquierda
    int left_posi = 0;
    int left_size_hueco;
    if (hay_mas_procesos_izquierda(itpl)) {
        --itpl;
        left_size_hueco = posi - itpl->first - itpl->second.consultar_memoria();
        left_posi = posi - left_size_hueco;
    }
    else left_size_hueco = posi;

    //elimino hueco de la izquierda del set para crear un hueco más grande que incluya al proceso que eliminaré+hueco izquierda
    map<int, set<int>>::iterator left_its = mapa_size_position.find(left_size_hueco);
    set<int>::iterator left_itsaux = left_its->second.find(left_posi);
    //hay 2 opciones
    //(a) es el único hueco de este tamaño
    if (left_its->second.size() == 1) mapa_size_position.erase(left_its);
    //(b) hay más huecos de este tamaño
    else left_its->second.erase(left_itsaux);
    posi = left_posi;//calculo posicion inicial del nuevo hueco
    return left_size_hueco;
}

int Procesador::metodo_hueco_derecha(const int& posi,const int& size_proceso, map<int, Proceso>::iterator& itpr) 
{
//busco tamaño y posicion inicial del hueco de la derecha
            int right_posi  = posi + size_proceso; //right_posi = posicion inicial del hueco de la derecha
            int right_size_hueco;
            if (hay_mas_procesos_derecha(itpr)) {
                ++itpr; //apunta al proceso de la derecha, donde itpaux->first es su posicion inicial
                right_size_hueco = itpr->first - right_posi; //right_size_hueco = tamaño del hueco de la derecha
            }
            else right_size_hueco = consultar_memoria() - (posi + size_proceso);
            //elimino hueco de la derecha del set para crear un hueco más grande que incluya al proceso que eliminaré+hueco derecha
            map<int, set<int>>::iterator right_its = mapa_size_position.find(right_size_hueco);
            set<int>::iterator right_itsaux = right_its->second.find(right_posi);
            //hay 2 opciones
            //(a) es el único hueco de este tamaño
            if (right_its->second.size() == 1) mapa_size_position.erase(right_its);
            //(b) hay más huecos de este tamaño
            else right_its->second.erase(right_itsaux);
            return right_size_hueco;
}

void Procesador::crear_hueco(const int& size, const int& posi) 
{
    map<int, set<int>>::iterator add_its = mapa_size_position.find(size);
    //2 opciones
    //opcion a) no existe un hueco de este tamaño:
    if (add_its == mapa_size_position.end()) {
        set<int> set;
        set.insert(posi);
        mapa_size_position[size] = set;
    }
    //opcion b) ya existe un hueco de este tamaño:
    else add_its->second.insert(posi);

}

void Procesador::eliminar_proceso(map<int, int>::iterator& it, map<int, Proceso>::iterator& itp) 
{
    mapa_donde_esta_proceso.erase(it);
    mapa_int_proceso.erase(itp);
}

void Procesador::baja_proceso_procesador(const int& id_proceso)
{ 
//El procesador puede ser visualizado como un rectángulo horizontal que tiene una posición inicial y se extiende hacia la derecha. Dentro de este rectángulo, 
//se encuentran una serie de espacios vacíos, o "huecos", que representan diferentes etapas o pasos en el procesamiento de la información.
//Cuando se inicia el procesador, los huecos más cercanos a la posición inicial, es decir, los de la izquierda, son los primeros en ser ocupados. 
//Estos huecos representan las primeras tareas o instrucciones que se deben ejecutar. A medida que se completan estas tareas, se crean huecos del tamaño del proceso terminado, 
//dejando espacio libre para nuevos procesos en el procesador. Este modelo visual del procesador nos permite entender cómo se ejecutan las instrucciones de manera secuencial. 
    map<int, int>::iterator it = mapa_donde_esta_proceso.find(id_proceso);
    if (it == mapa_donde_esta_proceso.end()) cout << "error: no existe proceso" << endl;
    else {
        map<int, int>::iterator it = mapa_donde_esta_proceso.find(id_proceso);
        int posi = it->second; //posi = posicion inicial del proceso
        map<int, Proceso>::iterator itp = mapa_int_proceso.find(posi), itpl = itp, itpr = itp; //apunta al proceso con posicion inicial posi
        int size_proceso = itp->second.consultar_memoria();
        memoria_disponible += size_proceso;
        bool left_hueco = hueco_izquierdo(id_proceso);
        bool right_hueco = hueco_derecho(id_proceso);

        if (left_hueco and right_hueco) { //elimina con hueco a la izquierda y a la derecha
            //calculo tamaño nuevo hueco = tamaño proceso a eliminar + tamaño hueco izquierda
            int size_hueco = size_proceso + metodo_hueco_derecha(posi, size_proceso, itpr);
            //calculo tamaño nuevo hueco = tamaño hueco izquierda + proceso + tamaño hueco derecha
            size_hueco += metodo_hueco_izquierda(posi, itpl);
            crear_hueco(size_hueco, posi);
            eliminar_proceso(it, itp);
        }
        else if (left_hueco and not right_hueco) { //elimina con solo hueco izquierda
            //calculo tamaño nuevo hueco = tamaño proceso a eliminar + tamaño hueco izquierda
            int size_hueco = size_proceso + metodo_hueco_izquierda(posi, itpl);
            crear_hueco(size_hueco, posi);
            eliminar_proceso(it, itp);
        }
        else if (not left_hueco and right_hueco) { //elimina con solo hueco derecho
            //calculo tamaño nuevo hueco = tamaño proceso a eliminar + tamaño hueco derecha
            int size_hueco = size_proceso + metodo_hueco_derecha(posi, size_proceso, itpr);
            crear_hueco(size_hueco, posi);
            eliminar_proceso(it, itp);
        }
        else { //elimina sin huecos
            crear_hueco(size_proceso, posi);
            eliminar_proceso(it, itp);
        }
    } 
}

void Procesador::colocar_proceso(const Proceso& p) 
{ 
   if (tiene_proceso(p.consultar_id())) cout << "error: ya existe proceso" << endl;
   else cabe_proceso_al_procesador(p);
}

void Procesador::cabe_proceso_al_procesador(const Proceso& p) 
{ 
   if (p.consultar_memoria() > memoria_total) cout << "error: no cabe proceso" << endl; //si proceso ocupa más que el hueco que tenemos disponible
   else {
        map<int, set<int>>::iterator it = mapa_size_position.lower_bound(p.consultar_memoria());
        //el iterador apunta al elemento con la posición más ajustada
        if (it == mapa_size_position.end()) cout  << "error: no cabe proceso" << endl;
        else {
            int size_hueco = it->first - p.consultar_memoria();
            set<int>::iterator position_hueco = it->second.begin(); //primer valor del set, posición donde empieza el hueco
            int posi = *position_hueco;
            mapa_donde_esta_proceso[p.consultar_id()] = posi;
            mapa_int_proceso[posi] = p;
            memoria_disponible -= p.consultar_memoria();
            if (it->first > p.consultar_memoria()) {
                //existen 2 opciones
                //(a) no existe un hueco del mismo tamaño dentro del mapa
                map<int, set<int>>::iterator its = mapa_size_position.find(size_hueco);
                if (its == mapa_size_position.end()) {
                    set<int> set;
                    set.insert(posi+p.consultar_memoria());
                    mapa_size_position[size_hueco] = set;
                }
                //(b) ya existe un hueco del mismo tamaño dentro del mapa
                else its->second.insert(posi+p.consultar_memoria());
            }
            if (it->second.size() == 1) mapa_size_position.erase(it);
            else it->second.erase(position_hueco);
       }
   }
}

bool Procesador::hay_espacio(int& hueco, const int& memoria_ocupada) 
{ 
    map<int, set<int>>::iterator it = mapa_size_position.lower_bound(memoria_ocupada); // itm->second.consultar_memoria() = tamaño del procesador
    if (it == mapa_size_position.end()) return false;
    else {
        hueco = it->first;
        return true;
    }
}
