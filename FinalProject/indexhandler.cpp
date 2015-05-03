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
    parser = new DocParser;
    if (asHashTable) index = new HashTableInterface;
    else index = new AVLTreeInterface;
}

void IndexHandler::index_document(string filePath)
{
    parser->index_document(index, filePath);
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
