#ifndef SOLAR_HPP
#define SOLAR_HPP
#include <fstream>
#include <armadillo>


using namespace std;
using namespace arma;


class CelBody{
private:
  vec m_r, m_v, m_a;
  string m_name;
  double m_mass, m_beta;
  bool movable, relativistic;
public:
  CelBody(string, vec ,vec, double, bool = true, bool = false, double = 2.);
  CelBody() { };
  string getName();
  double getMass();
  vec getPos();
  vec getVel();
  bool isMovable();
  void updateAcce(int,CelBody*);
  void update(double,int,CelBody*);
  void updateEuler(double,int,CelBody*);
};

class MultiBodySystem{
private:
  int m_n;
  CelBody *m_bodies;
  vec m_time;
public:
  MultiBodySystem(int,CelBody*);
  void simulate(string, double, int, bool = false);
};


#endif
