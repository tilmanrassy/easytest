Easytest
========

Simple header-only C++ library for unit tests.

A test is represented by one of the macros TEST, TEST_EXCEPTION, and TEST_NO_EXCEPTION.

TEST accepts a C++ expression as argument. The expression must evaluate to a boolean. The
test is considered successful if, and only if, the evaluation yields true.

TEST_EXCEPTION accepts two arguments, a C++ expression and a string. The test is considered
successful if, and only if, the expression throws an exception, and the exception's explanatory string
as obtained by `what()` equals the string passed as the second argument.

TEST_NO_EXCEPTION accepts a C++ expression as argument. The test is considered successful if,
and only if, the expression throws no exception.

One ore more tests form a test suite. A test suite is represented by a C++ source file containing one ore more of the macros
described above. The file must also contain the Macros TEST_SUITE_INIT, TEST_SUITE_START and TEST_SUITE_END to work properly.
Here is an example:

```c++

#include <regex>
#include <easytest.hpp>
#include "../src/Float.hpp"
#include "../src/Integer.hpp"

TEST_SUITE_INIT;

int main ()
{
  TEST_SUITE_START;

  Oma::Float* num = Oma::Float::type.get_instance(-0.5);

  TEST(num->get_value() == -0.5);
  TEST(std::regex_match(num->to_string(), std::regex("-0\\.50*")));
  TEST(num->get_type() == Oma::Float::type);
  TEST(num->get_type().get_name() == "float");

  Oma::Float* num1 = Oma::Float::type.get_instance(-0.5);
  Oma::Float* num2 = Oma::Float::type.get_instance(3.1);

  TEST(num != num1);
  TEST(num != num2);
  TEST(num->has_same_type_and_equals(num1) == true);
  TEST(num->has_same_type_and_equals(num2) == false);

  Oma::Float* num3 = Oma::Float::type.get_instance(5);
  TEST(num3->get_value() == 5);
  TEST(std::regex_match(num3->to_string(), std::regex("5(?:\\.0*)?")));
  
  TEST_EXCEPTION(num->is_true(), "Number cannot be interpreted as boolean");
  
  TEST_SUITE_END;
}
```

Compiling the source file produces an executable program. Running the program performs the tests. When all tests pass,
the program simply exits with code 0. When one or more tests fail, the program prints a message to stderr for each
failed test. The message contains the program name, the source line number, and the expression of the failed test. The
exit code is 1 in this case.

The macro TEST_SUITE_INIT initializes some global variables. The macros TEST_SUITE_START and TEST_SUITE_END surround the
region where testing takes place. Each TEST macro must occurr within this region.

The project also provides a shell script named `easytest.sh`. It is a simply utility to run several test suites in turn
and present the results in a compact way in the console. A prerequisite for the script to function is that the test
suite executables have names ending with `_test_suite`. The script searches for files in the working directory
fulfilling this naming convention. Each such file is considered a test suite and executed. If all tests of the test
suite pass, the script prints "ok", otherwise "failed". In the former case, all outpunt of the test suite is
suppressed. In the latter case, the stdout and stderr output is printed to the screen. This looks like the following:

![Script output (no fails)](screenshots/01_script_output.png "Script output (no fails)")

Or, if failed tests occur:

![Script output (with fails)](screenshots/02_script_output.png "Script output (with fails)")


