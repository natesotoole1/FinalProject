#include "indexinterface.h"

IndexInterface::IndexInterface()
{
    letters = new LetterTerms[27];
    currDocTitle = "Before Main Page";
    count = 0;
}

IndexInterface::~IndexInterface()
{

}

void IndexInterface::add_all_appearances_for_value(string value)
{
    // To save overhead.
    int size = value.size();

    // To store the current term to insert in the inverted index.
    string currTerm = "";

    // Iterate through each char in the value string.
    for (int pos=0; pos < size; ++pos)
    {
        // The value could contain several sentences, perhaps including many strange
        // characters.  To find each valid "term" to push to the inverted index,
        // find groups of adjacent chars that are all either letters or numbers.
        // Ignore all other chars.

        // Get the ascii value of the current char.
        int ascii = (int)value.at(pos);

        // If it's a letter, push it back to newTerm.
        if ((ascii > 64 && ascii < 91)
                || (ascii > 96 && ascii < 123)
                // Values for numbers, now ignored.
                /* || (ascii > 47 && ascii < 58)*/) currTerm.append(value.substr(pos, 1));

        // If it's a not a letter (i.e. it's a useless char),
        // end the term if and insert it in the inverted index
        // if newTerm has any chars in it.  Otherwise, ignore the char.
        else if (currTerm.size())
        {
            add_appearance(index_for_letter(currTerm.front()), currTerm, currDocTitle);
            currTerm.clear();
        }
    }
    // If the end of the value string is reached and there's a new term to
    // insert in the inverted index, do so.
    if (currTerm.size()) add_appearance(index_for_letter(currTerm.front()), currTerm, currDocTitle);
}

int IndexInterface::index_for_letter(char letter)
{
    // Get the raw ASCII value of the letter.
    int ascii = (int)letter;

    // If the letter is uppercase, get the lowercase equivalent
    // by increasing its ASCII value by 32.
    if (ascii > 64 && ascii < 91) ascii += 32;

    // a's ASCII value is 97; b's is 98, and so on...
    // To get the return value, subtract 96.
    ascii -= 96;
    return ascii;
}

void IndexInterface::index_corpus()
{
    letters[0].add_all_stop_words();

    // Use RapidXML's "parse" function to make all data
    // accessible via nodes, attributes, values, etc.
    file<> secFile("Order.xml");
    xml_document<> secDoc;
    secDoc.parse<0>(secFile.data());

    // Index the root level of the WikiDump (this will fetch all terms).
    xml_node<>* startNode = secDoc.first_node();
    index_level(startNode);
}

void IndexInterface::index_level(xml_node<>* currNode)
{
    // Index first node at this level,
    index_node(currNode);
    // Then recursively check its children if it has any.
    check_for_children(currNode);

    // Index remaining nodes at this level.
    while (currNode->next_sibling())
    {
        currNode = currNode->next_sibling();
        index_node(currNode);
        check_for_children(currNode);
    }
    cout<<"Fin "<<count<<endl;
    ++count;
    if (count == 16)
    {
        cout<<"stop\n";
    }
}

void IndexInterface::check_for_children(xml_node<>* currNode)
{
    if (currNode->first_node())
    {
        // If the node one level deeper has a name (and is thus
        // worth checking), index_level for that deeper level.
        string nextName = currNode->first_node()->name();
        if (nextName != "") index_level(currNode->first_node());
    }
}

void IndexInterface::index_attributes(xml_attribute<>* currAttr)
{
    // Index the first attribute.
    add_all_appearances_for_value(currAttr->value());

    // Loop through and index remaining attributes.
    while (currAttr->next_attribute())
    {
        currAttr = currAttr->next_attribute();
        // Fucntioanlity for attr.
        // add_all_appearances_for_value();
    }
}

void IndexInterface::index_node(xml_node<>* currNode)
{
    // Check if the node has attributes and index them if so.
    if (currNode->first_attribute()) index_attributes(currNode->first_attribute());

    // If this element is the document title, update the current document title.
    string name = currNode->name();
    if (name.compare("title") == 0)
    {
        // cout<<"Found new title: "<<currNode->value()<<endl;
        currDocTitle = currNode->value();
    }

    string value = currNode->value();
    // Only do anyything if the value has contents.
    if (value != "") add_all_appearances_for_value(value);
}


void IndexInterface::print_sample_data(string term)
{
    cout<<"Terms with the same hash value as "<<term<<" are:\n";

    // Call print_sample for the corresponding LetterTerms object.
    letters[index_for_letter(term.front())].print_sample(term);
}
