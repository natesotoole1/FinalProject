#include "term.h"

Term::Term()
{
    /*pagesAppearedOn = vector<AprnsAtPage>();

    name = "";
    next = NULL;*/
}

Term::~Term()
{

}

Term::Term(string theName, int currID)
{
    /*name = theName;
    totalFreq = 1;
    AprnsAtPage* firstAprn = new AprnsAtPage(currID);
    pagesAppearedOn.push_back(*firstAprn);
    next = NULL;*/
}

void Term::add_aprn_at_page(int currID)
{
    /*
    // Check if currID is already in pagesAppearedOn.
    int size = pagesAppearedOn.size();
    for (int i=0; i<size; ++i)
    {
        // If the term has already appeared on the current doc,
        // merely increment that AprnsAtDoc's frequency by 1.
        if (pagesAppearedOn[i].get_infoID() == currID)
        {
            pagesAppearedOn[i].incr_freq();
            ++totalFreq;
            return;
        }
    }

    // By this point, currID wasn't pagesAppearedOn,
    // so append the new AprnsAtDoc object to the end of the list.
    AprnsAtPage* newAprn = new AprnsAtPage(currID);
    pagesAppearedOn.push_back(*newAprn);
    ++totalFreq;*/
}

string Term::get_name()
{
    return name;
}

Term* Term::get_next()
{
    return next;
}

void Term::set_next(Term* theNext)
{
    next = theNext;
}

void Term::write_term(ofstream &persistence)
{
    /*spread = pagesAppearedOn.size();

    persistence<<name<<" "<<totalFreq<<"~"<<spread;
    int size = pagesAppearedOn.size();
    for (int i=0; i<size; ++i)
    {
        pagesAppearedOn[i].write_aprns(persistence);
    }
    persistence<<endl;*/
}
