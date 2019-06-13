.PHONY: all re fclean clean

CC=clang
FLAGS=-Wextra -Wall -Werror
NAME=lem-in
FILENAMES=main ants parser_utils parser paths
SRCS=$(addsuffix .c,$(FILENAMES))
OBJS=$(addsuffix .o,$(FILENAMES))
LIB_NAME=libftprintf/libftprintf.a
LIB=libftprintf

all: $(NAME)

$(NAME): $(OBJS)
	make -C $(LIB)
	$(CC) $(FLAGS) $(OBJS) $(FRAMEWORKS) $(LIB_NAME) -o $(NAME)

%.o: $(addprefix srcs/, %.c)
	$(CC) -c $< $(FLAGS)

clean:
	make clean -C libftprintf
	/bin/rm -f $(OBJS)

fclean: clean
	make fclean -C libftprintf
	/bin/rm -f $(NAME)

re: fclean all
