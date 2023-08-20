#ifndef CLASS_Cluster_HH
#define CLASS_Cluster_HH
#ifndef NO_DIAGRAM
#include <iostream>
#include <map>
#include <queue>
#include "BinTree.hh"
#endif
#include "Procesador.hh"
using namespace std;

/** @class Cluster
*   @author Oriol Farrés i Vilar
*   @date Mayo del 2023
*   @brief <b>Un cluster consiste en varios procesadores interconectados distribuidos en una estructura de árbol binario, donde cada procesador tiene su propia memoria y capacidad de procesamiento. 
           Los procesadores trabajan en conjunto para ejecutar procesos de manera simultánea y coordinada.</b>
*/

class Cluster {

private:
    /** @brief <b>Árbol binario con el que represento el identificador de cada procesador (la estructura de conexiones del Cluster)</b> */
    BinTree<string> arbol; 
    /** @brief <b>Mapa con llave: string identificador del procesador y value: Procesador. 
               Nos permite tener los procesadores ordenados por orden lexicográfico de identificador (string) y 
               permite consultar/acceder, añadir y eliminar procesadores eficientemente manteniendo el orden lexicográfico</b> */ 
    map<string, Procesador> mapa_string_procesador; 


public:
    //Constructoras:
/** @brief <b>Inicializa un proceso con los valores default</b>
\pre <em>Existe</em> 
\post El resultado es un cluster incializado con su arbol binario y su mapa respectivo asignados al clúster parámetro implícito
*/
Cluster();


    //Consultoras:


   //Lectoras:
/** @brief <b>Configura un cluster </b>
\pre <em>Existe árbol binario a de procesadores. Los identificadores de los procesadores no están repetidos</em> 
\post Lee los procesadores del clúster, sus conexiones y la memoria de cada uno de ellos. 
Si ya existía un clúster anterior, este deja de existir.
*/
void configurar_cluster();



    //Escritoras:
/** @brief <b>Imprime el procesador de id_procesador del cluster</b>
\pre <em>Existe</em> 
@param id_procesador String, identificador del procesador con el cuál imprimiremos el procesador 
\post Si no existe dicho procesador en el cluster, da un error.
En caso contrario, llama al método 'PROCESADOR-->imprimir_procesador' para imprimir dicho proceso
*/
void imprimir_procesador(string& id_procesador);

/** @brief <b>Imprime los procesadores de un cluster</b>
\pre <em>Existe</em> 
\post Escribe todos los procesadores del clúster por orden creciente de identificador.
Para cada procesador se escribe lo mismo que en la funcionalidad anterior
*/
void imprimir_procesadores_cluster();

/** @brief <b>Imprime la estructura de un cluster</b>
\pre <em>Existe</em> 
\post Escribe la estructura de procesadores del clúster. 
*/
void imprimir_estructura_cluster();


