# Interactive-World-Builder
Simple game in which a player can navigate around in a simple world. The world will simply be a set of locations connected by paths/roads. The "explorer" (user) is assumed to start at the first node, node 0. The program will then read a series of commands from standard input to navigate through that world. Each command will be just one of the letters N, S, W or E, representing a request by the explorer to move from the current location to a neighbouring location along a path heading in the direction North, South, West or East respectively. An additional command, Q, is used to quit the program and L is used to get the description of the current node, if there is one. 

The program will read in a text file of the world description file and should follow the following format, 

Line 1: two space separated integers n and m, specifying the number of nodes and the number of edges in the graph respectively. 0 < n <= 1000, 0 < m <= 4000.

The next n lines are the node definitions for the n nodes. A node definition consists of a node name optionally followed by a colon, a space and a node description. The total length of an input line, not including the newline and the terminating null byte, is at most 500 characters.

The next m lines define the bi-directional edges of the graph. Lines are at most 500 characters in length, excluding the newline and string terminator. Each line consists of four space separated fields. The first two are the 0-origin node numbers that the edge connects, and the third and fourth fields are each a single character specifying the direction from which the edge leaves the first and second nodes respectively. The allowable directions are NSEW for North, South, East and West respectively. 

A simple example of a two-node world with node descriptions is the following 5-line file.

2 2
Kauri tree: You are standing at the base of a large Kauri tree. A sign, nailed to the tree, says in tiny writing "Please stay well clear of the base of this tree to avoid damaging the delicate roots". There is a well-formed trail off to the east and rocky ill-formed tracks to the west and south.
Waterfall: You're in a grassy clearing at the base of a steep bank. A waterfall cascades down the bank. To the north, a staircase climbs up the bank beside the waterfall.
0 0 W S
0 1 E N
