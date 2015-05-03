#include <chrono>
#include <time.h>
#include <iostream>
#include <string>

#include "indexhandler.h"
#include "interface.h"

using namespace std;

int main()
{
    // Use clock_t objects to track the program's total runtime.
    clock_t start, end;
    // Get the number of clicks already used by the program.
    start = clock();

    // Before activating the interface, read the WikiBooks file into a hash
    // table to write the persistence file.
    IndexHandler* handler = new IndexHandler(true);
    handler->index_document("WikiBooks.xml");

    Interface* ui = new Interface(handler);

    handler->run_queries();











    // Get the number of clicks used up to now.
    end = clock();

    // The total number of seconds elapsed is the difference in number of
    // clicks used since the very beginning and end of the program divided
    // by the number of clicks used in a real second.
    float timeElapsed = ((float)end - (float)start) / CLOCKS_PER_SEC;

    std::cout<<"A total of "<<timeElapsed<<" seconds were used.";

    return 0;
}
