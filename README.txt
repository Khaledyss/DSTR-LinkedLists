========================================================================
PROGRAM COMPILATION AND EXECUTION MANUAL
========================================================================
System Module : Student Record Management System
Architecture  : Singly Linked List (Custom Implementation from Scratch)
Developer     : Khaled Yaser Salaheldin Khalil Elhamamy
Student ID    : TP073614
Course Code   : CT077_LW1 (Lab Work #1)
========================================================================

------------------------------------------------------------------------
1. SYSTEM REQUIREMENTS & ENVIRONMENT
------------------------------------------------------------------------
* IDE Compatibilities: Microsoft Visual Studio (2019/2022) or CodeBlocks
* Compiler: GCC / MinGW or MSVC supporting C++11 standard or higher
* Core Library Dependencies: None (built purely from scratch without STL)

------------------------------------------------------------------------
2. INDIVIDUAL SUBMISSION DIRECTORY STRUCTURE
------------------------------------------------------------------------
To ensure seamless verification and execution, verify that your submission
directory contains the following files exactly in this root layout:

  ├── TP073614_KhaledYaserSalaheldinKhalilElhamamy_CT077_LW1.cpp
  ├── README.txt
  ├── TP073614_PerfRecord.txt
  ├── DATASET_README.txt
  ├── programmes.csv
  ├── students_500.csv
  ├── students_2000.csv
  ├── students_8000.csv
  └── students_30000.csv

*Note: Keep all data .csv files in the same relative execution directory 
       as the compiled application executable.*

------------------------------------------------------------------------
3. COMPILATION INSTRUCTIONS
------------------------------------------------------------------------
Choose one of the methods below based on your testing environment:

Method A: Command Line Implementation (GCC / MinGW)
  Open your terminal/command prompt inside the source directory and run:
  g++ -O3 -std=c++11 TP073614_KhaledYaserSalaheldinKhalilElhamamy_CT077_LW1.cpp -o StudentSystem.exe

  (The -O3 flag is highly recommended as it enables compiler optimizations 
  for high-precision runtime measurements during performance tests)

Method B: Visual Studio IDE
  1. Open Visual Studio and create a new "Empty C++ Project".
  2. Copy 'TP073614_KhaledYaserSalaheldinKhalilElhamamy_CT077_LW1.cpp' into 
     the project folder and add it under "Source Files" in the Solution Explorer.
  3. Ensure the build configuration dropdown at the top is toggled from 
     "Debug" to "Release" to ensure accurate microsecond benchmarking.
  4. Build the project using the shortcut (Ctrl + Shift + B).

Method C: CodeBlocks IDE
  1. Go to File -> New -> Empty File.
  2. Add the source code and save it as the specified .cpp filename.
  3. Go to Project -> Build Options -> Select "Release" -> Click OK.
  4. Click the 'Build and Run' icon (F9).

------------------------------------------------------------------------
4. EXECUTION & BENCHMARKING GUIDE
------------------------------------------------------------------------
1. Execute the output file (StudentSystem.exe).
2. Upon initiation, the program executes an automated high-resolution 
   chrono profiling sequence tracking all operations sequentially across 
   all four file constraints (n=500, n=2,000, n=8,000, n=30,000).
3. Standard display terminal buffers are systematically suppressed during 
   timing loops to prevent console I/O bottlenecks from polluting pure 
   algorithmic processing runtimes.
4. After benchmarking completes, the program opens an interactive console 
   menu where you can manually perform structural insertions, lookups, 
   deletions, count computations, and iterative pointer-swapping merge sorts.
========================================================================