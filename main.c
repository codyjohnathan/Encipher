#include <cs50.h>
#include <string.h>
#include <stdio.h>
#include <ctype.h>

void organise_alphabet(char uppercase[], char lowercase[]);
void print_encipher(char ciphertext[], int pt_len);

int main(int argc, char *argv[])
{

    //Validate Key
    // Error handling for command line arguments
    if (argc != 2)
    {
        printf("Usage: ./substitution key\n");
        return 1;
    }

    int ciph_len = strlen(argv[1]);

    int alpha_count = 26;

    //Get key
    char *cipher = argv[1];

    // check key length
    if (ciph_len != alpha_count)
    {
        printf("Key must contain 26 characters.\n");
        return 1; // - exit code 1
    }


    // check for non alphabetic characters
    for (int i = 0; i < ciph_len; i++)
    {
        if (isalpha(cipher[i]) == 0)
        {
            printf("Usage: ./substitution key\n");
            printf("'%c' NOT ALPHA\n", cipher[i]);
            return 1;
        }

    }

    //check for repeated characters (case insensitive)
    int char_count[alpha_count]; // creating an array to hold every character in the alphabet (26)

    for (int i = 0; i < alpha_count; i++)
    {
        char_count[i] = 0; // initialisating each element to 0
    }

    for (int i = 0; i < ciph_len ; i++)//nested for loop to compare every letter [i] with an ascending list [j] one at a time
    {
        for (int j = 0; j < ciph_len; j++)
        {
            if (cipher[i] == cipher[j]) // the value will always match once since there'll always meet each other once when going over the list
            {
                char_count[i]++; // So we keep track of that by adding 1 to our array[] of ints - does this even never to be an array,
            }
        }
    }


    for (int i = 0; i < alpha_count; i++)
    {
        if (char_count[i] > 1) // we know every value we meet each other once, so we keep track of that by adding 1
        {
            printf("Usage: ./substitution key\n"); // however if it's more than once they meet we know we've a repeated value
            printf("REPEATED CHARACTER: %c\n", cipher[i]);
            return 1;
        }
    }
    //==============================================================================================================//
    // Build an organised alphabet
    char upper[alpha_count];
    char lower[alpha_count];
    organise_alphabet(upper, lower);

    // Get plaintext input from user and it's length
    char *plaintext = get_string("plaintext: "); // I need to malloc enough space in real time, watching whatever user types in

    int pt_len = strlen(plaintext);

    // Main enciphering algorithm
    char ciphertext[pt_len];

    for (int b = 0; b < pt_len; b++)// pt_len
    {
        for (int a = 0; a < alpha_count; a++)  // alpha_count
        {
            //===================== Start operations with alphabetical characters================//

            if (isalpha(plaintext[b]))
            {
                // TRY THIS
                // Perserve case
                if (upper[a] == plaintext[b])
                {
                    // here we're storing the index of our corresponding letter to our array
                    ciphertext[b] = toupper(cipher[a]);
                }

                else if (lower[a] == plaintext[b])
                {
                    ciphertext[b] = tolower(cipher[a]);
                }


                // ==================End operations with alphabetical characters============
            }
            // Leave non alpha characters alone
            else
            {
                ciphertext[b] = plaintext[b];
            }
        }
    }

    //Print ciphertext
    print_encipher(ciphertext, pt_len);

    return 0;
}

void organise_alphabet(char uppercase[], char lowercase[])
{
    // Uppercase alphabet

    for (int a = 65, b = 0; a < 91 && b < 26; a++, b++)
    {
        uppercase[b] = (char) a;
    }

    // Lowercase alphabet

    for (int a = 97, c = 0; a < 123 && c < 26; a++, c++)
    {
        lowercase[c] = (char) a;
    }

    return;
}

void print_encipher(char ciphertext[], int pt_len)
{
    printf("ciphertext: ");
    for (int i = 0; i < pt_len; i++)
    {
        printf("%c", ciphertext[i]);
    }
    printf("\n");
}