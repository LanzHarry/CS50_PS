#include <cs50.h>
#include <stdio.h>
#include <string.h>

int main(void)
{

    // instantiate string for repeated user input prompting
    string name_string;

    // prompt user until valid input detected
    while (1)
    {
        // get user input - ask for their name
        name_string = get_string("What's your name?: ");

        // ensure string was read and has at least a length of 1
        if ((name_string != NULL) && (strlen(name_string) > 0))
        {
            // break out of while loop to print greeting
            break;
        }
    }

    // print the greeting to the terminal
    printf("hello, %s\n", name_string);

    // return 0 at end of main upon successful program completion
    return 0;
}
