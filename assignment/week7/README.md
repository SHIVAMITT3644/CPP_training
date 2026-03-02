Overview

This project is a Bank Management System Simulator developed in C++ using Object-Oriented Programming principles.

It supports:

Admin operations
Account Holder operations
Deposit & Withdrawal
Transaction History
Login functionality
Unit Testing using Google Test & Google Mock

Project Structure
week7/
│
├── include/        → Header files
├── src/            → Source files
├── test/include    → Unit test files header
|---test/src        → Unit test files (Google Test & Google Mock) 
├── README.md
 Requirements

Make sure the following are installed:

g++ (C++17 or above)
Google Test
Google Mock
pthread library

Install on Ubuntu:
sudo apt update
sudo apt install build-essential
sudo apt install libgtest-dev
sudo apt install libgmock-dev
How to Compile the Application

Navigate to the week7 directory:

g++ -Iinclude src/*.cpp -o bank_app

 Run the Application
./bank_app

How to Compile Unit Tests
g++  -Iinclude -Itest/include \
src/*.cpp test/*.cpp \
-lgmock -lgmock_main -lgtest -lpthread \
-o test_runner

Run Unit Tests
./test_runner

Expected output:

[==========] Running 54 tests...
[  PASSED  ] 54 tests.
Concepts Used

Object-Oriented Programming (Encapsulation, Abstraction, Polymorphism)

Inheritance
Virtual Functions
Dynamic Casting
Interface Design (IBank)
Dependency Injection
Unit Testing
Mocking (Google Mock)
Separation of Business Logic and UI

Design Highlights

IBank interface created for loose coupling and testing
MockBank used to test use cases independently
Admin and AccountHolder inherit from base class User
Clean separation between simulator logic and business logic
All major modules are unit tested

Test Coverage

Modules Covered:

Account
AccountHolder
Admin
Bank
Bank Simulator Usecases

Total Test Suites: 12
Total Tests: 54
All Tests Passing 
