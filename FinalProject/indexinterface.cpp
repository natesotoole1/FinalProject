#include "indexinterface.h"

IndexInterface::IndexInterface()
{
    infoForIDs = vector<PageInfo>();
}

IndexInterface::~IndexInterface()
{

}

//void IndexInterface::add_term_to_persistence(Term* term)
//{
//    persistence.emplace(make_pair(term, term));
//}

int IndexInterface::append_page_info(PageInfo* currInfo)
{
    infoForIDs.push_back(*currInfo);
    return infoForIDs.size()-1;
}

void IndexInterface::display_result(int rank, int pageID, double tdidf)
{
    PageInfo resultInfo = infoForIDs.at(pageID);
    cout<<"Result rank #"<<rank<<": \n";
    cout<<"\tTDF/IDF value of "<<tdidf<<endl;
    cout<<"\tPage name: "<<resultInfo.get_title()<<endl;
    cout<<"\tTimestamp: "<<resultInfo.get_timestamp()<<endl;
    cout<<"\tContributor name or IP Address: "<<resultInfo.get_contributor()<<endl;
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

double IndexInterface::calc_tdidf(int pageID, int freq, int spread)
{
    // Calculate TF value.
    int totalWords = infoForIDs.at(pageID).get_totalWords();
    double tf = (double)freq/totalWords;

    // Calculate IDF value.
    int totalDocsInCorpus = infoForIDs.size();
    double idf = log((double)totalDocsInCorpus/spread);

    return tf*idf;
}

void IndexInterface::incr_total_words_on_page(int currID)
{
    infoForIDs.at(currID).incr_totalWords();
}

void IndexInterface::load_persistence()
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
            pageAprns.emplace(make_pair(stoi(word1), stoi(word2)));
            while (word1.compare("!") != 0)
            {
                pageAprns.emplace(make_pair(stoi(word1), stoi(word2)));
                ifs >> word1;
                ifs >> word2;
            }
            add_term_to_ii(index_for_letter(name.front()), new Term(name, pageAprns));
        }
    }
}

int IndexInterface::get_total_words_in_corpus()
{
    int total = 0;
    for (int i=0; i<infoForIDs.size(); ++i) total += infoForIDs.at(i).get_totalWords();
    return total;
}
