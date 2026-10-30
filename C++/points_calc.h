#include <math.h>

typedef struct {

    int x;
    int y;

  } Point;


double distancia(Point p1, Point p2);
double area(Point p1, Point p2);

/**
 *Calcula a distancia entre dois pontos.
*/
double distancia(Point p1, Point p2){

    //Distancia entre os dois pontos
    double d = sqrt( pow( (p2.x - p1.x),2) + pow( ( p2.y - p1.y),2) );
    //std::cout << d << std::endl;
    return d;

}

double area(Point p1, Point p2){
  
  double deltaX, deltaY;

  deltaX = p2.x - p1.x;
  deltaY = p2.y - p1.y;
  
  double result = (deltaX * deltaY)/2;

  return result; 
}