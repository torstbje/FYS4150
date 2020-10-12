#include "solar.hpp"
#include <larmadillo>

using namespace std;
using namespace arma;


MultiBodySystem::MultiBodySystem(Planet* planets,int nPlanets){
  m_planets = planets;
  m_nP = nPlanet;
}

MultiBodySystem::simulate(double h){
  
}
