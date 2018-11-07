# Algorithms and Data Structures

## Problems

### 0. Quick Sort
Write a templated function that performs in-place quick-sorting using random partitioning. It should accept custom compare functions.

### 1. Greedy Robin
There are coins on the road. Each coin has a position (determined by a single integer number - the distance in metres from some origin). Every coin is located on one side of that origin. Robin Hood starts wherever he wants and collects these coins. He goes 1 metre per second. Each coin has a timer in seconds after which it expires (strictly after). Robin Hood is determined to collect them all.  
The first line of the input contains the number *n* (1 &leq; *n* &leq; 1000). The following *n* lines contain 2 integers - position and expiration time. Positions are integers between 0 and 1000000. Timers are integers between 0 and 1000000. The output should contain one number - the minimum time required to collect every single coin. If the task is not possible, simply output '-1'.

|input|output|
|-----|------|
|5<br>1 3<br>3 1<br>5 8<br>8 19<br>10 15|11|
|5<br>1 5<br>2 1<br>3 4<br>4 2<br>5 3|-1|

Time complexity: O(n<sup>2</sup>)

### 2. Solid Team
You want to build a football team. Every player has his performance described by an integer. The greater the number, the more effective the player is. Every team should be solid. If one of the players plays much better than all others, then other team members will dislike him, and the team will not be solid. Thus, the performance of every team member should not exceed the sum of performances of any two other team members.  
Your task is to assemble a solid team with maximum total performance (which is the sum of performances of all players). The first line of the input contains the number *n* (1 &leq; *n* &leq; 100000). The second line contains the performances of every of the n players. Performances are positive integers not greater than 2<sup>31</sup>-1. The output should contain two lines. The first line should contain the maximum total performance of the team you can build from given players. The second line should contain the numbers of the players (in ascending order) that you need to put to your team in order to reach this performance. The players have numbers starting from 1 to n in the same order that their performances appear in the input. If there are several ways to
build the team, output any of them.  

|input|output|
|-----|------|
|5<br>3 2 5 4 1|14<br>1 2 3 4|
|5<br>1 2 4 8 16|24<br>4 5|

Time complexity: O(n*log(n))

### 3. Similar Triangles
You have *n* triangles (1 &leq; *n* &leq; 1000000). Every one of them is defined by its 3 sides - using 3 integers not greater than 10<sup>9</sup>. Some of them are [**similar**](https://en.wikipedia.org/wiki/Similarity_(geometry)#Similar_triangles). Let us say that two triangles are different if they are not similar. How many different triangles do you have?  
The first line of the input contains the number *n*. The following *n* lines contain 3 integers that define triangles. The output should contain a single number - number of different triangles.

|input|output|
|-----|------|
|3<br>6 6 10<br>15 25 15<br> 35 21 21|1|
|4<br>3 4 5<br>10 11 12<br>6 7 8<br>6 8 10|3|

Time complexity: O(n)

### 4. AVL Tree
Create a class defining [AVL Tree](https://en.wikipedia.org/wiki/AVL_tree). Define the following operations: insert, get, erase, print.

### 5. Bonus
Create calculator interpreter. It should accept a single line containing only the following symbols:  
`0 1 2 3 4 5 6 7 8 9 . e ( ) - + * / ^ !`  
The output should contain a result, or 'error' in case of invalid input expression.

|input|output|
|-----|------|
|13*(2^2-1.5*2-1e0)+0!|1|
|1/0|error|
