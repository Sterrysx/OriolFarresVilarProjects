#ifndef CLASS_Proceso_HH
#define CLASS_Proceso_HH
#ifndef NO_DIAGRAM
#include <iostream>
#endif
using namespace std;

/** @class Proceso
*   @author Oriol Farrés i Vilar
*   @date Mayo del 2023
*   @brief <b>Un proceso en este contexto representa una tarea o conjunto de instrucciones con un identificador único, que requiere una cierta cantidad de memoria y un tiempo estimado de ejecución. 
           Los procesos pueden estar pendientes, activos o finalizados, y se ejecutan en un clúster multiprocesador, donde cada procesador tiene su propia memoria y puede ejecutar múltiples procesos simultáneamente.</b>
*/

class Proceso {

private:
/** @brief <b>Entero que representa el identificador de cada proceso</b> */
    int id_proceso;  
/** @brief <b>Entero que representa el tamaño total de la memoria de cada proceso</b> */
    int size; 
/** @brief <b>Entero que representa el tiemo de ejecución que tiene cada proceso</b> */
    int tiempo; 


public:
    //Constructoras:
/** @brief <b>Inicializa un proceso con los valores default</b> 
\pre  <em>Existe</em> 
\post El resultado es un proceso incializado con los valores por defecto asignados al proceso parámetro implícito
*/
Proceso();

/** @brief <b>Inicializa un proceso con su id, tiempo y memoria respectivos</b>
\pre <em>Existe string , tiempo >= 0 y memoria</em> 
@param id_proceso Entero, identificador del proceso con el cuál inicializaremos el proceso parámetro implícito
@param tiempo Entero, tiempo con el cuál inicializaremos el proceso parámetro implícito
@param memoria_ocupada Entero, memoria que ocupa el proceso con el cuál inicializaremos el proceso parámetro implícito
\post El resultado es un proceso con el id_proceso, tiempo y memoria_ocupada asignados al proceso parámetro implícito
*/
Proceso(const int& id_proceso, const int& tiempo,  const int& memoria_ocupada);


    //Consultoras:
/** @brief <b>Nos permite consultar un id</b>
\pre <em>Existe</em>
\post El resultado es el id del parámetro implícito
@return Id del proceso 
*/
int consultar_id() const;

/** @brief <b>Nos permite consultar un tamaño
\pre <em>Existe</em> 
\post El resultado es el tamaño del proceso del parámetro implícito 
@return Tamaño del proceso 
*/
int consultar_memoria() const;

/** @brief <b>Nos permite consultar un tiempo</b>
\pre <em>Existe</em>
\post El resultado es el tiempo de ejecución del parámetro implícito
@return Tiempo de ejecución del proceso 
*/
int consultar_tiempo() const;


    //Lectoras:
/** @brief <b>Lee un proceso</b>
\pre <em>Existe</em> 
\post Lee un proceso con su id, tiempo y memoria respectivos
*/
void read_proceso();



    //Escritoras:
/** @brief <b>Imprime un proceso</b>
\pre <em>Dado un proceso con su id, tiempo y memoria respectivo</em> 
\post Imprime dicho proceso con con su id, tiempo y memoria respectivos
*/
void imprimir_proceso();



    //Modificadoras:
/** @brief <b>Modifica el tiempo de un proceso</b>
\pre <em>Dado el tiempo de un proceso</em> 
@param t Entero, tiempo transcurrido, mandado desde el Cluster
\post Modifica el tiempo de un proceso permitiendo avanzar el tiempo t unidades de tiempo
*/
void modificar_tiempo(const int& t);


};
#endif
