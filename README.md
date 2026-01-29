PART 1: IMPLICIT DYNAMIC LINKING

Step 1: Compile library source files into object files

From the project root:
g++ -fPIC -Iinclude -c src/*.cpp

Step 2: Create the shared library
g++ -shared -o lib/libMathImplicit.so \
Addition.o Subtraction.o Multiplication.o Division.o

Step 3: Compile the implicit application
g++ -Iinclude app/ImplicitCalulatorApp.cpp \
-Llib -lMathImplicit -o ImplicitCalulatorApp

Step 4: Run the implicit application
LD_LIBRARY_PATH=./lib ./ImplicitCalulatorApp


PART 2: EXPLICIT DYNAMIC LINKING

Step 1: Create the explicit shared library
g++ -shared -o lib/libMathExplicit.so \
Addition.o Subtraction.o Multiplication.o Division.o

Step 2: Compile the explicit application
g++ -Iinclude app/ExplicitCalulatorApp.cpp -ldl -o app/ExplicitCalulatorApp

Step 3: Run the explicit application
From project root:
./app/ExplicitCalulatorApp

