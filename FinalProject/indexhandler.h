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

    void index_document(string filePath);

    void run_queries();

private:
    IndexInterface* index;
    DocParser* parser;
};

#endif // INDEXHANDLER_H
