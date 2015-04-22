#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <iostream>
#include <queue>
#include <string>
#include <fstream>
#include <time.h>
#include <unistd.h>

#include "a_star.h"
#include "heuristic.h"
#include "serialib.h"

#define DEVICE_PORT "/dev/ttyUSB0"      // FTDI

using namespace std;



//******************** VARIABLES GLOBALES ********************//

const int xTaille = 100;                //Nombre de noeuds (x)
const int yTaille = 100;                //Nombre de noeuds (y)

int map[xTaille][yTaille];              //Map pour afficher le chemin

int mapNodesClosed[xTaille][yTaille];   //Map des noeuds déjà visités
int mapNodesOpen[xTaille][yTaille];     //Map des noeuds à visiter
int mapDirections[xTaille][yTaille];    //Map des directions prises


//On a 8 directions possibles, selon x et y (noeuds voisins)
//           n n-e e  s-e  s  s-o  o  n-o
int dx[8] = {0, 1, 1,  1,  0, -1, -1, -1};
int dy[8] = {1, 1, 0, -1, -1, -1,  0,  1};

//*************************************************************//



//Classe nécessaire pour la queue, permet de classer les éléments par coutF
class CompareFcost
{
public:
    bool operator()(node &n1, node &n2)
    {
       if (n1.get_coutF() > n2.get_coutF()) return true;
       return false;
    }
};


//Le gros morceau de l'algorithme
string pathFinding(int xStart, int yStart, int xEnd, int yEnd)
{
    //Création d'une queue de noeuds avec priorité sur coutF
    priority_queue <node, vector<node>, CompareFcost> pq[2];

    static int pqi; //indice pour accéder à l'élément souhaité dans la queue

    node *n0;
    node *m0;
    node *f0;

    char c;

    static int x;
    static int y;

    static int xNext;
    static int yNext;

    int i = 0;
	int j = 0;

    //Reset des maps
	for(i=0; i <= xTaille-1; i++)
	{
		for(j=0; j <= yTaille-1; j++)
		{
			mapNodesClosed[i][j] = 0;
			mapNodesOpen[i][j] = 0;
		}
	}

    n0 = new node(xStart, yStart, 0, 0); //Définition de n0 comme noeud de départ
    f0 = new node(xEnd, yEnd, 0, 0);     //Définition de f0 comme noeud d'arrivée

    n0 -> calculate_heuristic(*f0); //Calcul de l'heuristique entre n0 et f0
    n0 -> modifyF();

    pq[pqi].push(*n0); //On place n0 dans notre queue

    // A* search
    while(!pq[pqi].empty())
    {
        // On chope le noeud prioritaire
        n0 = new node(pq[pqi].top().get_xPos(),
                      pq[pqi].top().get_yPos(),
                      pq[pqi].top().get_coutH(),
                      pq[pqi].top().get_coutG());

        x = n0 -> get_xPos();
        y = n0 -> get_yPos();

        pq[pqi].pop(); // On enlève le noeud de la queue

        //Noeud visité (0 dans open, 1 dans closed)
        mapNodesOpen[x][y] = 0;
        mapNodesClosed[x][y] = 1;


        // Test pour savoir si on est à la fin
        //*******************************************************
        if(x == xEnd && y == yEnd)
        {
            //Génération du chemin
            string path = "";
            while(!(x == xStart && y == yStart))
            {
                j = mapDirections[x][y];

                //Pour l'affichage des directions prises
                //Symétrie vis-à-vis des directions (chemin retour)
                c = '0'+(j+4)%8;
                path = c + path;

                x += dx[j];
                y += dy[j];
            }

            // On vide la mémoire
            delete n0;
            while(!pq[pqi].empty()) pq[pqi].pop();

            return path;
        }
        //*******************************************************


        // Si on est pas à la fin, on teste tous les voisins
        for(i=0; i<8; i++)
        {
            xNext=x+dx[i]; yNext=y+dy[i];

            //   limites map*******************************************************  Obstacle***************   Noeud déjà visité****************
            if(!(xNext < 0 || xNext > xTaille-1 || yNext < 0 || yNext > yTaille-1 || map[xNext][yNext] == 1 || mapNodesClosed[xNext][yNext] == 1))
            {
                //On crée un noeud fils
                m0 = new node(xNext, yNext, n0 -> get_coutH(), n0 -> get_coutG());
                m0 -> calculate_g(i);

                m0 -> calculate_heuristic(*f0);
                m0 -> modifyF();


                // Si le noeud fils n'est pas dans la openMap, on le met dedans
                if(mapNodesOpen[xNext][yNext] == 0)
                {
                    mapNodesOpen[xNext][yNext] = m0 -> get_coutF();
                    pq[pqi].push(*m0);

                    // On lui affecte la direction du parent
                    mapDirections[xNext][yNext] = (i+4)%8;
                }

                // Sinon, si on a un coutF plus élevé, on modifie notre queue
                else if(mapNodesOpen[xNext][yNext] > m0 -> get_coutF())
                {
                    //MAJ des infos (coutF + parent)
                    mapNodesOpen[xNext][yNext] = m0 -> get_coutF();
                    mapDirections[xNext][yNext] = (i + 4) % 8;

                    // On remplace le noeud en vidant la queue
                    // sauf le noeud à remplacer qui va être pop
                    while
                    (!(pq[pqi].top().get_xPos() == xNext && pq[pqi].top().get_yPos() == yNext))
                    {
                        pq[1-pqi].push(pq[pqi].top());
                        pq[pqi].pop();
                    }

                    pq[pqi].pop();


                    if(pq[pqi].size() > pq[1-pqi].size())
                    {
                    pqi=1-pqi;
                    }

                    while(!pq[pqi].empty())
                    {
                        pq[1-pqi].push(pq[pqi].top());
                        pq[pqi].pop();
                    }

                    pqi=1-pqi;

                    pq[pqi].push(*m0);
                }

                else delete m0;

            }
        }

        delete n0;
    }

    return ""; // Pas de chemin
}



