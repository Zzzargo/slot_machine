**POLITEHNICA Bucharest**
**Faculty of Automatic Control and Computer Science**
**Computer Programming and Programming Languages**

Burlacu Vasile - CTI-311CD
---

# :book: Homework 1

## :scroll: Overview
For this homework I created a slot machine simulator, that has useful functionality. This program uses dynamic programming to create a matrix which simulates the functionality of a slot machine. The "visible screen of the machine" is represented by the first 3 rows of the matrix.


## :gear: Functionality
- Spin a chosen column a desired number of times *task 1*
- Check if a given matrix configuration has winning combinations and calculate the total score of the configuration *task 2*
- Calculate the total score after a number of spins *task 3*
- Calculate what could be the highest score if one symbol of the matrix could be changed to an arbitrary value *task 4*
- Calculate what could be the highest score if 2 columns of the matrix could pe spun an arbitrary number of times *task 5*
- A bonus game *task 6*

### :trophy: Winning combinations
- There are 3 types of winning combinations:
    - A sequence of 3+ symbols of the same value on the same row
        - The score of this type is given by the biggest number of consecutive symbols on a row
    - Any of the diagonals with the symbols of the same value of a 3x3 square built inside the "visible screen"
        - The score of this type is 7
    - If in a 3x3 square both diagonals are winning combinations, they are treated as a single winning combination, the "X"
        - The score of this type is 21

### :gift: Bonus score
- If the value found in any winning combination is '7', then the score of that combination is doubled
- If in the whole "visible screen" there are no more than 4 distinct values, 15 points are added to the score
- If in the whole "visible screen" there are no more than 2 distinct values, 100 points are added to the score
*The last 2 bonuses are not cumulative*

### :rocket: Bonus game
- The game is played inside the "visible screen", the player cannot exit it
- The player can move up, down, left and right from the current position
- The cost of each move is given by the absolute value of the difference between the value of the first symbol and the value of the symbol the player wants to move to
- The objective in the bonus game is to find the "cheapest" road starting from the symbol in the upper-left corner to the lower-right corner