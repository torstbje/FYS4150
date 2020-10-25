#include "Solar.hpp"
using namespace std;
using namespace arma;
double absVector(vec);

CelBody::CelBody(string name, vec r, vec v, double mass, bool canBeMoved, bool isRel, double beta){
  m_name = name;
  m_r = r;
  m_v = v;
  m_a = vec(r.n_rows,fill::zeros);
  m_mass = mass;
  m_beta = beta;          //Defaults to 2
  movable = canBeMoved;   //Decides if the object is immovable
  relativistic = isRel;   //Decides if the object follows the relativistic expression for gravitation
}

string CelBody::getName(){
  return m_name;
}
double CelBody::getMass(){
  return m_mass;
}
vec CelBody::getPos(){
  return m_r;
}
vec CelBody::getVel(){
  return m_v;
}
bool CelBody::isMovable(){
  return movable;
}

void CelBody::updateAcce(int nBodies, CelBody* celestialBodies){
  if (!movable){return;}

  m_a = vec(m_a.n_rows,fill::zeros);
  double mass, grav = 1.488e-34;      //universal gravity   [AU^3/days^2]
  vec pos;
  string name;
  vec diffV;
  double diff, l_squared;
  long double corr = 0.0;                    //Correction if we use relativistic expression

  if (relativistic == true){
    l_squared = pow(m_v(1)*m_r(0),2);        //Squared angular momentum, assumes the other values to be zero. Unit: [AU^4/day^2]
  }

  for (int i = 0; i < nBodies; i++){
    /*Loops over all other objects*/
    name = celestialBodies[i].getName();
    if (name != m_name){
      /*Does not accelerate towards it self*/
      mass = celestialBodies[i].getMass();
      pos = celestialBodies[i].getPos();

      if (relativistic == true){
        /*Computes the correction to the Newtonian gravitational force. Everything used here is initalized
        here so it doesn't get initalized when it's not needed*/
        double c_squared = 2.998e4;                  //Unit: [AU^2/day^2]
        vec relPos = m_r - pos;
        double pos_squared = pow(absVector(relPos),2);
        corr = 3*l_squared/(pos_squared*c_squared);
      }

      diffV = pos-m_r;                        //Vector of difference between the two objects
      diff = absVector(diffV);
      m_a += diffV*grav*mass/(pow(diff,m_beta + 1))*(1 + corr);         //We add one to beta to compensate for te position vector diffV
    }
  }
}

void CelBody::update(double h, int nBodies, CelBody* celestialBodies){
  //Updates position, velocity, acceleration with the Verlet method
  m_r += h*m_v + pow(h,2)*m_a/2;
  vec p_a = m_a;
  updateAcce(nBodies,celestialBodies);
  m_v += h*(m_a+p_a)/2;
}

void CelBody::updateEuler(double h, int nBodies, CelBody* celestialBodies){
  //Updates position, velocity, acceleration with the Euler method
  m_r += h*m_v;
  m_v += h*m_a;
  updateAcce(nBodies,celestialBodies);
}

double absVector(vec v){
  /*Calculates the absolute value of a vector*/
  return sqrt(pow(v(0),2) + pow(v(1),2) + pow(v(2),2));
}
