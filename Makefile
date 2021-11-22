CC := gcc
CFLAGS :=
LDFLAGS :=

project := bin/Dictionary
source_files := $(shell find src -name "*.c")
object_files := $(patsubst src%.c, build%.o, $(source_files))
include_dirs := $(shell find include -type d)
libraries := curl tidy ncurses

CFLAGS += -g
LDFLAGS += $(patsubst %, -I%, $(include_dirs)) $(patsubst %, -l%, $(libraries))

.PHONY: all
all: build $(object_files) bin $(project)

build:
	mkdir -p build

$(object_files): build%.o : src%.c
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) $(LDFLAGS) -c $< -o $@

bin:
	mkdir -p bin

$(project): $(object_files)
	$(CC) $(object_files) $(LDFLAGS) -o $(project)

.PHONY: clean
clean:
	rm -rf build bin