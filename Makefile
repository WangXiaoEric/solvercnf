CFLAGS = -O3 -o ./ec
SRC = main.cpp

all:
	/tools/linux/gnu/centos6/toolkits/bin/g++ -std=c++11 ${CFLAGS} ${SRC}

clean:
	rm -f ./ec
