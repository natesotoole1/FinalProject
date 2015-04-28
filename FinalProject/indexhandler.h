#ifndef INDEXHANDLER_H
#define INDEXHANDLER_H

#include "docparser.h"

#include <vector>

using namespace std;

class IndexHandler
{
public:
    IndexHandler();
    ~IndexHandler();

    void index_corpus(bool asHashTable);

protected:


};

#endif // INDEXHANDLER_H
