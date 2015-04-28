#include "aprnsatdoc.h"

AprnsAtDoc::AprnsAtDoc()
{
    docTitle = "";
    freq = 0;
}

AprnsAtDoc::AprnsAtDoc(string theDocTitle)
{
    docTitle = theDocTitle;
    freq = 1;
}

AprnsAtDoc::~AprnsAtDoc()
{

}

void AprnsAtDoc::incr_freq()
{
    ++freq;
}

void AprnsAtDoc::set_next(AprnsAtDoc*theNext)
{
    next = theNext;
}

string AprnsAtDoc::get_doc_title()
{
    return docTitle;
}

AprnsAtDoc* AprnsAtDoc::get_next()
{
    return next;
}

void AprnsAtDoc::print()
{
    cout<<"On "<<docTitle<<" "<<freq<<" times.\n";
}
