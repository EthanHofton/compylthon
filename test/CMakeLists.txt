# INCLUDE GTEST
include(FetchContent)

FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG        release-1.11.0
)
FetchContent_MakeAvailable(googletest)
add_library(GTest::GTest INTERFACE IMPORTED)
target_link_libraries(GTest::GTest INTERFACE gtest_main)

# EXAMPLE TEST
# 1. create test executable
# add_executable(example_test example_test.cpp)
# 2. link test executable with gtest
# target_link_libraries(example_test PRIVATE GTest::GTest lrp)
# 3. add test
# add_test(NAME example_gtests COMMAND example_test WORKING_DIRECTORY ${CMAKE_BINARY_DIR})

add_executable(test_lexer test_lexer.cpp ${CMAKE_SOURCE_DIR}/src/lexer.cpp)
target_link_libraries(test_lexer PRIVATE GTest::GTest)
target_include_directories(test_lexer PRIVATE ${CMAKE_SOURCE_DIR}/include)
add_test(NAME test_lexer_gtest COMMAND test_lexer WORKING_DIRECTORY ${CMAKE_BINARY_DIR})

add_executable(test_parser test_parser.cpp ${CMAKE_SOURCE_DIR}/src/parser.cpp)
target_link_libraries(test_parser PRIVATE GTest::GTest)
target_include_directories(test_parser PRIVATE ${CMAKE_SOURCE_DIR}/include)
add_test(NAME test_parser_gtest COMMAND test_parser WORKING_DIRECTORY ${CMAKE_BINARY_DIR})

add_executable(test_transaction_manager test_transaction_manager.cpp)
target_link_libraries(test_transaction_manager PRIVATE GTest::GTest)
target_include_directories(test_transaction_manager PRIVATE ${CMAKE_SOURCE_DIR}/include)
add_test(NAME test_transaction_manager_gtest COMMAND test_transaction_manager WORKING_DIRECTORY ${CMAKE_BINARY_DIR})
