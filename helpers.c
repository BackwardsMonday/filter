#include "helpers.h"
#include <math.h>
#include <stdio.h>

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

RGBTRIPLE avregeSquare(int pixalsHight, int pixalsWidth, int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE newValue;
    float values = 0;
    newValue.rgbtBlue = 0;
    newValue.rgbtGreen = 0;
    newValue.rgbtRed = 0;

    for (int i = -1; i < 2; i++)
    {
        for(int j = -1; j < 2; j++)
        {
            if ((i == -1 && pixalsHight == 0) || (i == 1 && pixalsHight == height-1) || (j == -1 && pixalsWidth == 0) || (j == 1 && pixalsWidth == width-1))
            {
                continue;
            }
            else
            {
                values++;
                newValue.rgbtBlue+= image[pixalsHight+i][pixalsWidth+j].rgbtBlue;
                newValue.rgbtRed+= image[pixalsHight+i][pixalsWidth+j].rgbtRed;
                newValue.rgbtGreen+= image[pixalsHight+i][pixalsWidth+j].rgbtGreen;
            }
        }
    }
    newValue.rgbtRed = round(newValue.rgbtRed/values);
    newValue.rgbtBlue = round(newValue.rgbtBlue/values);
    newValue.rgbtGreen = round(newValue.rgbtGreen/values);
   
    return newValue;
}
void blur(int height, int width, RGBTRIPLE image[height][width])
{  
    RGBTRIPLE originalImage[height][width];
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            originalImage[i][j] = image[i][j];
        }
    }
    for (int i = 0; i < height; i++)
    {
        for(int j = 0; j < width; j++)
        {
            RGBTRIPLE newValue = avregeSquare(i, j, height, width, originalImage);

            image[i][j] = newValue;
        }
    }
    return;
}

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    int xKernel[3][3] =  {
        {-1, 0, 1},
        {-2, 0, 2},
        {-1, 0, 1}
    };
    int yKernel[3][3] = {
        {-1, -2, -1},
        {0, 0, 0},
        {1, 2, 1}
    };
    RGBTRIPLE originalImage[height][width];
    for(int i = 0; i < height; i++)
    {
        for(int j = 0; j < width; i++)
        {
            originalImage[i][j] = image[i][j];
        }
    }

    for(int i = 0; i < height; i++)
    {
        for(int j = 0; j < width; j++)
        {
            RGBTRIPLE pixial = image[i][j];
            RGBTRIPLE black;
            black.rgbtBlue = 0;
            black.rgbtGreen = 0;
            black.rgbtRed = 0;
            RGBTRIPLE Gx = black;
            RGBTRIPLE Gy = black;

            for(int k = 0; k < 2; k++)
            {
                Gx.rgbtBlue+= originalImage[k][j-1].rgbtBlue*xKernel[k][0];
                Gx.rgbtGreen+= originalImage[k][j-1].rgbtGreen*xKernel[k][0];
                Gx.rgbtRed+= originalImage[k][j-1].rgbtRed*xKernel[k][0];

                Gx.rgbtBlue+= originalImage[k][j+1].rgbtBlue*xKernel[k][2];
                Gx.rgbtGreen+= originalImage[k][j+1].rgbtGreen*xKernel[k][2];
                Gx.rgbtRed+= originalImage[k][j+1].rgbtRed*xKernel[k][2];
            }
            for(int k = 0; k < 2; k++)
            {
                
            }
        }
    }
    return;
}
