//Austin Griffith
//October 15, 2017
//ISYE 6767

#ifndef READER_H
#define READER_H

#include <fstream>
#include <iostream>
#include <stdio.h>
#include <vector>

using namespace std;

class reader{

public:
    //interest csv
    vector<double> int_rate;
    vector<string> int_date;

    //sec csv
    vector<string> sec_date;
    vector<double> sec_close;

    //op csv
    vector<string> op_date;
    vector<string> op_exdate;
    vector<string> op_cp;
    vector<double> op_strike;
    vector<double> op_bid;
    vector<double> op_offer;

    //days to expiration
    double exp_days;
    double trade_days;

    reader();
    //csv readers
    void interest_input(ifstream& filein);
    void sec_input(ifstream& filein);
    void op_input(ifstream& filein);
    void trimmer(string t0, string t1, string texp,
        vector<double>& r_vec, vector<double>& s_vec,
        vector<string>& d_vec);
    double bid(string date, string texp, double K,
        string option);
    double offer(string date, string texp, double K,
        string option);
};

#endif
