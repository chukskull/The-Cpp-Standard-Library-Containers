CC= c++ 
FLAGS= -std=c++98 -Wall -Wextra -Werror
RM= rm -rf
FILES_VECTOR = tester_vector.cpp
FILES_MAP = tester_map.cpp
FILES_STACK = tester_stack.cpp
FILES_SET= tester_set.cpp

FILES = main.cpp $(addprefix tester/, $(FILES_MAP) $(FILES_STACK) $(FILES_VECTOR))
FILES_BONUS = main_bns.cpp $(addprefix tester/, $(FILES_SET))

NAME= ft_container

HEADER_MAP =   map/map.hpp map/bider_iterator.hpp map map/RBT.hpp map/pair.hpp
HEADER_STACK = stack/stack.hpp
HEADER_VECTOR = vector/is_integral.hpp vector/lexicographical.hpp vector/random_iter.hpp vector/traits.hpp\
vector/vector.hpp
HEADER_SET = set/set.hpp

INCLUDE = $(HEADER_MAP) $(HEADER_STACK) $(HEADER_VECTOR) tester/tester.hpp

# bonus= 1
ifeq ($(bonus), 1)
	INCLUDE = $(HEADER_MAP) $(HEADER_STACK) $(HEADER_VECTOR) tester/tester.hpp
	TO_COMPILE = $(FILES_BONUS)
else
	TO_COMPILE = $(FILES)
	INCLUDE = $(HEADER_MAP) $(HEADER_STACK) $(HEADER_VECTOR) $(HEADER_SET) tester/tester.hpp
endif

OBJ= $(TO_COMPILE:.cpp=.o)

all:$(NAME) 

$(NAME): $(OBJ) $(INCLUDE)
	$(CC) $(FLAGS) $(OBJ) -o $(NAME)

%.o:%.cpp
	$(CC) $(FLAGS) -c $< -o $@
clean:
	$(RM) $(OBJ)
fclean : clean
	$(RM) $(NAME)

re: fclean all



