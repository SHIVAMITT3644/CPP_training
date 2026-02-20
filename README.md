# Multi-Format File Parser – User Guide

This program allows you to parse JSON, CSV, and XML files** and display their data in a readable format.


## How to Run

1. Compile the program (from project root):

g++ -Iinclude -Ilib src/* main.cpp -o Main

2. Run the executable:

./Main

## Menu Overview
After running the program, you will see:

============================
1. Parse JSON File
2. Parse CSV File
3. Parse XML File
4. Exit
============================

Enter the number corresponding to the parser you want.

## Using a Parser

After selecting a parser, you will see:

============================
1. Enter File Name
2. Exit
============================

Choose 1 to enter a file name.

The program will check:

-> If the file exists.
-> If the file extension matches the parser type.
-> If valid, the file will be parsed and displayed in a readable format.

Choose 2 to exit or return to the main menu.

## File Requirements

JSON → Must follow standard JSON syntax.
CSV → Must have headers in the first row, values separated by commas.
XML → Must be well-formed with a single root element.

Place all files in the resources/ folder for the program to access them.

## Exiting

At any point, select 2 in the secondary menu to go back or exit the program.

From the main menu, select 4 to completely exit the application.
