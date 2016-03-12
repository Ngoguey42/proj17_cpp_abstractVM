#

# ============================================================================ #
# Directories

# Git submodule to init
MODULES					:=
# include search path for .o dependencies
MKGEN_INCLUDESDIRS		:= include
# Obj files directory
MKGEN_OBJDIR			:= obj
# Source files directories
MKGEN_SRCSDIRS_DEFAULT	:= srcs srcs_build
MKGEN_SRCSDIRS_TEST		:= srcs srcs_test

# mkgen -> MKGEN_SRCSBIN_* variables
# mkgen -> $(MKGEN_OBJDIR)/**/*.o rules


# ============================================================================ #
# Default  flags
BASE_FLAGS		= -Wall -Wextra
HEAD_FLAGS		= $(addprefix -I,$(INCLUDEDIRS))
LD_FLAGS		= $(BASE_FLAGS) -o $@

MAKEFLAGS		+= -j


# ============================================================================ #
# Build mode
#	NAME		link; target
#	CC_LD		link; ld
#	LIBSBIN		link; dependancies
#	LIBSMAKE	separate compilation; makefiles to call
#	SRCSBIN		separate compilation; sources
#	INCLUDEDIRS	separate compilation; sources includes path

BUILD_MODE		= default
ifeq ($(BUILD_MODE),test)
	NAME			:= avm-test
	CC_LD			= $(CC_CPP)
	LIBSBIN			=
	LIBSMAKE		=
	SRCSBIN			= $(MKGEN_SRCSBIN_TEST) #gen by mkgen
	INCLUDEDIRS		= $(MKGEN_INCLUDESDIRS)
	BASE_FLAGS		+= -O2
	LD_FLAGS		+= -lboost_unit_test_framework
# else ifeq ($(BUILD_MODE),debug)
# 	NAME			:= lemipc
# 	CC_LD			= $(CC_C)
# 	LIBSBIN			= libft/libft.a
# 	LIBSMAKE		= libft
# 	SRCSBIN			= $(MKGEN_SRCSBIN_DEFAULT) #gen by mkgen
# 	INCLUDEDIRS		= $(MKGEN_INCLUDESDIRS)
# 	BASE_FLAGS		+= -g
# else ifeq ($(BUILD_MODE),gui)
# 	NAME			:= lemipc-gui
# 	CC_LD			= $(CC_CPP)
# 	LIBSBIN			= libft/libft.a libftui/libftui.a
# 	LIBSMAKE		= libft libftui
# 	SRCSBIN			= $(MKGEN_SRCSBIN_GUI) #gen by mkgen
# 	INCLUDEDIRS		= $(MKGEN_INCLUDESDIRS) libftui/_objs/_public
# 	BASE_FLAGS		+= -O2 -DMAC_OS_MODE=1
# 	LD_FLAGS		+= -lglfw3 -framework OpenGL -lfreetype
# 	LD_FLAGS		+= -Llibftui -lftui
# 	LD_FLAGS		+= -Llibftui/liblua/lua-5.3.1/src -llua
else
	NAME			:= avm
	CC_LD			= $(CC_CPP)
	LIBSBIN			=
	LIBSMAKE		=
	SRCSBIN			= $(MKGEN_SRCSBIN_DEFAULT) #gen by mkgen
	INCLUDEDIRS		= $(MKGEN_INCLUDESDIRS)
	BASE_FLAGS		+= -O2
endif


# ============================================================================ #
# Misc
UNAME			:= $(shell uname | cut -c1-6)
PRINT_OK		= printf '\033[32m$<\033[0m\n'
PRINT_LINK		= printf '\033[32m$@\033[0m\n'
DEPEND			:= depend.mk
MODULE_RULES	:= $(addsuffix /.git,$(MODULES))
SHELL			:= /bin/bash


# ============================================================================ #
# C
C_FLAGS			= $(HEAD_FLAGS) $(BASE_FLAGS)
ifeq ($(UNAME),CYGWIN)
	CC_C		= x86_64-w64-mingw32-gcc
else
	CC_C		= clang
endif


# ============================================================================ #
# C++
CPP_FLAGS		= $(HEAD_FLAGS) $(BASE_FLAGS) -std=c++14
ifeq ($(UNAME),CYGWIN)
	CC_CPP		= x86_64-w64-mingw32-g++
	LD_FLAGS	+= -static
else
	CC_CPP		= clang++
endif


# ============================================================================ #
# Rules
# Default rule (needed to be before any include)
all: _all_git

-include $(DEPEND)

_all_git: $(MODULE_RULES)
	$(MAKE) _all_libs

_all_libs: $(LIBSMAKE)
	$(MAKE) _all_separate_compilation

_all_separate_compilation: $(SRCSBIN)
	$(MAKE) _all_linkage

_all_linkage: $(NAME)

# Linking
$(NAME): $(LIBSBIN) $(SRCSBIN)
	$(CC_LD) $(LD_FLAGS) $(SRCSBIN) && $(PRINT_LINK)

# Compiling
$(MKGEN_OBJDIR)/%.o: %.c
	$(CC_C) $(C_FLAGS) -c $< -o $@ && $(PRINT_OK)
$(MKGEN_OBJDIR)/%.o: %.cpp
	$(CC_CPP) $(CPP_FLAGS) -c $< -o $@ && $(PRINT_OK)

# Init submodules
$(MODULE_RULES):
	git submodule init $(@:.git=)
	git submodule update $(@:.git=)

# Compile libs
$(LIBSMAKE):
	$(MAKE) -C $@

# Create obj directories
$(MKGEN_OBJDIR)/%/:
	mkdir -p $@

# Clean obj files
clean:
	rm -f $(SRCSBIN)

# Clean everything
fclean: clean
	rm -f $(NAME)

# Clean and make
re: fclean
	$(MAKE) all


# ============================================================================ #
# Special targets
.SILENT:
.PHONY: all clean fclean re _all_git _all_libs _all_separate_compilation _all_linkage $(LIBSMAKE)
