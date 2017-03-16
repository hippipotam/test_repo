
#set_property(TARGET gtest APPEND_STRING PROPERTY COMPILE_FLAGS " -w")

include_directories("/usr/local/include")
link_directories("/usr/local/lib")

add_executable(ToDoTest ToDoTest.cpp)

target_link_libraries(ToDoTest
							pthread 
							toDoCore
							gmock_main)

add_test(ToDoTest ToDoTest)