#include <iostream>
#include <fstream>
#include <cstring>
#include <cstdlib>
#include <chrono>

#include "PagedArray.h"
#include "Algorithms/bubbleSort.h"
#include "Algorithms/insertionSort.h"
#include "Algorithms/quickSort.h"

int main(int argc, char* argv[]) {
    if (argc != 7) {
        std::cerr << "Uso: sorter -input <INPUT FILE PATH> -output <OUTPUT FILE PATH> -alg <ALGORITMO>\n";
        return 1;
    }

    const char* inputFlag = argv[1];
    const char* inputFilePath = argv[2];
    const char* outputFlag = argv[3];
    const char* outputFilePath = argv[4];
    const char* algorithm = argv[6];

    if (strcmp(inputFlag, "-input") != 0 || strcmp(outputFlag, "-output") != 0) {
        std::cerr << "Uso: sorter -input <INPUT FILE PATH> -output <OUTPUT FILE PATH> -alg <ALGORITMO>\n";
        return 1;
    }

    std::cout << "Ruta del archivo de entrada: " << inputFilePath << "\n";
    std::cout << "Ruta del archivo de salida: " << outputFilePath << "\n";
    std::cout << "Algoritmo seleccionado: " << algorithm << "\n";

    // Copiar archivo de entrada al archivo de salida
    std::ifstream src(inputFilePath, std::ios::binary);
    std::ofstream dst(outputFilePath, std::ios::binary);
    dst << src.rdbuf();
    src.close();
    dst.close();

    PagedArray pagedArray(outputFilePath);

    std::ifstream inputFile(outputFilePath, std::ios::binary | std::ios::ate);
    if (!inputFile.is_open()) {
        std::cerr << "Error al abrir el archivo para lectura en: " << outputFilePath << "\n";
        return 1;
    }
    std::size_t fileSize = inputFile.tellg();
    std::size_t numElements = fileSize / sizeof(int);

    if (fileSize % sizeof(int) != 0) {
        std::cerr << "El tamano del archivo no es multiplo del tamano de un entero.\n";
        return 1;
    }

    std::cout << "Tamano del archivo: " << fileSize << " bytes\n";
    std::cout << "Numero de elementos: " << numElements << "\n";

    auto start = std::chrono::high_resolution_clock::now();

    if (strcmp(algorithm, "QS") == 0) {
        std::cout << "Usando Quick Sort\n";
        quickSort(pagedArray, 0, numElements - 1);
    } else if (strcmp(algorithm, "IS") == 0) {
        std::cout << "Usando Insertion Sort\n";
        insertionSort(pagedArray, 0, numElements - 1);
    } else if (strcmp(algorithm, "BS") == 0) {
        std::cout << "Usando Bubble Sort\n";
        bubbleSort(pagedArray, 0, numElements - 1);
    } else {
        std::cerr << "Algoritmo desconocido. Use QS, IS, o BS.\n";
        return 1;
    }

    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed = end - start;

    std::ofstream outputFile(outputFilePath); // Open file as text
    if (!outputFile.is_open()) {
        std::cerr << "Error al abrir el archivo para escritura en: " << outputFilePath << "\n";
        return 1;
    }

    for (std::size_t i = 0; i < numElements; ++i) {
        int value = pagedArray[i];
        outputFile << value;
        if (i < numElements - 1) {
            outputFile << ","; // Add comma separator
        }
        if (i % (numElements / 10) == 0) { // Print progress every 10% of the total elements
            std::cout << "Escribiendo elemento: " << i << "\n";
        }
    }

    outputFile.close();

    std::cout << "Archivo ordenado generado exitosamente en: " << outputFilePath << "\n";
    std::cout << "Tiempo durado: " << elapsed.count() << " segundos\n";
    std::cout << "Algoritmo utilizado: " << algorithm << "\n";
    std::cout << "Page Faults: " << pagedArray.getPageFaults() << "\n";
    std::cout << "Page Hits: " << pagedArray.getPageHits() << "\n";

    return 0;
}
