//Proyecto programacion avanzada
//David Rodriguez, Samuel Osorio, Samuel Campos, Natalia Jimenez

#include <iostream>
#include <fstream>
#include <cstring>
#include <locale.h>
#include <stdlib.h>

using namespace std;

struct Pokemon{
  char name[20]=" ";
  short level;
  short attack;
  short live;
  short speed;
  Pokemon* previous=NULL;
  Pokemon* next=NULL;
  bool mainPlayer;
  int game;
};

struct Player{
    char name[20]=" ";
    bool mainPlayer;
    int game;
    Pokemon* team= NULL;
};

//Declaracion de funciones

int menu1();
int menu2();
int menu3();
int game();
Player crearJugador(bool, string);
Pokemon* leerPokemones(bool, int, string);
void mostrarPokemones(Pokemon*, bool);
void reordenarPokemones(Pokemon*);
void jugarTurno(Pokemon*, Pokemon*);
void eliminarPokemones(Player &);
Pokemon* copiaTeam(Player &);
Pokemon* cambiarPokemon(Player &);
void guardarPartida(Player &, Player &);
int mostrarPartidas();
Pokemon* cargarPokemones(int, bool);
void cargarPartida(Player &, Player &, int);

int main(){
  setlocale(LC_ALL, "spanish");

    Player usuario;
    Player enemigo;

    int salirMenu2=0, salirMenu3=0, partida;

    switch(menu1())
    {
    case 1:
        usuario= crearJugador(1, "main.txt");
        enemigo= crearJugador(0, "enemy.txt");

        while(salirMenu2!=1)
        {
            salirMenu3=0;

            switch(menu2())
            {
            case 1:
                //mostrar lo pokemones de un jugador

                system("cls");
                cout<<"Jugador: "<<usuario.name<<endl<<endl;
                mostrarPokemones(usuario.team,1);
                cout<<endl;
                system("pause");
                break;

            case 2:
                //Reordenar los pokemones

                system("cls");
                cout<<"Jugador: "<<usuario.name<<endl<<endl;
                reordenarPokemones(usuario.team);
                cout<<endl;
                system("pause");
                break;

            case 3:
                while(salirMenu3!=1)
                {
                    system("cls");

                    //Aviso del resultado de la partida

                    if((usuario.team==NULL)&&(enemigo.team!=NULL))
                    {
                        cout<<"PERDISTE, TE HAS QUEDADO SIN POKEMONES"<<endl<<endl;
                        cout<<usuario.name<<" FUE DERROTADO POR "<<enemigo.name<<endl;
                        cout<<"Recuerda guardar tu partida"<<endl;
                        cout<<endl;
                        system("pause");
                        break;
                    }

                    if((enemigo.team==NULL)&&(usuario.team!=NULL ))
                    {
                        cout<<"¡GANASTE, EL OPONENTE SE HA QUEDADO SIN POKEMONES!"<<endl<<endl;
                        cout<<"¡"<<usuario.name<<" HA DERROTADO A "<<enemigo.name<<" !"<<endl;
                        cout<<"Recuerda guardar tu partida"<<endl;
                        cout<<endl;
                        system("pause");
                        break;
                    }

                    if((enemigo.team==NULL)&&(usuario.team==NULL))
                    {
                        cout<<"¡LOS DOS JUGADORES SE HAN QUEDADO SIN POKEMONES!"<<endl<<endl;
                        cout<<"¡HUBO UN EMPATE!"<<endl;
                        cout<<"Recuerda guardar tu partida"<<endl;
                        cout<<endl;
                        system("pause");
                        break;
                    }

                    switch(menu3())
                    {
                    case 1:
                        system("cls");

                        jugarTurno(usuario.team, enemigo.team);

                        if(usuario.team->live<=0)
                            cout<<endl<<usuario.team->name<<" fue derrotado"<<endl<<endl;

                        if(enemigo.team->live<=0)
                            cout<<endl<<enemigo.team->name<<" fue derrotado"<<endl<<endl;

                        usuario.team= copiaTeam(usuario);
                        enemigo.team= copiaTeam(enemigo);

                        cout<<endl;
                        system("pause");
                        break;

                    case 2:

                        system("cls");
                        int opcion;

                        cout<<"Tu pokemon principal es: "<<endl<<endl;
                        mostrarPokemones(usuario.team, 0);

                        cout<<"¿Deseas cambiarlo?"<<endl<<endl;
                        cout<<"1. Si"<<endl;
                        cout<<"2. No"<<endl;

                        cout<<endl<<"Digite su opcion: ";
                        cin>>opcion;

                        if(opcion==1)
                        {
                            system("cls");
                            usuario.team= cambiarPokemon(usuario);
                        }

                        else if((opcion!=2)&&(opcion!=1))
                            cout<<"Digita una opcion valida por favor"<<endl;


                        cout<<endl;
                        system("pause");
                        break;

                    case 3:
                        salirMenu3=1;
                        break;

                    default:
                        cout<<"Digita una opcion valida por favor"<<endl;
                        cout<<endl;
                        system("pause");
                        break;
                    }
                }
                break;

            case 4:
                guardarPartida(usuario, enemigo);
                salirMenu2=1;
                break;

            default:
                cout<<"Digita una opcion valida por favor"<<endl;
                cout<<endl;
                system("pause");

                break;

            }
        }

        break;


    case 2:
        system("cls");

        cout<<"Cual de las siguientes partidas quieres cargar"<<endl<<endl;
        partida= mostrarPartidas();

        cargarPartida(usuario, enemigo, partida);

        cout<<endl;

        system("pause");
        system("cls");
        cout<< "Bienvenido, "<< usuario.name<< ",preparate para luchar";

        while(salirMenu2!=1)
        {
            salirMenu3=0;

            switch(menu2())
            {
            case 1:
                system("cls");
                cout<<"Jugador: "<<usuario.name<<endl<<endl;
                mostrarPokemones(usuario.team,1);
                cout<<endl;
                system("pause");
                break;

            case 2:
                system("cls");
                cout<<"Jugador: "<<usuario.name<<endl<<endl;
                reordenarPokemones(usuario.team);
                cout<<endl;
                system("pause");
                break;

            case 3:
                while(salirMenu3 != 1){
                    system("cls");

                    if((usuario.team==NULL)&&(enemigo.team!=NULL))
                    {
                        cout<<"PERDISTE, TE HAS QUEDADO SIN POKEMONES"<<endl<<endl;
                        cout<<usuario.name<<" FUE DERROTADO POR "<<enemigo.name<<endl;
                        cout<<"Recuerda guardar tu partida"<<endl;
                        cout<<endl;
                        system("pause");
                        break;
                    }

                    if((enemigo.team==NULL)&&(usuario.team!=NULL ))
                    {
                        cout<<"¡GANASTE, EL OPONENTE SE HA QUEDADO SIN POKEMONES!"<<endl<<endl;
                        cout<<"¡"<<usuario.name<<" HA DERROTADO A "<<enemigo.name<<" !"<<endl;
                        cout<<"Recuerda guardar tu partida"<<endl;
                        cout<<endl;
                        system("pause");
                        break;
                    }

                    if((enemigo.team==NULL)&&(usuario.team==NULL))
                    {
                        cout<<"¡LOS DOS JUGADORES SE HAN QUEDADO SIN POKEMONES!"<<endl<<endl;
                        cout<<"¡HUBO UN EMPATE!"<<endl;
                        cout<<"Recuerda guardar tu partida"<<endl;
                        cout<<endl;
                        system("pause");
                        break;
                    }

                    switch(menu3())
                    {
                    case 1:
                        system("cls");

                        jugarTurno(usuario.team, enemigo.team);

                        if(usuario.team->live<=0)
                            cout<<endl<<usuario.team->name<<" fue derrotado"<<endl<<endl;

                        if(enemigo.team->live<=0)
                            cout<<endl<<enemigo.team->name<<" fue derrotado"<<endl<<endl;

                        usuario.team= copiaTeam(usuario);
                        enemigo.team= copiaTeam(enemigo);

                        cout<<endl;
                        system("pause");
                        break;

                    case 2:

                        system("cls");
                        int opcion;

                        cout<<"Tu pokemon principal es: "<<endl<<endl;
                        mostrarPokemones(usuario.team, 0);

                        cout<<"¿Deseas cambiarlo?"<<endl<<endl;
                        cout<<"1. Si"<<endl;
                        cout<<"2. No"<<endl;

                        cout<<endl<<"Digite su opcion: ";
                        cin>>opcion;

                        if(opcion==1)
                        {
                            system("cls");
                            usuario.team= cambiarPokemon(usuario);
                        }

                        else if((opcion!=2)&&(opcion!=1))
                            cout<<"Digita una opcion valida por favor"<<endl;


                        cout<<endl;
                        system("pause");
                        break;

                    case 3:
                        salirMenu3=1;
                        break;

                    default:
                        cout<<"Digita una opcion valida por favor"<<endl;
                        cout<<endl;
                        system("pause");
                        break;
                    }
                }
                break;

            case 4:
                guardarPartida(usuario, enemigo);
                salirMenu2=1;
                break;

            default:
                cout<<"Digita una opcion valida por favor"<<endl;
                cout<<endl;
                system("pause");

                break;

            }
        }

        break;


    default:
        cout<<"Digita una opcion valida por favor"<<endl;
        break;
    }

    eliminarPokemones(usuario);
    eliminarPokemones(enemigo);
}

