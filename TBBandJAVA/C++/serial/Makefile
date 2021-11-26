CC = g++
CFLAGG = -g -Wall -std=c++14
INPUT_FILE_FIRST  = input1.txt
INPUT_FILE_SECOND = input2.txt
INPUT_FILE_THIRD  = input3.txt
INPUT_FILE_FORTH  = input4.txt
INPUT_FILE_FIFTH  = input5.txt
MAIN = main.cpp
EXEC_FILE_NAME = exec


all: clean compile

compile: 
	clear
	@echo "----Compiling...----"
	${CC} ${CFLAGG} ${MAIN} -o ${EXEC_FILE_NAME}.out 

run:
	./${EXEC_FILE_NAME}.out ${INPUT_FILE_FIRST} 500

clean:
	clear
	@echo "----Cleaning up...----"
	rm -f *.o ${EXEC_FILE_NAME}.out

zero_threads:
	@echo "Get status for 0 Thread" > info0.txt
	@echo "========================" >> info0.txt
	@echo "Iteration Number 100" >> info0.txt
	@echo "========================" >> info0.txt	
	seq 5 | xargs -Iz ./${EXEC_FILE_NAME}.out ${INPUT_FILE_FIRST} 100 >> info0.txt
	@echo "------------------------" >> info0.txt
	seq 5 | xargs -Iz ./${EXEC_FILE_NAME}.out ${INPUT_FILE_SECOND} 100 >> info0.txt
	@echo "------------------------" >> info0.txt
	seq 5 | xargs -Iz ./${EXEC_FILE_NAME}.out ${INPUT_FILE_THIRD} 100 >> info0.txt
	@echo "------------------------" >> info0.txt
	seq 5 | xargs -Iz ./${EXEC_FILE_NAME}.out ${INPUT_FILE_FORTH} 100 >> info0.txt
	@echo "------------------------" >> info0.txt
	seq 5 | xargs -Iz ./${EXEC_FILE_NAME}.out ${INPUT_FILE_FIFTH} 100 >> info0.txt
	@echo "========================" >> info0.txt
	@echo "Iteration Number 250"	>> info0.txt
	@echo "========================" >> info0.txt
	seq 5 | xargs -Iz ./${EXEC_FILE_NAME}.out ${INPUT_FILE_FIRST} 250 >> info0.txt
	@echo "------------------------" >> info0.txt
	seq 5 | xargs -Iz ./${EXEC_FILE_NAME}.out ${INPUT_FILE_SECOND} 250 >> info0.txt
	@echo "------------------------" >> info0.txt
	seq 5 | xargs -Iz ./${EXEC_FILE_NAME}.out ${INPUT_FILE_THIRD} 250 >> info0.txt
	@echo "------------------------" >> info0.txt
	seq 5 | xargs -Iz ./${EXEC_FILE_NAME}.out ${INPUT_FILE_FORTH} 250 >> info0.txt
	@echo "------------------------" >> info0.txt
	seq 5 | xargs -Iz ./${EXEC_FILE_NAME}.out ${INPUT_FILE_FIFTH} 250 >> info0.txt
	@echo "========================" >> info0.txt
	@echo "Iteration Number 500" >> info0.txt
	@echo "========================" >> info0.txt
	seq 5 | xargs -Iz ./${EXEC_FILE_NAME}.out ${INPUT_FILE_FIRST} 500 >> info0.txt
	@echo "------------------------" >> info0.txt
	seq 5 | xargs -Iz ./${EXEC_FILE_NAME}.out ${INPUT_FILE_SECOND} 500 >> info0.txt
	@echo "------------------------" >> info0.txt
	seq 5 | xargs -Iz ./${EXEC_FILE_NAME}.out ${INPUT_FILE_THIRD} 500 >> info0.txt
	@echo "------------------------" >> info0.txt
	seq 5 | xargs -Iz ./${EXEC_FILE_NAME}.out ${INPUT_FILE_FORTH} 500 >> info0.txt
	@echo "------------------------" >> info0.txt
	seq 5 | xargs -Iz ./${EXEC_FILE_NAME}.out ${INPUT_FILE_FIFTH} 500 >> info0.txt
	@echo "QQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQ\n\n" >> info0.txt