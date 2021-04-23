# The Markov Cluster Algorithm 
The MCL algorithm invented by Stjn van Dongen is short for the Markov Cluster Algorithm, a fast and scalable unsupervised cluster algorithm for graphs based on simulation of flow in graphs.   
[detail of MCL](micans.org/mcl/)

# Algorthm Steps
1. input a graph, Expansion $e$, Inflation $r$
2. build adj_matrix
3. add self_loop for every nodes(selected)
4. normolization adj_matrix
5. count the power of adj_matrix
6. inflate by matrix built from r
7. loop step5 and step6 until collect
9. turn the adj_matrix to result

# about project
data.cpp is some functions to process graph into matrix  

mcl.cpp is the algorithm , you can regulate the value in main.cpp

chamelon is another algorithm , I tried to combine them but havn't done.

if dataset is large, the performance maybe worse on the runtime.And the matrix can't be stored in the memory.

# It is a black hole...
I will try to combine these two algorithm in the future.And optimize the way of store and runtime.
we can seperate the matrix to some block and store in disk, and write w/r functions.

# how to find me?
my blog: melowlz.top  
my wechat: xxscoder
