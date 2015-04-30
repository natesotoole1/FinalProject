#include "term.h"

Term::Term()
{
    name = "";
    next = NULL;
}

Term::~Term()
{

}

Term::Term(string theName, pageMap theAprns)
{
    next = NULL;
    name = theName;
    spread = theAprns.size();
    totalFreq = 0;
    for (auto& aprn : theAprns)
    {
        // First is the docID, second is the frequency.
        aprns.emplace(make_pair(aprn.first, aprn.second));
        totalFreq += aprn.second;
    }
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
    /*
    persistence<<name<<" "<<totalFreq<<"~"<<spread;
    for (auto aprn : aprns)
    {
        persistence<<aprn.second<<"@"<<aprn.first;
    }
    persistence<<endl;*/

    cout<<name<<" "<<totalFreq<<"~"<<spread;
    for (auto& aprn : aprns)
    {
        cout<<aprn.second<<"@"<<aprn.first;
    }
    cout<<endl;
}
