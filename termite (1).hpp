#ifndef TERMITE_HPP
#define TERMITE_HPP
#include "grille.hpp"

class Termite{ 
private:
int id;
Coord pos;
Direction dir;
bool porte;//porte une brind
int sablier;//compteur de deplacement
bool tourne;//tourne sur place pour poser
int equipe;//(0 ou 1)
int equipePortee; //équipe de la brindille portée (-1 si neutre)

public:
Termite(int id, Coord pos, Direction dir, int equipe) : 
    id(id), pos(pos), dir(dir), porte(false),sablier(6),tourne(false),equipe(equipe),  equipePortee(-1) {}
int getId()const;
Coord getPos()const;
Direction getDir()const;
bool porteBrindille()const;
int getSablier()const;
//on passe au fonction du deplacemnet
int getequipe()const{return equipe;}
int getequipeportee()const{return equipePortee;}
void tourneADroite();
void tourneAGauche();
void tourneAleat();
//les diff interaction avec la grille
bool laVoieEstLibre(const Grille &g)const;
bool brindilleEnFace(const Grille& g) const;
int voisinsLibres(const Grille &g)const;
void avance(Grille &g);
void marcheAleatoire(Grille &g);
void chargeBrindille(Grille &g);
void dechargeBrindille(Grille &g);
bool brindilleRamassable(const Grille& g) const;
void vieTermite(Grille &g);//fais deux truc si il marche au hasard jusqu'a en trouver une deavnt lui ,puis il la ramasse le cas ou la temite ne fais porte pas de brindille,si le contaire il marche au hasard
  bool peutPoser(const Grille& g) const;
};
ostream &operator<<(ostream &os,const Termite &t);
#endif
