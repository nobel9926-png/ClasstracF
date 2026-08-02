CC      = gcc
TARGET  = classtrac

SRCS    = main.c \
          home_screen.c \
          subject_screen.c \
          attendance_screen.c \
          report_screen.c \
          storage.c \
          ui.c

OBJS    = $(SRCS:.c=.o)

# ---------- Platform detection ----------
UNAME := $(shell uname 2>/dev/null || echo Windows)

ifeq ($(OS),Windows_NT)
    LIBS    = -lraylib -lm -lopengl32 -lgdi32 -lwinmm
    TARGET  = classtrac.exe
else ifeq ($(UNAME),Darwin)
    RAYLIB_PREFIX := $(shell brew --prefix raylib 2>/dev/null)
    LIBS    = -lraylib -lm -framework OpenGL -framework Cocoa -framework IOKit
    ifneq ($(RAYLIB_PREFIX),)
        CFLAGS_PLATFORM = -I$(RAYLIB_PREFIX)/include
        LIBS += -L$(RAYLIB_PREFIX)/lib
    endif
else
    LIBS    = -lraylib -lm -ldl -lpthread -lX11
endif

CFLAGS  = -Wall -Wextra -std=c99 -O2 $(CFLAGS_PLATFORM)

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(OBJS) -o $(TARGET) $(LIBS)
	@echo "Build successful -> $(TARGET)"

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

run: all
	./$(TARGET)

clean:
	rm -f $(OBJS) $(TARGET) classtrac.exe

.PHONY: all run clean