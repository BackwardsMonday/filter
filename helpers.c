#include "helpers.h"
#include <math.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for(int i = 0; i < height; i++)
    {
        for(int j = 0; j < width; j++)
        {
            RGBTRIPLE pixel = image[i][j];
            int newValue = round((pixel.rgbtBlue + pixel.rgbtGreen + pixel.rgbtRed)/3);

            pixel.rgbtBlue = newValue;
            pixel.rgbtRed = newValue;
            pixel.rgbtGreen = newValue;

            image[i][j] = pixel;
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE originalImage[height][width];
    for(int i = 0; i < height; i++)
    {
        for(int j = 0; j < width; j++)
        {
            originalImage[i][j] = image[i][j];
        }
    }
    for(int i = 0; i < height; i++)
    {
        for(int j = 0; j < width; j++)
        {
            RGBTRIPLE pixal = image[i][j];
            pixal = originalImage[i][width - (j+1)];

            image[i][j] = pixal;
        }
    }
    return;
}

RGBTRIPLE add2dRGB(int height, int width, RGBTRIPLE array[height][width])
{
    RGBTRIPLE total;
    total.rgbtBlue = 0;
    total.rgbtGreen = 0;
    total.rgbtRed = 0;
    for(int i = 0; i < height; i++)
    {
        for(int j = 0; j < width; j++)
        {
            total.rgbtBlue+= array[i][j].rgbtBlue;
            total.rgbtGreen+= array[i][j].rgbtGreen;
            total.rgbtRed+= array[i][j].rgbtRed;
        }
    }
    return total;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE originalImage[height][width];
    for(int i = 0; i < height; i++)
    {
        for(int j = 0; j < width; j++)
        {
            originalImage[i][j] = image[i][j];
        }
    }

    for(int i = 0; i < height; i++)
    {
        for(int j = 0; j < width; j++)
        {
            int blanks = 0;
            RGBTRIPLE blank;
            blank.rgbtBlue = 0;
            blank.rgbtGreen = 0;
            blank.rgbtRed = 0;

            RGBTRIPLE square[3][3];
            
            if (i == 0)
            {
                if (j == 0)
                {
                    square[0][0] = blank;
                    square[0][1] = blank;
                    square[0][2] = blank;
                    square[1][0] = blank;
                    square[1][1] = originalImage[i][j];
                    square[1][2] = originalImage[i][j+1];
                    square[2][0] = blank;
                    square[2][1] = originalImage[i-1][j];
                    square[2][2] = originalImage[i-1][j+1];

                    blanks = 5;
                }
                else if (j == width-1)
                {
                    square[0][0] = blank;
                    square[0][1] = blank;
                    square[0][2] = blank;
                    square[1][0] = originalImage[i][j-1];
                    square[1][1] = originalImage[i][j];
                    square[1][2] = blank;
                    square[2][0] = originalImage[i-1][j-1];
                    square[2][1] = originalImage[i-1][j];
                    square[2][2] = blank;

                    blanks = 5;
                }
                else
                {
                    square[0][0] = blank;
                    square[0][1] = blank;
                    square[0][2] = blank;
                    square[1][0] = originalImage[i][j-1];
                    square[1][1] = originalImage[i][j];
                    square[1][2] = originalImage[i][j+1];
                    square[2][0] = originalImage[i-1][j-1];
                    square[2][1] = originalImage[i-1][j];
                    square[2][2] = originalImage[i-1][j+1];

                    blanks = 3;
                }
            }

            else if(i == height-1)
            {
                if (j == 0)
                {
                    square[0][0] = blank;
                    square[0][1] = originalImage[i+1][j];
                    square[0][2] = originalImage[i+1][j+1];
                    square[1][0] = blank;
                    square[1][1] = originalImage[i][j];
                    square[1][2] = originalImage[i][j+1];
                    square[2][0] = blank;
                    square[2][1] = blank;
                    square[2][2] = blank;

                    blanks = 5;
                }
                else if (j == width-1)
                {
                    square[0][0] = originalImage[i+1][j-1];
                    square[0][1] = originalImage[i+1][j];
                    square[0][2] = blank;
                    square[1][0] = originalImage[i][j-1];
                    square[1][1] = originalImage[i][j];
                    square[1][2] = blank;
                    square[2][0] = blank;
                    square[2][1] = blank;
                    square[2][2] = blank;

                    blanks = 5;
                }
                else
                {
                    square[0][0] = originalImage[i+1][j-1];
                    square[0][1] = originalImage[i+1][j];
                    square[0][2] = originalImage[i+1][j+1];
                    square[1][0] = originalImage[i][j-1];
                    square[1][1] = originalImage[i][j];
                    square[1][2] = originalImage[i][j+1];
                    square[2][0] = blank;
                    square[2][1] = blank;
                    square[2][2] = blank;

                    blanks = 3;

                }
            }

            else if (j == 0)
            {
                square[0][0] = blank;
                square[0][1] = originalImage[i+1][j];
                square[0][2] = originalImage[i+1][j+1];
                square[1][0] = blank;
                square[1][1] = originalImage[i][j];
                square[1][2] = originalImage[i][j+1];
                square[2][0] = blank;
                square[2][1] = originalImage[i-1][j];
                square[2][2] = originalImage[i-1][j+1];

                blanks = 3;
            }

            else if (j == width)
            {
                square[0][0] = originalImage[i+1][j-1];
                square[0][1] = originalImage[i+1][j];
                square[0][2] = blank;
                square[1][0] = originalImage[i][j-1];
                square[1][1] = originalImage[i][j];
                square[1][2] = blank;
                square[2][0] = originalImage[i-1][j-1];
                square[2][1] = originalImage[i-1][j];
                square[2][2] = blank;

                blanks = 3;
            }

            else
            {
                square[0][0] = originalImage[i+1][j-1];
                square[0][1] = originalImage[i+1][j];
                square[0][2] = originalImage[i+1][j+1];
                square[1][0] = originalImage[i][j-1];
                square[1][1] = originalImage[i][j];
                square[1][2] = originalImage[i][j+1];
                square[2][0] = originalImage[i-1][j-1];
                square[2][1] = originalImage[i-1][j];
                square[2][2] = originalImage[i-1][j+1];

            }
            

            RGBTRIPLE newValue = add2dRGB(3, 3, square);

            newValue.rgbtBlue = round(newValue.rgbtBlue/(9-blanks));
            newValue.rgbtGreen = round(newValue.rgbtGreen/(9-blanks));
            newValue.rgbtRed = round(newValue.rgbtRed/(9-blanks));

            image[i][j] = newValue;

        }
    }
    return;
}

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    return;
}
