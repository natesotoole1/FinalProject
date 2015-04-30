#ifndef INDEXHANDLER_H
#define INDEXHANDLER_H

#include "docparser.h"
#include "indexinterface.h"

#include <vector>

using namespace std;

class IndexHandler
{
public:
    IndexHandler();
    ~IndexHandler();
    IndexHandler(bool asHashTable);

    void index_corpus();

private:
    IndexInterface* index;
};

#endif // INDEXHANDLER_H
