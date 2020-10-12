#include "Solar.hpp"
using namespace std;
using namespace arma;

Planet::Planet(string name, vec r, vec v, double mass, void(*acceleration)(Planet, Planet[], int)){
  m_name = name;
  m_r = r;
  m_v = v;
  m_a = 0;
  m_mass = mass;
  accelerate = acceleration;
}

double Planet::setStep(double h){
  m_h = h;
}
double Planet::getName(){
  return m_name;
}

double Planet::getMass(){
  return m_mass;
}
vec Planet::getPos(){
  return m_r;
}
vec Planet::getVel(){
  return m_v;
}


void Planet::update(Planet thisPlanet, Planet[] celestialBodies, int nBodies){

  m_r += m_h*m_v + pow(m_h,2)*m_a/2;
  vec p_a = m_a;
  accelerate(celestialBodies, n_bodies);
  m_v += m_h*(m_a+p_a)/2;

}
