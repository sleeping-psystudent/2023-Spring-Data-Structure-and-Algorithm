# Magical Cats
Time Limit: 2 s<br>
Mem Limit: 1048576 KB

## Description
Demeter Sphynx Abyssinian (a.k.a. DSA) is a passionate cat lover who shares zir home with hundreds of thousands of furry felines. These adorable creatures consume tons of food every day, so DSA wants to gather statistics in order to formulate a feeding plan for the future.

There are $N$ cats in the house, and each cat living in the $i^{th}$ room has a unique appetite $a_i$. This appetite value represents the amount of food distributed to that cat every day. Furthermore, each cat is associated with a color represented by an integer value $b_i$.

DSA is interested in establishing a correlation between a cat's color and its appetite. In particular, ze wants to determine the number of cats that have an appetite falling within the range $\[1_j,r_j\]$ and possess the color $c_j$.

Nevertheless, there are some greedy cats in the household who desire more food and sneakily exchange their bowls with some unsuspecting cats. To avoid getting caught by DSA, a greedy cat always picks a victim whose appetite is closest to its own from among the cats with larger appetites. Whenever two cats' bowls are swapped, their appetites are swapped as well, since DSA distributes food based on the size of the bowls. Please note that the cat that has the largest appetite at any point cannot be greedy.

Recently, a magical fairy pays a visit to DSA's home and casts some spells on the cats. The fairy first selects a particular color $c_j$ and then picks the cat with the highest or lowest appetite among all the cats with that color. The chosen cat will then be able to increase its appetite to the highest appetite of all cats plus one, denoted as $\max_{0\leq i\leq N}(a_i)+1$. However, on occasion, the magic may fail, causing the opposite effect that decreases the cat's appetite to the smallest appetite of all cats minus one, denoted as $\min_{0\leq i\leq N}(a_i)-1$. The selection of the cat with the highest $(1)$ or lowest $0$ appetite to receive the magic is represented by $s_i\in \{1,0\}$, and the success $(1)$ or failure $(0)$ of the magic is represented by $t_j\in \{1,0\}$. It is important to note that a cat's appetite may become negative as a result of this magic.

Given $M$ mixed steps of DSA's question-asking, greedy cats' swapping, and fairy's magic spells, can you make sure that each of DSA's questions is answered correctly?

## Input
The first line contains two space-separated integers $N$,$M$ the number of cats and the number of steps. The cats will be $0$-indexed. The second line contains $N$ space-separated integers $a_0,a_1,...,a_{N-1}$, where $a_i$ is the appetite of the $i^{th}$ cat. The third line contains $N$ space-separated integers $b_0,b_1,...,b_{N-1}$, where $b_i$ is the color of the $i^{th}$ cat. Each of the next $M$ lines contains one of the following:

+ $1 c_j,l_j,r_j$ : a questioning step (1) followed by three space-separated integers $c_j,l_j,r_j$, which denote the color, the lower bound, and the upper bound of the question. There can be no cats that are of color $c_j$ in a questioning step.
+ $2 k_j$: a swapping step (2) followed by an integer $k_j$, which is the index of greedy cat.
+ $3 c_j,s_j,t_j$: a magic step (3) followed by three space-separated integers $c_j,s_j,t_j$, which denotes the color, the direction of the magic, and the success/failure of the magic. We guarantee that a cat with color $c_j$ always exists for a magic step.

## Output
For each questioning step, output the answer to the question in a new line.

## Constraints
+ $2\leq N\leq 3\times 10^5$
+ $1\leq M\leq 3\times 10^5$
+ $1\leq a_i,b_i,c_i\leq 10^9$
+ $0\leq k_j<N$
+ $s_j,t_j\in \{0,1\}$
+ $-2\times 10^9\leq l_j\leq r_j\leq 2\times 10^9$

## Sample Cases
### Smaple Input 1
```
6 5
2 1 6 4 5 3
2 1 3 2 3 3
1 2 1 4
1 4 3 6
2 3
1 2 2 3
1 3 4 6
```
### Sample Output 1
```
2
0
1
2
```
### Sample Input 2
```
10 7
6 3 2 4 10 5 9 8 7 1
5 8 1 6 7 7 4 9 1 9
2 8
3 1 0 1
1 1 9 11
1 1 8 10
1 1 5 11
2 8
1 1 5 9
```
### Sample Output2
```
1
1
2
1
```
