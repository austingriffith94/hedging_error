//Austin Griffith
//September 21, 2017
//ISYE 6767

#include <fstream>
#include <iostream>
#include <cmath>
#include "stdnormalcdf.h"

using namespace std;

stdnormalcdf::stdnormalcdf(double d_value):D(d_value){};

//approximation of the normal distribution, N(x)
//calculates to within 6 decimals of accuracy
//should be final function run
//requires R(z) and d value input
double stdnormalcdf::Nx()
{
    double a1 = 0.319381530;
    double a2 = -0.356563782;
    double a3 = 1.781477937;
    double a4 = -1.821255978;
    double a5 = 1.330274429;
    double Bval = sqrt(2*3.141592653589793238);

    //initialize normal approx values
    double Z;
    double r;
    double n;

    //calculates z value, used in R(z) function
    //calculates R(z) value, used in N(x) function
    //requires z value calculated from previous equation
    //calculates N(x) value using R(z) and D
    //for positive values
    if(D >= 0)
    {
        Z = 1/(1+(0.2316419*D));
        r = Z*(Z*(Z*(Z*((Z*a5)+a4)+a3)+a2)+a1);
        n = 1-(exp(-1*D*D*0.5)*r/Bval);
        return n;
    }

    //for negative values
    else
    {
        D = -1*D;
        Z = 1/(1+(0.2316419*D));
        r = Z*(Z*(Z*(Z*((Z*a5)+a4)+a3)+a2)+a1);
        n = 1-(exp(-1*D*D*0.5)*r/Bval);
        n = 1-n;
        return n;
    }
}
