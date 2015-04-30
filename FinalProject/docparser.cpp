#include "docparser.h"

DocParser::DocParser()
{
    // Add all stop words to stopWords.

    // Load the list of stop from the build directory.
    ifstream ifs("StopWords.txt");

    string word;
    // For each line in the stop words file (there is only one
    // word per line, add that word as if it were an appearance.
    // This function will only be called by letters[0].
    while (ifs >> word)
    {
        word = clean_term(word);
        stopWords.emplace(make_pair(word, word));
    }
}

DocParser::~DocParser()
{

}

void DocParser::add_appearance(string currTerm, int currID)
{
    // Check if currID is already in currTerm's pageMap.
    try
    {
        allTerms.at(currTerm).at(currID);
    }

    // This means currID wasn't already in the pageMap, so emplace it.
    catch (const out_of_range& notInAllTerms)
    {
        allTerms.at(currTerm).insert(make_pair(currID, 1));
        return;
    }

    // At this point, currID was already in the pageMap,
    // so increase the frequency by 1.
    allTerms.at(currTerm).at(currID)++;

}

string DocParser::clean_term(string term)
{
    // Stem term.
    Porter2Stemmer::stem(term);

    // Remove all uppercase letter from term.
    Porter2Stemmer::trim(term);



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

    // Iterate through allTerms and create a new Term object
    // using the data from each value.
    for (auto& value : allTerms)
    {
        cout<<value.first<<": ";
        for (auto val : allTerms.at(value.first))
        {
            cout<<val.second<<"@"<<val.first<<" ";
        }
        cout<<endl;
    }

    // By this point, allTerms contains all the info for
    // the inverted index.  Add each term to the inverted index.
    for (auto& term : allTerms)
    {
        index->add_term_to_ii(
                    index_for_letter(term.first.front()),
                    term.first,
                    term.second);
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
    ascii -= 97;
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
    index_text(currNode, currID);

}

void DocParser::index_text(xml_node<>* currNode, int currID)
{
    string text = currNode->value();

    // Replace all non-letters with whitespace char.
    // Got from http://stackoverflow.com/questions/5540008/need-a-regular-expression-
    // to-extract-only-letters-and-whitespace-from-a-string
    replace_if(text.begin(), text.end(),
                        is_not_alpha,
                        ' '
                        );

    istringstream stream(text);

    // To store the current term to insert in the inverted index.
    string currTerm = "";

    while (stream >> currTerm)
    {
        // Loads whatever characters are between each pair of whitespaces,
        // so clean it.
        currTerm = clean_term(currTerm);

        // If the currTerm a stop word, forego adding it to allTerms.
        if (is_stop_word(currTerm)) continue;

        // See if currTerm is already in allTerms;
        try
        {
            allTerms.at(currTerm);
        }

        // This means the term wasn't already in allTerms, so emplace it.
        catch (const out_of_range& notInAllTerms)
        {
            pageMap pMap;
            pMap.emplace(make_pair(currID, 1));
            allTerms.emplace(make_pair(currTerm, pMap));
            continue;
        }

        // This point will only be reached if
        // the term is already in allTerms.
        add_appearance(currTerm, currID);
    }
}

bool DocParser::is_stop_word(string term)
{
    // Use term as the key and see if it is in the stopWordMap.
    try
    {
        stopWords.at(term);
    }
    catch (const out_of_range& notAStopWord)
    {
        return false;
    }
    return true;
}
