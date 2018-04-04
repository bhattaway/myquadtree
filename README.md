# myquadtree

USAGE:

go into the demo folder, "make", then "make run"

input an integer. the program creates that many squares on screen.

during runtime, pressing spacebar will toggle between collision methods (quadtree or bruteforce)

PURPOSE:

Normal brute force collision checking between many objects becomes very intensive, (i.e. 
checking each object against each other object in the plane). O(n^2) comparisons are required,
where n is the number of objects. This is unsustainable for sufficiently large n.

One method to resolve this is to split the plane into smaller areas, such that you only need to
check objects against eachother if they are in the same subregion. This is the goal of the quadtree.

My program dynamically creates subtrees (partitioning a region into four equal, smaller regions) if
the number of objects in a given region exceeds some threshold (by default, 8). Then, if one of those
subregions contains 8 again, then it will subdivide further. This occurs until a max depth is reached
(by default, 6).

Inside each subregion, a brute force collision detection method is used, but n is very small (always 
less than threshold, unless max depth has been reached).

The collision tree is rebuilt every frame.

If an object happens to land on the border between two subregions, it is checked against all of the
subregions it intersects.

On my machine, noticable slowdown occurs when n=2000 using the brute force technique, and framerate
becomes extremely choppy at n=3000. Using the quadtree for collision detection, noticable slowdown 
does not occur until n=20000, sustaining ten times more objects than the brute force method.

When a collision occurs, each object changes its x and y velocity, as well as its color. It is not
particularly realistic, as this project was done moreso to demonstrate the differences between
collision detection methods, rather than having an accurate collision handler.
