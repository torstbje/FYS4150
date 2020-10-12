#include "Solar.hpp"
#include <armadillo>

using namespace std;
using namespace arma;


MultiBodySystem::MultiBodySystem(int nCelBodies,CelBody *celBodies){
  m_bodies = celBodies;
  m_nP = nCelBodies;
}
MultiBodySystem::~MultiBodySystem(){
  delete[] m_bodies;
}


void MultiBodySystem::simulate(double time, int steps){
  m_time = linspace(0,time,steps);
}
