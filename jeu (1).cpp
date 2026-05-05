#include "jeu.hpp"
#include <iostream>
#include <cstdlib>
using namespace std;
const int nbTermites = 20;//pour chaque equipte
const float densiteBrindille = 0.05;
Jeu::Jeu():nid0(5,5),nid1(tailleGrille-6,tailleGrille-6) {
    // Place les nids
    grille.poseNid(nid0, 0);
    grille.poseNid(nid1, 1);
    // Place les brindilles
    for (int i=0; i<tailleGrille;i++) {
        for (int j = 0; j <tailleGrille; j++) {
            Coord c(i,j);
            if (grille.estVide(c) &&
                (float)rand()/RAND_MAX <densiteBrindille) {
                grille.poseBrindille(c);
            }
        }
    }
    int place = 0;//on va avoir des identifiant entre 0 et 20
    while (place < nbTermites) {
        int i=rand() % tailleGrille;
        int j=rand() % tailleGrille;
        Coord c(i, j);
        if (grille.estVide(c)) {
            Direction d=Direction(rand() % 8);
            termites0.push_back(Termite(place, c, d, 0));
            grille.poseTermite(c,place);
            place++;
        }
    }
        //par contre la on va avoir des id entre 20 et 39
    place = nbTermites;
    while (place < nbTermites * 2) {
        int i = rand() % tailleGrille;
        int j = rand() % tailleGrille;
        Coord c(i, j);
        if (grille.estVide(c)) {
            Direction d = Direction(rand() % 8);
            termites1.push_back(Termite(place, c, d, 1));
            grille.poseTermite(c, place);
            place++;
        }
    }
}

void Jeu::affiche()const{
    for(int i=0;i<tailleGrille;i++){
        for(int j=0;j<tailleGrille;j++){
            Coord c(i,j);
            if(grille.estNid(c)){
                if(grille.equipeNid(c)==0)
                    cout<<"\033[31m#\033[0m ";
                else cout<<"\033[34m#\033[0m ";
            }
            else if(grille.contientBrindille(c)){
                int eq=grille.equipeBrindille(c);
                if(eq==0)
                    cout << "\033[31m*\033[0m ";
                else if (eq == 1)
                    cout << "\033[34m*\033[0m ";
                else 
                    cout<<"* ";
                }
            else if (grille.numeroTermite(c)!=-1){
                int id =grille.numeroTermite(c);
                Direction d;
                string col;
                if(id<nbTermites){
                    d=termites0[id].getDir();
                    col= "\033[31m";   // rouge
                }
                else{
                    d=termites1[id-nbTermites].getDir();
                    col= "\033[34m";// bleu
                }
                char sym;
                switch(d){
                    case N: case S: sym='|';break;
                    case E : case W: sym='_';break;
                        case NE :case SW :sym='/';break;
                     default:           sym = '\\'; break;
                    
                }
                cout<<col<<sym<<"\033[0m ";
                
            }else{
                cout<<". ";
            }
            }
        cout<<"\n";
        }
        cout << "\033[31m● Rouge: " << scoreEquipe(0) << "\033[0m   ";
    cout << "\033[34m● Bleu:  " << scoreEquipe(1) << "\033[0m\n";
    }


void Jeu::pasDeSimulation() {
    for (int i = 0; i < (int)termites0.size(); i++)
        termites0[i].vieTermite(grille);
    for (int i = 0; i < (int)termites1.size(); i++)
        termites1[i].vieTermite(grille);
}
void Jeu::verfieCoherence() const {
    for (int i = 0; i < (int)termites0.size(); i++) {
        Coord c = termites0[i].getPos();
        if (grille.numeroTermite(c) != termites0[i].getId())
            throw runtime_error("Incoherence equipe 0");
    }
    for (int i = 0; i < (int)termites1.size(); i++) {
        Coord c = termites1[i].getPos();
        if (grille.numeroTermite(c) != termites1[i].getId())
            throw runtime_error("Incoherence equipe 1");
    }
}
int Jeu::scoreEquipe(int equipe) const {
    int count = 0;
    for (int l = 0; l < tailleGrille; l++) {
        for (int c = 0; c < tailleGrille; c++) {
            Coord pos(l, c);
            if (grille.contientBrindille(pos) &&
                grille.equipeBrindille(pos) == equipe)
                count++;
        }
    }
    return count;
}
bool Jeu::partieTerminee() const {
    for (int l = 0; l < tailleGrille; l++) {
        for (int c = 0; c < tailleGrille; c++) {
            Coord pos(l, c);
            if (grille.contientBrindille(pos) &&
                grille.equipeBrindille(pos) == -1)
                return false;
        }
    }
    return true;
}