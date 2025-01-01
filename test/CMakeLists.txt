add_executable(test_random_generator test_random_generator.cpp)
target_link_libraries(test_random_generator
    PRIVATE gtest_main
    fmt::fmt
    Threads::Threads
)

add_executable(test_shrink test_shrink.cpp)
target_link_libraries(test_shrink
    PRIVATE gtest_main
    fmt::fmt
    Threads::Threads
)