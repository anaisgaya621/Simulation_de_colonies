#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "coord.hpp"
#include "grille.hpp"
#include "termite.hpp" 

TEST_CASE("Constructeur valide"){
    Coord c(0,0);
    CHECK(c.getlig()==0);
    CHECK(c.getcol()==0);
    Coord d(tailleGrille-1, tailleGrille-1);  // coin extrême
    CHECK(d.getlig() == tailleGrille-1);
}
TEST_CASE("Constructeur hors grille lève exception") {
    CHECK_THROWS(Coord(-1, 0));
    CHECK_THROWS(Coord(0, -1));
    CHECK_THROWS(Coord(tailleGrille, 0));
    CHECK_THROWS(Coord(0, tailleGrille));
}
TEST_CASE("Opérateur égalité") {
    CHECK(Coord(3, 5) == Coord(3, 5));
    CHECK_FALSE(Coord(3, 5) == Coord(3, 6));
}

TEST_CASE("left then right = actuel position") {
    for (int i = 0; i < 8; i++) {
        Direction d = Direction(i);
        CHECK(aDroite(aGauche(d)) == d);
        CHECK(aGauche(aDroite(d)) == d);
    }
}
TEST_CASE("devantcoord avance coorectemenet ver N"){
    Coord c(5,5);
    Coord devant=devantCoord(c,Direction::N);
    CHECK(devant==Coord(4,5));
}
TEST_CASE("poseBrindille et contientBrindille") {
    Grille g;
    Coord c(3, 5);
    CHECK_FALSE(g.contientBrindille(c));
    g.poseBrindille(c);
    CHECK(g.contientBrindille(c));
}
TEST_CASE("poseBrindille sur case non vide lève exception") {
    Grille g;
    Coord c(3, 5);
    g.poseBrindille(c);
    CHECK_THROWS(g.poseBrindille(c));   // déjà une brindille
}
TEST_CASE("enleveBrindille") {
    Grille g;
    Coord c(3, 5);
    g.poseBrindille(c);
    g.enleveBrindille(c);
    CHECK_FALSE(g.contientBrindille(c));
    
}
TEST_CASE("poseTermite et numeroTermite") {
    Grille g;//appel au default constr
    Coord c(2, 2);
    CHECK(g.numeroTermite(c) == -1);
    g.poseTermite(c, 0);
    CHECK(g.numeroTermite(c) == 0);
}
TEST_CASE("poseTermite sur case non vide lève exception") {
    Grille g;
    Coord c(2, 2);
    g.poseBrindille(c);
    CHECK_THROWS(g.poseTermite(c, 0));  // brindille déjà là
}
TEST_CASE("enleveTermite") {
    Grille g;
    Coord c(2, 2);
    g.poseTermite(c, 0);
    g.enleveTermite(c);
    CHECK(g.numeroTermite(c) == -1);
    CHECK_THROWS(g.enleveTermite(c));   // plus de termite
}
TEST_CASE("estVide") {
    Grille g;
    Coord c(1, 1);
    CHECK(g.estVide(c));
    g.poseBrindille(c);
    CHECK_FALSE(g.estVide(c));
}
TEST_CASE("Constructeur Termite") {
    Grille g;
    Coord c(5, 5);
    g.poseTermite(c, 0);
    Termite t(0, c, N);
    CHECK(t.getId() == 0);
    CHECK(t.getPos() == c);
    CHECK(t.getDir() == N);
    CHECK_FALSE(t.porteBrindille());
    CHECK(t.getSablier() == 0);
}

TEST_CASE("tourneADroite") {
    Termite t(0, Coord(5,5), N);
    t.tourneADroite();
    CHECK(t.getDir() == NE);
    t.tourneADroite();
    CHECK(t.getDir() == E);
}
TEST_CASE("tourneAGauche") {
    Termite t(0, Coord(5,5), N);
    t.tourneAGauche();
    CHECK(t.getDir() == NW);
    t.tourneAGauche();
    CHECK(t.getDir() == W);
}

TEST_CASE("tourneADroite then tourneAGauche = direction initiale") {
    Termite t(0, Coord(5,5), N);
    t.tourneADroite();
    t.tourneAGauche();
    CHECK(t.getDir() == N);
}
TEST_CASE("laVoieEstLibre - case vide devant") {
    Grille g;
    Coord c(5, 5);
    g.poseTermite(c, 0);
    Termite t(0, c, N);
    CHECK(t.laVoieEstLibre(g));   // (4,5) est vide
}
TEST_CASE("la voieEstlibre termite devant"){
    Grille g;
    Coord c(5,5);
    g.poseTermite(c,0);
    g.poseTermite(Coord(4,5),1);
    Termite t(0,c,N);
    CHECK_FALSE(t.laVoieEstLibre(g));
}
TEST_CASE("laVoieEstLibre - bord de grille") {
    Grille g;
    Coord c(0, 5);
    g.poseTermite(c, 0);
    Termite t(0, c, N);
    CHECK_FALSE(t.laVoieEstLibre(g));  // bord nord
}
TEST_CASE("brindilleEnFace - vrai") {
    Grille g;
    Coord c(5, 5);
    g.poseTermite(c, 0);
    g.poseBrindille(Coord(4, 5));
    Termite t(0, c, N);
    CHECK(t.brindilleEnFace(g));
}
TEST_CASE("brindilleEnFace - bord") {
    Grille g;
    Coord c(0, 5);
    g.poseTermite(c, 0);
    Termite t(0, c, N);
    CHECK_FALSE(t.brindilleEnFace(g));  
}

