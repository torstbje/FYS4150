#include "Solar.hpp"
#include <armadillo>

using namespace std;
using namespace arma;


MultiBodySystem::MultiBodySystem(int nCelBodies,CelBody *celBodies){
  m_n = nCelBodies;
  m_bodies = celBodies;

  for (int i = 0; i < m_n; i++){
    m_bodies[i].updateAcce(m_n,m_bodies);
  }
}


void MultiBodySystem::simulate(string filename, double time, int steps, bool euler){

  m_time = linspace(0,time,steps);
  double h = time/steps;
  vec r;
  int dim = m_bodies[0].getPos().n_rows;    //Finds the dimension of the vectors
  ofstream file;
  file.open(filename);

  string lineString;
  for (int i = 0; i < m_n; i++){
    if (m_bodies[i].isMovable()){
      string name = m_bodies[i].getName();
      lineString += name + " , ";
    }
  }
  lineString.pop_back();      //These remove the comma at the end of the line
  lineString.pop_back();
  file << lineString << endl;
  lineString = "";
  for (int i = 0; i < steps; i++){
    //Loops over steps
    //file << m_time(i) << " ";
    for (int j = 0; j < m_n; j++){
      //Loops over bodies
      if (m_bodies[j].isMovable()){
        //skips unmovable bodies
        r = m_bodies[j].getPos();
        for (int k = 0; k < dim; k++){
          //Loops over dimensions (x,y,z) or (x,y)
          lineString += to_string(r(k)) + " ";
        }
        lineString += ", ";
        if (euler){
          m_bodies[j].updateEuler(h, m_n, m_bodies);
        }
        else{
          m_bodies[j].update(h, m_n, m_bodies);
        }
      }
    }

    lineString.pop_back();
    lineString.pop_back();
    file << lineString <<endl;
    lineString = "";
  }

  file.close();
}
