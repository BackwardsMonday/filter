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
    for(int i = 0; i < height; i++)
    {
        for(int j = 0; j < height; j++)
        {
            RGBTRIPLE pixal = image[i][j];
            pixal = image[i][width - (j+1)];

            image[i][j] = pixal;
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    return;
}

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    return;
}
