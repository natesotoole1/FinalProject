#include "indexhandler.h"

IndexHandler::IndexHandler()
{

}

IndexHandler::~IndexHandler()
{

}

IndexHandler::IndexHandler(bool asHashTable)
{
    if (asHashTable) index = new HashTableIndex;
    // else index = new AVLTreeIndex;
}

void IndexHandler::index_corpus(bool asHashTable)
{
    DocParser* parser = new DocParser;
    parser->index_corpus(asHashTable);
}
