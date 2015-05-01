#ifndef INDEXHANDLER_H
#define INDEXHANDLER_H

#include "avltreeinterface.h"
#include "docparser.h"
#include "hashtableindex.h"
#include "hashtableinterface.h"
#include "indexinterface.h"
#include "queryprocessor.h"

#include <vector>

using namespace std;

class IndexHandler
{
public:
    IndexHandler();
    ~IndexHandler();
    IndexHandler(bool asHashTable);

    void index_corpus();

    void run_queries();

private:
    IndexInterface* index;
};

#endif // INDEXHANDLER_H
