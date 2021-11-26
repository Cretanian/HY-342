#!/bin/bash


echo "Get status for 0 Thread" > J_info0.txt
echo "========================" >> J_info0.txt
echo "Iteration Number 100" >> J_info0.txt
echo "========================" >> J_info0.txt

for i in 1 2 3 4 5
do	
	java -ea Main input1.txt 100 >> J_info0.txt
done

echo "------------------------" >> J_info0.txt

for i in 1 2 3 4 5
do	
	java -ea Main input2.txt 100 >> J_info0.txt
done

echo "------------------------" >> J_info0.txt

for i in 1 2 3 4 5
do	
	java -ea Main input3.txt 100 >> J_info0.txt
done

echo "------------------------" >> J_info0.txt

for i in 1 2 3 4 5
do	
	java -ea Main input4.txt 100 >> J_info0.txt
done

echo "------------------------" >> J_info0.txt

for i in 1 2 3 4 5
do	
	java -ea Main input5.txt 100 >> J_info0.txt
done

echo "========================" >> J_info0.txt
echo "Iteration Number 250" >> J_info0.txt
echo "========================" >> J_info0.txt

for i in 1 2 3 4 5
do	
	java -ea Main input1.txt 250 >> J_info0.txt
done

echo "------------------------" >> J_info0.txt

for i in 1 2 3 4 5
do	
	java -ea Main input2.txt 250 >> J_info0.txt
done

echo "------------------------" >> J_info0.txt

for i in 1 2 3 4 5
do	
	java -ea Main input3.txt 250 >> J_info0.txt
done

echo "------------------------" >> J_info0.txt

for i in 1 2 3 4 5
do	
	java -ea Main input4.txt 250 >> J_info0.txt
done

echo "------------------------" >> J_info0.txt

for i in 1 2 3 4 5
do	
	java -ea Main input5.txt 250 >> J_info0.txt
done

echo "========================" >> J_info0.txt
echo "Iteration Number 500" >> J_info0.txt
echo "========================" >> J_info0.txt

for i in 1 2 3 4 5
do	
	java -ea Main input1.txt 500 >> J_info0.txt
done

echo "------------------------" >> J_info0.txt

for i in 1 2 3 4 5
do	
	java -ea Main input2.txt 500 >> J_info0.txt
done

echo "------------------------" >> J_info0.txt

for i in 1 2 3 4 5
do	
	java -ea Main input3.txt 500 >> J_info0.txt
done

echo "------------------------" >> J_info0.txt

for i in 1 2 3 4 5
do	
	java -ea Main input4.txt 500 >> J_info0.txt
done

echo "------------------------" >> J_info0.txt

for i in 1 2 3 4 5
do	
	java -ea Main input5.txt 500 >> J_info0.txt
done
	
echo "QQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQ\n\n" >> J_info0.txt