int menu1()
{

    int i;

    cout<<"=========================================================="<<endl;
    cout<<endl<<"BIENVENIDO A POKEMON"<<endl;
    cout<<endl<<"INGRESA UNA DE LAS SIGUIENTES OPCIONES"<<endl;
    cout<<"1. Crear nueva partida"<<endl;
    cout<<"2. Cargar partida"<<endl;
    cout<<endl<<"=========================================================="<<endl;

    cout<<endl<<"Digita una opcion (1 o 2): ";
    cin>>i;

    return i;

}

int menu2()
{
    system("cls");
    int i;

    cout<<"====================================================================="<<endl;
    cout<<endl<<"MENU PRINCIPAL"<<endl;
    cout<<endl<<"INGRESA UNA DE LAS SIGUIENTES OPCIONES Y PREPARATE PARA LUCHAR"<<endl;
    cout<<"1. Mostrar pokemones"<<endl;
    cout<<"2. Reordenar pokemones"<<endl;
    cout<<"3. Luchar"<<endl;
    cout<<"4. Guardar y salir"<<endl;
    cout<<endl<<"====================================================================="<<endl;

    cout<<endl<<"Digita una opcion (1-4): ";
    cin>>i;

    return i;

    system("cls");

}

int menu3()
{
    system("cls");
    int i;

    cout<<"=========================================================="<<endl;
    cout<<endl<<"MENU DE LUCHA"<<endl;
    cout<<endl<<"INGRESA UNA DE LAS SIGUIENTES OPCIONES"<<endl;
    cout<<"1. Jugar turno"<<endl;
    cout<<"2. Cambiar pokemon"<<endl;
    cout<<"3. Volver al menu principal"<<endl;
    cout<<endl<<"=========================================================="<<endl;

    cout<<endl<<"Digita una opcion (1-3): ";
    cin>>i;

    return i;

}

