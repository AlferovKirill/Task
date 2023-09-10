file = "testData/degrees.txt"
all: exe
	./coordinates $(file)
	-rm coordinates 2>/dev/null
exe: main.c
	gcc -o coordinates main.c kinematic.c -lm
clean:
	-rm coordinates 2>/dev/null
