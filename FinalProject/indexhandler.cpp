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
    else
    {
        cout<<"here";
        index = new AVLTreeInterface;
    }
}

void IndexHandler::index_corpus()
{
    DocParser* parser = new DocParser;
    parser->index_corpus(index);
}


void IndexHandler::run_queries()
{
    QueryProcessor processor = QueryProcessor();

    cout << "Enter your query:";
    string input;
    cin >> input;

    string query;
    getline(cin, query);

    query = input += query;

    processor.initiate_query(index, query);
}