int numeroPartida()
{
    Player player;
    int contador=0;

    int partida;

    ifstream archivo("partidas.bin", ios::binary);

    if (!archivo)
        partida= 1;

    else
    {
        while(!archivo.eof())
        {
            archivo.read((char*)&player,sizeof(Player));
            contador++;

            if(archivo.eof())
                break;

        }

    }

    contador= contador/2;

    archivo.close();

    return partida;
}

Player crearJugador(bool bandera, string nombreArchivo)
{
    Player jugador;

    if(bandera==1)
    {
        cout<<endl;
        cout<<"Digite su nickname (maximo 20 carcateres): ";
        cin.ignore();
        cin.getline(jugador.name,20);
    }

    else if(bandera==0)
    {
        strncpy(jugador.name, "Alain\0", 20);
    }

    jugador.mainPlayer= bandera;

    jugador.game= numeroPartida();

    jugador.team= leerPokemones(bandera, jugador.game, nombreArchivo);

    return jugador;

}

Pokemon* leerPokemones(bool bandera, int game, string nombreArchivo)
{
    char linea[150];
    char* token;
    Pokemon* first= NULL;
    Pokemon* last= NULL;

    ifstream archivo;

    archivo.open(nombreArchivo, ios::in);

    if(!archivo.is_open())
    {
        cout<<"No se encontro el archivo";
        exit(1);
    }

    while(!archivo.eof())
    {
        archivo.getline(linea, 150, '\n');

        Pokemon* nuevo= new Pokemon;

        token = strtok(linea, ":-");

        while(token != NULL)
        {
            if(strcmp(token, "nombre") == 0)
            {
                token = strtok(NULL, ":-");
                strcpy(nuevo->name, token);
                token = strtok(NULL, ":-");
            }
            else if(strcmp(token, "nivel") == 0)
            {
                token = strtok(NULL, ":-");
                short nivel = atoi(token);
                nuevo->level = nivel;
                token = strtok(NULL, ":-");
            }
            else if(strcmp(token, "ataque") == 0)
            {
                token = strtok(NULL, ":-");
                short ataque = atoi(token);
                nuevo->attack = ataque;
                token = strtok(NULL, ":-");
            }
            else if(strcmp(token, "vida") == 0)
            {
                token = strtok(NULL, ":-");
                short vida = atoi(token);
                nuevo->live = vida;
                token = strtok(NULL, ":-");
            }
            else if(strcmp(token, "velocidad") == 0)
            {
                token = strtok(NULL, ":-");
                short velocidad = atoi(token);
                nuevo->speed = velocidad;
                token = strtok(NULL, ":-");
            }
        }

        nuevo->mainPlayer=bandera;
        nuevo->game= game;

        if(first==NULL)
        {
            first= nuevo;
            first->previous= first;
            first->next= first;
            last= first->previous;
        }

        else
        {
            last->next= nuevo;
            first->previous= nuevo;
            nuevo->previous= last;
            nuevo->next= first;
            last= first->previous;
        }


    }


    return first;
}

