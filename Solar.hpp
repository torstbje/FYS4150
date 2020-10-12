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
  double m_mass, m_h, m_beta;
  bool movable;
public:
  CelBody(string, vec ,vec, double, bool = true, double = 2.);
  string getName();
  double getMass();
  vec getPos();
  vec getVel();
  void setStep(double);
  void updateAcce(int,CelBody[]);
  void update(int,CelBody[]);
};

class MultiBodySystem{
private:
  int m_nP;
  CelBody bodies[];

public:
  MultiBodySystem(int,CelBody[]);
  //void simulate(double, int, void f(CelBody[], int));
};


#endif
