#ifndef INDEXINTERFACE_H
#define INDEXINTERFACE_H

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

#include "letterterms.h"

using namespace rapidxml;
using namespace std;

class IndexInterface
{
public:
    IndexInterface();
    ~IndexInterface();

    // HashTableIndex and AVLTreeIndex will handle new entries separately.
    void index_corpus();
    // Methods used inside index_doc
    void check_for_children(xml_node<>* currNode);
    void index_level(xml_node<>* currNode);
    void index_attributes(xml_attribute<>* currAttr);
    void index_node(xml_node<>* currNode);

    // For each node value (attributes included), find each term and
    // add it to the appropriate letter term for either the
    // HashTableIndex or the AVLTreeIndex.
    void add_all_appearances_for_value(string val);

    // Determine which LetterTerm should handle the appearance.
    // Pass the first letter of the term.  Returns  0 if the term
    // is a number, 1 for 'a', 2 for 'b', and so forth.
    int index_for_letter(char letter);

    // To be implemented separately in the HTI and ATI.
    virtual void add_appearance(int index, string term, string docTitle);

    void print_sample_data(string term);
protected:
    // For either the HTI or ATI, there will be 27 LetterTerms objects
    // holding the appearances of all terms beginning with each letter in
    // the alphabet.  letters[1] will hold all terms for words beginning
    // with 'a' and so forth; letters[0] will hold the stop words.
    LetterTerms* letters;

    string currDocTitle;

    int count;
};

#endif // INDEXINTERFACE_H
