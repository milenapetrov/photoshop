main:
	g++ -std=c++11 -o project2.out src/main.cpp src/Image.cpp
clean:
	del project2.out
	del *.cpp