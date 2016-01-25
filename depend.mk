O_FILES :=	o/srcs/InputHandler.o o/srcs/VMStack.o o/srcs/arith_wrappers.o \
			o/srcs/main.o

LIBS_DEPEND := 

libs:
.PHONY: libs



MAX_SOURCE_LEN := 23
o/srcs/InputHandler.o: srcs/InputHandler.cpp srcs/InputHandler.hpp | o/srcs/
o/srcs/VMStack.o: srcs/VMStack.cpp srcs/MStack.hpp srcs/VMStack.hpp \
	srcs/arith_operations.hpp srcs/arith_serializations.hpp \
	srcs/arith_types.hpp srcs/arith_wrappers.hpp | o/srcs/
o/srcs/arith_wrappers.o: srcs/arith_wrappers.cpp srcs/arith_operations.hpp \
	srcs/arith_serializations.hpp srcs/arith_types.hpp srcs/arith_wrappers.hpp \
	| o/srcs/
o/srcs/main.o: srcs/main.cpp srcs/MStack.hpp srcs/VMStack.hpp \
	srcs/arith_operations.hpp srcs/arith_serializations.hpp \
	srcs/arith_types.hpp srcs/arith_wrappers.hpp | o/srcs/
