#include "docparser.h"

DocParser::DocParser()
{

}

DocParser::~DocParser()
{

}

string DocParser::clean_term(string term)
{
    // Remove all non-letter chars from term.
    //term.erase(remove_if(term.begin(), term.end(), is_letter(term)), term.end());

    // Remove all uppercase letter from term.
    Porter2Stemmer::trim(term);

    // Stem term.
    Porter2Stemmer::stem(term);

    return term;
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
    //int count = 1;
    while (currNode->next_sibling())
    {
        currNode = currNode->next_sibling();
        index_page(currNode, index);
        //++count;
        //if (count == 10000) break;
    }

    index->write_persistence();
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

    istringstream stream(text);

    // To store the current term to insert in the inverted index.
    string currTerm = "";

    while (stream >> currTerm)
    {
        // Loads whatever characters are between each pair of whitespaces,
        // so clean it.
        currTerm = clean_term(currTerm);

        // See if currTerm is already in allTerms;
        try
        {
            allTerms.at(currTerm);
        }

        // This means the term wasn't already in allTerms, so emplace it.
        catch (const out_of_range& notInAllTerms)
        {
            //allTerms.emplace(make_pair(currTerm, pageMap(currID, 1)));
        }

    }
}

bool DocParser::is_letter(char curr)
{
    int ascii = (int)curr;

    if ((ascii > 64 && ascii < 91)
            || (ascii > 96 && ascii < 123)) return true;

    return false;
}
