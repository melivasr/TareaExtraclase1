#include "PagedArray.h"
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>

PagedArray::PagedArray(const std::string& filePath)
    : pageFaults(0), pageHits(0), numElements(0) {
    file.open(filePath, std::ios::in | std::ios::out | std::ios::binary);
    if (!file.is_open()) {
        std::cerr << "Error al abrir el archivo.\n";
        exit(1);
    }

    for (int i = 0; i < MAX_PAGES; ++i) {
        pages[i] = new int[PAGE_SIZE / sizeof(int)];
        loadedPages[i] = false;
        pageMap[i] = -1;
    }

    srand(static_cast<unsigned>(time(0)));
}

PagedArray::~PagedArray() {
    for (int i = 0; i < MAX_PAGES; ++i) {
        if (loadedPages[i]) {
            unloadPage(pageMap[i]);
        }
        delete[] pages[i];
    }
    if (file.is_open()) {
        file.close();
    }
}

void PagedArray::loadPage(int pageIndex) {
    int pageSlot = -1;

    // Encuentra un slot vacio para la pagina
    for (int i = 0; i < MAX_PAGES; ++i) {
        if (!loadedPages[i]) {
            pageSlot = i;
            break;
        }
    }

    // Si todos los slots estan ocupados, selecciona uno al azar para reemplazar
    if (pageSlot == -1) {
        pageSlot = rand() % MAX_PAGES;
        unloadPage(pageMap[pageSlot]);
    }

    // Carga la nueva pagina en el slot seleccionado
    file.seekg(pageIndex * PAGE_SIZE);
    file.read(reinterpret_cast<char*>(pages[pageSlot]), PAGE_SIZE);
    if (file.fail()) {
        std::cerr << "Error al leer la pagina del archivo.\n";
        exit(1);
    }

    loadedPages[pageSlot] = true;
    pageMap[pageSlot] = pageIndex;
    ++pageFaults;
}

void PagedArray::unloadPage(int pageIndex) {
    int pageSlot = -1;
    std::cout << "Descargando pagina: " << pageIndex << "\n";

    // Encuentra el slot correspondiente a la pagina a descargar
    for (int i = 0; i < MAX_PAGES; ++i) {
        if (pageMap[i] == pageIndex) {
            pageSlot = i;
            break;
        }
    }

    if (pageSlot != -1) {
        file.seekp(pageIndex * PAGE_SIZE);
        file.write(reinterpret_cast<char*>(pages[pageSlot]), PAGE_SIZE);
        if (file.fail()) {
            std::cerr << "Error al escribir la pagina del archivo.\n";
            exit(1);
        }

        loadedPages[pageSlot] = false;
        pageMap[pageSlot] = -1; // Marca el slot como no cargado
    }
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
    int pageSlot = -1;

    for (int i = 0; i < MAX_PAGES; ++i) {
        if (pageMap[i] == pageIndex) {
            pageSlot = i;
            ++pageHits;
            break;
        }
    }

    if (pageSlot == -1) {
        loadPage(pageIndex);
        for (int i = 0; i < MAX_PAGES; ++i) {
            if (pageMap[i] == pageIndex) {
                pageSlot = i;
                break;
            }
        }
    }

    return pages[pageSlot][offset];
}

int PagedArray::getPageFaults() const {
    return pageFaults;
}

int PagedArray::getPageHits() const {
    return pageHits;
}

void PagedArray::setNumElements(std::size_t elements) {
    numElements = elements;
}

