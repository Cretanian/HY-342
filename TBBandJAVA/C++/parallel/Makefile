CC = g++
CFLAGG = -g -Wall -std=c++14
TAG = -ltbb
INPUT_FILE_FIRST  = input1.txt
INPUT_FILE_SECOND = input2.txt
INPUT_FILE_THIRD  = input3.txt
INPUT_FILE_FORTH  = input4.txt
INPUT_FILE_FIFTH  = input5.txt
MAIN = main.cpp
EXEC_FILE_NAME = exec
ONE_THREADS = 1
TWO_THREADS = 2
FOUR_THREADS = 4

all: clean compile

compile:
	clear
	@echo "----Compiling...----"
	${CC} ${CFLAGG} ${MAIN} -o ${EXEC_FILE_NAME}.out ${TAG}

run30:
	./${EXEC_FILE_NAME}.out ${INPUT_FILE_FIFTH} 500 ${ONE_THREADS}

run180:
	./${EXEC_FILE_NAME}.out ${INPUT_FILE_FIRST} 180 ${ONE_THREADS}

run365:
	./${EXEC_FILE_NAME}.out ${INPUT_FILE_FIFTH} 365 ${ONE_THREADS}

clean:
	clear
	@echo "----Cleaning up...----"
	rm -f *.o ${EXEC_FILE_NAME}.out

