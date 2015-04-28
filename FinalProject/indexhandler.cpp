#include "indexhandler.h"

IndexHandler::IndexHandler()
{

}

IndexHandler::~IndexHandler()
{

}

void IndexHandler::index_corpus(bool asHashTable)
{
    DocParser* parser = new DocParser;
    parser->index_corpus(asHashTable);
}
