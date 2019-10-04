# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ablizniu <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/10/01 18:09:41 by ablizniu          #+#    #+#              #
#    Updated: 2019/10/01 18:30:30 by ablizniu         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


NAME		=	avm
FLAGS		= 	-Wall -Werror -Wextra
COMPILER	=	g++ -std=c++11

DIR_INC		=	./inc/
DIR_SRC		=	./src/
DIR_OBJ		= 	./obj/
BOOST_DIR   =   ~/.brew/Cellar/boost/1.71.0/include/

HEAD_AVM	=	Error.h \
                Error_messages.h \
                IOperands.h \
                IVm.h \
                lexer.h \
                parser.h

SRC_AVM		=	Error.cpp \
                FabricMethod.cpp \
                lexer.cpp \
                main.cpp \
                parser.cpp

INC_PATH 	= 	$(addprefix $(DIR_INC), $(HEAD_AVM))

OBJ 		= 	$(addprefix $(DIR_OBJ), $(SRC_AVM:.cpp=.o))
INC 		= 	$(addprefix -I, $(DIR_INC))

all: obj $(NAME)

obj:
	@mkdir -p $(DIR_OBJ)

$(NAME): $(OBJ)
	@$(COMPILER) -o $(NAME) $(OBJ)
	@echo "Compiling" [ $(NAME) ]

$(DIR_OBJ)%.o: $(DIR_SRC)%.cpp $(INC_PATH)
	@$(COMPILER) $(FLAGS) $(INC) -c -o $@ $< -I ~/.brew/Cellar/boost/1.71.0/include/
	@echo "Linking" [ $< ]

clean:
	@rm -rf $(DIR_OBJ)
	@echo "Clean [ obj files avm ]"

fclean:
	@rm -rf $(DIR_OBJ)
	@echo "Clean [ obj files avm ]"
	@rm -f $(NAME)
	@echo "Clean" [ $(NAME) ]

re: fclean all