//Austin Griffith
//October 15, 2017
//ISYE 6767

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
    //Hedging Error and Profit and Loss Calculations

    //initial values for part 2
    //can change these to find values for desired dates
    //t0 is purchase date
    //t1 is sell date
    //texp is the expiration date
    //type is call "C", or put "P"
    //q2 is dividends
    //K2 is the strike price
    //sigma2 is the sigma used in the vega estimation
    string t0 = "2011-07-05";
    string t1 = "2011-07-29";
    string texp = "2011-09-17";
    string type = "C";
    double q2 = 0.0;
    double K2 = 500.0;
    double sigma2 = 0.24;

    //class reads the csv files
    reader reader;

    //open and read interest.csv
    ifstream intfile("");
    intfile.open("interest.csv");
    if(intfile.good())
    {
        reader.interest_input(intfile);
    }
    intfile.close();

    //open and read op_GOOG.csv
    ifstream opfile("");
    opfile.open("op_GOOG.csv");
    if(opfile.good())
    {
        reader.op_input(opfile);
    }
    opfile.close();

    //open and read sec_GOOG.csv
    ifstream secfile("");
    secfile.open("sec_GOOG.csv");
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
        double bid = reader.bid(dates[i],texp,K2,type);
        double offer = reader.offer(dates[i],texp,K2,type);
        double bo = (bid + offer)*0.5;
        price.push_back(bo);
    }

    //initializes hedge class
    string name = "results.csv";
    hedge hedge2(sec,rates,price,dates,K2,reader.exp_days,sigma2,q2);
    hedge2.volatility();
    hedge2.error();
    hedge2.out(name);

    return 0.0;
}
