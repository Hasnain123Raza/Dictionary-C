CC := gcc
CFLAGS :=
LDFLAGS :=

project := bin/Dictionary
source_files := $(shell find src -name "*.c")
object_files := $(patsubst %.c, %.o, $(source_files))
include_dirs := $(shell find include -type d)
libraries := curl tidy ncurses

CFLAGS += -g
LDFLAGS += $(patsubst %, -I%, $(include_dirs)) $(patsubst %, -l%, $(libraries))

.PHONY: all
all: build $(object_files) bin $(project)

build:
	mkdir -p build

$(object_files): %.o : %.c
	$(CC) $(CFLAGS) $(LDFLAGS) -c $< -o build/$(@F)

bin:
	mkdir -p bin

$(project): $(patsubst %, build/%, $(notdir $(object_files)))
	$(CC) $(patsubst %, build/%, $(notdir $(object_files))) $(LDFLAGS) -o $(project)

.PHONY: clean
clean:
	rm -rf build bin