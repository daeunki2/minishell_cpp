# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: daeunki2 <daeunki2@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2026/02/12 16:11:30 by daeunki2          #+#    #+#              #
#    Updated: 2026/02/15 16:31:09 by daeunki2         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell
TEST_NAME = minishell_test

CC = c++

CFLAGS = -Wall -Wextra -Werror -std=c++98 -g
INCLUDES = -I inc

SRC_DIR = src
TEST_DIR = unit_test
OBJ_DIR = obj

# -------------------------
# Sources
# -------------------------
SRCS = $(SRC_DIR)/main.cpp \
		$(SRC_DIR)/Lexer.cpp \
		$(SRC_DIR)/Tokenizer.cpp

TEST_SRCS = $(TEST_DIR)/token_test.cpp \
            $(SRC_DIR)/Lexer.cpp \
			$(SRC_DIR)/Tokenizer.cpp

# -------------------------
# Objects
# -------------------------
OBJS = $(SRCS:$(SRC_DIR)/%.cpp=$(OBJ_DIR)/%.o)
TEST_OBJS = $(TEST_SRCS:%.cpp=$(OBJ_DIR)/%.o)

# -------------------------
# Rules
# -------------------------
all: $(NAME)

$(NAME): $(OBJS)
	@echo "Building $(NAME) 🛠️"
	@$(CC) $(CFLAGS) $(INCLUDES) $(OBJS) -o $(NAME)
	@echo "Build Complete! ✅"

test: $(TEST_NAME)

$(TEST_NAME): $(TEST_OBJS)
	@echo "Building $(TEST_NAME) 🧪"
	@$(CC) $(CFLAGS) $(INCLUDES) $(TEST_OBJS) -o $(TEST_NAME)
	@echo "Test Build Complete! ✅"

$(OBJ_DIR)/%.o: %.cpp
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	@echo "Cleaning object files 🧹"
	@rm -rf $(OBJ_DIR)
	@echo "cleaning ✅"

fclean: clean
	@echo "Cleaning Executables 🧹"
	@rm -f $(NAME) $(TEST_NAME)
	@echo "fclean ✅"

re: fclean all

.PHONY: all test clean fclean re
