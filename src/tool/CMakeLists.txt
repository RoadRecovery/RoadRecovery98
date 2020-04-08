set(tool_source_files
        ReadExcel.cpp
        ReadExcel.h
        )

add_library(tool ${tool_source_files})

target_link_libraries(tool entity)