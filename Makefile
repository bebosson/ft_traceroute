.POSIX:
.SUFFIXES:
CC = gcc
CFLAGS = -g -Wall -Wextra -Werror
SRC = ./src/
INC = ./inc/
INCH = ./inc/ft_traceroute.h
LIBFT = ./libft/libft.a
LIBFTH = ./libft/includes/
LIBDIR = ./libft/
BUILDIR = ./build/
BUILDOBJS = $(BUILDIR)ft_recv.o $(BUILDIR)ft_send.o $(BUILDIR)ft_traceroute.o \
			$(BUILDIR)print.o $(BUILDIR)parse_option.o $(BUILDIR)set_option.o \
			$(BUILDIR)read_pck.o $(BUILDIR)addr.o

all: ft_traceroute
ft_traceroute: $(BUILDIR)  $(LIBFT) $(BUILDOBJS) $(INCH)
	make -C ./libft/
	$(CC) $(DEBUG) $(CFLAGS) -I$(INC) -I$(LIBFTH) -o ft_traceroute $(BUILDOBJS) $(LIBFT)

$(BUILDIR):
	mkdir ./build/
$(LIBFT):
	git submodule init
	git submodule update
	make -C $(LIBDIR)

.SUFFIXES: .c .o

$(BUILDIR)%.o: $(SRC)%.c $(INCH) 
	$(CC) $(CFLAGS) -I$(INC) -I$(LIBFTH) -c $< -o $@

clean:
	rm -rf $(BUILDIR)
	make -C $(LIBDIR) clean 
fclean:
	rm -rf ft_traceroute 
	make -C $(LIBDIR) fclean
	
debug: $(BUILDIR)  $(LIBFT) $(BUILDOBJS) $(INCH)
	make -C ./libft/
	make all
	$(CC) $(CFLAGS) -I$(INC) -I$(LIBFTH) -o ft_traceroute $(BUILDOBJS) $(LIBFT) 

re: clean all
