# PSU CSE597 FALL 2018 Report1
##Basic Info
1. Author: Wenliang Sun
2. Date: Nov. 5, 2018
3. Please see license.txt for licensing information
4. Progress Report 2

## Info of the Files
1. gpl.txt and license.txt include licensing information.
2. LU.cpp, Jacobi.cpp and GetMatrix.cpp are source codes.

## Compile on ACI
1. serial  
g++ serial.c -o serial.out -g -pg
./serial.out
gprof serial.out gmon.out

2. original parallel  
g++ -fopenmp parallel_original.c -o original.out -g -pg
./original.out
gprof original.out gmon.out

3. optimized parallel  
g++ -fopenmp parallel.c -o parallel.out -g -pg
./parallel.out
gprof parallel.out gmon.out

## Other Info
Please check the report to get more information of the project.