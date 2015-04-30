#ifndef HASHTABLEINTERFACE_H
#define HASHTABLEINTERFACE_H

#include "hashtableindex.h"
#include "indexinterface.h"
#include "term.h"

#include <fstream>
#include <iostream>
#include <string>

// RapidXML includes
#include <rapidxml.hpp>
#include <rapidxml_print.hpp>
#include <rapidxml_utils.hpp>

using namespace rapidxml;
using namespace std;

class HashTableInterface : public IndexInterface
{
public:
    HashTableInterface();
    ~HashTableInterface();

    Term* find(string term);
};

#endif // HASHTABLEINTERFACE_H
