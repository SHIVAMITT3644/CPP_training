
The Banking Management System is a console-based C++ application developed using Object-Oriented Programming (OOP) principles.

This project simulates real-world banking operations including:

- Admin management
- Account holder registration and login
- Deposit and withdrawal operations
- Transaction history tracking
- Temporary and permanent account removal
- Strong input validation and error handling

The system is fully menu-driven and designed with clean architecture and dynamic memory management.

# System Architecture

## Core Classes

| Class | Responsibility |
|--------|---------------|
| `Bank` | Manages all users and accounts |
| `User` | Base class for Admin and AccountHolder |
| `Admin` | Performs administrative operations |
| `AccountHolder` | Performs banking operations |
| `Account` | Manages balance and transactions |
| `Transaction` | Stores transaction details |

# Features

##  Admin Features

- Create Account Holder Account
- Delete Account Holder Account
  - Temporary Deactivation
  - Permanent Removal
- View All Account Holders
- View Account Holder Balance
- View Account Holder Transaction History
- Logout

## Account Holder Features

- Signup
- Login
- View Account Details
- Deposit Money
- Withdraw Money
- View Current Balance
- View Mini Statement (Last 5 Transactions)
- View Full Statement
- Logout

# How to Compile

Using g++ (Linux / WSL / Mac):

g++ main.cpp src/*.cpp -I include -o bank

Run the program:

./bank

#  How to Use the Program

When the program starts, you will see:

Welcome to <Bank Name> Simulator!
1. Admin
2. Account Holder
3. Exit

# Admin Flow

## Step 1: Select Admin

Enter:1

## Step 2: Login

Enter:
- Username
- Password

If credentials are correct, the Admin menu will appear.

## Admin Menu
1. Create Account Holder Account
2. Delete Account Holder Account
3. View All Account Holders
4. View Account Holder Balance
5. View Account Holder Transaction History
6. Logout

## Creating an Account Holder

Admin must enter:

- Name
- Unique Username
- Password
- Initial Deposit

If successful:

Account created successfully.
Your account number is: XXXXX

## Deleting an Account

Admin can choose:

1. Temporary Delete
2. Permanent Delete

Temporary Delete:
- Account status becomes "Inactive"
- Account remains in system

Permanent Delete:
- Account is removed from system memory

# Account Holder Flow

From main menu select:2

You will see:
1. Login
2. Signup
3. Back

## Signup

User must enter:

- Name
- Unique Username
- Password
- Initial Deposit

System generates a unique Account Number.

---

## Login

User must enter:

- Username
- Password

If valid, Account Holder menu appears.
## Account Holder Menu

1. View Account Details
2. Deposit
3. Withdraw
4. View Balance
5. View Mini Statement
6. View Full Statement
7. Logout

## Deposit

- Enter amount
- Amount must be greater than 0
- Balance updates automatically
- Transaction is recorded

## Withdraw
- Enter amount
- Must be greater than 0
- Must be less than current balance
- Transaction is recorded

## Mini Statement
Displays last 5 transactions.

## Full Statement
Displays complete transaction history.

# Input Validation & Error Handling

The system handles:

- Invalid numeric input
- Empty string input
- Duplicate usernames
- Invalid password attempts
- Account not found
- Inactive accounts
- Insufficient balance
- Invalid menu selections

All inputs are validated using custom input validation functions.

# Transaction System

Each transaction stores:

- Transaction ID
- Transaction Type
- Amount
- Date & Time

Transactions are dynamically stored using manually resized arrays.

# Memory Management

- Dynamic arrays used for users and transactions
- Capacity doubles when full
- Proper destructors implemented to free allocated memory
- No memory leaks

# OOP Concepts Used

- Encapsulation
- Inheritance
- Polymorphism
- Dynamic Memory Allocation
- Constructor & Destructor Usage
- Static Members
- Enum Class
- Dynamic Casting
- Separation of Concerns

# Project Structure

assignment/week5/
│
├── include/
│   ├── Account.h
│   ├── AccountHolder.h
│   ├── Admin.h
│   ├── Bank.h
│   ├── Transaction.h
│   ├── User.h
│   ├── Constants.h
│   ├── Input.h
│
├── src/
│   ├── Account.cpp
│   ├── AccountHolder.cpp
│   ├── Admin.cpp
│   ├── Bank.cpp
│   ├── Transaction.cpp
│   ├── User.cpp
│   ├── Input.cpp
│
└── main.cpp
