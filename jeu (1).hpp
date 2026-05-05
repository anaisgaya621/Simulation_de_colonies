#ifndef JEU_HPP
#define JEU_HPP
#include "termite.hpp"
#include <vector>
class Jeu{
private:
Grille grille;
vector<Termite> termites0;
 vector<Termite> termites1;  
Coord nid0;                 
Coord nid1;
public:
Jeu();
void affiche()const;
void pasDeSimulation();
void verfieCoherence()const;
int scoreEquipe(int equipe) const;
bool partieTerminee() const;
};
#endif