#ifndef APRNSATPAGE_H
#define APRNSATPAGE_H

#include <fstream>
#include <iostream>
#include <string>

using namespace std;

class AprnsAtPage
{
public:
    AprnsAtPage();
    AprnsAtPage(int currID);
    ~AprnsAtPage();

    void incr_freq();

    int get_infoID();

    void write_aprns(ofstream& persistence);
private:
    // The number of times the term has appeared on the page.
    int freq;

    // The corresponding ID number for the appearances.
    int infoID;
};

#endif // APRNSATPAGE_H
