O_FILES :=	o/./InputHandler.o o/./Operands.o o/./main.o

LIBS_DEPEND := 

libs:
.PHONY: libs



MAX_SOURCE_LEN := 18
o/./InputHandler.o: ./InputHandler.cpp ./InputHandler.hpp | o/./
o/./Operands.o: ./Operands.cpp ./Evalexpr.hpp ./Operands.hpp | o/./
o/./main.o: ./main.cpp ./MStack.hpp ./Evalexpr.hpp ./Operands.hpp | o/./
