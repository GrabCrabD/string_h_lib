FLAGS= -Wall -Wextra -Werror
STD= -std=c11

all: s21_string.a

style:
	clang-format -i -style=google *.c
	clang-format -style=google -n *.c

s21_string.a: s21_string
	ar rc s21_string.a s21_*.o
	ranlib s21_string.a

s21_string: s21_string.c s21_sprintf.c s21_string.h
	gcc ${FLAGS} ${STD} -c s21_string.c s21_sprintf.c

test: s21_string.a test.c
	gcc ${FLAGS} ${STD} -c test.c
	gcc -c -fprofile-arcs -ftest-coverage s21_string.c s21_sprintf.c
	gcc -fprofile-arcs -ftest-coverage s21_string.c s21_sprintf.c test.o -lcheck -lm -lpthread -o run_tests
	./run_tests

gcov_report: test
	mkdir report
	./run_tests
	gcov -f *.gcno
	gcovr -r . --html --html-details -o report/report.html

clean:
	rm -rf *.o *.gcov *.gcno *.gcda test run_tests s21_string s21_string.a report
