# Alexander Loves Sweet Dumplings 2
Time Limit: 2 s<br>
Mem Limit: 1048576 KB

## Description
There are $N$ types of sweet dumplings for sale in DSA (Deluxe Supermarket Alliance). On any given day, each type of the dumplings have two packs available for purchase. However, these two packs of the same type have different prices.

At the end of each day, Alexander and Bomboo both want to purchase all types of dumplings, each with one pack. Both of them want to make the purchase with minimum costs. As a result, they reached an agreement to buy the sweet dumplings with these rules:

1) On any day, they will each take turn to buy one pack of sweet dumpling until they complete the purchases for the day. Alexandar always goes first at the beginning of any day. Both of them are genius and they will use optimal strategy to make the purchases, in order to save money.
2) For each of the $M$ days, each of them will complete the purchase for all $N$ types of dumplings, each with one pack.
3) At the beginning of each day, each of the $N$ types of sweet dumplings are restocked to two packs.
4) At the end of each day, the prices of two packs of one type of dumpling will be changed.

Your goal is to help Alexandar to determine the cost to make the purchase for each of the $M$ days.

## Input
The first line contains two integers, $N$ and $M$, representing the number of kinds of sweet dumplings and the length of Alexander's challenge.

The next $N$ lines contain two integers each, $a_i$ and $b_i$, representing the price of two packs of sweet dumplings of the $i$-th type.

In the following $M-1$ lines, the -th line contains five integers $t_i,c_i,d_i,e_i,f_i$. Indicating that the price of $t_i$-th sweet dumplings will change to $(c_i\times P+d_i \mod 1000000007)$ and $(e_i\times P+f_i \mod 1000000007)$ on day $i+1$, where $P$ is the minimum cost for Alexander on the previous day.

(This problem has nothing to do with the mathematical properties of the price-updating formula.)

## Output
The output should consist of $M$ lines. The $i$-th line should contain a single integer representing the minimum cost for Alexander to buy all kinds of sweet dumplings on the $i$-th day.

## Constraint
+ $1\leq N\leq 10^5$
+ $1\leq M\leq 10^5$
+ $1\leq a_i,b_i\leq 10^9$
+ $0\leq c_i,d_i,e_i,f_i\leq 10^9$
+ $1\leq t_i\leq N$

## Sample Testcases
### Sample Input 1
```
4 6
2 4
5 7
1 7
2 1
4 0 5 0 2
1 0 6 0 2
4 0 4 0 3
2 0 1 0 3
3 0 6 0 6
```
### Sample Output 1
```
12
15
16
16
12
14
```
### Sample Input 2
```
5 4
1 1
2 3
4 6
7 10
11 15
1 0 1 0 6
3 1 4 1 5
5 4 3 2 1
```
### Sample Output 2
```
29
31
61
174
```
## Hint
Here are the details of sample 1:

+ First day, Alexander can buy each type with price $4,5,1,2$ respectively to minimize his cost.
+ Second day, the price of type $4$ is changes to $ 12\times 0+5$ and $12\times 0+2$. Hence the price of each type is $(2,4),(5,7),(1,7),(5,2)$ respectively. And Alexander can buy each type with price $2,7,1,5$ respectively to minimize his cost.
+ Third day, the price of type $1$ is changes to $15\times 0+6$ and $15\times 0+2$. Hence the price of each type is $(6,2),(5,7),(1,7),(5,2)$ respectively. And Alexander can buy each type with price $6,7,1,2$ respectively to minimize his cost.
+ and so on.