    //Modificadoras:
/** @brief <b>Avanza t unidades de tiempo en la ejecución de todos los procesos</b>
\pre <em>Dado un int t >= 0</em>
@param t Entero, tiempo transcurrido
\post Lee un entero positivo t que indica las unidades de tiempo que han transcurrido desde la última vez que se avanzó 
el tiempo. Se eliminan todos los procesos activos que hayan acabado en ese intervalo de tiempo. 
La ejecución de todos los procesos de todos los procesadores han progresado t unidades de tiempo
*/
void avanzar_tiempo(const unsigned int& t);

/** @brief <b>Añade un proceso al procesador</b>
\pre <em>Dado un id del procesador y un id del proceso</em>
@param id_procesador String, identificador del procesador con el cuál imprimiremos el procesador 
@param p Proceso, el propio proceso que queremos tratar en el parámetro implícito (Área de procesos)
\post Comprueba si hay error. Si no hay error: se añade el proceso al procesador
*/
void alta_proceso_procesador(string& id_procesador, Proceso& p);

/** @brief <b>Elimina el proceso de un procesador</b>
\pre <em>Dado un id del procesador y un id del proceso</em> 
@param id_procesador String, identificador del procesador del cuál eliminaremos el proceso
@param id_proceso Entero, identificador del proceso que eliminaremos
\post Comprueba si hay error. Si no hay error: se elimina el proceso del procesador
*/
void baja_proceso_procesador(string& id_procesador, int& id_proceso);

/** @brief <b>Modifica un cluster</b>
\pre <em>Dado un cluster c y un string id</em> 
@param id_procesador String, identificador del procesador con el cuál imprimiremos el procesador 
@param c Cluster, Clúster que queremos utilizar para modificar el parámetro implícito
\post Lee los procesadores del clúster, sus conexiones y la memoria de cada uno de ellos. 
Si ya existía un clúster anterior, este deja de existir.
*/ 
void modificar_cluster(Cluster& c, const string& id_procesador);

/** @brief <b>Modifica el cluster</b>
\pre <em>Existen x, id_procesador, tree y found</em> 
@param id_procesador String, identificador del procesador con el cuál imprimiremos el procesador 
@param c Cluster, Clúster que queremos utilizar para modificar el parámetro implícito
@param found Booleano, lo utilizaremos para certificar que el árbol no esta vacío y su nódo equivale a un id del procesador
\post Modifica mediante un procedimiento recursivo un cluster
*/ 
void modificar_bintree(Cluster& c, const string& id_procesador, BinTree<string>& tree, bool& found);

/** @brief <b>Añade procesadores al cluster</b>
\pre <em>Dado un árbol binario a y un mapa <string, Procesador></em> 
@param a BinTree, árbol binario que utilizaremos para añadir procesadores 
@param m Mapa de string procesador, que pasamos por referencia para modificarlo
\post Añade mediante un procedimiento recursivo los procesadores al cluster, actualizando los valores del mapa 
*/ 
void add_procesadores(BinTree<string>& a, map<string, Procesador>& m);

/** @brief <b>Compacta la memoria de un cluster</b>
\pre <em>Existe</em> 
\post En cada procesador, se mueven todos los procesos hacia el principio de la memoria, sin dejar huecos, 
sin solaparse y respetando el orden inicial. 
*/ 
void compactar_memoria_cluster();

/** @brief <b>Compacta la memoria de un procesador</b>
\pre <em>Dado un id del procesador</em> 
@param id_procesador String, identificador del procesador con el compactaremos la memoria del procesador 
\post Lee el identificador de un procesador. 
Si no hay error: se mueven todos los procesos hacia el principio de la memoria del procesador, 
sin dejar huecos, sin solaparse y respetando el orden inicial.
*/ 
void compactar_memoria_procesador(string& id_procesador);

/** @brief <b>Nos permite saber si puedo enviar o no el proceso al cluster mediante un recorrido en amplitud (BFS)</b>
\pre <em>Existen el proceso y el árbol binario</em> 
@param p Proceso, el propio proceso que queremos evaluar
\post Función de inmersión de "bool puedo_enviar_proceso_cluster(Proceso& p)", donde pasamos por referencia además el árbol binario.
El resultado indica si podemos enviar o no el proceso 'p' al cluster.
@return True si puedo enviar el proceso al cluster
@return False si no puedo enviar el proceso al cluster
*/
bool i_BFS(Proceso& p, BinTree<string>& a);

/** @brief <b>Nos permite saber si puedo enviar o no el proceso al cluster</b>
\pre <em>Existe el proceso</em> 
@param p Proceso, el propio proceso que queremos evaluar
@param a BinTree, árbol binario que utilizaremos para añadir procesadores 
\post El resultado indica si podemos enviar o no el proceso 'p' al cluster
@return True si puedo enviar el proceso al cluster
@return False si no puedo enviar el proceso al cluster
*/
bool puedo_enviar_proceso_cluster(Proceso& p);

//Siguiendo el ejemplo encontrado en el disco de la FIB: "disseny_modular_doxygen_II/SOL_BINTREE/Sistema.hh"
private:

/** @brief <b>Imprime la estructura de un cluster</b>
\pre <em>Existe el árbol binario</em> 
@param a BinTree, árbol binario que utilizaremos para añadir procesadores 
\post Función de inmersión de "void imprimir_estructura_cluster()", donde pasamos por referencia además el árbol binario.
Como resultado imprime la estructura de un cluster mediante un procedimiento recursivo
*/
static void i_imprimir_estructura_cluster(BinTree<string>& a);

/** @brief <b>Configura un cluster</b>
\pre <em>Existen árbol binario a de procesadores y el mapa</em> 
@param a BinTree, árbol binario que utilizaremos para imprimir la estructura del cluster
@param m Mapa de string procesador, que pasamos por referencia para configurarlo
\post Función de inmersión de "configurar_cluster", la cuál lee los procesadores del clúster, sus conexiones y la memoria de cada uno de ellos. 
Si ya existía un clúster anterior, este deja de existir.
*/
static void i_configurar_cluster(BinTree<string>& a, map<string, Procesador>& mapa);

};
#endif
