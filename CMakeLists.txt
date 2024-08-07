cmake_minimum_required(VERSION 3.28)
project(TareaExtraclase1)

set(CMAKE_CXX_STANDARD 17)

# Agregar el directorio de encabezados
include_directories(${CMAKE_SOURCE_DIR}/Sorter)

# Agregar los archivos fuente del proyecto
add_executable(TareaExtraclase1
        Generator/generator.cpp
        Sorter/PagedArray.cpp
        Sorter/sorter.cpp
        Sorter/Algorithms/insertionSort.cpp
        Sorter/Algorithms/bubbleSort.cpp
        Sorter/Algorithms/quickSort.cpp
        Sorter/Algorithms/NoSort.cpp
)

# Incluir los archivos de encabezado
target_include_directories(TareaExtraclase1 PRIVATE
        Sorter
        Sorter/Algorithms
)
