//Austin Griffith
//October 15, 2017
//ISYE 6767

#ifndef HEDGE_H
#define HEDGE_H

#include <fstream>
#include <iostream>
#include <stdio.h>
#include <vector>

using namespace std;

class hedge{
private:
    //initialization values
    vector<double> so_;
    vector<double> p_;
    vector<string> d_;
    vector<double> r_;
    double k_;
    double T_;
    double sigma_;
    double q_;

    //passing of a business day
    double pass = 0.003968253968254;

public:
    //functions within hedge class
    hedge(vector<double> so, vector<double> r,
        vector<double> p, vector<string> d, double k, double T,
        double sigma, double q);
    void volatility();
    void B0();
    void out(string name);
    void error();

    //vectors for csv
    vector<double> HE;
    vector<double> delta;
    vector<double> PNL;
    vector<double> sigf;
    vector<double> value;

};

#endif
