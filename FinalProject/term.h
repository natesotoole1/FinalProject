#ifndef TERM_H
#define TERM_H

#include <fstream>
#include <iostream>
#include <string>
#include <unordered_map>
#include <utility>
#include <vector>

#include "aprnsatpage.h"

using namespace std;

typedef pair<int, int> pageAprns;

class Term
{
public:
    Term();
    ~Term();

    Term(string name, int currID);

    void add_aprn_at_page(int currID);

    string get_name();
    Term* get_next();

    void set_next(Term* theNext);

    void write_term(ofstream& persistence);
private:
    string name;

    // For the linked list functionality of each TermBucket.
    // Only used in HashTableIndex.
    Term* next;

    // The number of unique documents on which the term has appeared.
    int spread;

    int totalFreq;

    // Holds the IDs of pages on which it appeared.
    unordered_map<int, pageAprns> pagesAppearedOn;
};

#endif // TERM_H
