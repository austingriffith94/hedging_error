//Austin Griffith
//September 21, 2017
//ISYE 6767

#ifndef BLACK_H
#define BLACK_H

#include <fstream>
#include <iostream>
#include <stdio.h>
#include <cmath>

using namespace std;

class black{
private:
    //initializer values
    double so_;
    double k_;
    double T_;
    double r_;
    double sigma_;
    double q_;

public:
    black(double so, double k, double T, double r,
        double sigma,double q);
    //gives d1 value
    //is put into a normal distribution function, N(x)
    double d1 = (log(so_/k_) + (r_ - q_ + (sigma_*sigma_*0.5))*T_)/(sigma_*sqrt(T_));
    //gives d2 value
    //requires input of d1
    //shorter method chosen to reduce calculation time
    //is put into a normal distribution function, N(x)
    double d2 = d1 - (sigma_*sqrt(T_));
    double cdelta();
    double pdelta();
    double Vput();
    double Vcall();
};

#endif
