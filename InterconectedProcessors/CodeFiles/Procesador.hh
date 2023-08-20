#ifndef CLASS_Procesador_HH
#define CLASS_Procesador_HH
#include "Proceso.hh"
#ifndef NO_DIAGRAM
#include <iostream>
#include <set>
#include <map>
#endif
using namespace std;

/** @class Procesador
*   @author Oriol Farrés i Vilar
*   @date Mayo del 2023
*   @brief <b>Un procesador en esta arquitectura multiprocesador es una unidad de procesamiento individual con un identificador único, su propia memoria asignada y la capacidad de ejecutar varios procesos simultáneamente. 
           Los procesadores se organizan en una estructura de árbol binario y son responsables de administrar los procesos que se ejecutan en su memoria.</b>
*/

class Procesador { 

private:
    /** @brief <b>Mapa con llave: posición inicial de memoria del proceso y valor: proceso</b> */
    map<int, Proceso> mapa_int_proceso;
    /** @brief <b>Mapa con llave: id_proceso y valor: posición inicial de memoria del proceso (que servirá para el mapa de arriba)</b> */ 
    map<int, int> mapa_donde_esta_proceso;
    /** @brief <b>Mapa con llave: como de grande es el hueco y valor: set de todos los huecos de tamaño igual al de la llave. (posicion inicial del hueco la memoria)</b> */ 
    map<int, set<int>> mapa_size_position;
    /** @brief <b>String que representa el identificador de cada procesador</b> */
    string id_procesador;
    /** @brief <b>Entero que representa la memoria del procesador, es constante</b> */
    int memoria_total;
    /** @brief <b>Entero que representa la memoria disponible del procesador, memoria que varia en función de los huecos (decrementa al añadir procesos y incrementa al eliminarlos), no es constante</b> */ 
    int memoria_disponible;


public:
    //Constructoras:
/** @brief <b>Inicializa un procesador con los valores default</b>
\pre <em>Existe</em> 
\post El resultado es un procesador incializado con los valores por defecto asignados al procesador parámetro implícito
*/
Procesador();

/** @brief <b>Inicializa un proceso con su id, y memoria respectivos</b>
\pre <em>Existe id y memoria > 0 </em> 
@param id String, identificador del procesador con el cuál inicializaremos el procesador parámetro implícito
@param m Entero, memoria total que tiene el procesador con la cuál inicializaremos el proceso parámetro implícito
\post El resultado es un procesador con el id y memoria asignados al procesador parámetro implícito
*/
Procesador(string& id, const int& m);



