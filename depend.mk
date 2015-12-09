O_FILES :=	o/./Operands.o o/./main.o

LIBS_DEPEND := 

libs:
.PHONY: libs



MAX_SOURCE_LEN := 14
o/./Operands.o: ./Operands.cpp ./Operands.hpp | o/./
o/./main.o: ./main.cpp ./Operands.hpp ./Evalexpr.hpp | o/./
