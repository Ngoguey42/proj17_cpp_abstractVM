#

# ============================================================================ #
# Directories

# Executable name
NAME			:= avm
# Git submodule to init
MODULES			:=
# Makefiles to call
LIBS			:=

INCLUDE_DIRS	= include
SRCS_DIRS		= srcs
O_DIR			:= o


# ============================================================================ #
# Default  flags / compilers
BASE_FLAGS		= -Wall -Wextra
HEAD_FLAGS		= $(addprefix -I,$(INCLUDE_DIRS))
LD_FLAGS		= $(BASE_FLAGS)

CC_LD			= $(CC_CPP)

MAKEFLAGS		+= -j


# ============================================================================ #
# Build mode
BUILD_MODE		= build
ifeq ($(BUILD_MODE),test)
	SRCS_DIRS		+= srcs_test
	LD_FLAGS		+= -lboost_unit_test_framework
	BASE_FLAGS		+= -O2
else ifeq ($(BUILD_MODE),debug)
	SRCS_DIRS		+= srcs_build
	BASE_FLAGS		+= -g
else
	SRCS_DIRS		+= srcs_build
	BASE_FLAGS		+= -O2
endif

# legacy with makemake ===========================
DIRS			:= srcs srcs_build
# DEBUG_MODE		?= 0
# export DEBUG_MODE
# /legacy with makemake ===========================


# ============================================================================ #
# Misc
UNAME			:= $(shell uname -o)
PRINT_OK		= printf '\033[32m$<\033[0m\n'
PRINT_LINK		= printf '\033[32m$@\033[0m\n'
DEPEND			:= depend.mk
MODULE_RULES	:= $(addsuffix /.git,$(MODULES))
SHELL			:= /bin/bash


# ============================================================================ #
# C
C_FLAGS			= $(HEAD_FLAGS) $(BASE_FLAGS)
ifeq ($(UNAME),Cygwin)
	CC_C		= x86_64-w64-mingw32-gcc
else
	CC_C		= clang
endif


# ============================================================================ #
# C++
CPP_FLAGS		= $(HEAD_FLAGS) $(BASE_FLAGS) -std=c++14
ifeq ($(UNAME),Cygwin)
	CC_CPP		= x86_64-w64-mingw32-g++
	LD_FLAGS	+= -static
else
	CC_CPP		= clang++
endif



# ============================================================================ #
# Rules

# Default rule (need to be before any include)
all: $(MODULE_RULES) libs $(NAME)

# Include $(O_FILES) and dependencies
-include $(DEPEND)

# Linking
$(NAME): $(LIBS_DEPEND) $(O_FILES)
	$(CC_LD) -o $@ $(O_FILES) $(LD_FLAGS) && $(PRINT_LINK)

# Compiling
$(O_DIR)/%.o: %.c
	$(CC_C) $(C_FLAGS) -c $< -o $@ && $(PRINT_OK)
$(O_DIR)/%.o: %.cpp
	$(CC_CPP) $(CPP_FLAGS) -c $< -o $@ && $(PRINT_OK)

# Init submodules
$(MODULE_RULES):
	git submodule init $(@:.git=)
	git submodule update $(@:.git=)

# Create obj directories
$(O_DIR)/%/:
	mkdir -p $@

# Clean obj files
clean:
	rm -f $(O_FILES)

# Clean everything
fclean: clean
	rm -f $(NAME)

# Clean and make
re: fclean
	$(MAKE) all

# ============================================================================ #
# Special targets

.SILENT:
.PHONY: all clean fclean re
