# Computer-Vision
The following assignments involve the use of Sobel and Canny filters, using .pgm as the input and output results.

Sobel:

First make sure both Sobel.c and garb34.pgm are both in the same directory and ```cd``` to the proper directory if needed in terminal. In terminal run ```gcc -o Sobel Sobel.c``` then run. Once compiled then run in terminal the following inputs in terminal ```./Sobel garb34.pgm low.pgm high.pgm 30 70```. Once you run this you'll get three .pgm outputs giving you the magnitude ouput, low threshold output, and high threshold ouput. The smoothener is already calculated into the existing masks used in the program. The last two parameters can be varied if you wish to test other ouput results. The ouputs included in Sobel should match to the 30 70 parameters. 


Canny:

First make sure both Canny.c and garb34.pgm are both in the same directory and ```cd``` to the proper directory before running.
