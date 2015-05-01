#ifndef HASHTABLEINTERFACE_H
#define HASHTABLEINTERFACE_H

#include "docparser.h"
#include "hashtableindex.h"
#include "indexinterface.h"
#include "term.h"

#include <fstream>
#include <iostream>
#include <string>
#include <unordered_map>

using namespace std;

typedef unordered_map<int, int> pageMap;

class HashTableInterface : public IndexInterface, public DocParser
{
public:
    HashTableInterface();
    ~HashTableInterface();

};

#endif // HASHTABLEINTERFACE_H
