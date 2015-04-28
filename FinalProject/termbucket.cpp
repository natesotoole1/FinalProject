#include "termbucket.h"

TermBucket::TermBucket()
{
    root = NULL;
}

TermBucket::~TermBucket()
{

}

void TermBucket::add_term(string term, string docTitle)
{
    Term* newTerm = new Term(term, docTitle);
    if (!root) root = newTerm;

    else {

        Term* curr = root;
        if (curr->get_name().compare(term) == 0)
        {
            curr->add_appearance_at_doc(docTitle);
            return;
        }
        while (curr->get_next())
        {
            curr = curr->get_next();
            if (curr->get_name().compare(term) == 0)
            {
                curr->add_appearance_at_doc(docTitle);
                return;
            }
        }

        // By this point, the term hasn't already appeared so
        // make a new term.
        curr->set_next(newTerm);
    }

    cout<<"Added "<<term<<" at "<<docTitle<<endl;
}

bool TermBucket::has_word(string term)
{
    if (!root) return false;

    // Iterate through the linked list at this bucket,
    // checking each word for a match.
    Term* curr = root;
    if (curr->get_name().compare(term) == 0) return true;
    while (curr->get_next())
    {
        curr = curr->get_next();
        if (curr->get_name().compare(term) == 0) return true;
    }

    // By this point, it's checked every term (with no matches),
    // so return false.
    return false;
}

void TermBucket::print()
{
    if (!root) return;

    // Iterate through the linked list and print each term.
    Term* curr = root;
    cout<<"Bucket term #1 is "<<curr->get_name()<<endl;
    curr->print_aprns();
    int count = 2;
    while (curr->get_next())
    {
        curr = curr->get_next();
        cout<<"Bucket term #"<<count<<" is "<<curr->get_name()<<endl;
        curr->print_aprns();
        ++count;
    }
}
