//Greyson Will
//Date: 05/01/2026
//Project 10



#include <stdio.h>
#include <stdbool.h>

#define WORD_SIZE 5
#define MAX_TRIES 6

int getLength(char text[]);
int isAlpha(char ch);
char makeLower(char ch);
char makeUpper(char ch);
void lowerWord(char text[]);
int getSecretWord(char secret[]);
void askGuess(char guess[], int guessNum);
int goodGuess(char guess[]);
int wordsSame(char one[], char two[]);
int letterInSecret(char secret[], char ch);
int letterAlreadyCorrect(char guess[], char secret[], char ch);
void copyGuess(char list[][WORD_SIZE + 1], int row, char guess[]);
void showGuesses(char list[][WORD_SIZE + 1], int used, char secret[]);

int main(void)
{
    char secret[WORD_SIZE + 1];
    char guess[50];
    char guesses[MAX_TRIES][WORD_SIZE + 1];

    int guessNum = 0;
    int won = 0;

    if (getSecretWord(secret) == 0)
    {
        printf("Could not read word.txt\n");
        return 1;
    }

    lowerWord(secret);

    while (guessNum < MAX_TRIES && won == 0)
    {
        askGuess(guess, guessNum + 1);
        lowerWord(guess);

        while (goodGuess(guess) == 0)
        {
            printf("Your guess must be 5 letters long.\n");
            printf("Please try again: ");
            scanf("%49s", guess);
            lowerWord(guess);
        }

        copyGuess(guesses, guessNum, guess);
        guessNum++;

        printf("=====================================\n");
        showGuesses(guesses, guessNum, secret);

        if (wordsSame(guess, secret) == 1)
        {
            won = 1;
        }
    }

    if (won == 1)
    {
        printf("You guessed the word!\n");
    }
    else
    {
        printf("You ran out of guesses. The word was %s.\n", secret);
    }

    return 0;
}

int getLength(char text[])
{
    int i = 0;

    while (text[i] != '\0' && text[i] != '\n')
    {
        i++;
    }

    return i;
}

int isAlpha(char ch)
{
    if ((ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z'))
    {
        return 1;
    }

    return 0;
}

char makeLower(char ch)
{
    if (ch >= 'A' && ch <= 'Z')
    {
        ch = ch + 32;
    }

    return ch;
}

char makeUpper(char ch)
{
    if (ch >= 'a' && ch <= 'z')
    {
        ch = ch - 32;
    }

    return ch;
}

void lowerWord(char text[])
{
    int i = 0;

    while (text[i] != '\0' && text[i] != '\n')
    {
        text[i] = makeLower(text[i]);
        i++;
    }

    text[i] = '\0';
}

int getSecretWord(char secret[])
{
    FILE *fp = fopen("word.txt", "r");

    if (fp == NULL)
    {
        return 0;
    }

    fscanf(fp, "%5s", secret);
    secret[WORD_SIZE] = '\0';

    fclose(fp);

    return 1;
}

void askGuess(char guess[], int guessNum)
{
    printf("GUESS %d! Enter your guess: ", guessNum);
    scanf("%49s", guess);
}

int goodGuess(char guess[])
{
    int i;

    if (getLength(guess) != WORD_SIZE)
    {
        return 0;
    }

    for (i = 0; i < WORD_SIZE; i++)
    {
        if (isAlpha(guess[i]) == 0)
        {
            return 0;
        }
    }

    return 1;
}

int wordsSame(char one[], char two[])
{
    int i;

    for (i = 0; i < WORD_SIZE; i++)
    {
        if (one[i] != two[i])
        {
            return 0;
        }
    }

    return 1;
}

int letterInSecret(char secret[], char ch)
{
    int i;

    for (i = 0; i < WORD_SIZE; i++)
    {
        if (secret[i] == ch)
        {
            return 1;
        }
    }

    return 0;
}

int letterAlreadyCorrect(char guess[], char secret[], char ch)
{
    int i;

    for (i = 0; i < WORD_SIZE; i++)
    {
        if (guess[i] == ch && guess[i] == secret[i])
        {
            return 1;
        }
    }

    return 0;
}

void copyGuess(char list[][WORD_SIZE + 1], int row, char guess[])
{
    int i;

    for (i = 0; i < WORD_SIZE; i++)
    {
        list[row][i] = guess[i];
    }

    list[row][WORD_SIZE] = '\0';
}

void showGuesses(char list[][WORD_SIZE + 1], int used, char secret[])
{
    int row;
    int col;

    for (row = 0; row < used; row++)
    {
        for (col = 0; col < WORD_SIZE; col++)
        {
            if (list[row][col] == secret[col])
            {
                printf("%c", makeUpper(list[row][col]));
            }
            else
            {
                printf("%c", list[row][col]);
            }
        }

        printf("\n");

        for (col = 0; col < WORD_SIZE; col++)
        {
            if (list[row][col] != secret[col] &&
                letterInSecret(secret, list[row][col]) == 1 &&
                letterAlreadyCorrect(list[row], secret, list[row][col]) == 0)
            {
                printf("^");
            }
            else
            {
                printf(" ");
            }
        }

        printf("\n\n");
    }
}
