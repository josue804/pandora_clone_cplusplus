{Pandora Music Station Clone}_

##### _{Allows the user to like specific songs from a collection to add to their playlist. If they 'like' a song, the program may suggest a related song in a different genre that the user may enjoy.}, {June 6, 2015}_

#### By _**{Josue Valverde}**_

## Description

_{In this program, I created 3 data structures to store all information:
	1. An adjacency table that consists of an array of song genres where each genre points to a linear linked list of songs in that genre and also to an adjacency list (also a LLL) of nodes that point to related genres.
	2. A hash table (array that points to LLLs) where the key is determined by a calculation run on an artist's name.
	3. A circular linked list that keeps track of the user's playlist.

The program is object-oriented with 2 has-a relationships and 9 is-a relationships in the hierarchy.

I also used operator overloading for things such as inserting into the circular linked list with the << operator.}_

## Setup

* _`$ git clone [this_repository]`_
* _`$ g++ *.cpp`_
* _`$./a.out` to run program_


## Technologies Used

* _Written in C++_
* _Troubleshooted with GDB_
* _Memory leaks checked with valgrind_

### Legal

Copyright (c) 2015 **_{Josue Valverde}_**

This software is licensed under the MIT license.

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
