#include "Solar.hpp"
#include "CelBody.cpp"
#include "MultiBodySystem.cpp"
#include <fstream>
#include <armadillo>


using namespace std;
using namespace arma;

void makeObject(string&, istringstream&, CelBody*, int&, string, double);
void makeStatSun(CelBody*);


int main(int argc, char const *argv[]){

  int steps = stoi(argv[1]);
  double time = stod(argv[2]);
  string version = argv[3];


  ifstream inFile("initial_conditions.txt");
  string line, name, objects;
  double mass, beta = 2.;
  int n_bodies, c_b = 0;
  string modifier = "";
  bool statSun = true, useEuler = false;

  if (version == "Earth"){
    objects = "earth";
    modifier = "circular";
    n_bodies = 2;
  }
  if (version == "EarthEuler"){
    objects = "earth";
    useEuler = true;
    modifier = "circular";
    n_bodies = 2;
  }
  if (version == "EarthJup"){
    objects = "earth jupiter";
    n_bodies = 3;
  }

  if (version == "EarthMegaJup"){
    objects = "earth jupiter";
    modifier = "megaJup";
    n_bodies = 3;
  }

  if (version == "EarthGigaJup"){
    objects = "earth jupiter";
    modifier = "gigaJup";
    n_bodies = 3;
  }

  if (version == "EarthBeta"){
    objects = "earth";
    n_bodies = 2;
    cout << "What exponent do you want to use for beta?\n";
    cout << "Input: ";
    cin >> beta;
  }
  if (version == "EllipticalEarth"){
    objects = "earth";
    modifier = "elliptical";
    n_bodies = 2;
  }
  if (version == "All"){
    objects = "earth jupiter mars venus saturn mercury uranus neptune sun";
    statSun = false;
    n_bodies = 9;
  }
  if (version == "RelMercury"){
    objects = "mercury";
    n_bodies = 2;
    modifier = "relativistic";
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
      makeObject(name,iss,bodies,c_b, modifier, beta);
    }
  }
  inFile.close();

  MultiBodySystem solarSystem(n_bodies,bodies);
  string filename = version + ".txt";
  solarSystem.simulate(filename,time,steps);


  return 0;
}

void makeObject(string& name, istringstream& iss, CelBody* bodies, int& n, string modifier, double beta){
  double mass, x, y, z, vx, vy, vz;
  bool isRel = false;
  iss >> mass;
  if (modifier == "relativistic"){
    //This only works for mercury
    isRel = true;
    x = 0.3075; y = 0; z = 0;
    vx = 0; vy = 12.44/365.24; vz = 0;
  }
  else if (modifier == "circular"){
    //This only works for the earth
    double pi = 3.141592;
    x = 1; y = 0; z = 0;
    vx = 0; vz = 0;
    vy = 2*sqrt(pow(pi,2)/pow(365.24,2));
  }
  else if (modifier == "elliptical"){
    //This only works for the earth
    x = 1; y = 0; z = 0;
    vx = 0; vz = 0;
    cout << "What is initial angular velocity for " << name << "? [AU/yr]\n";
    cout << "Input: ";
    cin >> vy;
    vy /= 365.24;
  }
  else{
    iss >> x >> y >> z >> vx >> vy >> vz;
  }
  if (modifier == "megaJup" && name == "jupiter"){
    mass *= 10;
  }
  if (modifier == "gigaJup" && name == "jupiter"){
    mass *= 1000;
  }

  vec r({x,y,z});
  vec v({vx,vy,vz});
  bodies[n] = CelBody(name,r,v,mass,true,isRel,beta);
  n++;
}
void makeStatSun(CelBody* bodies){
  double mass = 2e30;
  vec r({0,0,0});
  vec v({0,0,0});
  bodies[0] = CelBody("sun",r,v,mass,false);
}
