#ifndef TERM_H
#define TERM_H

#include <string>
#include <vector>
#include <iostream>

#include "aprnsatpage.h"

using namespace std;

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

    void print_aprns();
private:
    string name;

    int totalFreq;

    // For the linked list functionality of each TermBucket.
    // Only used in HashTableIndex.
    Term* next;

    // Holds the IDs of pages on which it appeared.
    vector<AprnsAtPage> pagesAppearedOn;
};

#endif // TERM_H
