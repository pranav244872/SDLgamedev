build:
	g++ -Wall -std=c++17 -I "./libs/" src/*.cpp -l SDL2 -l SDL2_image -l SDL2_ttf -l lua5.4 -o gameengine

run:
	./gameengine

clean:
	rm gameengine
