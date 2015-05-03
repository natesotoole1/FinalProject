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

    else index = new AVLTreeInterface;
}

void IndexHandler::index_corpus()
{
    DocParser* parser = new DocParser;
    if (t == true){
        parser->index_document(index, string);
    }else{
        parser->index_document(index, string);
    }
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
