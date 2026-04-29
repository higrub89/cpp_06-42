
NAME        = identify
CXX         = c++
CXXFLAGS    = -Wall -Wextra -Werror -std=c++98 -O3
RM          = rm -rf

GREEN       = \033[0;32m
YELLOW      = \033[0;33m
RED         = \033[0;31m
NC          = \033[0m

OBJ_DIR     = obj

SRCS        =	Base.cpp \
				functions.cpp \
			 	main.cpp

OBJS        = $(addprefix $(OBJ_DIR)/, $(SRCS:.cpp=.o))

all: $(NAME)

$(NAME): $(OBJS)
	@echo "$(YELLOW)--- CREATION ./$(NAME)...$(NC)"
	@$(CXX) $(CXXFLAGS) $(OBJS) -o $(NAME)
	@echo "$(GREEN)✅  SUCCESSFUL COMPILATION  ✅$(NC)"

$(OBJ_DIR)/%.o: %.cpp Base.hpp A.hpp B.hpp C.hpp functions.hpp
	@mkdir -p $(OBJ_DIR)
	@echo "$(YELLOW) Compiling:$(NC) $<"
	@$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	@$(RM) $(OBJ_DIR)
	@echo "$(RED)--- DELETION OF OBJECT FILES ---$(NC)"

fclean: clean
	@$(RM) $(NAME)
	@echo "$(RED)--- DELETED FILE ./$(NAME) ---$(NC)"

re: fclean all

.PHONY: all clean fclean re
