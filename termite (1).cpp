#include "termite.hpp"
#include <cstdlib>
const float probaTourner = 0.1;
const int dureeSablier = 6;
int Termite::getId()const { return id; }
Coord Termite::getPos() const { return pos; }
Direction Termite::getDir()const { return dir; }
bool Termite::porteBrindille()const { return porte; }
int   Termite::getSablier()const { return sablier; }
ostream& operator<<(ostream& os, const Termite& t) {
    os << "Termite " << t.getId()
       << " pos=" << t.getPos()
       << " dir=" << t.getDir()
       << (t.porteBrindille() ? " [porte brindille]" : "");
    return os;
}
void  Termite:: tourneADroite(){dir=aDroite(dir);}
void Termite::tourneAGauche(){dir=aGauche(dir);}
void Termite::tourneAleat(){
    if(rand()%2==0) tourneADroite();
    else tourneAGauche();
}
bool Termite::laVoieEstLibre(const Grille &g)const{
    try{
        Coord devant=devantCoord(pos,dir);
        return g.estVide(devant);
    }
        catch(runtime_error&){
            return false;
        }
}
bool Termite::brindilleEnFace(const Grille& g) const{
    try{
        Coord devant=devantCoord(pos,dir);
        return g.contientBrindille(devant);}
        catch(runtime_error&){
            return false;
    }
}
int Termite::voisinsLibres(const Grille& g) const {
    int counter = 0;
    for (int i = 0; i < 8; i++) {
        try {
            Coord voisin = devantCoord(pos, Direction(i));
            if (g.estVide(voisin)) counter++;
        } catch(runtime_error&) {}
    }
    return counter;
}
//l 'iddee c que on peut meme ramasser les brildilee de mon adversaire alors
bool Termite::brindilleRamassable(const Grille& g) const {
    try {
        Coord devant = devantCoord(pos, dir);
        if (!g.contientBrindille(devant)) return false;
        int eq = g.equipeBrindille(devant);
        return eq == -1 || eq != equipe;
        
    } catch (runtime_error&) {
        return false;
    }
}
void Termite::avance(Grille &g){
    try{
        Coord devant=devantCoord(pos,dir);
        if(g.estVide(devant)){
            g.enleveTermite(pos);
            g.poseTermite(devant,id);
            pos=devant;
            sablier++;
        }
    }
        catch(runtime_error&){}
}
void Termite::marcheAleatoire(Grille &g){
    if(laVoieEstLibre(g)){
         if ((float)rand()/RAND_MAX < probaTourner)
            tourneAleat();
        avance(g);
    } else {
        tourneAleat();
    } 
}
void Termite::chargeBrindille(Grille &g){
    try{
        Coord devant=devantCoord(pos,dir);
        if(g.contientBrindille(devant)){
            equipePortee = g.equipeBrindille(devant);
            g.enleveBrindille(devant);
            porte=true;
            sablier=0;
        }
    }
        catch(runtime_error&){}
}
void Termite::dechargeBrindille(Grille &g){
    try{
        Coord devant=devantCoord(pos,dir);
        if(g.estVide(devant)){
            g.poseBrindille(devant);
            g.marqueBrindille(devant, equipe);
              
            porte=false;
            sablier=0;
            tourne=false;
        }
    }
        catch(runtime_error&){}
}
bool Termite::peutPoser(const Grille& g) const {
    try {
        Coord devant = devantCoord(pos, dir);
        return g.estVide(devant);

    } catch (runtime_error&) {
        return false;
    }
}
//la fonction pour decrire le comportement de la termite
void Termite::vieTermite(Grille& g) {
    if (!porte) {
        if (brindilleRamassable(g) && sablier >= dureeSablier)
            chargeBrindille(g);
        else
            marcheAleatoire(g);
    } else {
        if (sablier >= dureeSablier) {
            if (peutPoser(g))
                dechargeBrindille(g);
            else
                tourneAleat();
        } else {
            marcheAleatoire(g);
        }
    }
}