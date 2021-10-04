# Dictionary Project

## Introduction

This is a project that implements a dictionary (in the tradition sense rather than the data structure).

## Implementation Details

The dictionary is implemented as a binary search tree with nodes that store a word and its definitions. To support multiple definitions for a single word, a singly linked list is used. To allow a variable length of definition, a dynamic array is used. Overall, this means a binary search tree has nodes containing singly linked lists, and the nodes of the singly linked list contain a dynamic array.

A few basic commands are supported (check out usage section to get started). These are implemented using some rudimentary regular expressions. There is some level of input sanitization but try not to make too many mistakes.

## Usage

Currently, five different commands are supported. All commands share two basic principles:

1. The first character is a unique command selector
2. The rest of the characters are reserved for arguments

The five commands are as following:

### Insert

> i word definition

This command is used to insert words and definitions into the dictionary. If a word does not exist in the dictionary, it is added with the specified definition. Otherwise the definition is pushed onto the already existing word's definitions.

### Remove

> r word [index]

This command is used to remove a word or one of its definitions. If only a word is specified, the entire word along with all of its definitions is removed. If the index is also specified, only the definition pointed to by the index (counts from 1) is removed. Note, removing all definitions of a word also removes the word.

### Search

> s word [index]

This command is used to search a word or one of its definitions. If only a word is specified, all of the definitions are printed. If the index is also specified, only the definition pointed to by the index (counts from 1) is printed.

### Print

> p

This command is used to print the entire dictionary in a similar format as the tree command.

### Quit

> q

This command is used to quit the program.

To use this program, simply clone this repository, navigate to its root, and run make command.

This will generate a bin folder containing the driver executable.