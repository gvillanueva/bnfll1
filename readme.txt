CST320 - Term Project
---------------------
This lab implements a LL(1) parser generator.  The expected input language is
close to Backus-Naur Form.  Non-terminal symbols should be wrapped within '<'
and '>'. Terminal symbols should be wrapped with '"'.  Empty strings (lambda)
should be identified by the ? operator.  For an example, please see
tests/data/firstFollow.bnf.

The lab does not produce a full compiler, only the first set for an LL(1)
parsing table.  To achieve a fullr LL(1) compiler generate for the BNF language,
there needs to be follow set computation, as well as a lexical analyzer for
input tokens to the generated parser.

Installation
============
No additional libraries should be required. Only a standard C++ compiler and STL
is necessary to build the lab from source.

Compiling from source
=====================
In the project root, use the compiler of your choice to build the code. For
example:

GNU Compiler Collection (GCC) - g++, mingw
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
From a bash command prompt
1. g++ -o bnfll1 src/*.cpp
2. ../lab1c <filename>
