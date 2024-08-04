#include "PagedArray.h"
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>

PagedArray::PagedArray(const std::string& filePath)
    : pageFaults(0), pageHits(0) {
    std::srand(std::time(0));
    file.open(filePath, std::ios::binary);
    if (!file.is_open()) {
        std::cerr << "Error al abrir el archivo.\n";
        exit(1);
    }

    for (int i = 0; i < MAX_PAGES; ++i) {
        pages[i] = new int[PAGE_SIZE / sizeof(int)];
        loadedPages[i] = false;
    }
}

PagedArray::~PagedArray() {
    for (int i = 0; i < MAX_PAGES; ++i) {
        if (loadedPages[i]) {
            unloadPage(i);
        }
        delete[] pages[i];
    }
    if (file.is_open()) {
        file.close();
    }
}

void PagedArray::loadPage(int pageIndex) {
    std::cout << "Cargando pagina: " << pageIndex << "\n";
    file.seekg(pageIndex * PAGE_SIZE);
    if (file.fail()) {
        std::cerr << "Error al mover el puntero del archivo.\n";
        exit(1);
    }
    file.read(reinterpret_cast<char*>(pages[pageIndex % MAX_PAGES]), PAGE_SIZE);
    if (file.fail()) {
        std::cerr << "Error al leer la página del archivo.\n";
        exit(1);
    }
    loadedPages[pageIndex % MAX_PAGES] = true;
    ++pageFaults;
}

void PagedArray::unloadPage(int pageIndex) {
    std::cout << "Descargando pagina: " << pageIndex << "\n";
    loadedPages[pageIndex % MAX_PAGES] = false;
}

bool PagedArray::allLoaded() const {
    for (int i = 0; i < MAX_PAGES; ++i) {
        if (!loadedPages[i]) {
            return false;
        }
    }
    return true;
}

int& PagedArray::operator[](std::size_t index) {
    int pageIndex = index / (PAGE_SIZE / sizeof(int));
    int offset = index % (PAGE_SIZE / sizeof(int));

    if (!loadedPages[pageIndex % MAX_PAGES]) {
        if (allLoaded()) {
            int pageToUnload = std::rand() % MAX_PAGES;
            unloadPage(pageToUnload);
        }
        loadPage(pageIndex);
    }

    return pages[pageIndex % MAX_PAGES][offset];
}

int PagedArray::getPageFaults() const {
    return pageFaults;
}

int PagedArray::getPageHits() const {
    return pageHits;
}
