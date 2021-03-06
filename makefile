
test : 
        @g++ -g -O0 --coverage -I/path_to/googletest/googletest/include/ vector.hpp -pthread g_testing.cc /path_to/googletest/build/lib/libgtest.a -o test
        @./test
        @gcov g_testing.cc
        @lcov -c -d ./ -o test_coverage.info
        @genhtml test_coverage.info -o test_coverage


.PHONY : clean

clean :
        @rm -r test test_coverage *o *v *a &> /dev/null
