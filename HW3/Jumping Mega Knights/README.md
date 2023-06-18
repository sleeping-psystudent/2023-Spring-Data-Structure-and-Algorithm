# Jumping Mega Knights
Time Limit: 1 s<br>
Mem Limit: 1048576 KB

## Description
There are $n$ mega knights located at $n$ distinct positions. The $i$-th mega knight has a jump damage of $a_i$ and hitpoints of $h_i$.

In the following $m$ rounds, during the $i$-th round, the $x_i$-th mega knight suddenly wants to attack the $y_i$-th mega knight. All the mega knights located at the same position as the
$x_i$-th one will jump to the position of the $y-i$-th mega knight. Because the damage caused by a mega knight's attack is AOE (area of effect), all the mega knights at the same position as the $y-i$-th one will be attacked, and their hitpoints will be reduced by the total jump damage of the mega knights that jumped to their position. If a mega knight's hitpoints $\leq 0$, it will instantly die and will no longer jump or attack other mega knights.

Determine how many times each mega knight jumps.

## Input
The first line contains two positive integers $n$ and $m$ separated by a space -- the number of mega knights and the number of attack rounds. The second line contains $n$ positive integers
$h_1,h_2,...,h_n$ separated by spaces -- the hitpoints of each mega knight. The third line contains $n$ positive integers $a_1,a_2,...,a_n$, separated by spaces -- the jump damage of each mega knight. The next $m$ lines each contain two positive integers $x_i$ and $y-i$ separated by a space -- the attacking and the attacked mega knight.

Note that if the $x_i$-th mega knight wants to attack the $y_i$-th mega knight, but one of them is already dead, nothing will happen, as a dead mega knight cannot attack or be attacked. Also, if both mega knights are at the same position, nothing will happen, as mega knights need to jump to generate attack effects.

## Output
Output a line containing $n$ integers separated by spaces. The $i$-th integer represents the total number of jumps made by the $i$-th mega knight.

## Constrainsts
+ $1\leq n,m \leq 2\times 10^5$
+ $1\leq a_i,h_i \leq 10^9$
+ $1\leq x_i,y_i \leq n$
+ $x_i \neq y_i$

## Sample Cases
### Sample Input 1
```
6 5
7 7 7 7 7 14
3 1 4 1 5 9
2 3
2 1
4 3
1 6
6 3
```
### Sample Output 1
```
1 3 2 2 0 0
```
### Sample Input 2
```
6 5
7 7 7 7 7 14
3 1 4 1 5 9
1 6
3 2
4 5
5 3
2 6
```
### Sample Output2
```
1 0 1 2 1 0
```
