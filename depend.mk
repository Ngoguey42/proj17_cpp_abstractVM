MKGEN_SRCSBIN_DEFAULT :=\
	obj/srcs/arith_operations.o\
	obj/srcs/arith_serializations.o\
	obj/srcs/arith_wrappers.o\
	obj/srcs/cfg_checker.o\
	obj/srcs/Controller.o\
	obj/srcs/InputHandler.o\
	obj/srcs/VMStack.o\
	obj/srcs_build/main.o
MKGEN_SRCSBIN_TEST :=\
	obj/srcs/arith_operations.o\
	obj/srcs/arith_serializations.o\
	obj/srcs/arith_wrappers.o\
	obj/srcs/cfg_checker.o\
	obj/srcs/Controller.o\
	obj/srcs/InputHandler.o\
	obj/srcs/VMStack.o\
	obj/srcs_test/limitsFixture.o\
	obj/srcs_test/limitsTests.o\
	obj/srcs_test/main.o\
	obj/srcs_test/numbersFixture.o\
	obj/srcs_test/numbersTests.o\
	obj/srcs_test/stackLogicFixture.o\
	obj/srcs_test/stackLogicTests.o
obj/srcs/arith_operations.o: include/arith_serializations.hpp include/arith_operations.hpp include/arith_types.hpp srcs/arith_operations.cpp | obj/srcs/
obj/srcs/arith_serializations.o: include/arith_serializations.hpp include/arith_types.hpp srcs/arith_serializations.cpp | obj/srcs/
obj/srcs/arith_wrappers.o: include/arith_serializations.hpp include/arith_wrappers.hpp include/arith_operations.hpp srcs/arith_wrappers.cpp include/arith_types.hpp | obj/srcs/
obj/srcs/cfg_checker.o: srcs/cfg_checker.cpp | obj/srcs/
obj/srcs/Controller.o: include/arith_wrappers.hpp include/Controller.hpp include/arith_types.hpp include/VMStack.hpp include/InputHandler.hpp include/cfg_checker.hpp include/arith_operations.hpp include/MStack.hpp srcs/Controller.cpp | obj/srcs/
obj/srcs/InputHandler.o: srcs/InputHandler.cpp include/InputHandler.hpp | obj/srcs/
obj/srcs/VMStack.o: include/arith_serializations.hpp include/arith_operations.hpp include/MStack.hpp include/arith_types.hpp include/arith_wrappers.hpp include/VMStack.hpp srcs/VMStack.cpp | obj/srcs/
obj/srcs_build/main.o: srcs_build/main.cpp include/Controller.hpp | obj/srcs_build/
obj/srcs_test/limitsFixture.o: srcs_test/limitsFixture.cpp | obj/srcs_test/
obj/srcs_test/limitsTests.o: srcs_test/limitsTests.cpp | obj/srcs_test/
obj/srcs_test/main.o: srcs_test/main.cpp | obj/srcs_test/
obj/srcs_test/numbersFixture.o: srcs_test/numbersFixture.cpp | obj/srcs_test/
obj/srcs_test/numbersTests.o: srcs_test/numbersTests.cpp | obj/srcs_test/
obj/srcs_test/stackLogicFixture.o: srcs_test/stackLogicFixture.cpp | obj/srcs_test/
obj/srcs_test/stackLogicTests.o: srcs_test/stackLogicTests.cpp | obj/srcs_test/
