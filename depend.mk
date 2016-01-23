O_FILES :=	o/./Converter.o o/./InputHandler.o o/./Operands.o o/./VMStack.o \
			o/./main.o

LIBS_DEPEND := 

libs:
.PHONY: libs



MAX_SOURCE_LEN := 18
o/./Converter.o: ./Converter.cpp ./Converter.hpp | o/./
o/./InputHandler.o: ./InputHandler.cpp ./InputHandler.hpp | o/./
o/./Operands.o: ./Operands.cpp ./Evalexpr.hpp ./Operands.hpp | o/./
o/./VMStack.o: ./VMStack.cpp ./Evalexpr.hpp ./MStack.hpp ./Operands.hpp \
	./VMStack.hpp | o/./
o/./main.o: ./main.cpp ./MStack.hpp ./Evalexpr.hpp ./Operands.hpp \
	./VMStack.hpp ./Converter.hpp | o/./
