NAME		  := pipex
.DEFAULT_GOAL := all

# --------------------------------- includes --------------------------------- #

INCS		= ./include \
				./include/libft/include

LIB			:= ft
LIB_FT		:= include/libft/libft.a

BUILD_DIR	:= .build

# ---------------------------------------------------------------------------- #
#                                 source files                                 #
# ---------------------------------------------------------------------------- #

VPATH		:= src/ src/utils src/io src/processes

SRC			:= $(NAME).c
SRC_UTILS	:= print_file.c create_file.c free.c
SRC_IO		:= parsing.c
SRC_PROCS	:= parent.c childs.c

SRCS		:= $(SRC) $(SRC_UTILS) $(SRC_IO) $(SRC_PROCS)

# ---------------------------------------------------------------------------- #
#                             compilation arguments                            #
# ---------------------------------------------------------------------------- #

OBJS		:= $(addprefix $(BUILD_DIR)/, $(SRCS:%.c=%.o))
DEPS		:= $(OBJS:.o=.d)

CC			:= clang
CFLAGS		?= -g3 -Wall -Wextra -Werror #-Wpedantic
CPPFLAGS	:= $(addprefix -I,$(INCS)) -MMD -MP
LDFLAGS		= $(addprefix -L, $(dir $(LIB_FT)))
LDLIB		:= $(addprefix -l, $(LIB))

MAKEFLAGS	+= --no-print-directory --silent

DONE		= printf "\033[0;32m\xE2\x9C\x93\033[0m "
DONE_NL		= printf "\033[0;32m\xE2\x9C\x93\n\033[0m"

# ---------------------------------------------------------------------------- #
#                             building the program                             #
# ---------------------------------------------------------------------------- #

all: $(NAME)

$(LIB_FT):
	$(MAKE) -C $(@D) -B

$(NAME): $(OBJS) $(LIB_FT)
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
	make -C $(dir $(LIB_FT)) clean
	rm -rf .build
	$(DONE_NL)

fclean: clean
	rm -fv $(LIB_FT)
	rm -f $(NAME)

update: fclean
	git submodule update --init --recursive
# git stash
# git pull
# git stash pop

re:
	$(MAKE) fclean
	$(MAKE) all

# ----------------------------- additional rules ----------------------------- #
run: all
	./$(NAME) infile.txt "grep test" "awk '{count++} END {print count}'" outfile.txt
	./$(NAME) infile.txt "grep test" "awk {count++} END {print count}" outfile.txt
# ./$(NAME) infile.txt "grep test" "wc" outfile.txt
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
