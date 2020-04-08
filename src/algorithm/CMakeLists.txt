set(algorithm_source_files
        Algorithm.cpp
        Algorithm.h
        DPAlgorithm.cpp
        DPAlgorithm.h
        NullAlgorithm.cpp
        NullAlgorithm.h
        )

add_library(algorithm ${algorithm_source_files})

target_link_libraries(algorithm entity)