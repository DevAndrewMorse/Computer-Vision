# Computer-Vision
The following assignments involve the use of Sobel and Canny filters.

Sobel:

First make sure both Sobel.c and garb34.pgm are both in the same directory and ```cd``` to the proper directory if needed in terminal. In terminal run (Unix) ```gcc -o Sobel Sobel.c```. Once compiled then run the .exe in terminal the following command: ```./Sobel garb34.pgm mag.pgm low.pgm high.pgm 30 70```. Once executed, the result will be the three .pgm outputs: ```mag.pgm```, ```low.pgm```, ```high.pgm```. 


Canny:

First make sure both Canny.c and garb34.pgm are both in the same directory and ```cd``` to the proper directory before running. In terminal run (Unix) ```gcc -o Canny Canny.c```. Once compiled then run in terminal the following inputs in the terminal. ```./Canny garb34.pgm mag.pgm peaks.pgm doublethresholding.pgm 1```, where ```1``` denotes the sigma value for pixel width or Gaussian width. The output of ```mag.pgm```, ```peaks.pgm```, and ```doublethresholding.pgm``` should match the output results provided in the Canny folder. 
