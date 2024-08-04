// PagedArray.h
#ifndef PAGEDARRAY_H
#define PAGEDARRAY_H

#include <string>
#include <fstream>

class PagedArray {
private:
    static const int PAGE_SIZE = 4096;
    static const int MAX_PAGES = 4;
    int* pages[MAX_PAGES];
    bool loadedPages[MAX_PAGES];
    std::ifstream file;
    int pageFaults;
    int pageHits;

    void loadPage(int pageIndex);
    void unloadPage(int pageIndex);
    bool allLoaded() const;

public:
    PagedArray(const std::string& filePath);
    ~PagedArray();

    int& operator[](std::size_t index);
    int getPageFaults() const;
    int getPageHits() const;
};

#endif // PAGEDARRAY_H
