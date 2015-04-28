#ifndef APRNSATDOC_H
#define APRNSATDOC_H

#include <string>
#include <iostream>

#include "pageinfo.h"

using namespace std;

class AprnsAtDoc
{
public:
    AprnsAtDoc();
    AprnsAtDoc(string theDocTitle);
    ~AprnsAtDoc();

    void incr_freq();
    void set_next(AprnsAtDoc* theNext);

    string get_doc_title();
    AprnsAtDoc* get_next();

    void print();
private:
    // The number of times the term has appeared on the document.
    int freq;

    // The name of the document on which the term has appeared.
    PageInfo* info;

    // For the linked list functionality.
    AprnsAtDoc* next;
};

#endif // APRNSATDOC_H
