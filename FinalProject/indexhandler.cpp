/* Search Engine Project
 * CSE 2341: Data Stuctures
 * 05/03/2015
 * Nate O'Toole
 * Kiko Whiteley
 **/
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
    if (asHashTable) {
        index = new HashTableInterface;
    }
    else{
        index = new AVLTreeInterface;
    }
}

void IndexHandler::read_file(string filePath)
{
    index->read_file(filePath);
}


void IndexHandler::run_queries()
{
    QueryProcessor processor = QueryProcessor();

    cout << "Enter your query:\n";
    string input;
    cin >> input;

    string query;
    getline(cin, query);

    query = input += query;

    processor.initiate_query(index, query);
}
