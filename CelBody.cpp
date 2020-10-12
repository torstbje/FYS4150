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

void CelBody::setStep(double h){
  m_h = h;
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

void CelBody::updateAcce(int nBodies, CelBody celestialBodies[]){
  if (movable == false){return;}
  for (uint i = 0; i < m_a.n_rows; i++){
    m_a(i) = 0;
  }
  double mass;
  vec pos;
  string name;
  for (int i = 0; i < nBodies; i++){
    name = celestialBodies[i].getName();
    if (name != m_name){
      mass = celestialBodies[i].getMass();
      pos = celestialBodies[i].getPos();
      m_a += (pos-m_r)*mass/pow(abs(pos-m_r),m_beta + 1);
    }
  }
}

void CelBody::update(int nBodies, CelBody celestialBodies[]){

  m_r += m_h*m_v + pow(m_h,2)*m_a/2;
  vec p_a = m_a;
  updateAcce(nBodies,celestialBodies);
  m_v += m_h*(m_a+p_a)/2;

}
