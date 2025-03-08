#include <cs50.h>
#include <stdio.h>

int main(void)
{
    // initialise variables for pyramid height and valid height range
    int pyramid_height;
    int height_range[] = {1, 8}; // {min_height of 1, max_height of 8}

    // prompt the user for the height of the pyramid until a valid height has been input
    while (1)
    {
        // prompt the user for an integer height value
        pyramid_height = get_int("Height: ");

        // check if the value is within the height range and break if it is
        if (pyramid_height >= height_range[0] && pyramid_height <= height_range[1])
        {
            break;
        }
    }

    // if valid height supplied then build each row of pyramid
    // the height determines how many rows to print

    // construct each row half by half
    // initialise nested for loop counters
    // pad length determines number of spaces to form pyramid shape
    // brick length determines number of bricks to for pyramid body
    int i, j, pad_length, brick_length;

    // run for loops to build pyramid
    for (i = 0; i < pyramid_height; i++)
    {
        // calculate number of bricks in the row being printed
        brick_length = i + 1;

        // calculate number of spaces to print before # symbols
        pad_length = pyramid_height - brick_length;

        // print padding spaces
        for (j = 0; j < pad_length; j++)
        {
            printf(" ");
        }

        // print # symbols, N.B. j is reused here
        for (j = 0; j < brick_length; j++)
        {
            printf("#");
        }

        // print gap between # symbols
        printf("  ");

        // print # symbols, N.B. j is reused here
        for (j = 0; j < brick_length; j++)
        {
            printf("#");
        }

        // print newline for next row
        printf("\n");
    }

    // return 0 at end of main upon successful program completion
    return 0;
}