    //Consultoras:
/** @brief <b>Nos permite consultar un id</b>
\pre <em>Existe</em>  
\post El resultado es el id del parámetro implícito 
@return El id del procesador
*/
string consultar_id() const;

/** @brief <b>Nos devuelve la memoria total del procesador</b>
\pre <em>Existe</em> 
\post El resultado es la memoria total del parámetro implícito (esta memoria es constante y nunca puede variar) 
@return La memoria del procesador
*/
int consultar_memoria() const;

/** @brief <b>Nos devuelve la memoria libre del procesador</b>
\pre <em>Existe</em> 
\post El resultado es la memoria libre del parámetro implícito 
@return La memoria libre del procesador
*/
int consultar_memoria_libre() const;

/** @brief <b>Nos permite saber si un procesador está vacío</b>
\pre <em>Existe el procesador</em> 
\post El resultado indica si un procesador está vacío o no (contiene o no procesos) 
@return True si contiene procesos
@return False si no contiene procesos
*/
bool contiene_procesos() const;

/** @brief <b>Nos permite saber si el procesador tiene o no dicho proceso</b>
\pre <em>Existe </em> 
@param id_proceso Entero, identificador del proceso que puede estar o no en el procesador
\post El resultado indica si existe o no un proceso con dicho id en el procesador (tiene dicho proceso en el procesador o no)
@return True si tiene el proceso con id_proceso
@return False si no tiene el proceso con id_proceso
*/
bool tiene_proceso(const int& id_proceso) const;

/** @brief <b>Nos devuelve el hueco más grande del procesador</b>
\pre <em>Existe, id > 0 </em> 
\post El resultado es el tamaño del hueco más grande del procesador
@return El tamaño del hueco más grande del procesador
*/
int consultar_hueco_mas_grande() const;

/** @brief <b>Nos permite saber si el proceso tiene o no un hueco en la izquierda</b>
\pre <em>Existe, id > 0 </em> 
@param id_proceso Entero, identificador del proceso que está en el procesador
\post El resultado indica si existe o no un hueco a la izquierda de dicho proceso
@return True si existe un hueco a la izquierda del proceso id_proceso
@return False si no existe un hueco a la izquierda del proceso id_proceso
*/
bool hueco_izquierdo(const int& id_proceso) const;

/** @brief <b>Nos permite saber si el proceso tiene o no un hueco en la derecha</b>
\pre <em>Existe, id > 0 </em> 
@param id_proceso Entero, identificador del proceso que está en el procesador
\post El resultado indica si existe o no un hueco a la derecha de dicho proceso
@return True si existe un hueco a la derecha del proceso id_proceso
@return False si no existe un hueco a la derecha del proceso id_proceso
*/
bool hueco_derecho(const int& id_proceso) const;

/** @brief <b>Nos permite saber si el proceso tiene o no más procesos a su izquierda</b>
\pre <em>Existe, it apunta a  un proceso del mapa 'mapa_int_proceso'</em> 
@param it Iterador del mapa de int proceso, apunta al proceso que está en el procesador
\post El resultado indica si hay más procesos o no a la izquierda del proceso apuntado por el iterador 'it'
@return True si hay más procesos a la izquierda
@return False si no hay más procesos a la izquierda
*/
bool hay_mas_procesos_izquierda(const map<int, Proceso>::const_iterator& it) const;

/** @brief <b>Nos permite saber si el proceso tiene o no más procesos a su derecha</b>
\pre <em>Existe, it apunta a  un proceso del mapa 'mapa_int_proceso'</em> 
@param it Iterador del mapa de int proceso, apunta al proceso que está en el procesador
\post El resultado indica si hay más procesos o no a la derecha del proceso apuntado por el iterador 'it'
@return True si hay más procesos a la derecha
@return False si no hay más procesos a la derecha
*/
bool hay_mas_procesos_derecha(const map<int, Proceso>::const_iterator& it) const;



   //Lectoras:
/** @brief <b>Lee un procesador</b>
\pre <em>Existe</em> 
@param idp String, identificador del procesador con el cuál inicializaremos el procesador parámetro implícito
\post Lee un procesador con su memoria total e inicializa el mapa de huecos 
*/
void read_procesador(string& idp);



    //Escritoras:
/** @brief <b>Imprime un procesador</b>
\pre <em>Dado un procesador con sus datos respectivos</em> 
\post Imprime todos los procesos de dicho procesador
*/
void imprimir_procesador();



