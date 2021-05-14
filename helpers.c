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
typedef struct
{
    RGBTRIPLE rgbValue;
    int integer;
}rgbAndint;


rgbAndint addSquare(int pixalsHight, int pixalsWidth, int height, int width, RGBTRIPLE image[height][width])
{
    rgbAndint newValue;
    newValue.integer = 0;
    newValue.rgbValue.rgbtBlue = 0;
    newValue.rgbValue.rgbtGreen = 0;
    newValue.rgbValue.rgbtRed = 0;

    for (int i = -1; i < 2; i++)
    {
        for(int j  = -1; j < 2; j++)
        {
            if ((i == -1 && pixalsHight == 0) || (i == 1 && pixalsHight == height-1) || (j == -1 && pixalsWidth == 0) || (j == 1 && pixalsWidth == width-1))
            {
                continue;
            }
            newValue.integer+= 1;
            newValue.rgbValue.rgbtBlue+= image[pixalsHight+i][pixalsWidth+j].rgbtBlue;
            newValue.rgbValue.rgbtRed+= image[pixalsHight+i][pixalsWidth+j].rgbtRed;
            newValue.rgbValue.rgbtGreen+= image[pixalsHight+i][pixalsWidth+j].rgbtGreen;

        }
    }
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
        for(int j  = 0; j < width; j++)
        {
            rgbAndint newValue = addSquare(i, j, height, width, originalImage);

            newValue.rgbValue.rgbtRed = newValue.rgbValue.rgbtRed/newValue.integer;
            newValue.rgbValue.rgbtBlue = newValue.rgbValue.rgbtBlue/newValue.integer;
            newValue.rgbValue.rgbtGreen = newValue.rgbValue.rgbtGreen/newValue.integer;
            image[i][j] = newValue.rgbValue;
        }
    }
    return;
}

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    return;
}
