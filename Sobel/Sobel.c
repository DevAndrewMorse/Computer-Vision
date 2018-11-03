// Andrew Morse
// Sobel.c

#include <stdio.h>                         
#include <math.h>
#include <stdlib.h>

        int pic[256][256];
        int outpicx[256][256];
        int outpicy[256][256];
        int maskx[3][3] = {{-1,0,1},{-2,0,2},{-1,0,1}};
        int masky[3][3] = {{1,2,1},{0,0,0},{-1,-2,-1}};
        double ival[256][256],maxival;

int main(argc,argv)
int argc;
char **argv;
{
    int i,j,p,q,mr,sum1,sum2;
    // Two threshold Inputs
    double lowThreshold, highThreshold;
    // File Input and Output
    FILE *fp1, *fo1, *fo2, *fo3, *fopen();
    char *foobar;
    // Holds PGM Header 
    char throwaway[80];

    // PGM Input 
    argc--; argv++;
    foobar = *argv;
    fp1 = fopen(foobar,"rb");

    // File Ouput 1 - Magnitude 
    argc--; argv++;
    foobar = *argv;
    fo1 = fopen(foobar,"wb");

    // File Ouput 2 - Low Threshold Output
    argc--; argv++;
    foobar = *argv;
    fo2 = fopen(foobar,"wb");

    // File Ouput 3 - High Threshold Output
    argc--; argv++;
    foobar = *argv;
    fo3 = fopen(foobar,"wb");

    // Low Threshold Input -  Converts to Float
    argc--; argv++;
    foobar = *argv;
    lowThreshold = atof(foobar);

    // High Threshold Input - Converts to Float 
    argc--; argv++;
    foobar = *argv;
    highThreshold = atof(foobar);

    // Strip PGM Input Header
    fgets(throwaway, 80, fp1);
    fgets(throwaway, 80, fp1);
    fgets(throwaway, 80, fp1);
    if ( !( (throwaway[0]=='2') && (throwaway[1]=='5') && (throwaway[2]=='5')))
        fgets(throwaway, 80, fp1);

    // Apply Header to Output 
    fprintf(fo1, "P5\n%d %d\n255\n", 256, 256);
    fprintf(fo2, "P5\n%d %d\n255\n", 256, 256);
    fprintf(fo3, "P5\n%d %d\n255\n", 256, 256);

    // Gets Characters from Pic and Masks
    for (i = 0;i < 256; i++)
    {
      for (j = 0; j < 256; j++)
      {
            pic[i][j]  =  getc(fp1);
            pic[i][j]  &= 0377;
      }
    }

    // Convolution:
    // Apply Masks X & Y to Picture
    mr = 1;
    for (i = mr;i < 256 - mr; i++)
    {
      for (j = mr;j < 256 - mr; j++)
      {
        sum1 = 0;
        sum2 = 0;

        // Remember: P to X, Q to Y 
        for (p = -mr;p <= mr; p++)
        {
          for (q= -mr; q <= mr; q++)
          {
            sum1 += pic[i+p][j+q] * maskx[p+mr][q+mr];
            sum2 += pic[i+p][j+q] * masky[p+mr][q+mr];
          }
        }
        outpicx[i][j] = sum1;
        outpicy[i][j] = sum2;
      }
    }

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

    // TODO:
    // Threshold will not be applied to the magnitude
    // We will use this loop to give us the remaining outputs of black or white
    for (i = 0;i < 256; i++)
    { 
      for (j = 0;j < 256; j++)
      {
        // Magnitude
        ival[i][j] = (ival[i][j] / maxival) * 255;
        fprintf(fo1,"%c",(char)((int)(ival[i][j])));

        // Apply Black or White Low Threshold
        if (ival[i][j] > lowThreshold)
          fprintf(fo2, "%c", (char)((int)(255)));
        else
          fprintf(fo2, "%c", (char)((int)(0)));

        // Apply Black or White High Threshold
        if (ival[i][j] > highThreshold)
          fprintf(fo3, "%c", (char)((int)(255)));
        else
          fprintf(fo3, "%c", (char)((int)(0)));
      }
    }

    // Close Files
    fclose(fp1);
    fclose(fo1);
    fclose(fo2);
    fclose(fo3);
    return 0;
}
