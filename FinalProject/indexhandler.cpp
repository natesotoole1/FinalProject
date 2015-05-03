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

void IndexHandler::index_corpus(bool t)
{
    DocParser* parser = new DocParser;
    if (t == true){
        string filePath = "WikiBooks.xml";
        parser->index_document(index, filePath);
    }else{
        string filePath = "";
        parser->index_document(index, filePath);
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
