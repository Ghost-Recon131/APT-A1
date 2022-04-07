# APT Assignment 1
Name: Jingxuan Feng
Student Number: s3843790

# Known Bugs
- When switching branches in my Git Repository, CRLF line endings seem to be added again to all .expout test cases,
resulting in a failed test run when compared with .out files.
- This behavior is not always consistent, and I am unsure how to fix it. 
- A script has been provided loop through the test files and run the following command:  
```
dos2unix testCaseName.expout
```
- This should remove CRLF line endings from all tests. 

## Shell Scripts
To run these, use the following command to give permission to the shell script in terminal
```
chmod +x scriptName.sh
```

### build.sh
Compiles the program using as required
```
g++ -Wall -Werror -std=c++14 -O -o assign1 main.cpp Node.cpp NodeList.cpp PathPlanner.cpp milestone4.cpp
```

### clean.sh
Deletes the compiled binary 'assign1' as well as any .out files generated during testing. 

### fixCRLF.sh
Removes CRLF line endings from all .expout files. 

### test.sh
Calls "clean.sh", "build.sh" then "fixCRLF.sh". It then inputs the provided sample environment and matches the output to 
the expected output. This process is then repeated for all the tests I have written. At then end, it outputs the results 
of the comparison. Such as : 

```
Files sampleTest/sample01.out and sampleTest/sample01.expout are identical
Files TestCases/TC1.out and TestCases/TC1.expout are identical
Files TestCases/TC2.out and TestCases/TC2.expout are identical
```

## CMake
Used in CLion to test & debug, should not be used for actual compilation.


# Test Cases 
### sampleTest
Just the sample test and expected output given.

## TestCases Directory
Contains test cases written by me as part of Milestone 1. 

### Milestone 2&3 Test Cases 1 - 8 
- Tests basic functionality of Milestone 2-3
- Includes scenarios of multiple routes to goal, unreachable spaces in maze, multiple routes with same distance to G. 

### Milestone 4 Test Cases 1 - 11
- Tests basic functionality of Milestone 4
- Includes environment of either larger or smaller than 20x20
- Includes scenarios of multiple routes to goal, unreachable spaces in maze, multiple routes with same distance to G.
- Program will take some time (10-30sec depending on system specs)to complete Test Cases 7-10 as these use a fairly 
- larger sized environment. 

## Known Behaviors
- Program will prefer turning right rather than left when paths to G are of the same length. (See test case 10)
- Program will prefer going up rather than down when paths to G are of the same length. (See test case 11)
- Shortest path will always be calculated.