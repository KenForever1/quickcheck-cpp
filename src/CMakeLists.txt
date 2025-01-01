add_executable(quickcheck-cpp main.cpp)
target_link_libraries(quickcheck-cpp
    PRIVATE
    fmt::fmt
    Threads::Threads
)
