# SMOR: Specialized Matrix for Operations Research
SMOR is a matrix library that is especially tuned for multiplication performance in operations research algorithms.

# Build Instructions
SMOR is a headers-only library. So, in order to use it in other projects, you are only required to include the headers and point the compiler to src/include directory.
To build the tests on Unix systems, simply issue the following:
* mkdir build
* cd build
* cmake ../
* make

Now, you have an executable file named "smortest".
