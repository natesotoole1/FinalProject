#include "indexinterface.h"
//a
IndexInterface::IndexInterface()
{
    infoForIDs = vector<PageInfo>();



    // Probably don't need.
    currID = 0;
}

IndexInterface::~IndexInterface()
{

}

int IndexInterface::append_page_info(PageInfo* currInfo)
{
    infoForIDs.push_back(*currInfo);
    return infoForIDs.size()-1;
}

int IndexInterface::index_for_letter(char letter)
{
    // Get the raw ASCII value of the letter.
    int ascii = (int)letter;

    // If the letter is uppercase, get the lowercase equivalent
    // by increasing its ASCII value by 32.
    if (ascii > 64 && ascii < 91) ascii += 32;

    // a's ASCII value is 97; b's is 98, and so on...
    // To get the return value, subtract 96.
    ascii -= 96;
    return ascii;
}




