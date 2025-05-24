# redblacktree


Red-Black Tree Implementation
=============================

This project implements a Red-Black Tree (RBT) in C++. It supports dynamic insertion and deletion of nodes, depth-first search (DFS) with timestamp labeling, querying nodes by discovery/finish times, and printing the tree structure.

Features
--------
- Insert nodes into the Red-Black Tree
- Delete nodes while maintaining Red-Black properties
- Perform DFS and assign discovery/finish times
- Query nodes using DFS timestamps
- Print the tree structure with color and hierarchy
- Handles invalid operations gracefully

File Structure
--------------
- redblacktree.cpp â€” Main implementation of the Red-Black Tree and all command handling
- input.txt â€” Text file containing initial node names to be inserted (one per line)

How to Run
----------
Requirements:
- C++11 or higher
- Terminal or IDE (CLion, Visual Studio, etc.)

Compilation (Terminal Example):
    g++ -std=c++11 redblacktree.cpp -o rbt

Execution:
    ./rbt input.txt

`input.txt` should contain node names (strings) to be inserted into the RBT, one per line.

After launching, you can enter commands via standard input (keyboard).

Supported Commands
------------------
- insert <name>           Insert a node with the given name
- delete <name>           Delete a node by name
- dfs                     Perform depth-first search and assign timestamps
- query <d> <f>           Return node with given discovery and finish time
- print-rbt               Print the tree structure with node colors
- quit                    Exit the program

Example:
    insert 10
    insert 20
    dfs
    query 1 6
    print-rbt
    delete 20
    quit

Sample Input File (input.txt)
-----------------------------
alpha
beta
gamma
delta

Sample Output
-------------
Directive-----------------> insert alpha
Directive-----------------> insert beta
Directive-----------------> insert gamma
Directive-----------------> dfs
alpha (BLACK): d=1, f=6
...
Directive-----------------> query 1 6
Output: Node alpha (BLACK)
Directive-----------------> print-rbt
alpha (BLACK)
. beta (RED)
. . gamma (BLACK)
...
Directive-----------------> quit

Notes
-----
- Names must be unique strings (duplicates are ignored with error message).
- All insertions follow Red-Black Tree balancing rules.
- Timestamps are automatically managed in DFS traversal.