void mostrarPokemones(Pokemon* jugador, bool bandera)
{
    Pokemon* aux= jugador;
    int i=1;

    if(jugador==NULL)
    {
        cout<<"NO HAY POKEMONES PARA MOSTRAR"<<endl;
    }

    else
    {
        if(bandera==1)
        {
            do
            {

                cout<< i<<".° Pokemon"<< endl;
                cout<< "Nombre: "<< aux->name<< endl;
                cout<< "Nivel: "<< aux->level<< endl;
                cout<< "Ataque: "<< aux->attack<< endl;
                cout<< "Vida: "<< aux->live<< endl;
                cout<< "Velocidad: "<< aux->speed<< endl;
                cout<< "main: "<< aux->mainPlayer<<endl;
                cout<< "game: "<< aux->game<<endl;
                cout<<endl<<"=========================================================="<<endl;
                cout<<endl;

                aux= aux->next;

                i++;

            }
            while(aux!=jugador);
        }

        else
        {
            cout<< "Nombre: "<< aux->name<< endl;
            cout<< "Nivel: "<< aux->level<< endl;
            cout<< "Ataque: "<< aux->attack<< endl;
            cout<< "Vida: "<< aux->live<< endl;
            cout<< "Velocidad: "<< aux->speed<< endl;
            cout<<endl<<"=========================================================="<<endl;
            cout<<endl;
        }

    }



}

