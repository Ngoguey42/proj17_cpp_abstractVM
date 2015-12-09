O_FILES :=	o/./Operands.o o/./main.o

LIBS_DEPEND := 

libs:
.PHONY: libs



MAX_SOURCE_LEN := 14
o/./Operands.o: ./Operands.cpp ./Evalexpr.hpp ./Operands.hpp | o/./
o/./main.o: ./main.cpp ./MStack.hpp ./Evalexpr.hpp ./Operands.hpp | o/./
