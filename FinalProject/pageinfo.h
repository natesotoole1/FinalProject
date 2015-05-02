#ifndef PAGEINFO_H
#define PAGEINFO_H

#include <string>

using namespace std;

class PageInfo
{
public:
    PageInfo();
    ~PageInfo();

    // Getters.
    string get_contributor();
    string get_timestamp();
    string get_title();
    int get_totalWords();

    // Setters.
    void set_contributor(string theInfo);
    void set_timestamp(string theTimestamp);
    void set_title(string theTitle);

    void incr_total_words();
private:
    string contributorNameOrIP;
    string timestamp;
    string title;
    int totalWords;
};

#endif // PAGEINFO_H
