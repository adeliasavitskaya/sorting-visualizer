cmake_minimum_required(VERSION 3.10)
project(sorting-visualizer)

set(CMAKE_CXX_STANDARD 17)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

find_package(Qt5 REQUIRED COMPONENTS Widgets Core)

set(CMAKE_POLICY_VERSION_MINIMUM 3.5)

include(FetchContent)
FetchContent_Declare(
        doctest
        GIT_REPOSITORY https://github.com/doctest/doctest.git
        GIT_TAG v2.4.11
)
FetchContent_MakeAvailable(doctest)

set(SOURCES
        src/main.cpp
        src/algorithms/bubble_sort.cpp
        src/algorithms/merge_sort.cpp
        src/algorithms/quick_sort.cpp
        src/ui/app_window.cpp
        src/ui/array_input_widget.cpp
        src/ui/sort_visualizer.cpp
        src/core/step_generator.cpp
)

set(HEADERS
        src/core/sort_step.h
        src/core/step_generator.h
        src/algorithms/bubble_sort.h
        src/algorithms/merge_sort.h
        src/algorithms/quick_sort.h
        src/ui/app_window.h
        src/ui/array_input_widget.h
        src/ui/sort_visualizer.h
)

add_executable(${PROJECT_NAME} ${SOURCES} ${HEADERS})

target_link_libraries(${PROJECT_NAME} Qt5::Widgets Qt5::Core)

target_include_directories(${PROJECT_NAME} PRIVATE src)

add_executable(tests
        tests/test_bubble.cpp
        tests/test_merge.cpp
        tests/test_quick.cpp
        tests/test_step_generator.cpp
        src/algorithms/bubble_sort.cpp
        src/algorithms/merge_sort.cpp
        src/algorithms/quick_sort.cpp
        src/core/step_generator.cpp
)

target_include_directories(tests PRIVATE src tests ${doctest_SOURCE_DIR}/doctest)
target_link_libraries(tests Qt5::Widgets Qt5::Core doctest::doctest)

enable_testing()
add_test(NAME unit_tests COMMAND tests)