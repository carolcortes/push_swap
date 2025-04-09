# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: cade-oli <cade-oli@student.42porto.com>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/03/17 20:07:25 by cade-oli          #+#    #+#              #
#    Updated: 2025/04/09 12:43:56 by cade-oli         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

MAKE = make
NAME = push_swap

### Message Vars
_SUCCESS 		= [$(GRN)SUCCESS$(D)]
_INFO 			= [$(BLU)INFO$(D)]
_NORM 			= [$(MAG)Norminette$(D)]
_NORM_SUCCESS 	= $(GRN)=== OK:$(D)
_NORM_INFO 		= $(BLU)File no:$(D)
_NORM_ERR 		= $(RED)=== KO:$(D)
_SEP 			= =====================

#==============================================================================#
#                                    PATHS                                     #
#==============================================================================#

SRC_PATH	= src
INC_PATH	= inc
BONUS_PATH	= bonus
LIBS_PATH	= lib
BUILD_PATH	= .build
TEMP_PATH	= .temp


FILES = 	main.c push_swap.c simple_sort.c swap.c push.c rotate.c \
	reverse_rotate.c ft_split.c stack_init.c utils.c error_utils.c \
	stack_utils.c

SRCS = $(addprefix $(SRC_PATH)/, $(FILES))
OBJS = $(SRCS:$(SRC_PATH).c=$(BUILD_PATH).o)

VISUALIZER_PATH	= $(LIBS_PATH)/visualizer
RANDGEN_PATH	= $(LIBS_PATH)/randgen

#==============================================================================#
#                              COMPILER & FLAGS                                #
#==============================================================================#

CC = cc
CFLAGS = -Wall -Wextra -Werror -g

#==============================================================================#
#                                COMMANDS                                      #
#==============================================================================#

AR			= ar rcs
RM			= rm -rf
MKDIR_P		= mkdir -p

#==============================================================================#
#                                  RULES                                       #
#==============================================================================#

##@ push_swap Compilation Rules 🏗

all: deps $(NAME) 		## Compile All

$(NAME): $(BUILD_PATH) $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

$(BUILD_PATH)/%.o: $(SRC_PATH)/%.c
	@echo -n "$(MAG)█$(D)"
	$(CC) $(CFLAGS) $(DFLAGS) -MMD -MP -c $< -o $@

$(BUILD_PATH):
	$(MKDIR_P) $(BUILD_PATH)
	@echo "* $(YEL)Creating $(BUILD_PATH) folder:$(D) $(_SUCCESS)"

$(TEMP_PATH):
	$(MKDIR_P) $(TEMP_PATH)
	@echo "* $(YEL)Creating $(TEMP_PATH) folder:$(D) $(_SUCCESS)"

deps: 			## Download randgen
	@if test ! -d "$(RANDGEN_PATH)"; then make get_randgen; \
		else echo "$(YEL)[randgen]$(D) folder found 🖔"; fi
	@echo " $(RED)$(D) [$(GRN)Nothing to be done!$(D)]"

