# Word Search Solver and Generator

Author: Jennifer Li

### Goal

I would like to create a word search solver. The solver would be presented with a list of words to find and the puzzle itself. It’ll search the puzzle to see if it contains the words vertically, horizontally, diagonally, backwards vertically, backwards horizontally, and backwards diagonally. Once it’s done it’ll block out all letters except for where the words are and pretty print out the solution. In order to complete this project you need to know how backtracking works and what a trie data structure is.

### Motivation

I wanted to work on this project because I really struggled with organizing my classes and allowing functions to be called where they needed to be called in the Sudoku project. I wasn’t able to continue working on the Sudoku project to fix the program but I think after having more time to familiarize myself with CLion I’ll be better equipped to complete this project. 

### External Library

I'll be using [{fmt}](https://fmt.dev/6.2.0/index.html), which is a formatting library and a basic [trie header library](https://github.com/KnairdA/Trie).

### Timeline

Week 1:
* Import external libraries

Week 2:
* Write a parser class to take in a .spf file
* Write a puzzle class to support a word search puzzle, word bank, and solutions
* Write unit tests

Week 3:
* Write word search backtracking algorithm
* Write unit tests
* Display puzzle, solution, and word bank in Cinder terminal

### Stretch Goals

If I were to finish the project early, some extra “stretch goals” I could implement would be to create a puzzle generator, or making the puzzle interactive in the terminal.

---

