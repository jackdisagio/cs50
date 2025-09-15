#define max 9// Max number of candidates
#include <cs50.h>
#include <stdio.h>
#include <string.h>

typedef struct
{
    string name;
    int vote;
}cand;

bool check(int candidate_count);
void vote(int candidate_count, int number_vote, string argv[], cand candidates[]);
void winner(int candidate_count, cand candidates[]);

int main(int argc, string argv[])
{
    cand candidates[max];
    int candidate_count = argc - 1;
    if(check(candidate_count))
    {
        return 1;
    }
    int number_vote = get_int("number of vote: ");
    vote(candidate_count, number_vote, argv, candidates);
    winner(candidate_count, candidates);
}

void winner(int candidate_count, cand candidates[])
{
    int upper = 0;
    int w = 0;
    string winner[max];
    for(int i = 0; i < candidate_count; i++)
    {
        if(candidates[i].vote > upper)
        {
            upper = candidates[i].vote;
        }
    }
    for(int i = 0; i < candidate_count; i++)
    {
        if(candidates[i].vote == upper)
        {
            winner[w] = candidates[i].name;
            w++;
        }
    }
    if(w > 1)
    {
        printf("the winners are: ");
        for(int i = 0; i < w; i++)
        {
            printf("%s", winner[i]);
            if(i < w - 2)
            {
                printf(", ");
            }
            else if(i == w - 2)
            {
                printf(" and ");
            }
        }
        printf(" with %i vote\n", upper);
    }
    else
    {
        printf("the winner is: %s with %i vote\n", winner[0], upper);
    }
}

void vote(int candidate_count, int number_vote, string argv[], cand candidates[])
{
    for(int i = 0; i < candidate_count; i++)
    {
        candidates[i].name = (argv[i + 1]);
        candidates[i].vote = 0;
    }
    for(int i = 0; i < number_vote; i++)
    {
        int invalid_vote = 0;
        string name = get_string("vote: ");
        for(int j = 0; j < candidate_count; j++)
        {
            if (strcmp(candidates[j].name, name) == 0)
            {
                (candidates[j].vote)++;
            }
            else if (strcmp(candidates[j].name, name) != 0)
            {
                invalid_vote++;
            }
        }
        if (invalid_vote == candidate_count)
        {
            printf("invalide vote\n");
            i--;
        }
    }
}

bool check(int candidate_count)
{
    if(candidate_count > max)
    {
        printf("Maximum number of candidates is %i\n", max);
        return 1;
    }
    else if(candidate_count == 0)
    {
        printf("Usage: plurality [candidate ...]\n");
        return 1;
    }
    return 0;
}
