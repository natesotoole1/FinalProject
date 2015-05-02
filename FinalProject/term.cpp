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
    totalFreq = 0;
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
    /*
    spread = aprns.size();
    for (auto& aprn : aprns)
    {
        totalFreq+=aprn.second;
    }
    */
/*
    persistence<<"\""<<name<<"\" appeared "<<totalFreq<<" times across "<<spread<<" documents:";
    for (auto& aprn : aprns)
    {
        persistence<<" "<<aprn.second<<" times at doc id "<<aprn.first<<";";
    }
    persistence<<endl;
*/

    persistence<<"! "<<name;
    for (auto& aprn : aprns)
    {
        persistence<<" "<<aprn.second<<" "<<aprn.first;
    }
    persistence<<endl;
}
