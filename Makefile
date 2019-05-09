TARGET = test
WARNING = -Wall -Wshadow --pedantic -Wvla -Werror
GCC = g++ -g -std=c++17 $(WARNING) -iquote include/
DEFINES = -DDEBUG

SRCS = src/ScanFile.cc

# so i dont need to -B every time
HEADERS = include/last-cc_assert.hh include/last-cc.hh include/ScanFile.hh include/Scanner.hh \
	inlcude/Token.hh inlcude/TokenList.hh

TEST_SRCS = tests/TokenTest.cc tests/TokenListTest.cc tests/ScannerTest.cc tests/ScanFileTest.cc \
	tests/TokenizedFileTest.cc tests/ASTTests/ModifierTests.cc tests/ASTTests/ASTTests.cc

OBJS = $(SRCS:%.cc=%.o)

TEST_OBJS = $(TEST_SRCS:%.cc=%.o)

.cc.o:
	$(GCC) $(CXXFLAGS) $(DEFINES) -c $< -o $@

$(TARGET): $(OBJS)
	$(GCC) $(CXXFLAGS) $(LDFLAGS) $^ $(LDLIBS) -o $(TARGET)

.gtest.out: $(TEST_OBJS)
	clang++ /usr/local/lib/libgtest_main.a $^ -lpthread -lgtest -o .gtest.out

test: .gtest.out
	./.gtest.out

clean:
	rm -f $(OBJS)
	rm .gtest.out
