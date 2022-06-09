#include "helpers.h"
#include <stdio.h>
#include <math.h>

int get_most_intense_color(RGBTRIPLE rgb)
{
    int red = rgb.rgbtRed;
    int green = rgb.rgbtGreen;
    int blue = rgb.rgbtBlue;

    if ((red >= green) && (red >= blue))
    {
        return red;
    }
    else if ((green >= red) && (green >= blue))
    {
        return green;
    }
    return blue;
}

int get_average_rgb_color_number(RGBTRIPLE rgb)
{
    int red = rgb.rgbtRed;
    int green = rgb.rgbtGreen;
    int blue = rgb.rgbtBlue;
    int average = (int)((red + green + blue) / 3);
    return average;
}

int get_average(int total, int n)
{
    return (int)total / n;
}

RGBTRIPLE calculate_average_color(int i, int j, int width, int height, RGBTRIPLE image[height][width])
{
    int rgb[3];
    rgb[0] = 0;
    rgb[1] = 0;
    rgb[2] = 0;
    int available_pixels_around = 0;

    // calculate top pixels
    if (i - 1 >= 0)
    {
        if (j - 1 >= 0)
        {
            // top left
            rgb[0] += image[i - 1][j - 1].rgbtRed;
            rgb[1] += image[i - 1][j - 1].rgbtGreen;
            rgb[2] += image[i - 1][j - 1].rgbtBlue;
            available_pixels_around += 1;
        }
        if (j + 1 <= width - 1)
        {
            // top right
            rgb[0] += image[i - 1][j + 1].rgbtRed;
            rgb[1] += image[i - 1][j + 1].rgbtGreen;
            rgb[2] += image[i - 1][j + 1].rgbtBlue;
            available_pixels_around += 1;
        }
        // top
        rgb[0] += image[i - 1][j].rgbtRed;
        rgb[1] += image[i - 1][j].rgbtGreen;
        rgb[2] += image[i - 1][j].rgbtBlue;
        available_pixels_around += 1;
    }

    // calculate middle pixels
    if (j - 1 >= 0)
    {
        // left
        rgb[0] += image[i][j - 1].rgbtRed;
        rgb[1] += image[i][j - 1].rgbtGreen;
        rgb[2] += image[i][j - 1].rgbtBlue;
        available_pixels_around += 1;
    }
    if (i + 1 <= width - 1)
    {
        // right
        rgb[0] += image[i][j + 1].rgbtRed;
        rgb[1] += image[i][j + 1].rgbtGreen;
        rgb[2] += image[i][j + 1].rgbtBlue;
        available_pixels_around += 1;
    }

    // calculate bottom pixels
    if (i + 1 <= height - 1)
    {
        if (j - 1 >= 0)
        {
            // bottom left
            rgb[0] += image[i + 1][j - 1].rgbtRed;
            rgb[1] += image[i + 1][j - 1].rgbtGreen;
            rgb[2] += image[i + 1][j - 1].rgbtBlue;
            available_pixels_around += 1;
        }
        if (j + 1 <= width - 1)
        {
            // bottom right
            rgb[0] += image[i + 1][j + 1].rgbtRed;
            rgb[1] += image[i + 1][j + 1].rgbtGreen;
            rgb[2] += image[i + 1][j + 1].rgbtBlue;
            available_pixels_around += 1;
        }
        // bottom
        rgb[0] += image[i + 1][j].rgbtRed;
        rgb[1] += image[i + 1][j].rgbtGreen;
        rgb[2] += image[i + 1][j].rgbtBlue;
        available_pixels_around += 1;
    }

    image[i][j]
        .rgbtRed = get_average(rgb[0], available_pixels_around);
    image[i][j].rgbtGreen = get_average(rgb[1], available_pixels_around);
    image[i][j].rgbtBlue = get_average(rgb[2], available_pixels_around);
    return image[i][j];
}

int multiply_matrixes(int m_1[3][3], int m_2[3][3])
{
    int total = 0;
    for (int i = 0; i < 3; i++)
    {
        int row_total = 0;
        for (int j = 0; j < 3; j++)
        {
            row_total += m_1[i][j] * m_2[i][j];
        }
        total += row_total;
    }

    return total;
}

int compute_gx(int matrix[3][3])
{
    int gx[3][3] = {
        {-1, 0, 1},
        {-2, 0, 2},
        {-1, 0, 1}};

    return multiply_matrixes(matrix, gx);
}

int compute_gy(int matrix[3][3])
{
    int gy[3][3] = {
        {-1, -2, -1},
        {0, 0, 0},
        {1, 2, 1}};

    return multiply_matrixes(matrix, gy);
}

int calculate_new_chanel(int gx, int gy)
{
    return (int)sqrt(gx * gx + gy * gy);
}

