CC = gcc
CFLAGG = -g -Wall -std=c99
TAG = -fopenmp 
INPUT_FILE_ZERO  = ab.txt
INPUT_FILE_FIRST  = a.txt
INPUT_FILE_SECOND = b.txt
INPUT_FILE_THIRD  = c.txt
DEPENDENCIES_MAIN = main.c structs.o
EXEC_FILE_NAME = exec

all: clean compile

compile: ${DEPENDENCIES_MAIN}
	@echo "----Compiling...----"
	${CC} ${CFLAGG} ${TAG} -o ${EXEC_FILE_NAME}.out $^

%.o: %.c
	@echo "----Compiling header files...----"
	${CC} ${CFLAGG} ${TAG} -c $^ -o $@


run:
	seq 5 | xargs -Iz ./${EXEC_FILE_NAME}.out 30  ${INPUT_FILE_ZERO} ${INPUT_FILE_FIRST} 2

serial_run: zero_threads

zero_threads:
	@echo "Get status for 0 Thread"		
	seq 5 | xargs -Iz ./${EXEC_FILE_NAME}.out 30  ${INPUT_FILE_ZERO} ${INPUT_FILE_FIRST}   0
	@echo "------------------------"
	seq 5 | xargs -Iz ./${EXEC_FILE_NAME}.out 30  ${INPUT_FILE_ZERO} ${INPUT_FILE_SECOND}  0
	@echo "------------------------"
	seq 5 | xargs -Iz ./${EXEC_FILE_NAME}.out 30  ${INPUT_FILE_ZERO} ${INPUT_FILE_THIRD}   0
	@echo "========================"
	seq 5 | xargs -Iz ./${EXEC_FILE_NAME}.out 180 ${INPUT_FILE_ZERO} ${INPUT_FILE_FIRST}   0
	@echo "------------------------"
	seq 5 | xargs -Iz ./${EXEC_FILE_NAME}.out 180  ${INPUT_FILE_ZERO} ${INPUT_FILE_SECOND} 0
	@echo "------------------------"
	seq 5 | xargs -Iz ./${EXEC_FILE_NAME}.out 180  ${INPUT_FILE_ZERO} ${INPUT_FILE_THIRD}  0
	@echo "========================"
	seq 5 | xargs -Iz ./${EXEC_FILE_NAME}.out 365 ${INPUT_FILE_ZERO} ${INPUT_FILE_FIRST}   0
	@echo "------------------------"
	seq 5 | xargs -Iz ./${EXEC_FILE_NAME}.out 365  ${INPUT_FILE_ZERO} ${INPUT_FILE_SECOND} 0
	@echo "------------------------"
	seq 5 | xargs -Iz ./${EXEC_FILE_NAME}.out 365  ${INPUT_FILE_ZERO} ${INPUT_FILE_THIRD}  0
	@echo "QQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQ\n\n"

finall_run: D30 D180 D365

D30:
	@echo "DAYS 30"
	@echo "1 Thread"		
	seq 5 | xargs -Iz ./${EXEC_FILE_NAME}.out 30 ${INPUT_FILE_ZERO} ${INPUT_FILE_FIRST}   1
	@echo "------------------------"
	seq 5 | xargs -Iz ./${EXEC_FILE_NAME}.out 30 ${INPUT_FILE_ZERO} ${INPUT_FILE_SECOND}  1
	@echo "------------------------"
	seq 5 | xargs -Iz ./${EXEC_FILE_NAME}.out 30 ${INPUT_FILE_ZERO} ${INPUT_FILE_THIRD}   1
	@echo "========================"
	@echo "2 Thread"	
	seq 5 | xargs -Iz ./${EXEC_FILE_NAME}.out 30 ${INPUT_FILE_ZERO} ${INPUT_FILE_FIRST}   2
	@echo "------------------------"
	seq 5 | xargs -Iz ./${EXEC_FILE_NAME}.out 30 ${INPUT_FILE_ZERO} ${INPUT_FILE_SECOND}  2
	@echo "------------------------"
	seq 5 | xargs -Iz ./${EXEC_FILE_NAME}.out 30 ${INPUT_FILE_ZERO} ${INPUT_FILE_THIRD}   2
	@echo "========================"
	@echo "4 Thread"
	seq 5 | xargs -Iz ./${EXEC_FILE_NAME}.out 30 ${INPUT_FILE_ZERO} ${INPUT_FILE_FIRST}   4
	@echo "------------------------"
	seq 5 | xargs -Iz ./${EXEC_FILE_NAME}.out 30 ${INPUT_FILE_ZERO} ${INPUT_FILE_SECOND}  4
	@echo "------------------------"
	seq 5 | xargs -Iz ./${EXEC_FILE_NAME}.out 30 ${INPUT_FILE_ZERO} ${INPUT_FILE_THIRD}   4
	@echo "QQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQ\n\n"

