TARGET = test
WARNING = -Wall -Wshadow --pedantic -Wvla -Werror
GCC = gcc -g -std=c99 $(WARNING) -I./
DEFINES = -DDEBUG

SRCS = c00.c

OBJS = $(SRCS:%.c=%.o)

.c.o:
	$(GCC) $(DEFINES) -c $< -o $@

$(TARGET): $(OBJS)
	$(GCC) $(CXXFLAGS) $(LDFLAGS) $^ $(LDLIBS) -o $(TARGET)

clean:
	rm -f $(OBJS)
