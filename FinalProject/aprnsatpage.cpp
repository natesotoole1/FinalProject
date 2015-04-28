#include "aprnsatpage.h"

AprnsAtPage::AprnsAtPage()
{
    infoID = freq = 0;
}

AprnsAtPage::AprnsAtPage(int currID)
{
    infoID = currID;
    freq = 1;
}

AprnsAtPage::~AprnsAtPage()
{

}

void AprnsAtPage::incr_freq()
{
    ++freq;
}

int AprnsAtPage::get_infoID()
{
    return infoID;
}

void AprnsAtPage::print_info()
{
    cout<<"On doc ID "<<infoID<<" "<<freq<<" times.\n";
}
