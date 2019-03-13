all:
	g++ *.cpp -I/usr/include/postgresql/10/server -L/usr/include/postgresql/10/server -o result
lib:
	g++ *.cpp -I/usr/include/postgresql/10/server -L/usr/include/postgresql/10/server -fpic -c
	g++ -shared -o catslib.so *.o
clean:
	rm -rf *.o