int main(void)
{

    //********************* VARIABLES SERIAL *********************//

    serialib SERIAL;                    // Object of the serialib class

    int Ret;                            // Utilisé pour tester le port Serial

    char Buffer[128];
    int Value = 0;

    //***********************************************************//

    enemy *Bot1;


    int xA, yA;


    xA = 49;
    yA = 0;


    int xB, yB;

    xB = 49;
    yB = 99;



    while((yA != yB))
    {

    Ret=SERIAL.Open(DEVICE_PORT,9600);                                          // Open serial link at 115200 bauds

    if (Ret != 1)
    {                                                                       // If an error occured...
        printf ("Erreur\n");        // ... display a message ...
        return Ret;                                                         // ... quit the application
    }

    //printf ("Serial port opened successfully !\n");

    //cout<<"LECTURE"<<endl;

    //getchar();

    Ret = SERIAL.ReadString(Buffer,'\n',100,100);

    Value = atoi(Buffer);

    //cout<<Value<<endl;

    if(Value < 100)
    {
    Bot1 = new enemy(49,Value,8);
    }

    else
    {
    Bot1 = new enemy(49,49,0);
    }


    int n = xTaille;
    int m = yTaille;

    int x;
    int y;


    // Open serial port

    //Reset de la map
    for(x = 0; x < xTaille; x++)
    {
        for(y = 0; y < yTaille; y++)
        {
            map[x][y] = 0;
        }
    }


    for(x = (Bot1->xPos-25); x <= (Bot1->xPos+25); x++)
    {
        for(y=Bot1->yPos-25; y<=Bot1->yPos+25; y++)
        {
            map[x][y]=Bot1->enemyNodes[x-((Bot1->xPos)-25)][y-((Bot1->yPos)-25)];
        }
    }


    /*for(x = (Bot2->xPos-25); x <= (Bot2->xPos+25); x++)
    {
        for(y=Bot2->yPos-25; y<=Bot2->yPos+25; y++)
        {
            map[x][y]=Bot2->enemyNodes[x-((Bot2->xPos)-25)][y-((Bot2->yPos)-25)];
        }
    }*/


    // A* entre (xA,yA) et (xB,yB)
    string route = pathFinding(xA, yA, xB, yB);


    //****************************************************************************
    // Suit la route
    if(route.length()>0)
    {
        int j; char c;
        int x=xA;
        int y=yA;
        int i;
        map[x][y]=2;
        for(i=0;i<(int)route.length();i++)
        {
            c =route.at(i);
            j=atoi(&c);
            x=x+dx[j];
            y=y+dy[j];
            map[x][y]=3;
        }
        map[x][y]=4;


 for(int x=0;x<n;x++)
    {
        for(int y=0;y<m;y++)
        {
            if(map[x][y]==0)
            {
            cout<<". ";
            }
            else if(map[x][y]==1)
            {
            cout<<"O "; //obstacle
            }
            else if(map[x][y]==2)
            {
            cout<<"S "; //start}
            }
            else if(map[x][y]==3)
            {
            cout<<"R "; //route
            }
            else if(map[x][y]==4)
            {
            cout<<"F "; //finish
            }
            else
            {
            cout<<" ";//map[x][y];
            }
        }
        cout<<endl;
    }



    /*ofstream mapTxt;
    mapTxt.open ("MapNodes.txt");

    for(int y=0;y<m;y++)
        {
            for(int x=0;x<n;x++)
            {
                mapTxt<<map[x][y];
            }
            mapTxt<<endl;
        }*/


    }
    //****************************************************************************


    SERIAL.Close();

    int k; char d;

    if((int)route.length()>=1)
    {
    d=route.at(0);
    k=atoi(&d);

    xA=xA+dx[k];
    yA=yA+dy[k];
    }

    usleep(500 * 1000);

    std::system("clear");

    }

    cout<<"ARRIVE !"<<endl;


}





