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

VPATH		:= src/

SRC			:= $(NAME).c

SRCS		:= $(SRC)

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
	$(CC) $(CFLAGS) $(OBJS) -D WIDTH=$(WIDTH) -D HEIGHT=$(HEIGHT) \
	$(LIB_FT) $(CPPFLAGS) $(LDLIB) $(LDFLAGS) -o $(NAME)
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
	./$(NAME)

norme:
	clear
	-norminette src/ | grep Error

upgrade:
	-$(MAKE) update && $(MAKE) re

.PHONY: run update upgrade re
# .SILENT:
-include $(DEPS)
