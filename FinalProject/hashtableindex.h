#ifndef HASHTABLEINDEX_H
#define HASHTABLEINDEX_H

#include "indexhandler.h"
#include "indexinterface.h"
#include "letterterms.h"
#include "termbucket.h"


#include "porter2_stemmer.h"

#include <iostream>
#include <string>

// RapidXML includes
#include <rapidxml.hpp>
#include <rapidxml_print.hpp>
#include <rapidxml_utils.hpp>

using namespace rapidxml;
using namespace std;

class HashTableIndex : public IndexInterface
{
public:
    HashTableIndex();
    ~HashTableIndex();
};

#endif // HASHTABLEINDEX_H
