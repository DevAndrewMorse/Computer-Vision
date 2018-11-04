# Computer-Vision
The following assignments involve the use of Sobel and Canny filters, using .pgm as the input and output results.

Sobel:

First make sure both Sobel.c and garb34.pgm are both in the same directory and ```cd``` to the proper directory if needed in terminal. In terminal run (Unix) ```gcc -o Sobel Sobel.c```. Once compiled then run in terminal the following inputs in terminal ```./Sobel garb34.pgm low.pgm high.pgm 30 70```. Once you run this you'll get three .pgm outputs giving you the magnitude ouput, low threshold output, and high threshold ouput. The smoothener is already calculated into the existing masks used in the program. The last two parameters can be varied if you wish to test other ouput results. The ouputs included in Sobel should match to the 30 70 parameters. 


Canny:

First make sure both Canny.c and garb34.pgm are both in the same directory and ```cd``` to the proper directory before running. In terminal run (Unix) ```gcc -o Canny Canny.c```. Once compiled then run in terminal the following inputs in the terminal. ```./Canny garb34.pgm mag.pgm peaks.pgm doublethresholding.pgm 1```, where ```1``` denotes the sigma value for pixel width or Gaussian width. The out put of ```mag.pgm```, ```peaks.pgm```, and ```doublethresholding.pgm``` should match the output results provided in the Canny folder. 
