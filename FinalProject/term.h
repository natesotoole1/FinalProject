#ifndef TERM_H
#define TERM_H

#include <fstream>
#include <iostream>
#include <string>
#include <unordered_map>
#include <utility>
#include <vector>

using namespace std;

typedef unordered_map<int, int> pageMap;

class Term
{
public:
    Term();
    ~Term();

    Term(string theName, pageMap theAprns);

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
    pageMap aprns;
};

#endif // TERM_H
