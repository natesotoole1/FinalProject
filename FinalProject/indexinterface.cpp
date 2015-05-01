#include "indexinterface.h"

IndexInterface::IndexInterface()
{
    infoForIDs = vector<PageInfo>();
}

IndexInterface::~IndexInterface()
{

}

int IndexInterface::append_page_info(PageInfo* currInfo)
{
    infoForIDs.push_back(*currInfo);
    return infoForIDs.size()-1;
}






