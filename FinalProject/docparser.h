#ifndef DOCPARSER_H
#define DOCPARSER_H

// RapidXML includes
#include <rapidxml.hpp>
#include <rapidxml_print.hpp>
#include <rapidxml_utils.hpp>
// Apparently, including the header below creates problems.
// #include <rapidxml_iterators.hpp>

#include <algorithm>
#include <cctype>
#include <chrono>
#include <fstream>
#include <sstream>
#include <iostream>
#include <string>
#include <unordered_map>

#include "indexinterface.h"
#include "pageinfo.h"
#include "porter2_stemmer.h"
#include "timer.h"

class IndexInterface;

using namespace rapidxml;
using namespace std;

typedef unordered_map<int, int> pageMap;
typedef unordered_map<string, string> stopWordMap;
typedef unordered_map<string, pageMap> termMap;

class DocParser // : public IndexInterface
{
public:
    //DocParser();
    ~DocParser();
    DocParser(IndexInterface& theIndex);

    string clean_term(string term);

    // Determine which LetterTerm should handle the appearance.
    // Pass the first letter of the term.  Returns  0 if the term
    // is a number, 1 for 'a', 2 for 'b', and so forth.
    int index_for_letter(char letter);

    void push_allTerms_to_ii();

    void read_page(xml_node<>* currNode, bool readText);
    void read_text(xml_node<>* currNode);

    void init_file_page_infos(xml_node<>* currNode, bool readText);

    void read_file(string filePath);

    bool is_stop_word(string term);

private:
    termMap allTerms;

    IndexInterface& index;

    stopWordMap stopWords;

    int count = 0;
    // trivial

    string currWord;
    string currContent;
    string currContributorNameOrIP;
    string currTimestamp;
    string currTitle;
};

inline int is_not_alpha(char c)
{
    return !isalpha(c);
}

#endif // DOCPARSER_H
