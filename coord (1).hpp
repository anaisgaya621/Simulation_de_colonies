#ifndef COORD_HPP
#define COORD_HPP
#include<iostream>
#include<stdexcept>
using namespace std;
const int tailleGrille=20;
enum Direction {N,NE,E,SE,S,SW,W,NW};
ostream &operator<<(ostream & os,Direction dir);
Direction aGauche(Direction dir);
Direction aDroite(Direction dir);
class Coord {
private:
int lig,col;
public:
Coord(int lig,int col);
int getlig()const;
int getcol()const;
bool operator==(const Coord &other) const;
};
ostream& operator<<(ostream &os,Coord c);
Coord devantCoord(Coord c,Direction d);//leve runtime_errir si bord
#endif