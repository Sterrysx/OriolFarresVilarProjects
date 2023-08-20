#ifndef CLASS_Process_Area_HH
#define CLASS_Process_Area_HH
#include "Proceso.hh"
#include "Cluster.hh"
#ifndef NO_DIAGRAM
#include <list>
#include <set>
#include <iostream>
#include <map>
#endif
using namespace std;

/** @class Process_Area
*   @author Oriol Farrés i Vilar
*   @date Mayo del 2023
*   @brief <b>El "área de procesos" se refiere a una zona o espacio específico donde se almacenan los procesos pendientes de ejecución. 
           Es un área dedicada para contener los procesos que están en espera antes de ser ejecutados en el clúster multiprocesador.
           Los procesos en el área de procesos esperan su turno hasta que sean asignados a un procesador disponible para su ejecución.</b>
*/

class Process_Area {

private:
/** @struct priority
*   @brief <b>El struct "Prioridad" se refiere a un atributo asignado a los procesos pendientes que determina su orden de ejecución. 
           Los procesos con mayor prioridad tienen la preferencia de ser ejecutados antes que los de menor prioridad, siguiendo un sistema de clasificación basado en el nombre de prioridad.</b>
*/
    struct priority {
        /** @brief <b>Número de procesos colocados (aceptados)</b> */
        int npc; 
        /** @brief <b>Número de procesos rechazados</b> */
        int npr; 
        /** @brief <b>Lista ordenada de procesos más antiguos a procesos más recientes</b> */
        list<Proceso> l; 
        /** @brief <b>Mapa de solo llaves, donde la llave es el int que representa el id_proceso</b> */
        set<int> id_proceso; 
    };

    /** @brief <b>Mapa con llave: string (que puede ser un int) id_priority y el valor: struct priority.
               Mapa donde puedo almacenar Prioridades por orden lexicográfico de identificador</b>  */
    map<string, priority> mapa_string_priority; 


public:
    //Constructoras:
/** @brief <b>Inicializa una área de procesos con los valores default</b>
\pre <em>Existe</em> 
\post El resultado es una área de procesos incializada asignados al parámetro implícito 
*/
Process_Area();


    //Consultoras:
/** @brief <b>Nos permite saber si existe algún proceso con el id de prioridad que buscamos</b>
\pre <em>Existen el proceso y el id </em> 
@param p Proceso, el propio proceso que queremos tratar en el parámetro implícito (Área de procesos)
@param id_priority String, identificador de prioridad que tiene el propio proceso
\post El resultado indica si existe o no algún proceso "p" con el id de prioridad "id_priority" que buscamos
@return True si existe el proceso en el área de espera con id_priority que buscamos
@return False si no existe el proceso en el área de espera con id_priority que buscamos
*/
bool existe_proceso(const Proceso& p, const string& id_priority) const;


   //Lectoras:
/** @brief <b>Lee un área de espera</b>
\pre <em>Existe</em> 
\post Lee un área de espera con su número de prioridades y prioridades respectivas, inicializando los valores del número de procesos aceptados y el número de procesos rechazados a 0
*/
void read_process_area();


    //Escritoras:
/** @brief <b>Imprime los procesos pendientes del área de espera</b>
Pre: <em>Existe</em> 
\post Escribe los procesos pendientes de todas la prioridades del área de espera por orden creciente de prioridad. 
Para cada prioridad se escribe lo mismo que en la funcionalidad anterior
*/
void imprimir_area_espera();

/** @brief <b>Imprime los procesos pendientes de dicha prioridad</b>
\pre <em>Dado un id de prioridad</em>  
@param id_priority String, identificador de prioridad que tiene el propio proceso
\post Lee un identificador de prioridad. 
Si no hay error: se escriben los procesos pendientes de dicha prioridad por orden decreciente de antigüedad, desde su última alta. 
Además, escribe el número de procesos de la prioridad colocados en el clúster por la operación enviar_procesos_a_cluster y el número de procesos rechazos npr
*/
void imprimir_prioridad(string& id_priority);

/** @brief <b>Imprime los procesos de la lista</b>
\pre <em>Existe</em> 
@param it Iterador del mapa de string prioridad, apunta al id de prioridad que queremos tratar
@param itlista Iterador de la lista, imprimirá todos los procesos de la lista
\post Escribe todos los procesos de la lista, finalizando el método escribiendo el número de procesos aceptados y el número de procesos rechazados
*/
void imprimir_procesos_lista(map<string, priority>::iterator& it, list<Proceso>::iterator& itlista);


    //Modificadoras:
/** @brief <b>Añade una prioridad al área de espera</b>
\pre <em>Dado un id de prioridad</em> 
@param id_priority String, identificador de prioridad que tiene el propio proceso
\post Si ya existe en el área de espera una prioridad con el mismo identificador, se imprime un mensaje de error. En
caso contrario se añade esta prioridad al área de espera, sin procesos pendientes.
*/
void alta_prioridad(string& id_priority);

/** @brief <b>Añade una prioridad al área de espera</b>
\pre <em>Dado un id de prioridad</em> 
@param id_priority String, identificador de prioridad que tiene el propio proceso
\post Añade una prioridad con 'id_priority' al área de espera, sin procesos pendientes y inicializando los valores del número de procesos aceptados y el número de procesos rechazados a 0
*/
void anadir_prioridad_a_area_espera(string& id_priority);

/** @brief <b>Elimina una prioridad al área de espera</b>
\pre <em>Dado un id de prioridad</em> 
@param id_priority String, identificador de prioridad que tiene el propio proceso
\post Si ya existe en el área de espera una prioridad con el mismo identificador, se imprime un mensaje de error. En
caso contrario se elimina esta prioridad al área de espera, sin procesos pendientes.
*/
void baja_prioridad(string& id_priority);

/** @brief <b>Pasa un proceso al área de espera con la prioridad dada</b>
\pre <em>Dado un id de prioridad, un id del proceso</em> 
@param p Proceso, el propio proceso que queremos tratar en el parámetro implícito (Área de procesos)
@param id_priority String, identificador de prioridad que tiene el propio proceso
\post Lee los datos de un proceso y un identificador de prioridad. 
Si no hay error: el proceso pasa a al área de espera con dicha prioridad
*/
void alta_proceso_espera(const Proceso& P, const string& id_priority);

/** @brief <b>Envia procesos al cluster ordenados por orden de prioridad</b>
\pre <em>Dado un número de procesos pendientes npc y un cluster c</em> 
@param n Entero, número de procesos que queremos enviar al cluster
@param c Cluster, donde queremos enviar los procesos
\post Lee un entero no negativo n y se intentan enviar al clúster n procesos pendientes. Los procesos se intentan colocar 
en el clúster por orden de prioridad. Dentro de una misma prioridad, se intentan colocar primero los procesos más antiguos. Los
intentos continúan hasta haber colocado n procesos en el clúster o hasta que no queden procesos pendientes o hasta que 
todos los que queden pendientes se hayan intentado colocar sin éxito.
*/ 
void enviar_procesos_cluster(int unsigned& n, Cluster& c);


};
#endif
