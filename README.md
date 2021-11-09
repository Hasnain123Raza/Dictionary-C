# Dictionary Project

## Introduction

This is a project that implements a dictionary (in the tradition sense rather than the data structure). It allows interaction with the dictionary using commands in a few different ways. Words and definitions can be inserted, removed, or searched and the dictionary can be printed (checkout usage section to get started). It web scrapes words and definitions from this website https://simple.wiktionary.org/

## Implementation Details

The dictionary is implemented as a binary search tree with nodes that store a word and its definitions. To support multiple definitions for a single word, a singly linked list is used. To allow a variable length of definition, a dynamic array is used. Overall, this means a binary search tree has nodes containing singly linked lists, and the nodes of the singly linked list contain a dynamic array.

Words and definitions are downloaded through web scraping. Curl library (https://curl.se/libcurl/) is used to download the HTML and Tidy library (https://www.html-tidy.org/developer/) is used to parse the HTML DOM and extracts information. Scrapped data is written to a file which can be read from in the future runs (checkout usage section to see how).

A few basic commands are supported (check out usage section to get started). These are implemented using some rudimentary regular expressions. There is some level of input sanitization but try not to make too many mistakes.

GUI mode is implemented using the ncurses library (https://tldp.org/HOWTO/NCURSES-Programming-HOWTO/). There are three fundamental abstractions: SceneManager, Scene, and SceneElement. A SceneManager manages a collection of scenes providing useful functionality such as switching and displaying active scene. A Scene manages a collection of scene elements with features like focus. A SceneElement represents the individual element that appears on the screen. Scene elements can be selectable, in which case they have a doubly linked list providing reference to the previous and the next selectable scene element allowing the scene to move focus around the menu.

## Usage

The program accepts one command line argument. It is a integer argument specifying the amount of words to skip while webscrapping. For example, if the program is invoked with an argument of 50, only the every 50th word will have their definitions collected and be used in the program. If not argument is specified, the program assumes data is already available and attempts to read dictionary.txt file.

Currently, five different commands are supported. All commands share three basic principles:

1. The first character is a unique command selector
2. The rest of the characters are reserved for arguments
3. To deal with words with space, use quotation marks around them

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

### Graphical Mode

> g

This command is used to switch to the graphical mode. The graphical mode allows the user to switch back into command line mode if necessary.

### Quit

> q

This command is used to quit the program.

## Installation

This program depends on several third party libraries that need to be installed beforehand. These includes curl, tidy, and ncurses. To install curl, use the command `sudo apt-get install libcurl4-gnutls-dev`. To install tidy, use the command `sudo apt-get install libtidy-dev`. To install ncurses, use the command `sudo apt-get install libncurses5-dev libncursesw5-dev`. After that simply clone this repository, navigate to its root, and run make command.

This will generate a bin folder containing the driver executable.