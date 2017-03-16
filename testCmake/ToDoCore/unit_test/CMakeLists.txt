
#set_property(TARGET gtest APPEND_STRING PROPERTY COMPILE_FLAGS " -w")

include_directories("/usr/local/include")
link_directories("/usr/local/lib")

#add_executable(ToDoTest ToDoTest.cpp)

#target_link_libraries(ToDoTest
#							pthread 
#							toDoCore
#							gmock_main)

#
# add_gmock_test(<target> <sources>...)
#
#  Adds a Google Mock based test executable, <target>, built from <sources> and
#  adds the test so that CTest will run it. Both the executable and the test
#  will be named <target>.
#
function(add_gmock_test target)
	add_executable(${target} ${ARGN})
	target_link_libraries(${target}
							pthread 
							gmock_main)
	
	add_test(${target} ${target})
endfunction()


add_gmock_test(ToDoTest ToDoTest.cpp)
target_link_libraries(ToDoTest toDoCore)