/** @mainpage Simulacion del funcionamiento de una arquitectura multiprocesador, donde cada procesador trabaja exclusivamente con su propia memoria y puede ejecutar más de un proceso simultáneamente.
* El programa principal comenzará inicializando un primer clúster sin procesos. A continuación inicializará un área de espera vacía, leyendo para ello un número inicial de prioridades N > 0 y los identificadores de N prioridades. 
* Terminadas las inicializaciones, se procesará una serie de comandos, incluido el comando fin que terminará la ejecución.
*/
#include "Cluster.hh"
#include "Process_Area.hh"
#ifndef NO_DIAGRAM
#include <iostream>
#include <string>
#endif
using namespace std;

/** @author Oriol Farrés i Vilar
*   @date Mayo del 2023
*   @brief El código principal de la práctica (main)</b>*/

int main() {
    Cluster c;
    Process_Area pa;
    string order;
    c.configurar_cluster();
    pa.read_process_area();
    cin >> order;
    while (order != "fin") {
        if (order == "cc" or order == "configurar_cluster") //Comando 1
        {
	        c.configurar_cluster(); 
            cout << "#" << order << endl;
        }
        else if (order == "mc" or order == "modificar_cluster") //Comando 2
        {

            Cluster c2;          
            string id_procesador;
            cin >> id_procesador;
            c2.configurar_cluster();
            cout << '#' << order << ' ' << id_procesador << endl;
	        c.modificar_cluster(c2, id_procesador); 
        }
        else if (order == "ap" or order == "alta_prioridad") //Comando 3
        {
            string id_priority;
            cin >> id_priority;
            cout << "#" << order << " " << id_priority << endl;
	        pa.alta_prioridad(id_priority);
        }
        else if (order == "bp" or order == "baja_prioridad") //Comando 4
        {
            string id_priority;
            cin >> id_priority;
            cout << "#" << order <<" " << id_priority << endl;
            pa.baja_prioridad(id_priority);
        }
        else if (order == "ape" or order == "alta_proceso_espera") //Comando 5        
        {
            string id_priority;
            cin >> id_priority;
            Proceso p;
            p.read_proceso();
            cout << "#" << order << ' ' << id_priority << ' ' << p.consultar_id() << endl;
	        pa.alta_proceso_espera(p, id_priority);

        }
        else if (order == "app" or order == "alta_proceso_procesador") //Comando 6
        {
            string id_procesador;
            cin >> id_procesador;
            Proceso p;
            p.read_proceso();
            cout << '#' << order << ' ' << id_procesador << ' ' << p.consultar_id() << endl;
            c.alta_proceso_procesador(id_procesador, p);
        }
        else if (order == "bpp" or order == "baja_proceso_procesador") //Comando 7        
        {
            string id_procesador;
            cin >> id_procesador;
            int id_proceso;
            cin >> id_proceso;
            cout << '#' << order << ' ' << id_procesador << ' ' << id_proceso << endl;
	        c.baja_proceso_procesador(id_procesador, id_proceso);
        }
        else if (order == "epc" or order == "enviar_procesos_cluster") //Comando 8       
        {
            unsigned int n; //n = numero de procesos n >= 0
            cin >> n;
            cout << '#' << order << ' ' << n << endl;
	        pa.enviar_procesos_cluster(n, c);

        }
        else if (order == "at" or order == "avanzar_tiempo") //Comando 9       
        {
            int t;
            cin >> t;
            cout << "#" << order << ' ' << t << endl;
            c.avanzar_tiempo(t);
        }
        else if (order == "ipri" or order == "imprimir_prioridad") //Comando 10        
        {
            string id_priority;
            cin >> id_priority;
            cout << '#' << order << ' ' << id_priority << endl;
            pa.imprimir_prioridad(id_priority);
        }
        else if (order == "iae" or order == "imprimir_area_espera") //Comando 11        
        {
            cout << '#' << order << endl;
            pa.imprimir_area_espera();
        }
        else if (order == "ipro" or order == "imprimir_procesador") //Comando 12       
        {
            string id_procesador;
            cin >> id_procesador;
            cout << "#" << order << " " << id_procesador << endl;
            c.imprimir_procesador(id_procesador);

        }
        else if (order == "ipc" or order == "imprimir_procesadores_cluster") //Comando 13         
        {
            cout << '#' << order << endl;
            c.imprimir_procesadores_cluster();
        }
        else if (order == "iec" or order == "imprimir_estructura_cluster") //Comando 14
        {
            cout << '#' << order << endl;
            c.imprimir_estructura_cluster();
        }
        else if (order == "cmp" or order == "compactar_memoria_procesador") //Comando 15
        {
            string id_procesador;
            cin >> id_procesador;
            cout << '#' << order << ' ' << id_procesador << endl;
            c.compactar_memoria_procesador(id_procesador);
        }
        else if (order == "cmc" or order == "compactar_memoria_cluster") //Comando 16
        {
            cout << '#' << order << endl;
            c.compactar_memoria_cluster();
        }
        cin >> order;
    }
}
