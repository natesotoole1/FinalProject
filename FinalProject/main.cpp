#include <chrono>
#include <time.h>
#include <iostream>
#include <string>

#include "indexhandler.h"
#include "queryprocessor.h"

using namespace std;

typedef unordered_map<int, int> pageMap;

typedef unordered_map<string, pageMap> termMap;

int main()
{
    /*termMap terms;

    pageMap p;
    p.insert(make_pair(1,8));

    terms.emplace("newTerm", p);

    cout<<"IT IS "<<terms.at("newTerm").at(1)<<endl;
    // prints 8.
*/

    // Use clock_t objects to track the program's total runtime.
    clock_t start, end;
    // Get the number of clicks already used by the program.
    start = clock();

    // Index the corpus into a HashTableIndex.
    IndexHandler* handler = new IndexHandler(true);
    handler->index_corpus();
    /*
    cout<<"The inverted index has been loaded into a hash table by default.\n"<<
          "To load it into an AVL tree, press 1.  Otherwise, press any key.\n";
    char choice;
    cin>>choice;
    if (choice == '1')
    {
        // load into AVL
    }

    QueryProcessor* processor = new QueryProcessor;
    //Results* rankedResults;
*/
    // Get the number of clicks used up to now.
    end = clock();

    // The total number of seconds elapsed is the difference in number of
    // clicks used since the very beginning and end of the program divided
    // by the number of clicks used in a real second.
    float timeElapsed = ((float)end - (float)start) / CLOCKS_PER_SEC;

    std::cout<<"A total of "<<timeElapsed<<" seconds were used.";

    return 0;
}
