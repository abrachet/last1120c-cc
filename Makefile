TARGET = last-cc
WARNING = -Wall -Wshadow --pedantic -Wvla -Werror -Wno-unused-function
GCC = clang++ -g -std=c++17 $(WARNING) -iquote include/
DEFINES = -DDEBUG

SRCS = $(wildcard src/*.cc) $(wildcard src/Parse/*.cc)


# so i dont need to -B every time
HEADERS = $(wildcard include/*.h) $(wildcard include/AST*.h) $(wildcard include/AST/Decl*.h) \
		  $(wildcard include/AST/Expr*.h)  $(wildcard include/AST/Stmt*.h)

TEST_SRCS = $(wildcard tests/*.cc) $(wildcard tests/ASTTests/*.cc) $(wildcard tests/Parse/*.cc)

OBJS = $(SRCS:%.cc=%.o)

TEST_OBJS = $(TEST_SRCS:%.cc=%.o)

.cc.o:
	$(GCC) $(CXXFLAGS) $(DEFINES) -c $< -o $@

$(TARGET): $(OBJS)
	$(GCC) $(CXXFLAGS) $(LDFLAGS) $^ $(LDLIBS) -o $(TARGET)

.gtest.out: $(TEST_OBJS) $(OBJS) $(HEADERS)
	clang++ -g /usr/local/lib/libgtest_main.a $(filter %.o,$^) -lpthread -lgtest -o .gtest.out

test: .gtest.out
	./.gtest.out

clean:
	rm -f $(OBJS)
	rm -f $(TEST_OBJS)
	rm .gtest.out
