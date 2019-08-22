CC=g++
CFLAGS=-Wall -O3

openmp: 
	$(CC) $(CFLAGS) -fopenmp -o parallel_run matmul.cpp
	export OMP_NUM_THREADS=1
	./parallel_run > results_parallel_1threads.txt
	python check_results.py
	export OMP_NUM_THREADS=2
	./parallel_run > results_parallel_2threads.txt
	python check_results.py
	export OMP_NUM_THREADS=3
	./parallel_run > results_parallel_3threads.txt
	python check_results.py
	export OMP_NUM_THREADS=4
	./parallel_run > results_parallel_4threads.txt
	python check_results.py

serial:
	$(CC) $(CFLAGS) -o serial_run matmul.cpp
	./serial_run > results_serial.txt
	python check_results.py

all: serial openmp
