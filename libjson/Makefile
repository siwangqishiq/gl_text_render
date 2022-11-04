test_compile : json_test.cpp utest.hpp json.hpp json.cpp
	g++ json_test.cpp json.cpp -o test

test : test_compile
	./test

clean :
	rm -f test.exe 
	rm -f out.json



