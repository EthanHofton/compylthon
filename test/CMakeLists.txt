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

# add_executable(test_parse test_parse.cpp)
# target_link_libraries(test_parse PRIVATE GTest::GTest lrp)
# add_test(NAME test_parse_gtest COMMAND test_parse WORKING_DIRECTORY ${CMAKE_BINARY_DIR})
