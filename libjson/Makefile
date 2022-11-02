test_compile : json_test.cpp utest.h json.h json.cpp
	g++ json_test.cpp json.cpp -o test

test : test_compile
	./test

clean :
	rm -f test.exe 
	rm -f out.json



