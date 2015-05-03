#include "indexinterface.h"

IndexInterface::IndexInterface()
{
    totalPages = 0;
    totalWordsInCorpus = 0;
    infoForIDs = vector<PageInfo*>();
    parser = new DocParser(this);
}

IndexInterface::~IndexInterface()
{

}

void IndexInterface::append_page_info(PageInfo* currInfo)
{
    ++totalPages;
    infoForIDs.push_back(currInfo);
}

void IndexInterface::display_result(int rank, int pageID, double tdidf)
{
    PageInfo* resultInfo = infoForIDs.at(pageID);
    cout<<"Result rank #"<<rank<<": \n";
    cout<<"\tTotal TDF/IDF value: "<<tdidf<<endl;
    cout<<"\tPage name: "<<resultInfo->get_title()<<endl;
    cout<<"\tTimestamp: "<<resultInfo->get_timestamp()<<endl;
    cout<<"\tContributor name or IP Address: "<<resultInfo->get_contributor()<<endl;
}

void IndexInterface::display_page_content(int pageID)
{
    cout<<"Here is the text\n";
    cout<<infoForIDs.at(pageID)->get_content()<<endl;
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
    ascii -= 97;
    return ascii;
}

PageInfo* IndexInterface::info_for_pageID(int pageID)
{
    return infoForIDs.at(pageID);
}

void IndexInterface::read_file(string filePath)
{
    parser->read_file(filePath);
}

double IndexInterface::calc_tdidf(int pageID, int freq, int spread)
{
    // Calculate TF value.
    int totalWords = infoForIDs.at(pageID)->get_totalWords();
    double tf = (double)freq/totalWords;

    // Calculate IDF value.
    int totalDocsInCorpus = infoForIDs.size();
    double idf = log((double)totalDocsInCorpus/spread);

    return tf*idf;
}

void IndexInterface::incr_total_words_on_page(int currID, int incr)
{
    infoForIDs.at(currID)->incr_totalWords(incr);
}

void IndexInterface::read_persistence_file(termMap& allTerms)
{
    ifstream ifs("Persistence.txt");

    // Load two words at a time.
    string word1;
    string word2;

    ifs >> word1;
    ifs >> word2;

    while (!ifs.eof())
    {
        // For each new term, extract two words at a time until
        // another exclamation point is reached.
        if (word1.compare("!") == 0)
        {
            pageMap pageAprns;
            string name = word2;

            ifs >> word1;
            ifs >> word2;

            // For each subsequent pageID-frequency pair, add that to pageAprns
            // and increment that pageID's totalWords.
            while (word1.compare("!") != 0)
            {
                int num1 = stoi(word1);
                int num2 = stoi(word2);

                pageAprns.emplace(make_pair(num1, num2));
                infoForIDs.at(num1)->incr_totalWords(num2);
                ifs >> word1;
                ifs >> word2;
            }
            allTerms.emplace(make_pair(word2, pageAprns));
        }
    }
}

void IndexInterface::write_persistence_file()
{
    ofstream persistence;
    persistence.open("Persistence.txt", ofstream::out | ofstream::trunc);

    write_persistence_terms(persistence);
    /*
    // Write the totals for each pageID to file.
    for (int i=0; i<totalPages; ++i)
    {
        persistence<<infoForIDs.at(i)->get_totalWords(i)<<" ";
    }
    */
    persistence.close();
}

int IndexInterface::get_totalWordsInCorpus()
{
    if (totalWordsInCorpus == 0)
    {
    for (int i=0; i<infoForIDs.size(); ++i) totalWordsInCorpus += infoForIDs.at(i)->get_totalWords();
    }
    return totalWordsInCorpus;
}
