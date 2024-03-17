cmake_minimum_required(VERSION 3.27)
project(spell_checker)

set(CMAKE_CXX_STANDARD 17)

include(FetchContent)
FetchContent_Declare(
        MurmurHash3
        GIT_REPOSITORY https://github.com/aappleby/smhasher.git
        GIT_TAG        master
        SOURCE_DIR     "${CMAKE_BINARY_DIR}/MurmurHash3"
        CONFIGURE_COMMAND ""
        BUILD_COMMAND ""
        INSTALL_COMMAND ""
        TEST_COMMAND ""
)
FetchContent_MakeAvailable(MurmurHash3)

add_executable(bloom_filter_builder
        bloom_filter.cpp
        bloom_filter.h
        std_hasher.h
        hasher.h
        bloom_filter_manager.cpp
        bloom_filter_manager.h
        bloom_filter_build_invoker.cpp
)

add_executable(bloom_filter_deserializer
        bloom_filter.cpp
        bloom_filter.h
        std_hasher.h
        hasher.h
        bloom_filter_manager.cpp
        bloom_filter_manager.h
        bloom_filter_deserializer.cpp
        bloom_filter_deserializer.h
)

# Google Test setup
include(FetchContent)
FetchContent_Declare(
        googletest
        GIT_REPOSITORY https://github.com/google/googletest.git
        GIT_TAG        release-1.10.0
)
FetchContent_MakeAvailable(googletest)

enable_testing()

# Add test executable
add_executable(runTests
        bloom_filter_test.cpp bloom_filter.cpp bloom_filter.h
        std_hasher.h
        hasher.h
        bloom_filter_manager.cpp
        bloom_filter_manager.h)
target_link_libraries(runTests gtest_main)

