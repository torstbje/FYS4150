#include "Solar.hpp"
#include "CelBody.cpp"
#include "MultiBodySystem.cpp"
#include <fstream>
#include <armadillo>


using namespace std;
using namespace arma;

void makeObject(string&,istringstream&,CelBody*,int&,bool);
void makeStatSun(CelBody*);

int main(int argc, char const *argv[]){

  int steps = stoi(argv[1]);
  double time = stod(argv[2]);
  string version = argv[3];


  ifstream inFile("initial_conditions.txt");
  string line, name, objects;
  double mass;
  int n_bodies, c_b = 0;
  bool statSun = false, useEuler = false, circularEarth = false;

  if (version == "Earth"){
    objects = "earth";
    circularEarth = true;
    statSun = true;
    n_bodies = 2;
  }
  if (version == "EarthEuler"){
    objects = "earth";
    useEuler = true;
    circularEarth = true;
    statSun = true;
    n_bodies = 2;
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
      makeObject(name,iss,bodies,c_b, circularEarth);
    }
  }
  inFile.close();

  MultiBodySystem solarSystem(n_bodies,bodies);
  string filename = version + ".txt";
  solarSystem.simulate(filename,time,steps);


  return 0;
}

void makeObject(string& name, istringstream& iss, CelBody* bodies, int& n, bool circular){
  double mass, x, y, z, vx, vy, vz;

  if (circular){
    double pi = 3.141592;
    x = 1; y = 0; z = 0;
    vx = 0; vz = 0;
    vy = 2*sqrt(pow(pi,2)/pow(365.25,2));
  }
  else{
    iss >> mass >> x >> y >> z >> vx >> vy >> vz;
  }
  vec r({x,y,z});
  vec v({vx,vy,vz});
  bodies[n] = CelBody(name,r,v,mass);
  n++;
}
void makeStatSun(CelBody* bodies){
  double mass = 2e30;
  vec r({0,0,0});
  vec v({0,0,0});
  bodies[0] = CelBody("sun",r,v,mass,false);
}
