//Austin Griffith
//October 15, 2017
//ISYE 6767

#include <iostream>
#include <fstream>
#include <cmath>
#include <string>
#include <vector>
#include <cstdlib>
#include <sstream>
#include "stdnormalcdf.h"
#include "black.h"
#include "hedge.h"

using namespace std;

hedge::hedge(vector<double> so, vector<double> r,
    vector<double> p, vector<string> d, double k,
    double T, double sigma, double q)
:so_(so),d_(d),p_(p),k_(k),T_(T),r_(r),sigma_(sigma),q_(q){};

//calculates the volatility using vega
void hedge::volatility()
{
    //initializes value for nested for loops
    int max_count = 100;
    double sig0 = sigma_;
    double sig1;
    double Texp = T_;
    double miss = 0.000001;

    //reads through vectors, gets implied volatility
    //sigma available in class vector
    for(int n = 0; n < so_.size(); n++)
    {
        for(int i = 1; i < max_count; i++)
        {
            black cycle(so_[n],k_,Texp,r_[n],sig0,q_);
            double x = cycle.d1;
            double dpdf = exp(-1*0.5*pow(x,2))/sqrt(2*3.14159265359);
            double vega = (so_[n]*sqrt(Texp)*dpdf);
            sig1 = sig0 - ((cycle.Vcall() - p_[n])/vega);

            if(abs(sig1 - sig0) < miss)
            {
                sigf.push_back(sig0);
                i = max_count;
            }
            sig0 = sig1;
        }
        //passing of a business day
        Texp = Texp - pass;
    }
}

//creates csv using data from class vectors
void hedge::out(string name)
{
    ofstream myfile;
    myfile.open(name);
    myfile << "date, S, V, implied_vol, delta, HE, PNL" << endl;
    for(int i = 0; i < d_.size(); i++)
    {
        myfile << d_[i] << "," << so_[i] << "," <<
        p_[i] << "," << sigf[i] << "," <<
        delta[i] << "," << HE[i] << "," <<
        PNL[i] << endl;
    }
    myfile.close();
}

//calculates delta, HE and PNL
void hedge::error()
{
    //sets values for the for loop
    double s_old = so_[0];
    double s_new;
    double Texp = T_;

    //gets initial values, B0 and delta0
    black initial(so_[0],k_,Texp,r_[0],sigf[0],q_);
    double vs_delt0 = initial.cdelta();
    double B_old = initial.Vcall() - vs_delt0*s_old;


    //initial vector pushback
    HE.push_back(0.0);
    PNL.push_back(0.0);
    value.push_back(initial.Vcall());
    delta.push_back(vs_delt0);

    //first day now done
    Texp = Texp - pass;

    //start read from 1, since already solved for B0
    for(int i = 1; i <= so_.size(); i++)
    {
        //creates new stock price from price series
        //initializes black scholes
        s_new = so_[i];
        black cycle1(s_old,k_,Texp,r_[i],sigf[i],q_);
        black cycle2(s_new,k_,Texp,r_[i],sigf[i],q_);

        //creates new delta and B values
        int n = i - 1;
        double R = r_[n];
        double vs_delt1 = cycle2.cdelta();
        delta.push_back(vs_delt1);
        value.push_back(cycle2.Vcall());
        double B_new = vs_delt0*s_new + B_old*exp(R*pass) - vs_delt1*s_new;

        //determines hedging error for iteration i
        double hedge_error = vs_delt0*s_new + B_old*exp(R*pass) - cycle2.Vcall();
        HE.push_back(hedge_error);

        //determine PNL values
        double prof = cycle2.Vcall() - initial.Vcall();
        PNL.push_back(prof);

        //resets new values to old for next iteration
        Texp = Texp - pass; //updates time to expiration
        s_old = s_new;
        vs_delt0 = vs_delt1;
        B_old = B_new;
    }
}
