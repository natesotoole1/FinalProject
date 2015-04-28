#include <chrono>
#include <time.h>
#include <iostream>
#include <string>

#include "hashtableindex.h"
#include "indexinterface.h"

using namespace std;

int main()
{
    // Use clock_t objects to track the program's total runtime.
    clock_t start, end;
    // Get the number of clicks already used by the program.
    start = clock();

    // Create an empty InvertedIndex and traverse the WikiDump,
    // inserting found words into the HashTableIndex.
    IndexInterface* hti = new HashTableIndex;
    hti->index_corpus();

    // Fetch some sample data from the inverted index.
    hti->print_sample_data("carrots");

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
