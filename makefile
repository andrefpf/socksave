FLAGS := -pthread -lboost_filesystem -lboost_system


main: build/datastore.o build/server.o build/utils.o build/config.o
	g++ src/main.cpp -o main.o $(FLAGS) -I include/ $^

build/%.o: src/%.cpp
	g++ $< -o $@ -c -Wall $(FLAGS) -I include/

test:
	g++ src/test.cpp -o test.o $(FLAGS) $^

clean:
	@ rm -rf ./build/*
	@ rm -rf main.o
	@ rm -rf test.o

clean_data:
	@ rm -rf ./output/*