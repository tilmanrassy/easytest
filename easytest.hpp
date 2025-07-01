#ifndef EASYTEST_HPP
#define EASYTEST_HPP

#include <iostream>
#include <string>

#define TEST_SUITE_INIT                \
  unsigned int failed_tests_count = 0; \
  bool test_suite_crached = false;     \
  std::string test_comment = "";

#define TEST_SUITE_START               \
  try                                  \
  {

#define TEST_SUITE_END                                                            \
  }                                                                               \
  catch (std::exception& exc)                                                     \
  {                                                                               \
    std::cerr << __FILE__ << ": exception outside test (" << exc.what() << ")\n"; \
  }                                                                               \
  catch (...)                                                                     \
  {                                                                               \
    std::cerr << __FILE__ << ": non-exception thrown outside test\n";             \
  }                                                                               \
  int exit_code = 0;                                                              \
  if ( failed_tests_count > 0 )                                                   \
  {                                                                               \
    std::cerr << __FILE__ << ": " << failed_tests_count << " test(s) failed\n";   \
    exit_code = 1;                                                                \
  }                                                                               \
  if ( test_suite_crached )                                                       \
  {                                                                               \
    std::cerr << __FILE__ << ": crached\n";                                       \
    exit_code = 2;                                                                \
  }                                                                               \
  return exit_code;  
  

#define TEST(EXPRESSION)                                                                         \
  try                                                                                            \
  {                                                                                              \
    if ( !( EXPRESSION ) )                                                                       \
    {                                                                                            \
      ++failed_tests_count;                                                                      \
      std::cerr << __FILE__ << ":" << __LINE__ << " test failed: " << #EXPRESSION << std::endl;  \
      if ( test_comment != "" ) std::cerr << test_comment << std::endl;                           \
    }                                                                                            \
  }                                                                                              \
  catch (std::exception& ex)                                                                     \
  {                                                                                              \
    test_suite_crached = true;                                                                   \
    ++failed_tests_count;                                                                        \
    std::cerr << __FILE__ << ":" << __LINE__ << " test throw exception: " << #EXPRESSION         \
              << " (" << ex.what() << ")\n";                                                     \
    if ( test_comment != "" ) std::cerr << test_comment << std::endl;                             \
  }                                                                                              \
  test_comment = "";

#define TEST_EXCEPTION(EXPRESSION, EXPECTED_MESSAGE)                                                         \
  try                                                                                                        \
  {                                                                                                          \
    EXPRESSION;                                                                                              \
    ++failed_tests_count;                                                                                    \
    std::cerr << __FILE__ << ":" << __LINE__ << " test_exception failed: " << #EXPRESSION <<                 \
      " (no exception thrown))" << std::endl;                                                                \
    if ( test_comment != "" ) std::cerr << test_comment << std::endl;                                         \
  }                                                                                                          \
  catch (std::exception& ex)                                                                                 \
  {                                                                                                          \
    std::string msg { ex.what() };                                                                           \
    if ( msg != EXPECTED_MESSAGE )                                                                           \
    {                                                                                                        \
      ++failed_tests_count;                                                                                  \
      std::cerr << __FILE__ << ":" << __LINE__ << " test_exception failed: " << #EXPRESSION <<               \
        " (wrong message, expected: ``" << EXPECTED_MESSAGE << "´´, found: ``" << msg << "´´)" << std::endl; \
      if ( test_comment != "" ) std::cerr << test_comment << std::endl;                                       \
    }                                                                                                        \
  }                                                                                                          \
  test_comment = "";

#define TEST_NO_EXCEPTION(EXPRESSION)                                                            \
  try                                                                                            \
  {                                                                                              \
    EXPRESSION;                                                                                  \
  }                                                                                              \
  catch (std::exception& ex)                                                                     \
  {                                                                                              \
    ++failed_tests_count;                                                                        \
    std::cerr << __FILE__ << ":" << __LINE__ << " test_no_exception failed: " << #EXPRESSION <<  \
      " (expection thrown with message: ``" << ex.what() << "´´)" << std::endl;                  \
    if ( test_comment != "" ) std::cerr << test_comment << std::endl;                             \
  }                                                                                              \
  test_comment = "";

#endif
