set(CMAKE_CXX_STANDARD 98)
set(CMAKE_CXX_STANDARD_REQUIRED True)

set(entity_source_files
        NodeSource.h
        NodeType.h
        Node.cpp
        Node.h
        RuntimeNode.cpp
        RuntimeNode.h
        Edge.cpp
        Edge.h
        Path.cpp
        Path.h
        RuntimePath.cpp
        RuntimePath.h
        Graph.cpp
        Graph.h
        )

add_library(entity ${entity_source_files})