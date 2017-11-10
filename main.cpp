//Austin Griffith
//October 15, 2017
//ISYE 6767
//Hedging Error and Profit and Loss Calculations

#include <iostream>
#include <fstream>
#include <cstdlib>
#include <random>
#include <cmath>
#include <vector>
#include <sstream>
#include <string>
#include "stdnormalcdf.h"
#include "black.h"
#include "reader.h"
#include "hedge.h"

using namespace std;

int main()
{
    //initialized values
    string t0 = "2011-07-05";
    string t1 = "2011-07-29";
    string texp = "2011-09-17";
    string type = "C";
    double Q = 0.0;
    double K = 500.0;
    double sigma = 0.24;

    //class reads the csv files
    reader reader;

    //filenames
    string csv_int = "interest.csv";
    string csv_op = "op_GOOG.csv";
    string csv_sec = "sec_GOOG.csv";

    //open and read interest csv
    ifstream intfile("");
    intfile.open(csv_int);
    if(intfile.good())
    {
        reader.interest_input(intfile);
    }
    intfile.close();

    //open and read options csv
    ifstream opfile("");
    opfile.open(csv_op);
    if(opfile.good())
    {
        reader.op_input(opfile);
    }
    opfile.close();

    //open and read sec prices csv
    ifstream secfile("");
    secfile.open(csv_sec);
    if(secfile.good())
    {
        reader.sec_input(secfile);
    }
    secfile.close();

    //sec and interest rate trimmed vectors
    vector<double> rates;
    vector<double> sec;
    vector<string> dates;
    reader.trimmer(t0,t1,texp,rates,sec,dates);

    //option price vec from op csv
    //runs bid and offer functions in reader class
    vector<double> price;
    for(int i = 0; i < dates.size(); i++)
    {
        double bid = reader.bid(dates[i],texp,K,type);
        double offer = reader.offer(dates[i],texp,K,type);
        double bo = (bid + offer)*0.5;
        price.push_back(bo);
    }

    //initializes hedge class
    string name = "results.csv";
    hedge hedge1(sec,rates,price,dates,K,reader.exp_days,sigma,Q);
    hedge1.volatility();
    hedge1.error();
    hedge1.out(name);

    return 0.0;
}
