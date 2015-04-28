#ifndef DOCPARSER_H
#define DOCPARSER_H

// RapidXML includes
#include <rapidxml.hpp>
#include <rapidxml_print.hpp>
#include <rapidxml_utils.hpp>
// Apparently, including the header below creates problems.
// #include <rapidxml_iterators.hpp>

#include <fstream>
#include <sstream>
#include <iostream>
#include <string>

#include "avltreeindex.h"
#include "hashtableindex.h"
#include "indexinterface.h"
#include "letterterms.h"
#include "pageinfo.h"

using namespace rapidxml;
using namespace std;

class DocParser
{
public:
    DocParser();

    // HashTableIndex and AVLTreeIndex will handle new entries separately.
    void index_corpus(bool asHashTable);

    // Determine which LetterTerm should handle the appearance.
    // Pass the first letter of the term.  Returns  0 if the term
    // is a number, 1 for 'a', 2 for 'b', and so forth.
    int index_for_letter(char letter);

    void index_page(xml_node<>* currNode, IndexInterface* theIndex);
    void index_text(xml_node<>* currNode, int currID, IndexInterface* theIndex);


};

#endif // DOCPARSER_H
