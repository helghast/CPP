# Flatten array

Multidimensional arrays tend to be REALLY annoying when you're using arrays of arrays.
A multidimensional array can be flattened. Its dimensions are reduced to one. This transformation yields a single-dimensional array—one
that is simpler and faster. Generally, people use the formula (x*width+y) to simulate a 2d array in a 1d array.

A 2D array is accessed with a Y and then X position. For rectangular arrays (including all 2D arrays and many jagged arrays) you can
use a single array. You multiply the first coordinate by the width, and then add the second coordinate.

The advantages of using a flat array are improved performance and interoperability with C++ or other languages.

![alt text](https://upload.wikimedia.org/wikipedia/commons/thumb/3/3d/CPT-arrays-2d.svg/220px-CPT-arrays-2d.svg.png)

## Resources:

https://www.dotnetperls.com/flatten-array

http://www.cplusplus.com/doc/tutorial/arrays/

https://en.cppreference.com/w/cpp/language/array

http://www.cplusplus.com/forum/beginner/32587/

https://stackoverflow.com/questions/2151084/map-a-2d-array-onto-a-1d-array
