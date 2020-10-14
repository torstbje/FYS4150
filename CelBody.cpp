#include "Solar.hpp"
using namespace std;
using namespace arma;

CelBody::CelBody(string name, vec r, vec v, double mass, bool canBeMoved, double beta){
  m_name = name;
  m_r = r;
  m_v = v;
  m_a = vec(r.n_rows,fill::zeros);
  m_mass = mass;
  m_beta = beta;
  movable = canBeMoved;
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
  double mass, grav = 1.488e-34;      //universial graitiy   [AU^3/days^2]
  vec pos;
  string name;
  vec diffV;
  double diff;
  for (int i = 0; i < nBodies; i++){
    name = celestialBodies[i].getName();
    if (name != m_name){
      mass = celestialBodies[i].getMass();
      pos = celestialBodies[i].getPos();
      diffV = pos-m_r;
      diff = sqrt(pow(diffV[0],2) + pow(diffV[1],2) + pow(diffV[2],2));
      m_a += diffV*grav*mass/(pow(diff,m_beta + 1));
    }
  }
}

void CelBody::update(double h, int nBodies, CelBody* celestialBodies){
  m_r += h*m_v + pow(h,2)*m_a/2;
  vec p_a = m_a;
  updateAcce(nBodies,celestialBodies);
  m_v += h*(m_a+p_a)/2;
}

void CelBody::updateEuler(double h, int nBodies, CelBody* celestialBodies){
  m_r += h*m_v;
  m_v += h*m_a;
  updateAcce(nBodies,celestialBodies);
}
