#include"grille.hpp"
Grille::Grille(){};
void Grille::poseBrindille(Coord c){
    if(!estVide(c)) throw runtime_error("case non vide");
        cases[c.getlig()][c.getcol()].brindille=true;
      cases[c.getlig()][c.getcol()].equipeBrindille = -1;
    
}
void Grille::enleveBrindille(Coord c){
        if(!contientBrindille(c))
            throw runtime_error("y a pas de brindille");
                cases[c.getlig()][c.getcol()].brindille=false;
    cases[c.getlig()][c.getcol()].equipeBrindille = -1;
}
bool Grille::contientBrindille(Coord c)const{
            return cases[c.getlig()][c.getcol()].brindille;
}
void Grille::poseTermite(Coord c,int idT){
    if(!estVide(c))
        throw runtime_error("case non vide alors tu peux pas poser une termite ");
            cases[c.getlig()][c.getcol()].termite=idT; 
}
void Grille::enleveTermite(Coord c){
        if(numeroTermite(c)==-1)
            throw runtime_error("pas de termite dans cette case");
                cases[c.getlig()][c.getcol()].termite=-1;
}
int Grille::numeroTermite(Coord c)const{
            return cases[c.getlig()][c.getcol()].termite;
}
bool Grille::estVide(Coord c)const{
    return !contientBrindille(c)&&numeroTermite(c)==-1 && !estNid(c);
}
ostream &operator<<(ostream &os,const Grille &g){
     for (int l = 0; l < tailleGrille; l++) {
        for (int c = 0; c < tailleGrille; c++) {
            Coord coord(l, c);
            if (g.contientBrindille(coord))
                os << "* ";
            else if (g.numeroTermite(coord) != -1)
                os << "T ";
            else
                os << ". ";
        }
        os << "\n";
    }
    return os;
}
void Grille::poseNid(Coord c,int equipe){
    if(!estVide(c)) throw runtime_error("cas non vide");
     cases[c.getlig()][c.getcol()].nid = true;
    cases[c.getlig()][c.getcol()].equipeNid = equipe;
}
bool Grille::estNid(Coord c) const {
    return cases[c.getlig()][c.getcol()].nid;
}
int Grille::equipeNid(Coord c)const{
    return cases[c.getlig()][c.getcol()].equipeNid;
}
int Grille::equipeBrindille(Coord c) const {
    return cases[c.getlig()][c.getcol()].equipeBrindille;
}
void Grille::marqueBrindille(Coord c, int equipe) {
    if (!contientBrindille(c))
        throw runtime_error("marqueBrindille: pas de brindille ici");
    cases[c.getlig()][c.getcol()].equipeBrindille = equipe;
}


