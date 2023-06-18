# Alexander Loves Sweet Dumplings 2
Time Limit: 2 s<br>
Mem Limit: 1048576 KB

## Description

## Input
## Output
## Constraint
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
