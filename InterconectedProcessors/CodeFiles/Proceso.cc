#include "Proceso.hh"

    //Constructoras:
Proceso::Proceso() 
{ 
    size = 0;
    tiempo = 0;
    id_proceso = 0;
}

Proceso::Proceso(const int& id, const int& memoria_ocupa_proceso, const int& t) 
{ 
    size = memoria_ocupa_proceso;
    tiempo = t;
    id_proceso = id;
}


//Consultoras:
int Proceso::consultar_id() const 
{ 
    return id_proceso;
}

int Proceso::consultar_memoria() const 
{ 
    return size;
}

int Proceso::consultar_tiempo() const 
{ 
    return tiempo;
}   


    //Lectoras:
void Proceso::read_proceso() 
{
    cin >> id_proceso >> size >> tiempo;
}


//Escritoras:
void Proceso::imprimir_proceso() 
{ 
    cout << id_proceso << ' ' << size << ' ' << tiempo << endl;
}


//Modificadoras:
void Proceso::modificar_tiempo(const int& t) 
{ 
    tiempo -= t;
}
