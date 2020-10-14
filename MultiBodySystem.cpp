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


void MultiBodySystem::simulate(string filename, double time, int steps){
  m_time = linspace(0,time,steps);
  double h = time/steps;
  vec r;
  int dim = m_bodies[0].getPos().n_rows;    //Finds the dimension of the vectors
  ofstream file;
  file.open(filename);
  file << "time";

  for (int i = 0; i < m_n; i++){
    if (m_bodies[i].isMovable()){
      file  << " " << m_bodies[i].getName();
    }
  }
  file << endl;
  for (int i = 0; i < steps; i++){
    //Loops over steps

    file << m_time(i) << " ";
    for (int j = 0; j < m_n; j++){
      //Loops over bodies
      if (m_bodies[j].isMovable()){
        //skips unmovable bodies
        file << ", ";
        r = m_bodies[j].getPos();
        for (int k = 0; k < dim; k++){
          //Loops over dimensions (x,y,z)
          file << r(k) << " ";
        }
        m_bodies[j].update(h, m_n, m_bodies);
      }

    }
    file << endl;

  }

  file.close();
}
