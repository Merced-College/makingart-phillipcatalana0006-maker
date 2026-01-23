What do the two nested for loops over x and y represent in the program?

I chose Option A

I used arrays named red[], green[], and blue[] near the top of main. They store the RGB values for my color palette. 

Instead of just using one fixed color, the pixels can now change color based on how many iterations they took to escape. This makes the fractal show gradients and more detail.

The tricky part was that iter counts down from MAX_ITER to 0, so i had to convert it into iterations used and then map that value into the palette range. (I had the agents help a bit)