# Unlimited-length integers calculator
A C program which allows the user to store unlimited-length numbers and perform basic operations on them.
# Synopsis
Program created as a project for Algorithms and Data Structures classes. The main objective was to make the program able to store numbers which exceed the limit of C long long data type. The main challenge was to implement written addition and subtraction. It seems easy on paper, but algorythmically it needs a lot of code and small operations.
# How does it work
Each digit is stored in a dynamically allocated array. Subtraction and adding operation are implemented just like written operations (digit by digit, residual etc.). Minimum and maximum values are updated every time an existing number is modified.
# Commands and input
## User input
At first a user has to enter n number of stored numbers. Then the program reads n numbers and stores them.
## Commands
```
min             // prints out a minimum value
max             // prints out a maximum value
j = k + l       // performs addition of two numbers (j,k,l are indexes from range 0 to n)
n3 = n1 - n2    // subtraction of two numbers
?               // prints out all stored numbers
q               // quits the program
```
# Known bugs
- Code readability
- Program returns wrong adding and subtraction results when the result should equal 0