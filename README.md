# Nearest-Neighbour-Search

The objective of this assignment was, using good object oriented principles and practice, to
design and implement a “Nearest-Neighbour Search”.

I used NN-S to find which part of an image matches another given reference image.

Demonstrating object oriented principles in the programs, I had to:<br>
<b>Write a C++ program to search for the location of a reference image in
a larger image</b>

The images provided were in .txt format. That is, each pixel was represented by a value
from 0 – 255 representing a greyscale colour.

Provided:
<ul>
<li>.txt format large “Where’s Wally” image (Type: Large_Image)</li>
<li>.txt format reference image (Type: Ref_Image)</li>
<li>C++ code to read in the .txt format images</li>
<li>C++ code to write your output into a .pgm format image</li>
</ul>

The solution needed to contain at least three classes arranged in a hierarchy as shown here:
<ul>
  <li>Base_Image class
    <ul>
    <li>Large_Image class</li>
    <li>Ref_Image class</li>
    </ul>
  </li>
  </ul>
  
To Complete:
1) A C++ solution which matches a reference image to a location in a larger image
(as well as you can)
This solution should be the complete VS project, allowing it to be opened
and run in VS. 
2) Your C++ solution should contain:
A Matrix class (containing: constructors, a destructor, operator overloads,
etc)
Inheritance hierarchy as shown above
3) The “Where’s Wally” large image showing his location as an outlined or
shaded area from the algorithm running in your code.

