#include "docparser.h"

DocParser::DocParser()
{

}

void DocParser::index_corpus(IndexInterface* index)
{
    // Use RapidXML's "parse" function to make all data
    // accessible via nodes and values.
    file<> theFile("WikiBooks.xml");
    xml_document<> theDoc;
    theDoc.parse<0>(theFile.data());

    // Find the first node with name 'mediawiki'.
    xml_node<>* currNode = theDoc.first_node();

    // Go to 'siteinfo'.
    currNode = currNode->first_node();

    // Go to the first 'page'.
    currNode = currNode->next_sibling();

    index_page(currNode, index);


    // Index the remaining pages in the file.
    while (currNode->next_sibling())
    {
        currNode = currNode->next_sibling();
        index_page(currNode, index);
    }

    index->write_persistence();
}

int DocParser::index_for_letter(char letter)
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

void DocParser::index_page(xml_node<>* currNode, IndexInterface* theIndex)
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

    // Add the PageInfo to 'infoForID' vector.
    int currID = theIndex->append_page_info(currInfo);

    // Pass the current node to index_text to find all terms in
    // this page's text.
    index_text(currNode, currID, theIndex);
}

void DocParser::index_text(xml_node<>* currNode, int currID, IndexInterface* theIndex)
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

        char currChar = text.at(pos);

        // Get the ascii value of the current char.
        int ascii = (int)currChar;

        // If the letter is uppercase...
        if (ascii > 64 && ascii < 91)
        {
            // Increase its ascii value by 32 next conditional
            // (which only accepts lowercase chars).
            ascii += 32;
            // Make it lowercase by converting the increased ascii value back to a char.
            currChar = (char)ascii;
        }

        // If it's a letter (has to be lowercase), append it to newTerm.
        if (ascii > 96 && ascii < 123) currTerm+=currChar;

        // If it's a not a letter (i.e. it's a useless char),
        // end the term if and insert it in the inverted index
        // if newTerm has any chars in it.  Otherwise, ignore the char.
        else if (currTerm.size())
        {
            theIndex->add_appearance(index_for_letter(currTerm.front()), currTerm, currID);
            currTerm.clear();
        }
    }

    // If the end of the value string is reached and there's a new term to
    // insert in the inverted index, do so.
    if (currTerm.size()) theIndex->add_appearance(index_for_letter(currTerm.front()), currTerm, currID);
}
