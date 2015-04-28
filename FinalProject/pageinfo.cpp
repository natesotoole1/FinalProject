#include "pageinfo.h"

PageInfo::PageInfo()
{

}

PageInfo::~PageInfo()
{

}

string PageInfo::get_contributor()
{
    return contributorNameOrIP;
}

string PageInfo::get_timestamp()
{
    return timestamp;
}

string PageInfo::get_title()
{
    return title;
}

void PageInfo::set_contributor(string theInfo)
{
    contributorNameOrIP = theInfo;
}

void PageInfo::set_timestamp(string theTimestamp)
{
    timestamp = theTimestamp;
}

void PageInfo::set_title(string theTitle)
{
    title = theTitle;
}
