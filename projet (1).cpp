#include "jeu.hpp"
#include <cstdlib>
#include <ctime>
#include <ctime>
#include <unistd.h>
#include <iostream>
using namespace std;

int main() {
    srand(time(0));
    Jeu jeu;
    int pas = 0;

    while (!jeu.partieTerminee()) {
        cout << "\033[2J\033[H";
        jeu.affiche();
        cout << "Pas : " << pas << " — Ctrl+C pour quitter\n";
        jeu.pasDeSimulation();
        usleep(150000);
        pas++;
    }
    // Affiche le resultat final
    cout << "\033[2J\033[H";
    jeu.affiche();
    cout << "\n=== PARTIE TERMINEE en " << pas << " pas ===\n";

    if (jeu.scoreEquipe(0) > jeu.scoreEquipe(1))
        cout << "\033[31mROUGE GAGNE !\033[0m\n";
    else if (jeu.scoreEquipe(1) > jeu.scoreEquipe(0))
        cout << "\033[34mBLEU GAGNE !\033[0m\n";
    else
        cout << "EGALITE !\n";

    return 0;
}