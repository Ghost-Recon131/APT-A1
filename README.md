# APT Assignment 1
Name: Jingxuan Feng
Student Number: s3843790


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


### test.sh
Calls "clean.sh" then "build.sh". It then inputs the provided sample environment and matches the output to the expected output.
This process is then repeated for all the tests I have written. At then end, it outputs the results of the comparison.
Such as : 

```
Files sampleTest/sample01.out and sampleTest/sample01.expout are identical
Files TestCases/TC1.out and TestCases/TC1.expout are identical
Files TestCases/TC2.out and TestCases/TC2.expout are identical
```

## CMake
Used in CLion to test & debug, should not be used for actual compilation.


## Test Cases 
### sampleTest
Just the sample test and expected output given.

## TestCases
Contains test cases written by me as part of Milestone 1. 

Test Cases 1 - Number 
- Tests basic functionality of Milestone 2-3
- Includes scenarios of multiple routes to goal, unreachable spaces in maze, multiple routes with same distance to G. 

Test Cases Number - Number 
- Tests basic functionality of Milestone 4
- Includes environment of either larger or smaller than 20x20
- Includes scenarios of multiple routes to goal, unreachable spaces in maze, multiple routes with same distance to G. 