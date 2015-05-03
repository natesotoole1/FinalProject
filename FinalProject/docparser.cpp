#include "docparser.h"

DocParser::DocParser()
{

}

DocParser::DocParser(IndexInterface* theIndex)
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

    index = theIndex;
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

void DocParser::index_document(IndexInterface* index, string filePath)
{
    // Use RapidXML's "parse" function to make all data
    // accessible via nodes and values.
    file<> theFile(filePath.c_str());
    xml_document<> theDoc;
    theDoc.parse<0>(theFile.data());

    // Find the first node with name 'mediawiki'.
    xml_node<>* currNode = theDoc.first_node();

    // Go to 'siteinfo'.
    currNode = currNode->first_node();

    // Go to the first 'page'.
    currNode = currNode->next_sibling();

    init_info_at_page(currNode, index);


    // Index the remaining pages in the file.
    //int count = 1;
    while (currNode->next_sibling())
    {
        currNode = currNode->next_sibling();
        init_info_at_page(currNode, index);
        //++count;
        //if (count == 10000) break;
    }

    // Iterate through allTerms and create a new Term object
    // using the data from each value.
    /*for (auto& value : allTerms)
    {
        cout<<value.first<<": ";
        for (auto val : allTerms.at(value.first))
        {
            cout<<val.second<<"@"<<val.first<<" ";
        }
        cout<<endl;
    }*/

    // By this point, allTerms contains all the info for
    // the inverted index.  Add each term to the inverted index.

    int totalWordsInCorpus = index->get_total_words_in_corpus();

    for (auto& term : allTerms)
    {
        // If the word is longer than 12 characters, skip it.
        if (term.first.length() > 12) continue;

        // If the word accounts for more than 1% of the total words
        // in the corpus, skip it.
        int totalAprns = 0;
        for (auto& page : allTerms.at(term.first)) totalAprns += page.second;
        double fraction = (double)totalAprns/totalWordsInCorpus;
        if (fraction > 0.01) continue;

        Term* aTerm = new Term(term.first, term.second);
        index->add_term_to_ii(index_for_letter(term.first.front()), aTerm);
    }


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

void DocParser::read_page(xml_node<>* currNode, bool readText)
{
    // Regardless, init the pageInfo for this page.

    // Get the page title.

    currNode = currNode->first_node();
    currTitle = currNode->value();

    // Get the timestamp.

    // Go to 'revision' node.
    currNode = currNode->next_sibling("revision");

    // Move one level inward.
    currNode = currNode->first_node();

    // Get timestamp.
    currNode = currNode->next_sibling("timestamp");
    currTimestamp = currNode->value();

    // Get contributor or IP address.
    currNode = currNode->next_sibling("contributor");
    currContributorNameOrIP = currNode->value();

    // Go to 'text' node.
    currNode = currNode->next_sibling("text");
    currContent = currNode->value();

    // Having found all info for this page, push back a new
    // PageInfo object to the index's infoForIDs.
    index->append_page_info(new PageInfo(
                                currContent, currContributorNameOrIP, currTimestamp, currTitle));

    // If text should be read (i.e. it's a new file),
    // call read_text.
    if (readText) read_text(currNode);
}

void DocParser::read_text(xml_node<>* currNode)
{
    currContent = currNode->value();

    // Replace all non-letters with whitespace char.
    // Got from http://stackoverflow.com/questions/5540008/need-a-regular-expression-
    // to-extract-only-letters-and-whitespace-from-a-string
    replace_if(currContent.begin(), currContent.end(),
               is_not_alpha,
               ' '
               );

    istringstream stream(currContent);

    int totalWordsOnPage = 0;

    while (stream >> currWord)
    {
        // Loads whatever characters are between each pair of whitespaces,
        // so clean it.
        currWord = clean_term(currWord);

        // If the currTerm a stop word, forego adding it to allTerms.
        if (is_stop_word(currWord)) continue;

        ++totalWordsOnPage;

        // See if currTerm is already in allTerms;
        try
        {
            allTerms.at(currWord);
        }

        // This means the term wasn't already in allTerms, so emplace it.
        catch (const out_of_range& notInAllTerms)
        {
            pageMap pMap;
            pMap.emplace(make_pair(currID, 1));
            allTerms.emplace(make_pair(currWord, pMap));
            continue;

        }

        // This point will only be reached if
        // the term is already in allTerms.
        add_appearance(currWord, currID);
    }
    index->info_for_pageID(currID)->set_totalWords(totalWordsOnPage);
}

void DocParser::init_file_page_infos(xml_node<> *currNode, bool readText)
{
    read_page(currNode, readText);
    // Index the remaining pages in the file.
    //int count = 1;
    while (currNode->next_sibling())
    {

        currNode = currNode->next_sibling();
        read_page(currNode, readText);
        //++count;
        //if (count == 10000) break;
    }
}

void DocParser::read_file(string filePath)
{
    // Use RapidXML's "parse" function to make all data
    // accessible via nodes and values.
    file<> theFile(filePath.c_str());
    xml_document<> theDoc;
    theDoc.parse<0>(theFile.data());

    // Find the first node with name 'mediawiki'.
    xml_node<>* currNode = theDoc.first_node();

    // Go to 'siteinfo'.
    currNode = currNode->first_node();

    // Go to the first 'page'.
    currNode = currNode->next_sibling();

    if (filePath.compare("Wikibooks.xml") == 0)
    {
        index->read_persistence_file(allTerms);
        init_file_page_infos(currNode, false);
        return;
    }

    init_file_page_infos(currNode, true);
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
