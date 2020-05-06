# Word Search Solver

Author: Jennifer Li

### Goal
This program utilizes backtracking and tries to solve a word search puzzles. The algorithm follows the same rules that people would use when solving puzzles: it's able to find words in one direction whether that be vertically, horizontally, or diagonally. Once the puzzle is solved the program will display the puzzle and word bank in the Cinder terminal window and from there you can either solve the puzzle yourself or display the solution. 

### How to use
#### File 

Import a .spf file into the data folder with your word search puzzle. Make sure the puzzle has the following in a separate line:
* Begins with #spf1.0 header
* Word search as one string
* Words to be found separated by spaces

Some important notes
* The default puzzle size is 15x15 and the default word list size is 30 words max. 
* Case does not matter in the file however everything will be standardized to uppercase.

#### Solving the puzzle

To solve the puzzle go into my_app.cc and change the file_name_ to the name of your puzzle file. Then run the program. The Cinder terminal will default show just the puzzle and word bank. Press return to view the solutions or to revert back to the puzzle.

### External Library
For this program I imported an external [trie header library](https://github.com/KnairdA/Trie) to save time on making my own template. 

---