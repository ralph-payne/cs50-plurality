#include "cs50.h"
#include "cs50.c"
#include <stdio.h>
#include <string.h>

/* 
The define directive allows the definition of macros within your source code. These macro definitions allow constant values to be declared for use throughout your code.
Macro definitions are not variables and cannot be changed by your program code like variables. You generally use this syntax when creating constants that represent numbers, strings or expressions
Most C programmers define their constnat names in upper case, but it is not a requirement of the C Language
Note: Do NOT put a semicolon at the end of #define statements. This is a common mistake.
*/
// MAX is a constant that represents the maximum number of candidates an election can have
#define MAX 9

// Define a struct called candidate. Each candidate has two fields: a string called name representing the candidates's name, and an int called votes representing the number of votes the candidate has
// Candidates have name and vote count
typedef struct
{
    string name;
    int votes;
}
candidate;

// Declare global array of candidates, where each element is itself a candidate
candidate candidates[MAX];

// Declare global variable which counts the number of candidates
int candidate_count;

// Function prototypes
// The function vote takes as its input a name (string) and returns a boolean
bool vote(string name);
// The function print winner does not have any inputs and does not return anything. It will simply print the name of the winner
void print_winner(void);

int main(int argc, string argv[])
{
    // Check for invalid usage. If the argument count is less than 2, prompt the user to provide a candidate
    if (argc < 2)
    {
        printf("Usage: plurality [candidate ...]\n");
        // Return 1 to indicate failure
        return 1;
    }

    // Populate array of candidates. The array is equal to the argument count minus 1. We minus 1 because argv[0] holds the name of the program itself.
    candidate_count = argc - 1;
    // Perform check to see if candidate count is greater than the maximum (referring to the constant value of 9 you set at the top of the program)
    if (candidate_count > MAX)
    {
        printf("Maximum number of candidates is %i\n", MAX);
        // Return 2 to indicate failure
        return 2;
    }
    for (int i = 0; i < candidate_count; i++)
    {
        candidates[i].name = argv[i + 1];
        candidates[i].votes = 0;
    }

    int voter_count = get_int("Number of voters: ");

    // Loop over all voters
    for (int i = 0; i < voter_count; i++)
    {
        string name = get_string("Vote: ");

        // Check for invalid vote (i.e. if the vote function returns a value of false, you should print that the vote is invalid)
        if (!vote(name))
        {
            printf("Invalid vote.\n");
        }
    }

    // After you have looped through all the voters, you can then display the winner of election
    print_winner();
}

// Update vote totals given a new vote
/*
Iteration 1
Complete the vote function
(1) vote takes a single argument (a string called name)
(2) (ai) If name is equal to one of the names of the candidates in the election, then add one to that candidate's vote total. (aii) The vote function should then return true to indidicate a sucessful ballot (b) If name does not match the name of any of the candidates in the election, no vote totals shoudl change and the vote function should return false to indicate an invalid ballot
*/


bool vote(string name)
{
    // Perform lookup on input name

    // Loop through the array of names given in argv. The length is equal to the global constant candidate_count
    for (int i = 0; i < candidate_count; i++)
    {
        // Use strcmp (string comparison)
        if (strcmp(candidates[i].name, name) == 0)
        {
            // Increase counter
            candidates[i].votes++;
            // printf("%s count has been increased by %i\n", candidates[i].name, candidates[i].votes);
            // Return true if equal to one of the names
            return true;
        }
    }
     
    // If the candidate cannot be found, you should return false
    return false;
}

/*
Iteration 2
(3) The function should print out the name of the candidate who received the most votes in the election, and then print a newline
(4) It is possible that the election could end in a tie if multiple candidates each have the maximum number of votes. In that case, you shoudl output the names of each of the winning candidates, each on a separate line
*/

// Print the winner (or winners) of the election
void print_winner(void)
{
    // Declare a variable (an integer) that stores the number of votes that the winning candidate received
    int winning_number = 0;

    // Loop 1: Loop through each of the candidates. If the number of votes for the i'th candidate is greater then the winning_number, then the winning number should be updated with the number of votes for the i'th candidate
    for (int i = 0; i < candidate_count; i++)
    {
        if (candidates[i].votes > winning_number)
        {
            winning_number = candidates[i].votes;
        }
        // Note to self: I am assuming here that I don't need an else as if the number of votes is not bigger than the winning number, then the loop will move onto the next candidate
    }

    // Loop 2: Loop throught the candidates again. If the number of votes is equal to the winning number, then print out the i'th candidate's name
    for (int j = 0; j < candidate_count; j++)
    {
        if (candidates[j].votes == winning_number)
        {
            printf("%s\n", candidates[j].name);
        }
    }

    // This function does not return anything
    // Question: Is this return statement essential? Do I still need to included it even if the function doesn't return anything?
    return;
}