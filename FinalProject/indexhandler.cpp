#include "indexhandler.h"

IndexHandler::IndexHandler()
{
    index = new IndexInterface;
}

IndexHandler::~IndexHandler()
{

}

IndexHandler::IndexHandler(bool asHashTable)
{
    if (asHashTable) index = new HashTableInterface;

    /***** NEED TO CHANGE THIS TO AVLTreeIndex *******/
    else index = new HashTableInterface;
}

void IndexHandler::index_corpus()
{
    DocParser* parser = new DocParser;
    parser->index_corpus(index);
}


