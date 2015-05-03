#ifndef INTERFACE_H
#define INTERFACE_H

#include <algorithm>
#include <chrono>
#include <fstream>
#include <iostream>
#include <string>
#include <sstream>
#include <stdexcept>

#include "indexhandler.h"
#include "queryprocessor.h"

using namespace std;

class Interface
{
public:

//    Interface();
    Interface(IndexHandler& theHandler);

    void command(string, string);
    void search();
    void run_AVL();
    void run_hash();
    void run_maintenance();
    void set_mode();
    void add_file_to_index(string);
    void clear_index();
    string toLowerCase(string);
    void run_interactive();
    void quit();
    void permissionDenied(string);
    void get_command();
    void re_command();
    void choose_structure();


private:

    int mode;
    bool built;
    QueryProcessor currQuery;
    bool endSearch;
    bool endProgram;
    string dsBuilt;
    string modeStr;
    IndexHandler& handler;
};





#endif // INTERFACE_H
