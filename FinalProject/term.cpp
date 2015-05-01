#include "term.h"

Term::Term()
{
    totalFreq = 0;
    spread = 0;
    name = "a";
}

Term::~Term()
{

}

Term::Term(string theName, pageMap theAprns)
{
    next = NULL;
    name = theName;
    for (auto& aprn : theAprns)
    {
        // First is the docID, second is the frequency.
        aprns.emplace(make_pair(aprn.first, aprn.second));
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
    persistence<<name<<" "<<totalFreq<<"~"<<spread;
    for (auto& aprn : aprns)
    {
        persistence<<aprn.second<<"@"<<aprn.first;
    }
    persistence<<endl;
/*
    cout<<"NEW TERM\n";
    cout<<name<<" "<<totalFreq<<"~"<<spread;
    for (pageMap::iterator it = aprns.begin(); it != aprns.end(); ++it)
    {
        cout<<" "<<it->second<<"@"<<it->first;
    }
    cout<<endl;*/
}
