#include "Solar.hpp"
#include <armadillo>
#include <ctime>

using namespace std;
using namespace arma;


MultiBodySystem::MultiBodySystem(int nCelBodies,CelBody *celBodies){
  m_n = nCelBodies;
  m_bodies = celBodies;

  for (int i = 0; i < m_n; i++){
    //Finds the initial acceleration
    m_bodies[i].updateAcce(m_n,m_bodies);
  }
}


void MultiBodySystem::simulate(string filename, double time, int steps, bool euler, bool timing){

  m_time = linspace(0,time,steps);          //Unit: days
  double h = time/steps;
  vec r;
  int dim = m_bodies[0].getPos().n_rows;    //Finds the dimension of the vectors
  ofstream file;
  file.open(filename);

  string lineString;
  for (int i = 0; i < m_n; i++){
    if (m_bodies[i].isMovable()){
      //This skips the sun if its stationary
      string name = m_bodies[i].getName();
      lineString += name + " , ";
    }
  }
  lineString.pop_back();              //These remove the comma at the end of the line
  lineString.pop_back();
  file << lineString << endl;         //Writes a line to the file
  lineString = "";

  clock_t c_start;
  if (timing){
    c_start = clock();                //Starts timer
  }


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
          //These if-else decides which method is used
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
  clock_t c_end = clock();


  if (timing){
    double timer = (1000.0 * (c_end-c_start)/CLOCKS_PER_SEC);//ends timer
    string method;
    if (euler){
      method = "Euler";
    }
    else{
      method = "Verlet";
    }
    cout << "Total time for " << method << ": " << timer << " ms\n";
  }


  file.close();
}
