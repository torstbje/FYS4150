#include "solar.hpp"
#include <larmadillo>

using namespace std;
using namespace arma;


MultiBodySystem::MultiBodySystem(int nCelBodies,CelBody celBodies[]){
  m_CelBodies = CelBodies;
  m_nP = nCelBody;
}
MultiBodySystem::~MultiBodySystem(int nCelBodies,CelBody celBodies[]){
  delete[] m_CelBodies; 
}


MultiBodySystem::simulate(double h){

}