void reordenarPokemones(Pokemon* jugador)
{
    int posicion1, posicion2;
    Pokemon* aux1= jugador;
    Pokemon* aux2= jugador;
    Pokemon* aux3= new Pokemon;

    if(jugador==NULL)
    {
        cout<<"NO TIENES POKEMONES PARA JUGAR"<<endl;
    }

    else
    {
        mostrarPokemones(jugador,1);

        cout<<"Digita las dos posiciones de los pokemones que quieres cambiar"<<endl;
        cout<<endl<<"Posicion 1: ";
        cin>>posicion1;
        cout<<"Posicion 2: ";
        cin>>posicion2;

        for(int i=0; i<posicion1-1; i++)
            aux1= aux1->next;

        for(int j=0; j<posicion2-1; j++)
            aux2= aux2->next;

        strcpy(aux3->name, aux1->name);
        aux3->level= aux1->level;
        aux3->attack= aux1->attack;
        aux3->live= aux1->live;
        aux3->speed= aux1->speed;

        strcpy(aux1->name, aux2->name);
        aux1->level= aux2->level;
        aux1->attack= aux2->attack;
        aux1->live= aux2->live;
        aux1->speed= aux2->speed;

        strcpy(aux2->name, aux3->name);
        aux2->level= aux3->level;
        aux2->attack= aux3->attack;
        aux2->live= aux3->live;
        aux2->speed= aux3->speed;
    }

    delete aux3;

}

void jugarTurno(Pokemon* usuario, Pokemon* enemigo)
{
    cout<<"TU POKEMON ES: "<<endl<<endl;
    mostrarPokemones(usuario,0);

    cout<<"El POKEMON DEL OPONENTE ES: "<<endl<<endl;
    mostrarPokemones(enemigo,0);

    cout<<"¡ES HORA DE LUCHAR!"<<endl<<endl;


    if(usuario->speed > enemigo->speed)
    {
        cout<<"¡TU POKEMON, "<<usuario->name<<", FUE EL MAS RAPIDO!"<<endl<<endl;

        cout<<"¡Tu pokemon, "<<usuario->name<<", ha atacado!"<<endl;
        cout<<"El pokemon del oponente, "<<enemigo->name<<", ha recibido "<<usuario->attack<<" de daño"<<endl;
        enemigo->live-= usuario->attack;

        if(enemigo->live>0)
        {
            cout<<endl;
            cout<<"¡El pokemon del oponente, "<<enemigo->name<<", ha atacado!"<<endl;
            cout<<"Tu pokemon, "<<usuario->name<<", ha recibido "<<enemigo->attack<<" de daño"<<endl;
            usuario->live-= enemigo->attack;
        }

    }


    else if(usuario->speed < enemigo->speed)
    {
        cout<<"¡EL POKEMON DEL OPONENTE, "<<enemigo->name<<", FUE EL MAS RAPIDO!"<<endl<<endl;

        cout<<"¡El pokemon del oponente, "<<enemigo->name<<", ha atacado!"<<endl;
        cout<<"Tu pokemon, "<<usuario->name<<", ha recibido "<<enemigo->attack<<" de daño"<<endl;
        usuario->live-= enemigo->attack;

        if(usuario->live>0)
        {
            cout<<endl;
            cout<<"¡Tu pokemon, "<<usuario->name<<", ha atacado!"<<endl;
            cout<<"El pokemon del oponente, "<<enemigo->name<<", ha recibido "<<usuario->attack<<" de daño"<<endl;
            enemigo->live-= usuario->attack;
        }

    }

    else if(usuario->speed == enemigo->speed)
    {
        cout<<"LOS DOS POKEMONES TIENEN LA MISMA VELOCIDAD"<<endl<<endl;

        cout<<"¡Tu pokemon, "<<usuario->name<<", ha atacado!"<<endl;
        cout<<"El pokemon del oponente, "<<enemigo->name<<", ha recibido "<<usuario->attack<<" de daño"<<endl;
        enemigo->live-= usuario->attack;

        cout<<endl;

        cout<<"¡El pokemon del oponente, "<<enemigo->name<<", ha atacado!"<<endl;
        cout<<"Tu pokemon, "<<usuario->name<<", ha recibido "<<enemigo->attack<<" de daño"<<endl;
        usuario->live-= enemigo->attack;

    }


}

