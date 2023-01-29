# SomeConnect4Algorithm
idk I thought it would be fun to try and make a competitive connect 4 algorithm, even though I'm getting behind in my classes and have midterms coming up, because priorities.


I wrote it in C++, but it's a bit sloppy and my 4d array ended up being virtually unused because it seems like a lot of work for an extra few lines of code that make it virtually the same. Maybe I'll modify it later I guess.






uh, below are the original ideas for how the program would work, though they're probably not original outisde of my head since connnect 4 has been around for so long. At least it's the first time I've thought about this kind of thing so it's close enough to originality to me.

each empty space calculated on point system of 4 scales:
(V) Vertical
(H) Horizontal
(DR) diagonal:UpRight
(DL) diagonal:UpLeft

Calculated for both player and opponent.
Calculation: each empty space on grid weighed based on how many in row exist.
	If one empty space has horizontally, 2 filled red on right, 1 filled red on left, points added to 3; highest priority
	If one empty space has vertically, 3 yellow below, points 3; highest priority

ones directly atop currently filled spaces and bottom row if empty = REAL POINTS
all others above, not immediately able to be placed = THEORETICAL POINTS, AI prioritizes tricking opponent

priority given slightly more to gaining own points rather than blocking opponent. 3+ in a row for self highest possible priority
