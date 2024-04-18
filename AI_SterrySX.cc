#include "Player.hh"


/**
 * Write the name of your player and save this file
 * with the same name and .cc extension.
 */
#define PLAYER_NAME SterrySX


// DISCLAIMER: The following Demo player is *not* meant to do anything
// sensible. It is provided just to illustrate how to use the API.
// Please use AINull.cc as a template for your player.


struct PLAYER_NAME : public Player {

/**
 * Factory: returns a new instance of this class.
 * Do not modify this function.
 */
    static Player* factory () {
        return new PLAYER_NAME;
    }
// .....................................................................
typedef vector<int> VI;
typedef vector<vector<bool>> boolean_matrix;
typedef vector<vector<Pos>> PrePos;

//FALTA MILLORAR ESCAPAR-SE

bool is_okay(boolean_matrix& m, Pos p) {
    return (pos_ok(p) and cell(p).type == Cave and m[p.i][p.j] != 1);
}

int distance_between_2positions(const Pos p, Pos t) { //PERFECTE
    if (p.k != t.k) return 999;
    float dist = sqrt((p.i-t.i)*(p.i-t.i)+(p.j-t.j)*(p.j-t.j)); //pitagoras
    int distaux = int(sqrt((p.i-t.i)*(p.i-t.i)+(p.j-t.j)*(p.j-t.j)));
    if (dist < 10) {
        float decimal = dist/10;
        if (decimal > 0.00000000000000000001) ++distaux;
    }
    return distaux;
}

bool is_escapable(const Pos& p) {
    return (pos_ok(p) and cell(p).type == Cave and cell(p).id == -1);
}

//This method makes p escape from the enemy of position t
//HOW? using the pre pos matrix it goes back the positions
Dir direction_to_escape(const Pos& p, const Pos& t, const PrePos& m) { //REVISAR CORRECTESA
    Pos aux=t;

    while (m[aux.i][aux.j] != p) { // vull anar enrere
        aux=m[aux.i][aux.j];
    }
    //aux es posicio cap a on vindra l'enemic si vol atacar

    //cerr << "posicio furyan: " << p << " i posicio Hellhound: " << t << " i aux: " << aux << endl;

    if (p+BR == aux) {
        if (is_escapable(p+Top)) return Top;
        else if (is_escapable(p+TL)) return TL;
        else if (is_escapable(p+Left)) return Left;
    }
    else if (p+Bottom == aux) {
        if (is_escapable(p+Top)) return Top;
        else if (is_escapable(p+TL)) return TL;
        else if (is_escapable(p+RT)) return RT;       
    }
    else if (p+LB == aux) {
        if (is_escapable(p+Top)) return Top;
        else if (is_escapable(p+Right)) return Right;
        else if (is_escapable(p+RT)) return RT;      
    }
    else if (p+Left == aux) {
        if (is_escapable(p+BR)) return BR;
        else if (is_escapable(p+Right)) return Right;
        else if (is_escapable(p+RT)) return RT;       
    }
    else if (p+TL == aux) {
        if (is_escapable(p+Bottom)) return Bottom;
        else if (is_escapable(p+BR)) return BR;
        else if (is_escapable(p+Right)) return Right;  
    }
    else if (p+Top == aux) {
        if (is_escapable(p+LB)) return LB;
        else if (is_escapable(p+Bottom)) return Bottom;
        else if (is_escapable(p+BR)) return BR;
    }
    else if (p+RT == aux) {
        if (is_escapable(p+TL)) return TL;
        else if (is_escapable(p+Left)) return Left;
        else if (is_escapable(p+LB)) return LB;
    }  
    else if (p+Right == aux) {
        if (is_escapable(p+TL)) return TL;
        else if (is_escapable(p+Left)) return Left;
        else if (is_escapable(p+LB)) return LB;  
    }  
    
    return None;
}

//retorna la direccio a la que ha d'anar per escapar-se i HPos és la posicio del HellHound més proper
Dir BFS_nearest_HellHound(const Pos& FPos, Pos& HPos) {
    boolean_matrix m(rows(), vector<bool>(cols(), false)); //matriu de booleans, false si no ha passat, true si ha passat
    PrePos PosM(rows(), vector<Pos> (cols(),Pos(-1,-1,-1))); //matriu on guardes la posicio del que vens

    queue<Pos> q;
    q.push(FPos);

    //mark cell as visited
    m[FPos.i][FPos.j] = true;

    while (not q.empty()) {
        Pos p = q.front();
        q.pop();

        //0 because hellhounds are always underground.
        if (cell(p).id != -1 and unit(cell(p).id).player and unit(cell(p).id).type == Hellhound) {  //miro si en aquella posicio hi ha una unitat hellhound si id == -1, no hi ha cap unit
            HPos = p;
            return direction_to_escape(FPos, HPos, PosM); //direccio a la que escapar
        }

        for (int i = 0; i < 8; ++i) { //ha de mirar Bottom, BR, Right, RT, Top, TL, Left, LB,
            Pos paux = p+Dir(i);
            if (is_okay(m, paux)) {
                //mark cell as visited
                m[paux.i][paux.j] = true;
                q.push(paux);
                PosM[paux.i][paux.j] = p;
            }
        }
    }
    return None;
}

//returns true if the distance of the nearest HellHound is <= 3 and returns false if it's farther away
//FPos stands for the Furyans Position
//HHPos stands for HH position
bool HellHound_is_following(const Pos& FPos, Pos& HPos, Dir& d) { //NO VA
    //I will assume a HellHound is following if it's a distance of 3
    d = BFS_nearest_HellHound(FPos, HPos);
    int distance = distance_between_2positions(FPos, HPos);
    //cerr << "The distance between Furyan and Hellhound is: " << distance << endl;
    if (distance <= 3) return true;
    else return false;
}

void Furyan_escape_HellHound(const Pos& FPos, const Dir& d, const int id, const Pos& HPos) {
    //cerr << "The furyan of pos: " << FPos << " is escaping the HellHound of Pos: " << HPos <<  " and it's escaping in the direction number " << d << endl;
    command(id, d);
}

bool is_attackable(const Pos& p, const Pos& aux) { //PERFECT
    return (pos_ok(p) and cell(p).type == Cave and p == aux);
}

//This method calculates the best direction to move to make p attack t faster.
//HOW? using the pre pos matrix it goes back the positions
Dir furyan_direction_to_attack(const Pos& p, const Pos& t, const PrePos& m) { //PERFECT
    Pos aux=t;

    while (m[aux.i][aux.j] != p) { // vull anar enrere
        aux=m[aux.i][aux.j];
    }
    //cerr << "Posicio del furyan atacant: " << p << " Posicio del furyan/pioneer atacat: " << t << " posicio d'aux: " << aux << endl;

    if (is_attackable(p+Top, aux)) return Top;
    else if (is_attackable(p+RT, aux)) return RT;
    else if (is_attackable(p+Right, aux)) return Right;
    else if (is_attackable(p+BR, aux)) return BR;
    else if (is_attackable(p+Bottom, aux)) return Bottom;
    else if (is_attackable(p+LB, aux)) return LB;
    else if (is_attackable(p+Left, aux)) return Left;
    else if (is_attackable(p+TL, aux)) return TL;

    //cerr << "WARNING! The furyan of position: " << p << " is not moving to attack the enemy pioneer/furyan of position: " << t << endl;
    return None;
}

Dir BFS_nearest_pioneer_or_furyan(const Pos& FPos, Pos& p) { //PERFECT
    boolean_matrix m(rows(), vector<bool>(cols(), false)); //matriu de booleans, false si no ha passat, true si ha passat
    PrePos PosM(rows(), vector<Pos> (cols(),Pos(-1,-1,-1))); //matriu on guardes la posicio del que vens

    queue<Pos> q;
    q.push(FPos);

    //mark cell as visited
    m[FPos.i][FPos.j] = true;

    while (not q.empty()) {
        p = q.front();
        q.pop();

        //0 because hellhounds are always underground.
        if (cell(p).id != -1 and unit(cell(p).id).player != me() and (unit(cell(p).id).type == Pioneer or unit(cell(p).id).type == Furyan)) {  //miro si en aquella posicio hi ha una unitat hellhound
            //where FPos is our Furyan position and p the enemy position
            return furyan_direction_to_attack(FPos, p, PosM); //direccio a la que ha d'atacar
        }

        for (int i = 0; i < 8; ++i) { //ha de mirar Bottom, BR, Right, RT, Top, TL, Left, LB,
            Pos paux = p+Dir(i);
            if (is_okay(m, paux)) {
                m[paux.i][paux.j] = true;
                q.push(paux);
                PosM[paux.i][paux.j] = p;
            }
        }
    }
    return None;
}


void Furyan_attack(const Pos& FPos, const int id, Pos& EnemyPos) { //PERFECT
    Dir d = BFS_nearest_pioneer_or_furyan(FPos, EnemyPos);
    //cerr << "The furyan of pos: " << FPos << " wants to attack the enemy pioneer/furyan of pos: " << EnemyPos << " and it's going in direction number: " << d << endl;
    command(id, d);
}


//Dictates what every furyan must do every round: wether attack or escape
void move_furyans() { //PERFECT
    VI F = furyans(me()); //P is a vector of all the furyans id
    for (int id : F) { //id is each furyan ID
        Pos FPos = unit(id).pos; //FPos stands for Furyan position
        Pos HPos; //HPos stands for HellHound position
        Pos EnemyPos; //EnemyPos stands for enemy position
        Dir dir_escape;
        if (HellHound_is_following(FPos, HPos, dir_escape)) Furyan_escape_HellHound(FPos, dir_escape, id, HPos);
        else Furyan_attack(FPos, id, EnemyPos);
    }
}

//.........................................................................................................................................................

Dir BFS_nearest_Furyan(const Pos& PPos, Pos& FPos) {
    boolean_matrix m(rows(), vector<bool>(cols(), false)); //matriu de booleans, false si no ha passat, true si ha passat
    PrePos PosM(rows(), vector<Pos> (cols(),Pos(-1,-1,-1))); //matriu on guardes la posicio del que vens

    queue<Pos> q;
    q.push(PPos);

    //mark cell as visited
    m[PPos.i][PPos.j] = true;

    while (not q.empty()) {
        Pos p = q.front();
        q.pop();

        //0 because hellhounds are always underground.

        if (cell(p).id != -1 and unit(cell(p).id).player != me() and unit(cell(p).id).type == Furyan) {  //miro si en aquella posicio hi ha una unitat hellhound
            //where p is the enenmy pos
            FPos = p;
            return direction_to_escape(PPos, FPos, PosM); //direccio a la que ha d'escapar
        }

        for (int i = 0; i < 8; ++i) { //ha de mirar Bottom, BR, Right, RT, Top, TL, Left, LB,
            Pos paux = p+Dir(i);
            if (is_okay(m, paux)) {
                m[paux.i][paux.j] = true;
                q.push(paux);
                PosM[paux.i][paux.j] = p;
            }
        }
    }
    return None;
}

bool furyan_is_following(const Pos& PPos, Pos& FPos, Dir& d) {
    //I will assume a Furyan is following if it's a distance of 3
    d = BFS_nearest_Furyan(PPos, FPos);
    int distance = distance_between_2positions(PPos, FPos);
    if (distance <= 3) return true;
    else return false;
}

bool p2_is_nearer_to_aux_than_p1(const Pos& p1, const Pos& p2, const Pos& aux) {
    float dist1 = sqrt((p1.i)*(aux.i) + (p1.j)*(aux.j));
    float dist2 = sqrt((p2.i)*(aux.i) + (p2.j)*(aux.j));
    return dist2 < dist1;
}

Dir direction_to_conquer(const Pos& p, const Pos& t, const PrePos& m) {  
    Pos aux=t;

    while (m[aux.i][aux.j] != p) { // vull anar enrere
        aux=m[aux.i][aux.j];
    }

    //aux es posicio cap a on ha d'anar per conquerir
    if (p+Left == aux and cell(p+Left).type != Rock) return Left;
    else if (p+Right == aux and cell(p+Right).type != Rock) return Right; 
    else if (p+Top == aux and cell(p+Top).type != Rock) return Top;
    else if (p+Bottom == aux and cell(p+Bottom).type != Rock) return Bottom;
    else if (p+TL == aux and cell(p+TL).type != Rock) return TL;
    else if (p+BR == aux and cell(p+BR).type != Rock) return BR;
    else if (p+RT == aux and cell(p+RT).type != Rock) return RT;
    else if (p+LB == aux and cell(p+LB).type != Rock) return LB;

    else if (p2_is_nearer_to_aux_than_p1(p, p+Left, aux)) return Left;
    else if (p2_is_nearer_to_aux_than_p1(p, p+Right, aux)) return Right; 
    else if (p2_is_nearer_to_aux_than_p1(p, p+Top, aux)) return Top;
    else if (p2_is_nearer_to_aux_than_p1(p, p+Bottom, aux)) return Bottom;
    else if (p2_is_nearer_to_aux_than_p1(p, p+TL, aux)) return TL;
    else if (p2_is_nearer_to_aux_than_p1(p, p+BR, aux)) return BR;
    else if (p2_is_nearer_to_aux_than_p1(p, p+RT, aux)) return RT;
    else if (p2_is_nearer_to_aux_than_p1(p, p+LB, aux)) return LB;
    return None;
}

/*Miro si (en aquest ordre): //ya he mirat que la cela sigui correcta
    -La cela no té cap ficha 
    -La cella no esta conquerida per mi
*/
bool is_conquerable(const Pos& p, const int id) {
    return (cell(p).id == -1 and cell(p).owner != me());
}

Dir BFS_nearest_cell_not_conquered_by_me(const Pos& PPos, const int id) {
    boolean_matrix m(rows(), vector<bool>(cols(), false)); //matriu de booleans, false si no ha passat, true si ha passat
    PrePos PosM(rows(), vector<Pos> (cols(),Pos(-1,-1,-1))); //matriu on guardes la posicio del que vens

    queue<Pos> q;
    q.push(PPos);

    //mark cell as visited
    m[PPos.i][PPos.j] = true;


    while (not q.empty()) {
        Pos p = q.front();
        q.pop();
        
        if (is_conquerable(p, id)) {  
            //where p is the enenmy pos
            return direction_to_conquer(PPos, p, PosM); //direccio a la que ha d'anar per conquerir
        }

        for (int i = 0; i < 8; ++i) { //ha de mirar Bottom, BR, Right, RT, Top, TL, Left, LB,
            Pos paux = p+Dir(i);
            if (is_okay(m, paux)) {
                m[paux.i][paux.j] = true;
                q.push(paux);
                PosM[paux.i][paux.j] = p;
            }
        }
    }
    return None;
}

void pioneer_conquer(const Pos& p, const int id) { //p stands for pioneer's position
    Dir d = None;
    d = BFS_nearest_cell_not_conquered_by_me(p, id);
    command(id, d);
}

//FLTA MIRAR AIXO FERHO COM PIONEER CONQUER
void pioneer_escape(const Dir& d, const int id, const Pos& PPos) {
    if (d != None) {
        int aux1 = d+1;
        if (aux1 > 8) aux1 = 0;
        int aux2 = d-1;
        if(aux2 < 0) aux2 = 8;
        if (is_conquerable(PPos+Dir(d), id)) command(id, d);
        else if (is_conquerable(PPos+Dir(aux1), id)) command(id, d);
        else if (is_conquerable(PPos+Dir(aux2), id)) command(id, d); 
    }
}

void go_conquer(const Pos& PPos, const int id) {
    Pos FPos; 
    Dir d;
    if (furyan_is_following(PPos, FPos, d)) pioneer_escape(d, id, PPos);
    else pioneer_conquer(PPos, id);
}

void move_pioneers() {
   VI P = pioneers(me());
   for (int id : P) {
       Pos PPos = unit(id).pos; //PPos stands for Furyan position
       Pos HPos; //HPos stands for HellHound position
       Dir dir_escape;
       if (HellHound_is_following(PPos, HPos, dir_escape)) pioneer_escape(dir_escape, id, PPos);
       else go_conquer(PPos, id);
   }
} 

void play () {
    move_furyans();
    move_pioneers();
}
};
/**
 * Do not modify the following line.
 */
RegisterPlayer(PLAYER_NAME);
