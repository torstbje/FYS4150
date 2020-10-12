#ifndef SOLAR_HPP
#define SOLAR_HPP
#include <fstream>
#include <armadillo>


using namespace std;
using namespace arma;


class Planet{
private:
  vec m_r, m_v, m_a;
  string m_name;
  double m_mass;
  double m_h;
public:
  Planet(string, vec ,vec, double, void f(Planet*,int));
  void accelerate(Planet*,int);
  string getName();
  double getMass();
  vec getPos();
  vec getVel();
  void setStep(double);
  void f1(Planet*,int);
  void f2(Planet*,int);
  //void setAcceleration(Planet*, int, void f(Planet*, int));
  void update(Planet*, int);
};
class MultiBodySystem{
private:
  Planet* m_planets;
  int m_nP;

public:
  MultiBodySystem(Planet*, int);
  void simulate(double, int, void f(Planet*, int));
};


#endif