D180:
	@echo "DAYS 180"		
	@echo "1 Thread"		
	seq 5 | xargs -Iz ./${EXEC_FILE_NAME}.out 180 ${INPUT_FILE_ZERO} ${INPUT_FILE_FIRST}   1
	@echo "------------------------"
	seq 5 | xargs -Iz ./${EXEC_FILE_NAME}.out 180 ${INPUT_FILE_ZERO} ${INPUT_FILE_SECOND}  1
	@echo "------------------------"
	seq 5 | xargs -Iz ./${EXEC_FILE_NAME}.out 180 ${INPUT_FILE_ZERO} ${INPUT_FILE_THIRD}   1
	@echo "========================"
	@echo "2 Thread"	
	seq 5 | xargs -Iz ./${EXEC_FILE_NAME}.out 180 ${INPUT_FILE_ZERO} ${INPUT_FILE_FIRST}   2
	@echo "------------------------"
	seq 5 | xargs -Iz ./${EXEC_FILE_NAME}.out 180 ${INPUT_FILE_ZERO} ${INPUT_FILE_SECOND}  2
	@echo "------------------------"
	seq 5 | xargs -Iz ./${EXEC_FILE_NAME}.out 180 ${INPUT_FILE_ZERO} ${INPUT_FILE_THIRD}   2
	@echo "========================"
	@echo "4 Thread"
	seq 5 | xargs -Iz ./${EXEC_FILE_NAME}.out 180 ${INPUT_FILE_ZERO} ${INPUT_FILE_FIRST}   4
	@echo "------------------------"
	seq 5 | xargs -Iz ./${EXEC_FILE_NAME}.out 180 ${INPUT_FILE_ZERO} ${INPUT_FILE_SECOND}  4
	@echo "------------------------"
	seq 5 | xargs -Iz ./${EXEC_FILE_NAME}.out 180 ${INPUT_FILE_ZERO} ${INPUT_FILE_THIRD}   4
	@echo "QQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQ\n\n"

D365:
	@echo "DAYS 365"		
	@echo "1 Thread"		
	seq 5 | xargs -Iz ./${EXEC_FILE_NAME}.out 365 ${INPUT_FILE_ZERO} ${INPUT_FILE_FIRST}   1
	@echo "------------------------"
	seq 5 | xargs -Iz ./${EXEC_FILE_NAME}.out 365 ${INPUT_FILE_ZERO} ${INPUT_FILE_SECOND}  1
	@echo "------------------------"
	seq 5 | xargs -Iz ./${EXEC_FILE_NAME}.out 365 ${INPUT_FILE_ZERO} ${INPUT_FILE_THIRD}   1
	@echo "========================"
	@echo "2 Thread"	
	seq 5 | xargs -Iz ./${EXEC_FILE_NAME}.out 365 ${INPUT_FILE_ZERO} ${INPUT_FILE_FIRST}   2
	@echo "------------------------"
	seq 5 | xargs -Iz ./${EXEC_FILE_NAME}.out 365 ${INPUT_FILE_ZERO} ${INPUT_FILE_SECOND}  2
	@echo "------------------------"
	seq 5 | xargs -Iz ./${EXEC_FILE_NAME}.out 365 ${INPUT_FILE_ZERO} ${INPUT_FILE_THIRD}   2
	@echo "========================"
	@echo "4 Thread"
	seq 5 | xargs -Iz ./${EXEC_FILE_NAME}.out 365 ${INPUT_FILE_ZERO} ${INPUT_FILE_FIRST}   4
	@echo "------------------------"
	seq 5 | xargs -Iz ./${EXEC_FILE_NAME}.out 365 ${INPUT_FILE_ZERO} ${INPUT_FILE_SECOND}  4
	@echo "------------------------"
	seq 5 | xargs -Iz ./${EXEC_FILE_NAME}.out 365 ${INPUT_FILE_ZERO} ${INPUT_FILE_THIRD}   4
	@echo "QQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQ\n\n"
	
clean:
	@echo "----Cleaning up...----"
	rm -f *.o ${EXEC_FILE_NAME}.out