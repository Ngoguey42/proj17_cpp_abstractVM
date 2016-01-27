O_FILES :=	o/srcs/Controller.o o/srcs/InputHandler.o o/srcs/VMStack.o \
			o/srcs/arith_wrappers.o o/srcs/cfg_checker.o o/srcs_test/test1.o

LIBS_DEPEND := 

libs:
.PHONY: libs



MAX_SOURCE_LEN := 23
o/srcs/Controller.o: srcs/Controller.cpp include/MStack.hpp \
	include/VMStack.hpp include/arith_operations.hpp \
	include/arith_serializations.hpp include/arith_types.hpp \
	include/arith_wrappers.hpp include/Controller.hpp include/InputHandler.hpp \
	include/cfg_checker.hpp | o/srcs/
o/srcs/InputHandler.o: srcs/InputHandler.cpp include/InputHandler.hpp | o/srcs/
o/srcs/VMStack.o: srcs/VMStack.cpp include/MStack.hpp include/VMStack.hpp \
	include/arith_operations.hpp include/arith_serializations.hpp \
	include/arith_types.hpp include/arith_wrappers.hpp | o/srcs/
o/srcs/arith_wrappers.o: srcs/arith_wrappers.cpp include/arith_operations.hpp \
	include/arith_serializations.hpp include/arith_types.hpp \
	include/arith_wrappers.hpp | o/srcs/
o/srcs/cfg_checker.o: srcs/cfg_checker.cpp | o/srcs/
o/srcs_test/test1.o: srcs_test/test1.cpp | o/srcs_test/