RGBTRIPLE sobel_filter(int row, int col, int width, int height, RGBTRIPLE image[height][width])
{
    int red_chanel_matrix[3][3] = {{0, 0, 0}, {0, 0, 0}, {0, 0, 0}};
    int green_chanel_matrix[3][3] = {{0, 0, 0}, {0, 0, 0}, {0, 0, 0}};
    int blue_chanel_matrix[3][3] = {{0, 0, 0}, {0, 0, 0}, {0, 0, 0}};

    if (row - 1 >= 0)
    {
        if (col - 1 >= 0)
        {
            // top left
            red_chanel_matrix[0][0] = image[row - 1][col - 1].rgbtRed;
            green_chanel_matrix[0][0] = image[row - 1][col - 1].rgbtGreen;
            blue_chanel_matrix[0][0] = image[row - 1][col - 1].rgbtBlue;
        }
        if (col + 1 <= width - 1)
        {
            // top right
            red_chanel_matrix[0][2] = image[row - 1][col + 1].rgbtRed;
            green_chanel_matrix[0][2] = image[row - 1][col + 1].rgbtGreen;
            blue_chanel_matrix[0][2] = image[row - 1][col + 1].rgbtBlue;
        }
        // top
        red_chanel_matrix[0][1] = image[row - 1][col].rgbtRed;
        green_chanel_matrix[0][1] = image[row - 1][col].rgbtGreen;
        blue_chanel_matrix[0][1] = image[row - 1][col].rgbtBlue;
    }

    if (col - 1 >= 0)
    {
        // left
        red_chanel_matrix[1][0] = image[row][col - 1].rgbtRed;
        green_chanel_matrix[1][0] = image[row][col - 1].rgbtGreen;
        blue_chanel_matrix[1][0] = image[row][col - 1].rgbtBlue;
    }
    if (row + 1 <= width - 1)
    {
        // right
        red_chanel_matrix[1][2] = image[row][col + 1].rgbtRed;
        green_chanel_matrix[1][2] = image[row][col + 1].rgbtGreen;
        blue_chanel_matrix[1][2] = image[row][col + 1].rgbtBlue;
    }
    // middle
    red_chanel_matrix[1][1] = image[row][col].rgbtRed;
    green_chanel_matrix[1][1] = image[row][col].rgbtGreen;
    blue_chanel_matrix[1][1] = image[row][col].rgbtBlue;

    if (row + 1 <= height - 1)
    {
        if (col - 1 >= 0)
        {
            // bottom left
            red_chanel_matrix[2][0] = image[row + 1][col - 1].rgbtRed;
            green_chanel_matrix[2][0] = image[row + 1][col - 1].rgbtGreen;
            blue_chanel_matrix[2][0] = image[row + 1][col - 1].rgbtBlue;
        }
        if (col + 1 <= width - 1)
        {
            // bottom right
            red_chanel_matrix[2][2] = image[row + 1][col + 1].rgbtRed;
            green_chanel_matrix[2][2] = image[row + 1][col + 1].rgbtGreen;
            blue_chanel_matrix[2][2] = image[row + 1][col + 1].rgbtBlue;
        }
        // bottom
        red_chanel_matrix[2][1] = image[row + 1][col].rgbtRed;
        green_chanel_matrix[2][1] = image[row + 1][col].rgbtGreen;
        blue_chanel_matrix[2][1] = image[row + 1][col].rgbtBlue;
    }

    int red = calculate_new_chanel(compute_gx(red_chanel_matrix), compute_gy(red_chanel_matrix));
    int green = calculate_new_chanel(compute_gx(green_chanel_matrix), compute_gy(green_chanel_matrix));
    int blue = calculate_new_chanel(compute_gx(blue_chanel_matrix), compute_gy(blue_chanel_matrix));

    RGBTRIPLE new_rgb = {red, green, blue};
    return new_rgb;
}

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            int average = get_average_rgb_color_number(image[i][j]);
            image[i][j].rgbtBlue = average;
            image[i][j].rgbtGreen = average;
            image[i][j].rgbtRed = average;
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        RGBTRIPLE reflected_row[width];
        for (int j = width - 1; j > 0; j--)
        {
            reflected_row[width - j] = image[i][j];
        }
        for (int k = 0; k < width; k++)
        {
            image[i][k] = reflected_row[k];
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image[i][j] = calculate_average_color(i, j, width, height, image);
        }
    }
    return;
}

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE image_copy[height][width];

    // make copy
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image_copy[i][j] = image[i][j];
        }
    }

    for (int row = 0; row < height; row++)
    {
        for (int col = 0; col < width; col++)
        {
            image[row][col] = sobel_filter(row, col, width, height, image_copy);
        }
    }
    return;
}
