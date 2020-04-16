cmake_minimum_required(VERSION 3.15)
project(RoadRecovery98)

# for testing and release, respectively
set(GTEST true)

if (GTEST)
    set(cmake_cxx_standard 11)
#    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fsanitize=address -g -O")

    # Download and unpack googletest at configure time
    ###### uncomment begin
#    configure_file(CMakeLists.txt.in googletest-download/CMakeLists.txt)
#    execute_process(COMMAND ${CMAKE_COMMAND} -G "${CMAKE_GENERATOR}" .
#                    RESULT_VARIABLE result
#                    WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/googletest-download )
#    if(result)
#        message(FATAL_ERROR "CMake step for googletest failed: ${result}")
#    endif()
#    execute_process(COMMAND ${CMAKE_COMMAND} --build .
#                    RESULT_VARIABLE result
#                    WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/googletest-download )
#    if(result)
#        message(FATAL_ERROR "Build step for googletest failed: ${result}")
#    endif()
    ###### uncomment end

    # Prevent overriding the parent project's compiler/linker
    # settings on Windows
    set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

    # Add googletest directly to our build. This defines
    # the gtest and gtest_main targets.
    add_subdirectory(${CMAKE_CURRENT_BINARY_DIR}/googletest-src
                     ${CMAKE_CURRENT_BINARY_DIR}/googletest-build
                     EXCLUDE_FROM_ALL)

    # The gtest/gtest_main targets carry header search path
    # dependencies automatically when using CMake 2.8.11 or
    # later. Otherwise we have to add them here ourselves.
    if (CMAKE_VERSION VERSION_LESS 2.8.11)
        include_directories("${gtest_SOURCE_DIR}/include")
    endif()

    # Now simply link against gtest or gtest_main as needed. Eg
    #add_executable(test test/PathRestorationTest.cpp)
    #target_link_libraries(test gtest_main)
    #add_test(NAME example_test COMMAND test)

    # For customized command
    add_subdirectory(test)
    add_subdirectory(src/algorithm)
    add_subdirectory(src/core)
    add_subdirectory(src/entity)
    add_subdirectory(src/tool)

    # Typically you don't care so much for a third party library's tests to be
    # run from your own project's code.
    set(JSON_BuildTests OFF CACHE INTERNAL "")

    # If you only include this third party in PRIVATE source files, you do not
    # need to install it when your main project gets installed.
    # set(JSON_Install OFF CACHE INTERNAL "")
    include_directories(test/json/include)

    # Don't use include(nlohmann_json/CMakeLists.txt) since that carries with it
    # unintended consequences that will break the build.  It's generally
    # discouraged (although not necessarily well documented as such) to use
    # include(...) for pulling in other CMake projects anyways.
    add_subdirectory(test/json)

    add_executable(RRTest test/PathRestorationTest.cpp)
    target_link_libraries(RRTest gtest_main core nlohmann_json::nlohmann_json)
    add_test(NAME RRTestRun COMMAND RRTest)

else()
    set(cmake_cxx_standard 98)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fsanitize=address -g -O -pedantic-errors -std=c++98")

    add_subdirectory(src/algorithm)
    add_subdirectory(src/core)
    add_subdirectory(src/entity)
    add_subdirectory(src/tool)

    add_executable(main src/main.cpp)

    target_link_libraries(main core)

    include_directories(src)
endif()