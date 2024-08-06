#ifndef PAGEDARRAY_H
#define PAGEDARRAY_H

#include <string>
#include <fstream>
#include <iostream>
#include <cstdlib>

class PagedArray {
public:
    static const int PAGE_SIZE = 4096;
    static const int MAX_PAGES = 4;
    int* pages[MAX_PAGES];
    bool loadedPages[MAX_PAGES];
    int pageMap[MAX_PAGES]; // Para mapear qué página se ha cargado en cada índice
    std::fstream file;
    std::ofstream outputFile;
    int pageFaults;
    int lastAccesedPage;
    int pageHits;
    std::size_t numElements; // Agrega esta variable para almacenar el número de elementos

    void loadPage(int pageIndex);
    void unloadPage(int pageIndex);
    bool allLoaded() const;

public:
    PagedArray(const std::string& filePath);
    ~PagedArray();

    int& operator[](std::size_t index);
    int getPageFaults() const;
    int getPageHits() const;
    void setNumElements(std::size_t numElements);
};

#endif // PAGEDARRAY_H
