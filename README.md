
// fichier <- stream << data        ofstream
// fichier -> stream >> data        ifstream

e47e8bda35bc0d8ef9a71e038f566eb85773645a:
second best of 5 try ->
make re  5.74s user 0.27s system 292% cpu 2.056 total

explicit instanciation of arith_serialization file: (add arith_serialization.cpp)
make re  6.10s user 0.30s system 288% cpu 2.221 total

removed 4 include<> from arith_serialization.hpp
make re  6.14s user 0.31s system 291% cpu 2.214 total