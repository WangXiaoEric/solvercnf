CFLAGS = -O3 -o ./ec
SRC = main.cpp

all:
# 	g++ -std=c++11 ${CFLAGS} ${SRC}
	/tools/linux/gnu/centos6/toolkits/bin/g++ -static-libstdc++ -std=c++11 ${CFLAGS} ${SRC}
clean:
	rm -f ./ec
