#ifndef TERM_H
#define TERM_H

#include <string>
#include <vector>

#include "aprnsatdoc.h"

using namespace std;

class Term
{
public:
    Term();
    ~Term();

    Term(string name, string docTitle);

    void add_appearance_at_doc(string docTitle);

    string get_name();
    Term* get_next();

    void set_next(Term* theNext);

    void print_aprns();
private:
    string name;

    // For the linked list functionality of each TermBucket.
    Term* next;

    // For linked list functionality.
    AprnsAtDoc* root;
};

#endif // TERM_H
