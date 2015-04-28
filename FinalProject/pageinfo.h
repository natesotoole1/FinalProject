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

    // Setters.
    void set_contributor(string theInfo);
    void set_timestamp(string theTimestamp);
    void set_title(string theTitle);
private:
    string contributorNameOrIP;
    string timestamp;
    string title;
};

#endif // PAGEINFO_H
