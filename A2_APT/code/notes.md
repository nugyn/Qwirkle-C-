#Assignment 

##Base Requirements

1) Name of Player (Current)
2) Scores
3) Gamestate
4) The tiles of the current players hand 
5) The user prompt

##Player actions:

1) Place a tile
2) Replace a tile in their hand 

##Alternative:

1) Save the game to a file (store as a csv)
 - Store values of the tiles, then rebuild the data structs 

2) Quit the game 


##The Board
1) The board is `2D Grid` of tiles, up to a maximum size of 26 * 26

    Idea: we traverse through the Linked List, grab tile from Node. Then place in 2D array. 

        When console prints the board, it just interacts with the 2D Array.
        Reason: it's easier to know what the coordinates are, and there are able to make combinations easier
        If the whole thing is an array of Linked List, what if it's in position A, 2. 

    Linked List, is a chain. And so if is empty. Will only have one node. 

        Pros: The linkedList will be fixed, and therefore we run into out of index array bs.

        Cons: To implement a grid with a LinkedList. There must exist an array of Linked List (a to f ) of size 6 (with 6 linkedlist). Therefore, the linked begins as empty. As all we go is traverse and place a tile in. 
        I think this is not efficient. When a player chooses a grid, it requires to traverse to the start the middle, this is O(n) worst case. (it requires a constant for loop to place a tile, as well as generate the map)

    A vector or 2D array can keep track of indexes, easier, place them into the array with at O(1) 

        Pros: Placing a tile is O(1), it easier to keep track of coordinates. 
        It however, still requires a loop to generate the map. 

        Cons: We may lose track of array index out of bounds, memory management is more cumbersome

##Player Hand

Specs: When adding a tile, it is always added at the end of the list.•When removing a tile, theremainingtiles stay in thesame order

For the reasons, a linked list is the way we go. We make it a private variable. 

It is stored in a save game file (!!!Figure out how to read files, and save the tiles)