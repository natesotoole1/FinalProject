#ifndef INTERFACE_H
#define INTERFACE_H
#include <fstream>
#include <iostream>
#include <string>
#include <queryprocessor.h>
#include "indexhandler.h"
#include "hashtableinterface.h"
#include "avltreeinterface.h"

using namespace std;
class Interface
{
public:
    Interface();
    void command();
    void search(string);
    void runAVL();
    void runHash();
    void runMaintenance();
    void setMode();
    void addFileToIndex(string);
    void clearIndex();
    void lowerCase(string);
    void options();
    void quit();
private:
    int mode;
    bool built;
    QueryProcessor currQuery;
    IndexHandler* index;
    bool endPro = false;
    string strMode;

};

#endif // INTERFACE_H
