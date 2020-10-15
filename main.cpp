#include "Solar.hpp"
#include "CelBody.cpp"
#include "MultiBodySystem.cpp"
#include <fstream>
#include <armadillo>


using namespace std;
using namespace arma;

void makeObject(string&,istringstream&,CelBody*,int&);
void makeStatSun(CelBody*);

int main(int argc, char const *argv[]){

  string version = argv[3];
  //"EarthJup";

  ifstream inFile("initial_conditions.txt");
  string line, name, objects;
  double mass;
  int n_bodies, c_b = 0;
  bool statSun = false;

  if (version == "Earth"){
    objects = "earth";
    n_bodies = 2;
    statSun = true;
  }
  if (version == "EarthJup"){
    objects = "earth jupiter";
    n_bodies = 3;
    statSun = true;
  }



  CelBody bodies[n_bodies];
  if (statSun){
    makeStatSun(bodies);
    c_b++;
  }

  getline(inFile,line);

  while(getline(inFile,line)){
    istringstream iss(line);
    iss >> name;
    if (objects.find(name) != string::npos){
      makeObject(name,iss,bodies,c_b);
    }
  }
  inFile.close();

  MultiBodySystem solarSystem(n_bodies,bodies);
  string filename = version + ".txt";
  solarSystem.simulate(filename,30,3001);


  return 0;
}

void makeObject(string& name, istringstream& iss, CelBody* bodies, int& n){
  double mass, x, y, z, vx, vy, vz;
  iss >> mass >> x >> y >> z >> vx >> vy >> vz;
  vec r {x,y,z};
  vec v {vx,vy,vz};
  bodies[n] = CelBody(name,r,v,mass);
  n++;
}
void makeStatSun(CelBody* bodies){
  double mass = 2e30;
  vec r {0,0,0};
  vec v {0,0,0};
  bodies[0] = CelBody("sun",r,v,mass,false);
}