void eliminarPokemones(Player &jugador)
{
    if(jugador.team!=NULL)
    {
        Pokemon* auxiliar1 = jugador.team;
        Pokemon* auxiliar2 = auxiliar1->next;

        do
        {

            delete auxiliar1;
            auxiliar1= auxiliar2;
            auxiliar2= auxiliar1->next;

        }
        while(auxiliar1!=jugador.team);

    }

}

Pokemon* copiaTeam(Player &jugador)
{
    Pokemon* first= NULL;
    Pokemon* last= NULL;
    Pokemon* auxiliar= jugador.team;

    do
    {
        if(auxiliar->live > 0)
        {
            Pokemon* copia= new Pokemon;

            strcpy(copia->name, auxiliar->name);
            copia->level= auxiliar->level;
            copia->attack= auxiliar->attack;
            copia->live= auxiliar->live;
            copia->speed= auxiliar->speed;
            copia->mainPlayer= auxiliar->mainPlayer;
            copia->game= auxiliar->game;

            if(first==NULL)
            {
                first= copia;
                first->previous= first;
                first->next= first;
                last= first->previous;
            }

            else
            {
                last->next= copia;
                first->previous= copia;
                copia->previous= last;
                copia->next= first;
                last= first->previous;
            }

        }

        auxiliar= auxiliar->next;

    }
    while(auxiliar!= jugador.team);

    eliminarPokemones(jugador);

    return first;

}

Pokemon* cambiarPokemon(Player &jugador)
{
    Pokemon* auxiliar= jugador.team;
    int opcion;

    if(auxiliar==NULL)
    {
        cout<<"NO TIENES POKEMONES PARA JUGAR"<<endl;
    }

    else
    {
        cout<<"¿Por cual de estos pokemones quieres cambiarlo?"<<endl<<endl;

        cout<<"1. Pokemon anterior al principal"<<endl<<endl;
        mostrarPokemones(auxiliar->previous,0);

        cout<<"2. Pokemon siguiente al principal"<<endl<<endl;
        mostrarPokemones(auxiliar->next,0);

        cout<<"Digita tu opcion (1 o 2): ";
        cin>>opcion;

        if(opcion==1)
            auxiliar= auxiliar->previous;

        if(opcion==2)
            auxiliar= auxiliar->next;

        if((opcion!=1)&&(opcion!=2))
            cout<<"Digita una opcion valida por favor"<<endl;
    }


    return auxiliar;

}

void guardarPartida(Player &usuario, Player &enemigo)
{
    ofstream archivoPartidas("partidas.bin", ios::app | ios::binary);

    if(!archivoPartidas.is_open())
    {
        cout<<"No se pudo abrir el archivo de jugadores";
        exit (1);
    }

    archivoPartidas.write((char*)&usuario, sizeof(Player));

    archivoPartidas.write((char*)&enemigo, sizeof(Player));

    archivoPartidas.close();

    ofstream archivoPokemon("pokemones.bin", ios::app | ios::binary);

    if(!archivoPokemon.is_open())
    {
        cout<<"No se pudo abrir el archivo de pokemones"<<endl;
        exit (1);
    }

    Pokemon* aux1= usuario.team;
    Pokemon* aux2= enemigo.team;

    if(aux1!=NULL)
    {
        do
        {

            archivoPokemon.write((char*)aux1, sizeof(Pokemon));

            aux1 = aux1->next;

        }
        while(aux1!=usuario.team);
    }


    if(aux2!=NULL)
    {
        do
        {

            archivoPokemon.write((char*)aux2, sizeof(Pokemon));

            aux2 = aux2->next;

        }
        while(aux2!=enemigo.team);
    }

    archivoPokemon.close();
}

