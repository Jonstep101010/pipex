NAME		  := pipex
.DEFAULT_GOAL := all

#change compiler if on linux

# --------------------------------- includes --------------------------------- #

INCS		= ./include \
				./include/libft/include

LIB			:= ft
LIB_FT		:= include/libft/libft.a

BUILD_DIR	:= .build

# ---------------------------------------------------------------------------- #
#                                 source files                                 #
# ---------------------------------------------------------------------------- #

VPATH		:= src/ src/utils src/io src/default_pipe src/here_doc src/multiple_pipe

SRC			:= $(NAME).c
SRC_UTILS	:= print_file.c create_file.c free.c print_arr.c files.c
SRC_IO		:= parse_pipe.c path_env.c parse_args.c error_exit.c
SRC_DEF		:= parent.c childs.c
SRC_HDOC	:= here_doc.c parse_here_doc.c childs_here_doc.c
SRC_MULT	:= middle.c parent_mult.c

SRCS		:= $(SRC) $(SRC_UTILS) $(SRC_IO) $(SRC_DEF) $(SRC_HDOC) $(SRC_MULT)

# ---------------------------------------------------------------------------- #
#                             compilation arguments                            #
# ---------------------------------------------------------------------------- #

OBJS		:= $(addprefix $(BUILD_DIR)/, $(SRCS:%.c=%.o))
DEPS		:= $(OBJS:.o=.d)

CC			:= clang
ifeq ($(shell uname), Linux)
	CC = gcc
endif
CFLAGS		?= -g3 -Wall -Wextra -Werror -DRELEASE=1 #-Wpedantic
CPPFLAGS	:= $(addprefix -I,$(INCS)) -MMD -MP
LDFLAGS		= $(addprefix -L, $(dir $(LIB_FT)))
LDLIB		:= $(addprefix -l, $(LIB))

MAKEFLAGS	+= --no-print-directory --silent

DONE		= printf "\033[0;32m\xE2\x9C\x93\033[0m "
DONE_NL		= printf "\033[0;32m\xE2\x9C\x93\n\033[0m"

# RELEASE		= 0

# ---------------------------------------------------------------------------- #
#                             building the program                             #
# ---------------------------------------------------------------------------- #

bonus: all
all: $(NAME)

$(LIB_FT): | update
	$(MAKE) -C $(@D) -B

$(NAME): $(LIB_FT) $(OBJS)
	$(info creating $(NAME) executable)
	$(CC) $(CFLAGS) $(OBJS) $(LIB_FT) $(CPPFLAGS) $(LDLIB) $(LDFLAGS) -o $(NAME)
	$(DONE_NL)

$(BUILD_DIR)/%.o: %.c | $(BUILD_DIR)
	$(CC) $(CFLAGS) $(CPPFLAGS) -c -o $@ $< && $(DONE)
	echo $(notdir $<)
# info $($<)
$(BUILD_DIR):
	mkdir -p .build

# ---------------------------------------------------------------------------- #
#                                     rules                                    #
# ---------------------------------------------------------------------------- #

clean:
	$(info Cleaning...)
	rm -rf .build
	make -C $(dir $(LIB_FT)) clean
	$(DONE_NL)

fclean: clean
	rm -f $(NAME)
	rm -fv $(LIB_FT)

directory = include/libft
dir_absent = $(dir $(LIB_FT))-

$(dir_absent):
	echo "$(directory) does not exist. Cloning now...";
	mkdir -p $(@D)
	git clone https://github.com/Jonstep101010/libft include/libft

update: $(!dir_absent)
	git submodule update --init --recursive
# git stash
# git pull
# git stash pop

re:
	$(MAKE) fclean
	$(MAKE) all

ifeq ($(shell uname), Linux)
VALGRIND = valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes
endif

# ----------------------------- additional rules ----------------------------- #
run: all
	rm -f outfile.txt
	$(VALGRIND)./$(NAME) infile.txt "ls -l src/" "grep .c" "wc -l" outfile.txt; cat outfile.txt
	$(VALGRIND)./$(NAME) infile.txt "grep test" "wc" outfile.txt; cat outfile.txt
	$(VALGRIND)./$(NAME) infile.txt "grep test" "awk '{count++} END {print count}'" outfile.txt; cat outfile.txt
# $(VALGRIND)./$(NAME) "/dev/urandom" "cat" "head -1" "outs/test-xx.txt"; cat outs/test-xx.txt
# ./$(NAME) infile.txt "grep test" "awk {count++} END {print count}" outfile.txt;
# ./$(NAME) infile.txt "wc" "ls" outfile.txt
# ./$(NAME) infile.txt "grep test" "wc -c" outfile.txt

norme:
	clear
	-norminette src/ | grep Error

upgrade:
	-$(MAKE) update && $(MAKE) re

test:
	cd ./../tests-pipex && sh ./test.sh

infile:
	echo "Some test data." > ./../pipex/infile.txt;
	echo "Line 2." >> ./../pipex/infile.txt;

test_infile: infile
	./pipex ./infile.txt

.PHONY: run update upgrade re
# .SILENT:
-include $(DEPS)
