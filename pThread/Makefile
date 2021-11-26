CC = gcc
CFLAGG = -g -Wall
TAG = -pthread
INPUT_FILE_NAME = a.txt
NUMBER_OF_THREADS = 3
DEPENDENCIES_MAIN = main.c structs.o
EXEC_FILE_NAME = exec

all: clean compile

compile: ${DEPENDENCIES_MAIN}
	@echo "----Compiling...----"
	${CC} ${CFLAGG} ${TAG} -o ${EXEC_FILE_NAME}.out $^

%.o: %.c
	@echo "----Compiling header files...----"
	${CC} ${CFLAGG} -c $^ -o $@

run:
	@echo "running file: '${INPUT_FILE_NAME}' with '${NUMBER_OF_THREADS}' threads.."
	./${EXEC_FILE_NAME}.out ${INPUT_FILE_NAME} ${NUMBER_OF_THREADS}

clean:
	@echo "----Cleaning up...----"
	rm -f *.o ${EXEC_FILE_NAME}.out