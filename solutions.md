### 0. Quick Sort
Combine [this](https://en.wikipedia.org/wiki/Quicksort) with
[this](https://github.com/5981/Algorithms/blob/master/notSoQuickSort.cpp).

### 1. Greedy Robin
First, sort all the coins by their positions just in case they are not. At any time during his optimal coin collecting
Robin has collected all the coins between a certain *i* and *j* inclusive (1 ≤ *i* ≤ *j* ≤ *n*). If not all, then he should have
while going from *i* to *j* to make his way optimal.  
Let us build the following array of answers: ans[i][j][0 or 1]. ans[i][j][0] is the minimal time required to
collect all the coins from *i* to *j* and to finish in *i*. ans[i][j][1] is the minimal time required to collect
all the coins from *i* to *j* and to finish in *j*. You may check that the following is correct:  

ans[i][j][0] = min(ans[i+1][j][0] + dist(coins[i],coins[i+1]), ans[i+1][j][1] + dist(coins[i], coins[j]))  
ans[i][j][1] = min(ans[i][j-1][0] + dist(coins[i],coins[j]), ans[i][j-1][1] + dist(coins[j-1], coins[j]))  

If at any point ans[i][j][0] > lifetime[i] or ans[i][j][1] > lifetime[j], then we put a special number there
corresponding to infinity (e.g. -1).  

The answer to the whole problem is therefore min(ans[0][n-1][0], ans[0][n-1][1]). We start from all possible sections
(i,i), where 1 ≤ *i* ≤ *n* (collect one coin; *n* sections in total). Then all sections
(i,i+1) (*n*-1 sections in total), then (i,i+2) (*n*-2 sections in total) etc, according to the formulae above.
Until we reach (0,*n*-1) (1 section), at which point we have an answer. In total we've produced an array θ(*n*<sup>2</sup>)
of size in θ(*n*<sup>2</sup>) time.

### 2. Solid team
First, sort all the players by their performance. Any team has a captain and the weakest player. Let's call them *C* and *X*.
Since all the players are sorted, the weakest player is defined as  

player[X-1] + player[X] < player[C]  
AND  
player[X+1] + player[X] ≥ player[C]  

Players from *X* to *C* is the largest and best team with this captain *C*. At first we make the last player (with highest
performance) the captain. We find the weakest player for his team, summing up all the performances and memorise the result.
Then we go to the next player as a captain (1 step), and move *X* a bit as well (according to the new captain). Since
we have already summed up some players' performances, we only have to substract the previous captain and add new members,
and memorise the result. When *X* reaches the weakest player ever, we finish, and take the best team found. Our *X* and *C*
pointers moved from right to left not more than *n* steps, and for the total performance we have added or substracted each
player only once.  

Apart from sorting our algorithm performs in linear time and linear memory. Sorting does require O(n*logn), however.

### 3. Similar triangles
First, let us scale all the triangles: divide them all by their longest size. Each triangle is now presented as (a,b,1),
where 0 < a,b ≤ 1. How many of them are different? Sorting is prohibited, since we have to do it in linear time. We
use hash-table (std::unordered_map) with a hash-function based on (a,b) pair. If we see the same triangle in our table
while adding a new one, we know that it is similar. If not, we make +1 to the nubmer of different triangles.

### 4. AVL Tree
It is all explained [here](https://en.wikipedia.org/wiki/AVL_tree). Nothing to it, really.

### 5. Bonus
We can plainly parse the whole string in O(*n*<sup>2</sup>) time. 

OR use the following method which is easier to program as well  

First, make postfix (reverse Polsih) notation from the default infix one
[like this](https://en.wikipedia.org/wiki/Shunting-yard_algorithm).  
Second, calculate in postfix notation as described [here](https://en.wikipedia.org/wiki/Reverse_Polish_notation).  
Both in linear time.
