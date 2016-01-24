O_FILES :=	o/./InputHandler.o o/./VMStack.o o/./arith_wrappers.o o/./main.o

LIBS_DEPEND := 

libs:
.PHONY: libs



MAX_SOURCE_LEN := 20
o/./InputHandler.o: ./InputHandler.cpp ./InputHandler.hpp | o/./
o/./VMStack.o: ./VMStack.cpp ./MStack.hpp ./VMStack.hpp ./arith_operations.hpp \
	./arith_serializations.hpp ./arith_types.hpp ./arith_wrappers.hpp | o/./
o/./arith_wrappers.o: ./arith_wrappers.cpp ./arith_operations.hpp \
	./arith_serializations.hpp ./arith_types.hpp ./arith_wrappers.hpp | o/./
o/./main.o: ./main.cpp ./MStack.hpp ./VMStack.hpp ./arith_operations.hpp \
	./arith_serializations.hpp ./arith_types.hpp ./arith_wrappers.hpp | o/./
