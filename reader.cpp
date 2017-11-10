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
#include "reader.h"

using namespace std;

reader::reader(){};

//retrieves date and interest rate from csv file
void reader::interest_input(ifstream& filein)
{
    string looks;
    //run loop till end of file
    while(!filein.eof())
    {
        //gets line in csv
        getline(filein,looks);
        string date;
        date = looks.substr(0, looks.find(','));

        //finds date value in csv
        int check;
        check = date.find('-');

        //if date valid, gets date and interest
        if(check != string::npos)
        {
            double rateD;
            string rateS;
            rateS = looks.substr(looks.find(',') + 1,looks.size());
            rateD = strtod(rateS.c_str(), NULL);
            rateD = rateD*0.01;
            int_rate.push_back(rateD);
            int_date.push_back(date);
        }
    }
}

//retrieves sec and date values from csv file
void reader::sec_input(ifstream& filein)
{
    string looks;
    //run loop till end of file
    while(!filein.eof())
    {
        //gets line in csv
        getline(filein,looks);
        string date;
        date = looks.substr(0, looks.find(','));

        //finds date value in csv
        int check;
        check = date.find('-');

        //if date valid, gets date and interest
        if(check != string::npos)
        {
            double rateD;
            string rateS;
            rateS = looks.substr(looks.find(',') + 1,looks.size());
            rateD = strtod(rateS.c_str(), NULL);
            sec_close.push_back(rateD);
            sec_date.push_back(date);
        }
    }
}

//retrives all values from op csv file
void reader::op_input(ifstream& filein)
{
    string looks;
    getline(filein,looks); //skips first line

    //run loop till end of file
    while(!filein.eof())
    {
        //initializes variables
        string date, exdate, cp, k, bid, offer;

        //gets next line in csv
        getline(filein,looks);

        //creates stringstream using line
        std::istringstream iss(looks);

        //parses through each comma of iss
        getline(iss,date,',');
        getline(iss,exdate,',');
        getline(iss,cp,',');
        getline(iss,k,',');
        getline(iss,bid,',');
        getline(iss,offer,',');

        //vectors updated with value from each line
        op_date.push_back(date);
        op_exdate.push_back(exdate);
        op_cp.push_back(cp);
        double kd = strtod(k.c_str(), NULL);
        op_strike.push_back(kd);
        double bidd = strtod(bid.c_str(), NULL);
        op_bid.push_back(bidd);
        double offerd = strtod(offer.c_str(), NULL);
        op_offer.push_back(offerd);

    }
}

//trims the interest and csv file
void reader::trimmer(string t0, string t1, string texp,
    vector<double>& r_vec, vector<double>& s_vec,
    vector<string>& d_vec)
{
    //vector location values
    int vec_start;
    int vec_end;
    int vec_exp;

    //sec and interest are same length vecs
    //gets the data for the desired dates
    for(int i = 0; i < sec_date.size(); i++)
    {
        string check = sec_date[i];

        if(sec_date[i] == t0)
            vec_start = i;

        else if(sec_date[i] == t1)
            vec_end = i;

        //for expiration date
        //often times doesn't fall on market open day
        //for month
        else if(check.substr(5,2) == texp.substr(5,2))
            {
                //for day
                string d = check.substr(8,2);
                string e = texp.substr(8,2);
                double D = strtod(d.c_str(), NULL);
                double E = strtod(e.c_str(), NULL);
                if(d == e)
                {
                    vec_exp = i;
                    i = sec_date.size();
                }

                else if(D > E)
                {
                    vec_exp = i - 1;
                    i = sec_date.size();
                }
            }
    }

    //bumps the section of vector into trimmed vector
    vector<double>::const_iterator start;
    vector<double>::const_iterator end;
    start = int_rate.begin() + vec_start;
    end = int_rate.begin() + vec_end + 1;
    vector<double> rates(start,end);

    start = sec_close.begin() + vec_start;
    end = sec_close.begin() + vec_end + 1;
    vector<double> sec(start,end);

    vector<string> dates;
    for(int i = vec_start; i <= vec_end; i++)
        dates.push_back(sec_date[i]);

    //vectors pushed back to main
    s_vec = sec;
    r_vec = rates;
    d_vec = dates;

    //days to exp value in header public
    exp_days = (vec_exp - vec_start)/252.0;
    trade_days = (vec_end - vec_start)/252.0;
}

//gets bid value for a given day, exp, strike, option type
double reader::bid(string date, string texp, double K,
        string option)
{
    double B;
    for(int n = 0; n < op_date.size(); n++)
    {
        if(op_date[n] == date)
        {
            if(op_exdate[n] == texp)
            {
                if(op_cp[n] == option)
                {
                    if(op_strike[n] == K)
                    {
                        B = op_bid[n];
                        //kills for loop
                        n = op_date.size();
                    }
                }
            }
        }
    }
    return B;
}


//gets offer value for a given day, exp, strike, option type
double reader::offer(string date, string texp, double K,
        string option)
{
    double off;
    for(int n = 0; n < op_date.size(); n++)
    {
        if(op_date[n] == date)
        {
            if(op_exdate[n] == texp)
            {
                if(op_cp[n] == option)
                {
                    if(op_strike[n] == K)
                    {
                        off = op_offer[n];
                        //kills for loop
                        n = op_date.size();
                    }
                }
            }
        }
    }
    return off;
}
