#

# Executable name
NAME			:= avm

# Git submodule to init
MODULES			:=
# Makefiles to call
LIBS			:=

# Base flags
BASE_FLAGS		= -Wall -Wextra -std=c++14
HEAD_FLAGS		= $(addprefix -I,$(INCLUDE_DIRS))

# Compilation flags (per language)
C_FLAGS			= $(HEAD_FLAGS) $(BASE_FLAGS)
CPP_FLAGS		= $(HEAD_FLAGS) $(BASE_FLAGS)

LINK_FLAGS		= $(BASE_FLAGS)


# Project directories
DIRS			:= srcs srcs_build

# LINK_FLAGS		+= -lstdc++
# LINK_FLAGS		+= -fno-exceptions
# DIRS			:= srcs srcs_test
# LINK_FLAGS		+= -lboost_unit_test_framework

INCLUDE_DIRS	:= include

# CC_CPP			:= clang++
CC_CPP			:= g++
# CC_CPP			:= x86_64-w64-mingw32-clang++
# CC_CPP			:= i686-w64-mingw32-clang++



ifeq ($(DEBUG_MODE),1)
	# Extra flags used in debug mode
	BASE_FLAGS	+= -g
	C_FLAGS		+=
	CPP_FLAGS	+=
else
	# Extra flags used when not in debug mode
	BASE_FLAGS	+= -O2
	C_FLAGS		+=
	CPP_FLAGS	+=
endif

DEBUG_MODE		?= 0
export DEBUG_MODE

# Jobs
JOBS			:= 8

# Column output
COLUMN_OUTPUT	:= 0

ifeq ($(COLUMN_OUTPUT),0)
	PRINT_OK	= printf '\033[32m$<\033[0m\n'
	PRINT_LINK	= printf '\033[32m$@\033[0m\n'
else
	PRINT_OK	= echo $(patsubst $(firstword $(DIRS))/%,%,$<) >> $(PRINT_FILE)
	PRINT_LINK	= printf '\n\033[32m$@\033[0m\n'
endif

# Objects directory
O_DIR			:= o

# Depend file name
DEPEND			:= depend.mk

# tmp
MODULE_RULES	:= $(addsuffix /.git,$(MODULES))
PRINT_FILE		:= .tmp_print
SHELL			:= /bin/bash

# Default rule (need to be before any include)
all: $(MODULE_RULES) libs
ifeq ($(COLUMN_OUTPUT),0)
	make -j$(JOBS) $(NAME)
else
	PER_LINE=$$((`tput cols` / $$(($(MAX_SOURCE_LEN) + 2))));			\
	CURR=0;																\
	rm -f $(PRINT_FILE);												\
	touch $(PRINT_FILE);												\
	tail -n0 -f $(PRINT_FILE) | while read l;							\
	do																	\
		if [[ $$CURR -ge $$PER_LINE ]];									\
		then															\
			CURR=0;														\
			echo;														\
		fi;																\
		CURR=$$(($$CURR + 1));											\
		printf '\033[32m%-*s\033[0m  ' "$(MAX_SOURCE_LEN)" "$$l";		\
	done &																\
	make -j$(JOBS) $(NAME);												\
	STATUS=$$?;															\
	kill -9 `jobs -p`;													\
	rm -f $(PRINT_FILE);												\
	exit $$STATUS
endif

# Include $(O_FILES) and dependencies
-include $(DEPEND)

# Linking
$(NAME): $(LIBS_DEPEND) $(O_FILES)
	$(CC_CPP) -o $@ $(O_FILES) $(LINK_FLAGS) && $(PRINT_LINK)

# Compiling
$(O_DIR)/%.o: %.c
	clang $(C_FLAGS) -c $< -o $@ && $(PRINT_OK)
$(O_DIR)/%.o: %.cpp
	$(CC_CPP) $(CPP_FLAGS) -c $< -o $@ && $(PRINT_OK)

# Init submodules
$(MODULE_RULES):
	git submodule init $(@:.git=)
	git submodule update $(@:.git=)

# Create obj directories
$(O_DIR)/%/:
	mkdir -p $@

# Set debug mode and make
debug: _debug all

# Clean, set debug mode and make
rebug: fclean debug

# Clean obj files
clean:
	rm -f $(PRINT_FILE)
	rm -f $(O_FILES)

# Clean everything
fclean: clean
	rm -f $(NAME)

# Clean and make
re: fclean all

# Set debug flags
_debug:
	$(eval DEBUG_MODE = 1)

.SILENT:
.PHONY: all clean fclean re debug rebug _debug