int mostrarPartidas()
{
    Player player1;
    Player player2;

    int partida, i=0, j=0;

    fstream archivo("partidas.bin", ios::binary | ios::in);

    if (!archivo.is_open())
    {
        cout<<"No hay partidas guardadas"<<endl;
        exit(1);
    }

    else
    {
        while((!archivo.eof())&&(archivo.good()))
        {

            i++;

            archivo.seekg(j*sizeof(Player));

            archivo.read((char*)&player1, sizeof(Player));

            j++;

            archivo.seekg(j*sizeof(Player));

            archivo.read((char*)&player2, sizeof(Player));

            j++;

            archivo.seekg(j*sizeof(Player));

            if(i%2!=0)
            {
                cout<<i<<".° Partida "<<endl;
                cout<<player1.name<<" VS "<<player2.name<<endl;
                cout<<endl<<"=========================================================="<<endl;
                cout<<endl;
            }
            }


        cout<<"Digita el numero de la partida que quieres cargar: ";
        cin>>partida;
    }

    archivo.close();

    return partida;
}

Pokemon* cargarPokemones(int partida, bool bandera)
{
    Pokemon* first= NULL;
    Pokemon* last= NULL;

    ifstream archivoPokemon("pokemones.bin", ios::binary);

    if(!archivoPokemon)
    {
        cout<<"No hay pokemones guardados en el archivo"<<endl;
        exit(1);
    }

    while(!archivoPokemon.eof())
    {
        Pokemon* nuevo= new Pokemon;

//        archivoPokemon.read((char*)(&(nuevo->name)), sizeof(nuevo->name));
//        archivoPokemon.read((char*)(&(nuevo->level)), sizeof(nuevo->level));
//        archivoPokemon.read((char*)(&(nuevo->attack)), sizeof(nuevo->attack));
//        archivoPokemon.read((char*)(&(nuevo->live)), sizeof(nuevo->live));
//        archivoPokemon.read((char*)(&(nuevo->speed)), sizeof(nuevo->speed));
//        archivoPokemon.read((char*)(&(nuevo->mainPlayer)), sizeof(nuevo->mainPlayer));
//        archivoPokemon.read((char*)(&(nuevo->game)), sizeof(nuevo->game));

        archivoPokemon.read((char*)nuevo, sizeof(Pokemon));

        if((nuevo->game==partida)&&(nuevo->mainPlayer==bandera))
        {
            if(first==NULL)
            {
                first= nuevo;
                first->previous= first;
                first->next= first;
                last= first->previous;
            }

            else
            {
                last->next= nuevo;
                first->previous= nuevo;
                nuevo->previous= last;
                nuevo->next= first;
                last= first->previous;
            }

        }

        else
            delete nuevo;

    }

    archivoPokemon.close();

    return first;

}

void cargarPartida(Player &usuario, Player &enemigo, int partida)
{
    int posicion;

    posicion=partida-1;



    ifstream archivoPartidas("partidas.bin", ios::binary);

    archivoPartidas.seekg((posicion)*sizeof(Player));

    archivoPartidas.read((char*)&usuario, sizeof(Player));

    posicion++;

    archivoPartidas.seekg((posicion)*sizeof(Player));

    archivoPartidas.read((char*)&enemigo, sizeof(Player));

    if(usuario.team!=NULL)
    {
        usuario.team= cargarPokemones(usuario.game, usuario.mainPlayer);
    }

    if(enemigo.team!=NULL)
    {
        enemigo.team= cargarPokemones(enemigo.game, enemigo.mainPlayer);
    }

    archivoPartidas.close();

}
