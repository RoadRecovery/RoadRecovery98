set(core_source_files
        PathRestoration.cpp
        PathRestoration.h
        )

add_library(core ${core_source_files})

target_link_libraries(core algorithm tool)