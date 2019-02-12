.PHONY: all re clean fclean

NAME=lem-in

ifeq ($(OS), Linux)
FLAGS=
else
FLAGS=-Wextra -Wall -Werror
endif

GNL=get_next_line.c

GNLO=get_next_line.o

SRCS=ants.c main.c parser.c parser_utils.c paths.c

OBJ=$(SRCS:.c=.o)

LIBS=libftprintf/libftprintf.a

all: $(NAME)

$(NAME): $(OBJ) $(LIBS)
	gcc $(FLAGS) $(addprefix obj/, $(OBJ) $(GNLO)) $(LIBS) -o $(NAME)

$(OBJ): $(addprefix srcs/, $(SRCS)) $(addprefix gnl/, $(GNL))
	gcc $(FLAGS) -c $(addprefix srcs/, $(SRCS))
	gcc $(FLAGS) -c $(addprefix gnl/, $(GNL))
	mv $(OBJ) $(GNLO) obj/

$(LIBS):
	make -C libftprintf

clean:
	/bin/rm -rf $(addprefix obj/, $(OBJ) $(GNLO))
	make clean -C libftprintf

fclean: clean
	/bin/rm $(NAME)
	make fclean -C libftprintf

re: fclean all