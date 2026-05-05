#ifndef GRILLE_HPP
#define GRILLE_HPP
#include "coord.hpp"
#include<vector>
using namespace std;
struct Case{
bool brindille;
int termite;//-1 si absnet
int equipeBrindille;
bool nid;//est ce il s agit d un nid
int equipeNid;//a quelle equipe appartient ce nid
Case():brindille(false), termite(-1),equipeBrindille(-1),nid(false),equipeNid(-1){};
};
class Grille {
private:
Case cases[tailleGrille][tailleGrille];
public:
Grille();
void poseBrindille(Coord c);//POSE une brindille en c
void enleveBrindille(Coord c);//enlve la brindille en c
bool contientBrindille(Coord c)const;//verfier si il y a une bridile
void poseTermite(Coord c,int idT);//place le termite numero idt en c
void enleveTermite(Coord c) ;//enleve le termite
bool estVide(Coord c)const;//retourne l'id du termire
int numeroTermite(Coord c) const;//verfier si la cse ne contient ni termite ni brindille
// Pose un nid de lequipe 'equipe' en coordonnée c
// Lève une exception si la case n'est pas vide
void poseNid(Coord c, int equipe);

// Retourne vrai si la case c contient un nid
bool estNid(Coord c) const;

// Retourne lequipe du nid en c (0 ou 1)
// À appeler seulement si estNid(c) est vrai
int equipeNid(Coord c) const;

// Retourne l'équipe de la brindille en c
// Retourne -1 si la brindille est neutre
// À appeler seulement si contientBrindille(c) est vrai
int equipeBrindille(Coord c) const;

// Marque la brindille en c come appartenant a equoe
// Leve une exception si il ny a pas de brindille en c
void marqueBrindille(Coord c, int equipe);

};
ostream& operator<<(ostream& os,Grille &g);
#endif 