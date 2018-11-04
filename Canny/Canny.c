
#include <stdlib.h>
#include <stdio.h>                  
#include <math.h>

#define  PICSIZE 256
#define  MAXMASK 100

        int pic[PICSIZE][PICSIZE];
        int edgeflag[PICSIZE][PICSIZE];
        int  histogram[PICSIZE];
        double outpicx[PICSIZE][PICSIZE];
        double outpicy[PICSIZE][PICSIZE];
        double ival[PICSIZE][PICSIZE];
        double maskx[MAXMASK][MAXMASK];
        double masky[MAXMASK][MAXMASK];
        double xconv[PICSIZE][PICSIZE];
        double yconv[PICSIZE][PICSIZE];
        double peaks [PICSIZE][PICSIZE];
        double final [PICSIZE][PICSIZE];
        
int main(argc,argv)
int argc;
char **argv;
{
    int     i,j,p,q,s,t,mr,centx,centy, moretodo;
    double  maskval, sum1, sum2, sig, maxival, minival, maxval, slope, HI, LO;
    FILE    *fp1, *fo1, *fo2, *fo3, *fopen();
    char    *foobar;

    // Holds PGM Header 
    char throwaway[80];

    // Input PMG
    argc--; argv++;
    foobar = *argv;
    fp1 = fopen(foobar,"rb");

    // #1
    // Output Magnitude
    argc--; argv++;
    foobar = *argv;
    fo1 = fopen(foobar,"wb");

    // #2
    //Output Black/White Peaks
    argc--; argv++;
    foobar = *argv;
    fo2 = fopen(foobar,"wb");

    // #3
    // Output Black/White Double Thresholding
    argc--; argv++;
    foobar = *argv;
    fo3 = fopen(foobar,"wb");

    // Sigma Input - Converts to Float Value
    argc--; argv++;
    foobar = *argv;
    sig = atof(foobar);

    // Strip PGM Header
    fgets(throwaway, 80, fp1);
    fgets(throwaway, 80, fp1);
    fgets(throwaway, 80, fp1);
    if ( !( (throwaway[0]=='2') && (throwaway[1]=='5') && (throwaway[2]=='5')))
    fgets(throwaway, 80, fp1);

    // Apply Headers to Output 
    fprintf(fo1, "P5\n%d %d\n255\n", 256, 256);
    fprintf(fo2, "P5\n%d %d\n255\n", 256, 256);
    fprintf(fo3, "P5\n%d %d\n255\n", 256, 256);


    mr = (int)(sig * 3);
    centx = (MAXMASK / 2);
    centy = (MAXMASK / 2);


    // Getting information from input PGM
    for (i = 0; i < 256; i++)
        for (j = 0; j < 256; j++)
            pic[i][j]  =  getc(fp1);


        //__________________________________________________________________

        // Part 1:
        // TODO: Changes
        // Second derivative needs to be changed to first derivative
        
        for (p = -mr; p <= mr; p++)
        {
          for (q = -mr; q <= mr; q++)
          {
            // First derivative 
            maskval = exp(-((p * p + q * q) / (2 * sig * sig)));

            // Applied to masks X and Y: X to P and Y to Q 
            maskx[centy + q][centx + p] = -p * maskval;
            masky[centy + q][centx + p] = -q * maskval; 
          }
        }

        for (i = mr; i <= 255 - mr; i++)
        {
          for (j = mr; j <= 255 - mr; j++)
          {
            
            sum1 = 0;
            sum2 = 0;

            for (p = -mr; p <= mr; p++)
            {
              for (q = -mr; q <= mr; q++)
              {
                sum1 += pic[i + p][j + q] * maskx[p + centy][q + centx];
                sum2 += pic[i + p][j + q] * masky[p + centy][q + centx];
              }
            }
             outpicx[i][j] = sum1;
             outpicy[i][j] = sum2;

             xconv[i][j] = sum1;
             yconv[i][j] = sum2;   
          }
        }

        // Taken from sobel.c
        // Computing Magnitude: 
        maxival = 0;
        for (i = mr; i < 256 - mr; i++)
        {
            for (j= mr;j < 256 - mr; j++)
            {
                ival[i][j] = sqrt((double)((outpicx[i][j]*outpicx[i][j]) + (outpicy[i][j]*outpicy[i][j])));
                if (ival[i][j] > maxival)
                    maxival = ival[i][j];
            }
        }

        // Taken from sobel.c
        // Header already applied to ouput 1
        for (i = 0; i < 256; i++) 
        {
            for (j = 0; j < 256; j++) 
            {
                ival[i][j] = (ival[i][j] / maxival) * 255;
                fprintf(fo1,"%c",(char)((int)(ival[i][j])));
            }
        }

        //____________________________________________________________________

        // Part 2:
        // Getting black/white peaks

        for (i = mr; i < 256-mr; i++) {
            for(j = mr; j < 256-mr; j++) {

                if ((xconv[i][j]) == 0.0) {
                    xconv[i][j] = 0.00001;
                }

                slope = yconv[i][j]/xconv[i][j];

                if ((slope <= 0.4142) && (slope > -0.4142)) {
                    if((ival[i][j] > ival[i][j - 1]) && (ival[i][j] > ival[i][j + 1])) {
                        peaks[i][j] = 255;
                    }
                }

                else if ((slope <= 2.4142) && (slope > 0.4142)) {
                    if ((ival[i][j] > ival[i - 1][j - 1]) && (ival[i][j] > ival[i + 1][j + 1])) {
                        peaks[i][j] = 255;
                    }
                }

                else if ((slope <= -0.4142) && (slope > -2.4142)) {
                    if ((ival[i][j] > ival[i + 1][j - 1]) && (ival[i][j] > ival[i - 1][j + 1])) {
                        peaks[i][j] = 255;
                    }
                }

                else {
                    if ((ival[i][j] > ival[i - 1][j]) && (ival[i][j] > ival[i + 1][j])) {
                        peaks[i][j] = 255;
                    }
                }
            }
        }

        // Print information to Peaks
        for (i = 0; i < 256; i++) 
        {
            for (j = 0; j < 256; j++) 
            {
                fprintf(fo2,"%c",(char)((int)(peaks[i][j])));
            }
        }

        //_____________________________________________________________________________
        // Part 4:
        // Get HI and LO
        // First determine HI and take 35% of that result for LO

        // Index input data from magnitudes to histogram
        for (i = 0; i < 256; i++) 
        {
        	for (j = 0;  j < 256; j++) 
            {
        		(histogram[(int)ival[i][j]])++;
        	}
        }

        // Compute HI // Cutoff .05 originally 
        double cutOff = 0.05 * 256 * 256;
        double areaOfTops = 0;

        for (i = 255; i > 0; i--) 
        {
            areaOfTops += histogram[i];
            if (areaOfTops > cutOff)
                break;
        }

        // Set our HI & LO
        HI = i;
        LO = 0.35 * HI;

        //____________________________________________________________________________
        // Part 3: 
        // Double Threshold

        // Black/White for Peaks and Final
        for (i = 0; i < 256; i++) 
        {
            for(j = 0; j < 256; j++) 
            {
                if (peaks[i][j] == 255) 
                {
                    // ival holds magnitude
                    if (ival[i][j] > HI) 
                    {
                        peaks[i][j] = 0;
                        final[i][j] = 255;
                    }
                    else if (ival[i][j] < LO) 
                    {
                        peaks[i][j] = 0;
                        final[i][j] = 0;
                    }
                }
            }
        }

        // Inefficient method
        moretodo = 1;
        while (moretodo == 1) 
        {
            // Flag ON/OFF
            moretodo = 0;

            for (i = 0; i < 256; i++) 
            {
                for (j = 0; j < 256; j++) 
                {
                    if (peaks[i][j] == 255) 
                    {
                        // P for X and Q for Y
                        for (p = -1; p <= 1; p++) 
                        {
                            for (q = -1; q <= 1; q++) 
                            {
                                if (final[i + p][j + q] == 255) 
                                {
                                    peaks[i][j] = 0;
                                    final[i][j] = 255;
                                    moretodo = 1;
                                }
                            }
                        }
                    }
                }
            }
        }

        // Print information to Final PGM
        for (i = 0; i < 256; i++) 
        {
            for (j = 0; j < 256; j++) 
            {
                fprintf(fo3,"%c",(char)((int)(final[i][j])));
            }
        }
        
        // Close File
        fclose(fp1);
        fclose(fo1);
        fclose(fo2);
        fclose(fo3);
        return 0;

}
