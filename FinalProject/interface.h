#ifndef INTERFACE_H
#define INTERFACE_H

#include <fstream>
#include <iostream>
#include <string>
#include <queryprocessor.h>
#include "indexhandler.h"

class Interface
{
public:
    Interface();
    Interface(IndexHandler* theHandler);
    void command(string, string);
    void search();
    void runAVL();
    void runHash();
    void runMaintenance();
    void setMode();
    void addFileToIndex(string);
    void clearIndex();
    string toLowerCase(string);
    void options();
    void quit();
    void permissionDenied(string);
    void getCommand();
    void reCommand();
    
private:
    int mode;
    bool built;
    QueryProcessor currQuery;
    bool endSearch;
    string modeStr;
    IndexHandler handler;
};

#endif // INTERFACE_H
