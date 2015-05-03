/* Search Engine Project
 * CSE 2341: Data Stuctures
 * 05/03/2015
 * Nate O'Toole
 * Kiko Whiteley
 **/
#include "indexhandler.h"

/*IndexHandler::IndexHandler() : index(*(new IndexInterface))
{

}*/

IndexHandler::~IndexHandler()
{

}

IndexHandler::IndexHandler(bool asHashTable)
{
    if (asHashTable) index = HashTableInterface();
    else index = AVLTreeInterface();
}

void IndexHandler::read_file(string filePath)
{
    index->read_file(filePath);
}

void IndexHandler::run_queries(string query)
{
    QueryProcessor processor = QueryProcessor();
    processor.initiate_query(query);
}
