#ifndef APRNSATPAGE_H
#define APRNSATPAGE_H

#include <string>
#include <iostream>

#include "pageinfo.h"

using namespace std;

class AprnsAtPage
{
public:
    AprnsAtPage();
    AprnsAtPage(int currID);
    ~AprnsAtPage();

    void incr_freq();

    int get_infoID();

    void print();
private:
    // The number of times the term has appeared on the page.
    int freq;

    // The corresponding ID number for the appearances.
    int infoID;
};

#endif // APRNSATPAGE_H