TEST_CASE("voisinsLibres - grille vide autour") {
    Grille g;
    Coord c(5, 5);
    g.poseTermite(c, 0);
    Termite t(0, c, N);
    CHECK(t.voisinsLibres(g) == 8);  // toutes les cases autour sont libres
}
TEST_CASE("voisinsLibres - une brindille autour") {
    Grille g;
    Coord c(5, 5);
    g.poseTermite(c, 0);
    g.poseBrindille(Coord(4, 5));
    Termite t(0, c, N);
    CHECK(t.voisinsLibres(g) == 7);
}
TEST_CASE("AVCANCE VERS N"){
    Grille g;
    Coord c(5,5);
    g.poseTermite(c,0);
    Termite t(0,c,N);
    t.avance(g);
    CHECK(t.getSablier()==1);
}
TEST_CASE("AVANCE BLOC PAR BRINDILLE"){
    Grille g;
    Coord c(5,5);
    g.poseTermite(c,0);
    g.poseBrindille(Coord(4,5));
    Termite t(0,c,N);
    t.chargeBrindille(g);
    CHECK(t.porteBrindille());
    CHECK_FALSE(g.contientBrindille(Coord(4,5)));
}
TEST_CASE("CHARGEbrindille ramasse"){
    Grille g;
    Coord c(5,5);
    g.poseTermite(c,0);
    g.poseBrindille(Coord(4,5));
     Termite t(0, c, N);
    t.chargeBrindille(g);
    CHECK(t.porteBrindille());
    CHECK_FALSE(g.contientBrindille(Coord(4, 5)));
}
TEST_CASE("chargeBrindille rien devant") {
    Grille g;
    Coord c(5, 5);
    g.poseTermite(c, 0);
    Termite t(0, c, N);
    t.chargeBrindille(g);
    CHECK_FALSE(t.porteBrindille());
}

TEST_CASE("coherence grille termite apres avance") {
    Grille g;
    Coord c(5, 5);
    g.poseTermite(c, 0);
    Termite t(0, c, N);
    t.avance(g);
    CHECK(t.getPos() == Coord(4, 5));
    CHECK(g.numeroTermite(Coord(4, 5)) == 0);
    CHECK(g.estVide(Coord(5, 5)));
}
TEST_CASE("poseNid et estNid") {
    Grille g;
    Coord c(5, 5);
    g.poseNid(c, 0);
    CHECK(g.estNid(c));
    CHECK(g.equipeNid(c) == 0);
    CHECK_FALSE(g.estVide(c));
}

TEST_CASE("poseNid sur case non vide leve exception") {
    Grille g;
    Coord c(5, 5);
    g.poseBrindille(c);
    CHECK_THROWS(g.poseNid(c, 0));
}

TEST_CASE("marqueBrindille neutre puis marquee") {
    Grille g;
    Coord c(3, 3);
    g.poseBrindille(c);
    CHECK(g.equipeBrindille(c) == -1);
    g.marqueBrindille(c, 0);
    CHECK(g.equipeBrindille(c) == 0);
}

TEST_CASE("brindilleRamassable - neutre") {
    Grille g;
    Coord c(5, 5);
    g.poseTermite(c, 0);
    g.poseBrindille(Coord(4, 5));
    Termite t(0, c, N, 0);
    CHECK(t.brindilleRamassable(g));
}

TEST_CASE("brindilleRamassable - meme equipe") {
    Grille g;
    Coord c(5, 5);
    g.poseTermite(c, 0);
    g.poseBrindille(Coord(4, 5));
    g.marqueBrindille(Coord(4, 5), 0);
    Termite t(0, c, N, 0);
    CHECK_FALSE(t.brindilleRamassable(g));
}

TEST_CASE("brindilleRamassable - equipe adverse") {
    Grille g;
    Coord c(5, 5);
    g.poseTermite(c, 0);
    g.poseBrindille(Coord(4, 5));
    g.marqueBrindille(Coord(4, 5), 1);
    Termite t(0, c, N, 0);
    CHECK(t.brindilleRamassable(g));
}

TEST_CASE("getEquipe") {
    Termite t(0, Coord(5, 5), N, 0);
    CHECK(t.getEquipe() == 0);
    Termite t2(1, Coord(3, 3), S, 1);
    CHECK(t2.getEquipe() == 1);
}