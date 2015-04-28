#include "term.h"

Term::Term()
{
    name = "";
    next = NULL;
}

Term::~Term()
{

}

Term::Term(string theName, string docTitle)
{
    name = theName;
    totalAprns = 1;
    root = new AprnsAtDoc(docTitle);
    next = NULL;
}

void Term::add_appearance_at_doc(string docTitle)
{
    // If the term has already appeared on the current doc,
    // merely increment that AprnsAtDoc's frequency by 1.

    AprnsAtDoc* newAprn = new AprnsAtDoc(docTitle);

    if (!root)
        // This shouldn't happen (because this can only be called by Term objects
        // already constructed), but checking prevents potential errors.
    {
        root = newAprn;
        totalAprns = 1;
    }

    else
    {
        // Check each node in the linked list.  If the docTitle is
        // already in the list of documents appeared on, increase that
        // AprnsAtDoc's frequency by 1.  Otherwise, create a new AprnsAtDoc
        // object from docTitle (with frequency of 1).
        AprnsAtDoc* curr = root;
        if (curr->get_doc_title().compare(docTitle) == 0)
        {
            curr->incr_freq();
            ++totalAprns;
            return;
        }
        while (curr->get_next())
        {
            curr = curr->get_next();
            if (curr->get_doc_title().compare(docTitle) == 0)
            {
                curr->incr_freq();
                ++totalAprns;
                return;
            }
        }

        // By this point, the docTitle wasn't in the list, append a new AprnsAtDoc
        // object to the end of the list.
        curr->set_next(newAprn);
        ++totalAprns;
    }


    // Otherwise, push make a new AprnsAtDoc object with the
    // current info and push it back to docsAppearedOn.
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

void Term::print_aprns()
{
    if (!root) return;

    AprnsAtDoc* curr = root;
    curr->print();
    while (curr->get_next())
    {
        curr = curr->get_next();
        curr->print();
    }
}
