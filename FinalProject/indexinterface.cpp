#include "indexinterface.h"

IndexInterface::IndexInterface()
{
    letters = new LetterTerms[27];
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
    // accessible via nodes and values.
    file<> theFile("WikiBooks.xml");
    xml_document<> doc;
    doc.parse<0>(theFile.data());

    // Find the first node with name 'mediawiki'.
    xml_node<>* currNode = doc.first_node();

    // Go to 'siteinfo'.
    currNode = currNode->first_node();

    // Go to the first 'page'.
    currNode = currNode->next_sibling();

    index_page(currNode);

    while (currNode->next_sibling())
    {
        currNode = currNode->next_sibling();
        index_page(currNode);
    }

}

void IndexInterface::index_page(xml_node<>* currNode)
{
    PageInfo* currInfo = new PageInfo;
    string currName;
    string currValue;

    // Get the page title.
    currNode = currNode->first_node();
    currValue = currNode->value();
    currInfo->set_title(currValue);

    // Get the timestamp.

    // Go to 'revision' node.
    currNode = currNode->next_sibling();
    currName = currNode->name();
    while (currName.compare("revision") != 0)
    {
        currNode = currNode->next_sibling();
        currName = currNode->name();
    }
    // Move one level inward.
    currNode = currNode->first_node();
    // Go to 'timestamp' node.
    currName = currNode->name();
    while (currName.compare("timestamp") != 0)
    {
        currNode = currNode->next_sibling();
        currName = currNode->name();
    }
    currValue = currNode->value();
    currInfo->set_timestamp(currValue);

    // Get contributor name.

    // Go to 'contributor' node.
    currNode = currNode->next_sibling();
    currName = currNode->name();
    while (currName.compare("contributor") != 0)
    {
        currNode = currNode->next_sibling();
        currName = currNode->name();
    }
    // Get contributor's username or IP.
    currValue = currNode->first_node()->value();
    currInfo->set_contributor(currValue);

    // Go to 'text' node.
    currNode = currNode->next_sibling();
    currName = currNode->name();
    while (currName.compare("text") != 0)
    {
        currNode = currNode->next_sibling();
        currName = currNode->name();
    }

    // Pass the current node to index_text to find all terms in
    // this page's text.
    index_text(currNode, currInfo);
}

void IndexInterface::check_for_children(xml_node<>* currNode)
{
    if (currNode->first_node())
    {
        // If the node one level deeper has a name (and is thus
        // worth checking), index_level for that deeper level.
        string nextName = currNode->first_node()->name();
        if (nextName != "") index_page(currNode->first_node());
    }
}

void IndexInterface::index_attributes(xml_attribute<>* currAttr)
{
    // Can probably ignore attributes altogether.

    /*
    // Index the first attribute.
    add_all_appearances_for_value(currAttr->value());

    // Loop through and index remaining attributes.
    while (currAttr->next_attribute())
    {
        currAttr = currAttr->next_attribute();
        // Fucntioanlity for attr.
        // add_all_appearances_for_value();
    }*/
}

void IndexInterface::index_text(xml_node<>* currNode, PageInfo *currInfo)
{
    string text = currNode->value();

    // To save overhead.
    int size = text.size();

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
        int ascii = (int)text.at(pos);

        // If it's a letter, push it back to newTerm.
        if ((ascii > 64 && ascii < 91)
                || (ascii > 96 && ascii < 123)
                // Values for numbers, now ignored.
                /* || (ascii > 47 && ascii < 58)*/) currTerm.append(text.substr(pos, 1));

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


void IndexInterface::print_sample_data(string term)
{
    cout<<"Terms with the same hash value as "<<term<<" are:\n";

    // Call print_sample for the corresponding LetterTerms object.
    letters[index_for_letter(term.front())].print_sample(term);
}
