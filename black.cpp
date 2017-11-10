//Austin Griffith
//September 21, 2017
//ISYE 6767

#include <iostream>
#include <fstream>
#include <cmath>
#include "stdnormalcdf.h"
#include "black.h"

using namespace std;

//initializer
black::black(double so, double k, double T, double r, double sigma, double q)
:so_(so),k_(k),T_(T),r_(r),sigma_(sigma),q_(q) {};

//for delta call value in hedging error
double black::cdelta()
{
    stdnormalcdf normal(d1);
    return abs(exp(-q_*T_)*normal.Nx());
}

//for delta put value in hedging error
double black::pdelta()
{
    stdnormalcdf normal(d1);
    return abs(exp(-q_*T_)*(normal.Nx() - 1));
}

//give Vput value for european put option
//requires N(d1) and N(d2) for inputs
double black::Vcall()
{
    stdnormalcdf norm1(d1);
    stdnormalcdf norm2(d2);
    double v = so_*exp(-1*q_*T_)*norm1.Nx() - k_*exp(-1*r_*T_)*norm2.Nx();
    return v;
}

//give Vput value for european put option
//requires N(-d1) and N(-d2) for inputs
double black::Vput()
{
    stdnormalcdf norm1(-1*d1);
    stdnormalcdf norm2(-1*d2);
    double v = -1*so_*exp(-1*q_*T_)*norm1.Nx() + k_*exp(-1*r_*T_)*norm2.Nx();
    return v;
}


