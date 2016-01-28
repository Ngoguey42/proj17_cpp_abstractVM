O_FILES :=	o/srcs/Controller.o o/srcs/InputHandler.o o/srcs/VMStack.o \
			o/srcs/arith_wrappers.o o/srcs/cfg_checker.o \
			o/srcs_test/limitsFixture.o o/srcs_test/limitsTests.o \
			o/srcs_test/main.o o/srcs_test/numbersFixture.o \
			o/srcs_test/numbersTests.o o/srcs_test/stackLogicFixture.o \
			o/srcs_test/stackLogicTests.o

LIBS_DEPEND := 

libs:
.PHONY: libs



MAX_SOURCE_LEN := 31
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
o/srcs_test/limitsFixture.o: srcs_test/limitsFixture.cpp \
	srcs_test/limitsFixture.hpp include/Controller.hpp srcs_test/testConf.hpp \
	srcs_test/testTools.hpp | o/srcs_test/
o/srcs_test/limitsTests.o: srcs_test/limitsTests.cpp \
	srcs_test/limitsFixture.hpp | o/srcs_test/
o/srcs_test/main.o: srcs_test/main.cpp | o/srcs_test/
o/srcs_test/numbersFixture.o: srcs_test/numbersFixture.cpp \
	include/Controller.hpp srcs_test/numbersFixture.hpp srcs_test/testConf.hpp \
	srcs_test/testTools.hpp | o/srcs_test/
o/srcs_test/numbersTests.o: srcs_test/numbersTests.cpp include/Controller.hpp \
	srcs_test/numbersFixture.hpp srcs_test/testConf.hpp \
	srcs_test/testTools.hpp | o/srcs_test/
o/srcs_test/stackLogicFixture.o: srcs_test/stackLogicFixture.cpp \
	include/Controller.hpp srcs_test/stackLogicFixture.hpp \
	srcs_test/testConf.hpp srcs_test/testTools.hpp | o/srcs_test/
o/srcs_test/stackLogicTests.o: srcs_test/stackLogicTests.cpp \
	include/Controller.hpp srcs_test/stackLogicFixture.hpp \
	srcs_test/testConf.hpp srcs_test/testTools.hpp | o/srcs_test/
