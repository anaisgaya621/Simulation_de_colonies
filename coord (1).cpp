#include "coord.hpp"
ostream&operator<<(ostream &os,Direction dir){
    string direction[]={"N","NE","E","SE","S","SW","W","NW"};
os<<direction[int(dir)];
return os;
}
Direction aGauche(Direction dir){
    return Direction((int(dir)+7)%8);
}
Direction aDroite (Direction dir){
    return Direction((int(dir)+1)%8);
}
Coord::Coord(int l,int c){
    if(l<0||l>=tailleGrille||c<0||c>=tailleGrille)
        throw runtime_error("cordonnee invalide");
            lig=l; col=c;
}
int Coord::getlig()const{
    return lig;
}
int Coord::getcol()const{
    return col;
}
bool Coord::operator==(const Coord &other) const{
    return lig==other.lig&&col==other.col;
}
ostream &operator<<(ostream &os,Coord c){
    os<<"("<<c.getlig()<<", "<<c.getcol()<<")";
    return os;
}
Coord devantCoord(Coord c,Direction d){
    int l=c.getlig();
    int col=c.getcol();
    if(d==N||d ==NE||d==NW)l--;
     if (d == S|| d == SE || d == SW) l++;
    if (d == E|| d == NE || d == SE) col++;
    if (d == W  || d == NW || d == SW) col--;
    return Coord(l, col);  // lève runtime_error si hors grille
}

