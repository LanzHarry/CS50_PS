#include <cs50.h>
#include <math.h>
#include <stdio.h>

/**
 * LUHN'S ALGORITHM SUMMARY
 * Multiply every other digit by 2, starting with the number’s second-to-last digit, and then add
 * those products’ digits together.
 *
 * Add the sum to the sum of the digits that weren’t multiplied by 2.
 *
 * If the total’s last digit is 0 (or, put more formally, if the total modulo 10 is congruent to 0),
 * the number is valid!
 *
 * AMEX - Start with 34 or 37; with 15 digits
 * MC   - Start with 51, 52, 53, 54, or 55; with 16 digits
 * VISA - Start with 4; with 13 or 16 digit numbers
 */

// define custom function to check for valid card numbers
// only input is the card number
string validate_card_type(long card_number);

// custom function to extract a target digit from a base number
int extract_digit(long initial_number, int digit_to_extract);

// custom function to get the length of an integer
int number_length(long number_to_check);

// define constants for card number lengths and starting values of cards
// specify card number lengths for each card type
const int AMEX_LEN = 15, MASTERCARD_LEN = 16, VISA_LEN_0 = 13,
          VISA_LEN_1 = 16; // VISA can have two lengths

// specify leading numbers for each card type
const int AMEX_START_1 = 34, AMEX_START_2 = 37;
const int MASTERCARD_START_1 = 51, MASTERCARD_START_2 = 52, MASTERCARD_START_3 = 53,
          MASTERCARD_START_4 = 54, MASTERCARD_START_5 = 55;
const int VISA_START_1 = 4;

int main(void)
{
    // prompt the user for card number input
    long card_number_input = get_long("Number: ");

    // use custom function to get result of card number input
    string card_number_result = validate_card_type(card_number_input);

    // print the result of the card number check
    printf("%s\n", card_number_result);

    // return 0 for successful program completion
    return 0;
}

// custom function to check if card number is valid and classify it
// takes a long card_number as input
string validate_card_type(long card_number_to_check)
{
    // if the card number is negative then it is invalid even though a long can take negative input
    if (card_number_to_check < 0)
    {
        return "INVALID";
    }

    // get the length of the card number
    int card_number_len = number_length(card_number_to_check);

    // based on number of digits initial validity check can be carried out
    // check if card_number_len doesn't match known card lengths, if it doesn't then it is invalid
    if ((card_number_len != AMEX_LEN) && (card_number_len != MASTERCARD_LEN) &&
        (card_number_len != VISA_LEN_0) && (card_number_len != VISA_LEN_1))
    {
        return "INVALID";
    }

    // if length of card number is valid then run checksum on number
    // initialise sum variables for checking digits of number
    // digits in odd positions i.e. 1st, 3rd, 5th etc are summed
    // digits in even positions i.e. 2nd, 4th, 6th etc are doubled and then their digits summed
    int check_sum = 0; // initialise to 0

    // declare a variable to store the extracted digit for processing
    int extracted_digit;

    // iterate over digits in the number, extract each digit and process it based on its position
    for (int i = 1; i < (card_number_len + 1); i++)
    {
        // extract target digit
        extracted_digit = extract_digit(card_number_to_check, i);

        // check even- or odd-ness of i
        if (i % 2 == 1) // odd case, simply add value
        {
            check_sum += extracted_digit;
        }
        else // even case, double then add value of digits to checksum
        {
            // double the extracted digit
            extracted_digit *= 2;

            // calculate number of digits and extract them again
            int num_extracted_digits = number_length((long) extracted_digit);

            // for each digit in the extracted digit add to even sum
            for (int j = 1; j < (num_extracted_digits + 1); j++)
            {
                check_sum += extract_digit((long) extracted_digit, j);
            }
        }
    }

    // check if the result of the checksum is valid using modulo 10
    if (check_sum % 10 != 0)
    {
        return "INVALID";
    }

    // if all validity checks are passed then determine card type
    // extract the leading digit first to check visa
    int leading_digits = extract_digit(card_number_to_check, card_number_len);

    // perform visa check
    // successful check has right leading digit and card length
    if (leading_digits == VISA_START_1)
    {
        if ((card_number_len == VISA_LEN_0) || (card_number_len == VISA_LEN_1))
        {
            return "VISA";
        }
        else
        {
            return "INVALID";
        }
    }

    // otherwise extract second digit to check other card types
    // multiply first digit by 10 to form 2 digit number
    leading_digits = leading_digits * 10 + extract_digit(card_number_to_check, card_number_len - 1);

    // check values and return card type, return invalid if no matches
    // successful check has right leading digit and card length
    switch (leading_digits)
    {
        // check both AMEX cases and fall through until return statement
        case AMEX_START_1:
        case AMEX_START_2:
            if (card_number_len == AMEX_LEN)
            {
                return "AMEX";
            }
            else
            {
                return "INVALID";
            }
        case MASTERCARD_START_1:
        case MASTERCARD_START_2:
        case MASTERCARD_START_3:
        case MASTERCARD_START_4:
        case MASTERCARD_START_5:
            if (card_number_len == MASTERCARD_LEN)
            {
                return "MASTERCARD";
            }
            else
            {
                return "INVALID";
            }
        default:
            return "INVALID";
    }
}

// custom function to extract a target digit from a base number
int extract_digit(long initial_number, int digit_to_extract)
{
    // to get a specific digit, shift by 10 until mod 10 returns given digit
    // for digit 1 - no shifting required, digit 2 - 1 shift required etc
    for (int i = 0; i < (digit_to_extract - 1); i++)
    {
        initial_number /= 10;
    }

    return initial_number % 10;
}

// custom function to get the length of an integer
int number_length(long number_to_check)
{
    // the number 0 has 1 digit
    if (number_to_check == 0)
    {
        return 1;
    }

    int total_length = 0;

    // get the length of the number by dividing by 10 successively
    // until the number is no longer greater than 0 (1/10 will give 0 due to long type)
    while (number_to_check > 0)
    {
        // increment length counter
        total_length++;

        // divide number to check by 10
        number_to_check /= 10;
    }

    return total_length;
}