    //Modificadoras:
/** @brief <b>Avanza t unidades de tiempo a todoa los procesos del procesador</b>
\pre <em>Existe un tiempo t >= 0</em> 
@param t Entero, tiempo transcurrido, mandado desde el Cluster
\post Avanza t unidades de tiempo los procesos almacenados en un procesador. 
La simulación de su ejecución consiste en disminuir el tiempo que les queda hasta que terminan. 
Cuando su tiempo es 0, los procesos se eliminan automáticamente del procesador y se convierten en huecos de su memoria.
*/
void avanzar_tiempo(const unsigned int& t); 

/** @brief <b>Compacta la memoria del procesador</b>
\pre <em>Existe</em>  
\post El resultado es la memoria del procesador compactada
*/ 
void compactar_memoria_procesador();

/** @brief <b>Calcula el tamaño del hueco de la izquierda y elimina el hueco previo</b>
\pre <em>Dado el iterador del proceso que queremos eliminar en el "método baja_proceso_procesador"</em> 
@param itpl Iterador del mapa de int proceso, apunta al proceso que está en el procesador
@param posi Entero, representa la posicion inicial del hueco de la izquierda
\post Este método es capaz de calcular el tamaño del hueco de la izquierda (previamente hemos comprobado que había hueco a la izquierda).
Además, elimina el hueco de la izquierda del set para crear un hueco más grande que incluya al proceso que eliminaré + el hueco de la izquierda
@return Tamaño del hueco de la izquierda
*/
int metodo_hueco_izquierda(int& posi, map<int, Proceso>::iterator& itpl);

/** @brief <b>Calcula el tamaño del hueco de la derecha y elimina el hueco previo</b>
\pre <em>Dado el iterador del proceso que queremos eliminar en el bpp</em> 
@param itp Iterador del mapa de int proceso, apunta al proceso que está en el procesador
@param posi Entero, representa la posicion inicial del hueco de la izquierda
@param size_proceso Entero, representa el tamaño del proceso
\post Este método es capaz de calcular el tamaño del hueco de la derecha (previamente hemos comprobado que había hueco a la derecha).
Además, elimina el hueco de la derecha del set para crear un hueco más grande que incluya al proceso que eliminaré + el hueco de la derecha
@return Tamaño del hueco de la derecha
*/
int metodo_hueco_derecha(const int& posi,const int& size_proceso, map<int, Proceso>::iterator& itp);

/** @brief <b>Crea un hueco con un tamaño y una posicion inicial determinados</b>
\pre <em>Existen size > 0 y representa el tamaño del hueco, posi > 0 y representa la posición inicial del hueco que queremos crear</em> 
@param posi Entero, representa la posicion inicial del hueco de la izquierda
@param size Entero, representa tamaño del hueco que quiero crear
\post Crea un hueco de tamaño (size) y con posición inicial (posi). Modifica el map<int, set<int>>
*/
void crear_hueco(const int& size, const int& posi);

/** @brief <b>Elimina el proceso designado del procesador</b>
\pre <em>Existen it y itp que apuntan al proceso que queremos</em> 
@param it Iterador del mapa de int int, apunta al id del proceso que queremos eliminar
@param itp Iterador del mapa de int proceso, apunta al proceso que está en el parámetro implícito (procesador)
\post Elimina el proceso referenciado por el iterador it del map<int, int> 'mapa_donde_esta_proceso', mientras que el iterador itp lo elimina del map<int, Proceso> 'mapa_int_proceso'
*/
void eliminar_proceso(map<int, int>::iterator& it, map<int, Proceso>::iterator& itp);

/** @brief <b>Elimina el proceso de un procesador</b>
\pre <em>Existe un id del proceso</em> 
@param id_proceso Entero, identificador del proceso que puede estar o no en el procesador
\post Lee el identificador de un procesador y de un proceso.
Si no hay error: se elimina el proceso del procesador
*/
void baja_proceso_procesador(const int& id_proceso);

/** @brief <b>Coloca si se puede el proceso en el procesador</b>
\pre <em>Existe un Proceso p</em> 
@param p Proceso, el propio proceso que queremos colocar en el parámetro implícito (procesador)
\post Si ya existe dicho proceso en el procesador, da un error.
En caso contrario, llama al método 'cabe_proceso_al_procesador' para colocar dicho proceso
*/
void colocar_proceso(const Proceso& p);

/** @brief <b>Si cabe el proceso en el procesador, introduce el proceso en la memoria del procesador</b>
\pre <em>Existe un Proceso p</em> 
@param p Proceso, el propio proceso que queremos colocar en el parámetro implícito (procesador)
\post Si no cabe el proceso en el procesador, da un error.
En caso contrario, introduce el proceso 'p' en el procesador
*/
void cabe_proceso_al_procesador(const Proceso& p);

/** @brief <b>Determina si hay espacio (y lo calcula) o no</b>
\pre <em>Existe un hueco y es modificable, itm  apunta al procesador que queremos</em> 
@param hueco Entero, si hay espacio, lo calcula
@param memoria_ocupada Entero, memoria que ocupa el proceso tratado
\post Si no cabe el proceso en el procesador, devuelve false.
En caso contrario, calcula el valor del espacio (hueco) y devuelve true
@return True si cabe el proceso en el procesador y calcula el valor del hueco 
@return False si no cabe el proceso en el procesador
*/
bool hay_espacio(int& hueco, const int& memoria_ocupada);


};
#endif