-include $(BUILD_PATH)/*.d

get_randgen:
	@echo "* $(CYA)Getting Randgen submodule$(D)]"
	git clone git@github.com:PedroZappa/randgen.git $(RANDGEN_PATH)
	@echo "* $(GRN)Randgen submodule download$(D): $(_SUCCESS)"

build_randgen: all $(TEMP_PATH)
	@if test ! -d "$(RANDGEN_PATH)"; then \
	git clone git@github.com:PedroZappa/randgen.git $(RANDGEN_PATH); fi
	$(MAKE) -C $(RANDGEN_PATH)

randgen: build_randgen		## Generate list of n random values w/ given seed
	@echo "* [$(YEL)Generating list of random values$(D)]"
	./lib/randgen/randgen $(n) $(seed) | tee $(TEMP_PATH)/rand.txt
	@echo "* [$(YEL)List of random values generated with$(D): $(_SUCCESS)]"

visual: 					## Run push_swap Visualizer
	@if test ! -d "$(VISUALIZER_PATH)"; then make get_visual; \
	else echo "$(YEL)[push_swap Visualizer]$(D) folder found 🖔"; \
		./$(VISUALIZER_PATH)/build/bin/visualizer; fi
	make visual

get_visual:
	@echo "* [$(CYA)Getting push_swap Visualizer$(D)]"
	git clone https://github.com/o-reo/push_swap_visualizer.git $(VISUALIZER_PATH)
	@echo "* $(GRN)Visualizer download$(D): $(_SUCCESS)"
	@echo "[$(YEL)Building push_swap Visualizer$(D)]"
	cd $(VISUALIZER_PATH) && mkdir build && cd build && cmake .. && make
	@echo "[$(_SUCCESS) building $(MAG)push_swap Visualizer!$(D) $(YEL)🖔$(D)]"

##@ Test

check_ext_func: 		## Check for external functions
	@echo "[$(YEL)Checking for external functions$(D)]"
	@echo "$(YEL)$(_SEP)$(D)"
	@echo "$(CYA)Reading binary$(D): $(MAG)push_swap$(D)"
	nm ./push_swap | grep "U" | grep -v "__" | tee $(TEMP_PATH)/ext_func.txt
	@echo "$(YEL)$(_SEP)$(D)"
	@echo "$(CYA)Reading binary$(D): $(MAG)checker$(D)"
	nm ./checker | grep "U" | tee $(TEMP_PATH)/ext_func.txt
	@echo "$(YEL)$(_SEP)$(D)"

valgrind: all build_randgen		## Run push_swap w/ Valgrind
	make randgen n=$(n)
	@ARG=$$(cat $(TEMP_PATH)/rand.txt); \
	valgrind --leak-check=full --show-leak-kinds=all ./$(NAME) "$$ARG" | tee $(TEMP_PATH)/out.txt; \
	# N_ARGS=$$(cat $(TEMP_PATH)/rand.txt | wc -w); \
	# echo "N_ARGS: $(GRN)$$N_ARGS$(D)";
	@make --no-print-directory print_test

##@ Clean-up Rules 󰃢

clean:
	$(RM) $(BUILD_PATH)

fclean: clean
	$(RM) $(NAME) randgen $(LIBS_PATH) $(TEMP_PATH)

re: fclean all

help: 			## Display this help page
	@awk 'BEGIN {FS = ":.*##"; \
			printf "\n=> Usage:\n\tmake $(MAG)<target>$(D)\n"} \
		/^[a-zA-Z_0-9-]+:.*?##/ { \
			printf "\t$(MAG)%-15s$(D) %s\n", $$1, $$2 } \
		/^##@/ { \
			printf "\n=> %s\n", substr($$0, 5) } ' Makefile
## Tweaked from source:
### https://www.padok.fr/en/blog/beautiful-makefile-awk

#==============================================================================#
#                                  UTILS                                       #
#==============================================================================#

# Colors
#
# Run the following command to get list of available colors
# bash -c 'for c in {0..255}; do tput setaf $c; tput setaf $c | cat -v; echo =$c; done'
#
B  		= $(shell tput bold)
BLA		= $(shell tput setaf 0)
RED		= $(shell tput setaf 1)
GRN		= $(shell tput setaf 2)
YEL		= $(shell tput setaf 3)
BLU		= $(shell tput setaf 4)
MAG		= $(shell tput setaf 5)
CYA		= $(shell tput setaf 6)
WHI		= $(shell tput setaf 7)
GRE		= $(shell tput setaf 8)
BRED 	= $(shell tput setaf 9)
BGRN	= $(shell tput setaf 10)
BYEL	= $(shell tput setaf 11)
BBLU	= $(shell tput setaf 12)
BMAG	= $(shell tput setaf 13)
BCYA	= $(shell tput setaf 14)
BWHI	= $(shell tput setaf 15)
D 		= $(shell tput sgr0)
BEL 	= $(shell tput bel)
CLR 	= $(shell tput el 1)
