#include <chrono>
#include <time.h>
#include <iostream>
#include <string>

#include "indexhandler.h"

using namespace std;

int main()
{
    // Use clock_t objects to track the program's total runtime.
    clock_t start, end;
    // Get the number of clicks already used by the program.
    start = clock();

    IndexHandler* handler = new IndexHandler;

    // Index the corpus into a HashTableIndex
    handler->index_corpus(true);

    cout<<"The inverted index has been loaded into a hash table by default.\n"<<
          "To load it into an AVL tree, press 1.  Otherwise, press any key.\n";
    char choice;
    cin>>choice;
    if (choice == '1')
    {
        /**********load into AVL***********/
    }

    cout<<"What is your query?\n";
    string query;


    // cin the input; call index_corpus(false) if it's 1.

    // Fetch some sample data from the inverted index.
    //hti->print_sample_data("carrots");

    // Get the number of clicks used up to now.
    end = clock();

    // The total number of seconds elapsed is the difference in number of
    // clicks used since the very beginning and end of the program divided
    // by the number of clicks used in a real second.
    float timeElapsed = ((float)end - (float)start) / CLOCKS_PER_SEC;

    std::cout<<"A total of "<<timeElapsed<<
               " seconds were used to parse the WikiDump and fetch sample data.\n";

    return 0;
}
