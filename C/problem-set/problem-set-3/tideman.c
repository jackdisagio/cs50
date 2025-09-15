#define max 9
#include <cs50.h>
#include <stdio.h>
#include <string.h>

typedef struct
{
    string name1;
    string name2;
    int vote_name1;
    int vote_name2;
}cad;

typedef struct
{
    string winner_name;
    string loser_name;
    int difference;
}w;

typedef struct
{
    string winner_name;
    string loser_name;
}lock;

bool check(int candidate_count);
int candidate_arrow(int candidate_count);
void write_names(string all_name[], int candidate_count, string argv[]);
void couples(cad candidate_coupple[], string all_name[], int candidate_count);
void ballot(int number_ballot, int candidate_count, string all_name[], cad candidate_coupple[], int arrow);
int winners_count(int arrow, cad candidate_coupple[]);
bool winning_strength(w strength[], int arrow, cad candidate_coupple[]);
void sorting(int Wcount, w strength[]);
bool check_cycle(int Wcount, int candidate_count, string all_name[], w strength[]);
void lock_couples(int count, w strength[], lock coupple[]);
bool check_cycle2(int candidate_count, string all_name[], int count, lock coupple[], string *winner);

int main(int argc, string argv[])
{
    int candidate_count = argc - 1;
    if (check(candidate_count))
    {
        return 1;
    }
    int number_ballot = get_int("number of ballot: ");
    int arrow = (candidate_count * candidate_count) - candidate_arrow(candidate_count);
    string all_name[candidate_count];
    write_names(all_name, candidate_count, argv);
    cad candidate_coupple[arrow];
    couples(candidate_coupple, all_name, candidate_count);
    ballot(number_ballot, candidate_count, all_name, candidate_coupple, arrow);
    int Wcount = winners_count(arrow, candidate_coupple);
    if(Wcount == 0)
    {
        printf("the candidates all have the same votes\n");
        return 1;
    }
    printf("archi tra coppie: %i\n", Wcount);
    w strength[Wcount];
    if(winning_strength(strength, arrow, candidate_coupple))
    {
        return 0;
    }
    sorting(Wcount, strength);
    lock coupple[Wcount];
    string winner = NULL;
    if(check_cycle(Wcount, candidate_count, all_name, strength))
    {
        printf("\narchi locckati:\n");
        int count = 0;
        while(true)
        {
            lock_couples(count, strength, coupple); //done
            if(check_cycle2(candidate_count, all_name, count, coupple, &winner))
            {
                printf("The winner is: %s\n", winner);
                return 0;
            }
            count++;
            if(count == Wcount + 1)
            {
                printf("\nloop infinito individuato \n");
                return 0;
            }
        }
    }
}

bool check_cycle2(int candidate_count, string all_name[], int count, lock coupple[], string *winner)
{
    int no_loser_count = 0;
    bool resultate;
    string W_name = NULL;
    for (int i = 0; i < candidate_count; i++)
    {
        int L_name = 0;
        for(int j = 0; j < count; j++)
        {
            if(strcmp(all_name[i], coupple[j].loser_name) == 0)
            {
                L_name++;
            }
        }
        if(L_name == 0)
        {
            no_loser_count++;
            W_name = all_name[i];
        }
    }
    if(no_loser_count == 0)
    {
        resultate = true;
    }
    else if(no_loser_count > 1)
    {
        resultate = false;
        printf("w: %s | l: %s\n", coupple[count].winner_name, coupple[count].loser_name); //da eliminare
    }
    else //solo se è 1
    {
        (*winner) = W_name;
        resultate = false;
        printf("w: %s | l: %s\n", coupple[count].winner_name, coupple[count].loser_name); //da eliminare
    }
    return resultate;
}

void lock_couples(int count, w strength[], lock coupple[])
{
    coupple[count].winner_name = strength[count].winner_name;
    coupple[count].loser_name = strength[count].loser_name;
}

bool check_cycle(int Wcount, int candidate_count, string all_name[], w strength[])
{
    bool resultate = false;
    int no_loser_count = 0;
    string winner = NULL;
    for(int i = 0; i < candidate_count; i++)
    {
        int L_name = 0;
        for(int j = 0; j < Wcount; j++)
        {
            if(strcmp(all_name[i], strength[j].loser_name) == 0)
            {
                L_name++;
            }
        }
        if(L_name == 0)
        {
            no_loser_count++;
            winner = all_name[i];
        }
    }
    if(no_loser_count > 1)
    {
        resultate = true;
    }
    else if (no_loser_count == 0)
    {
        resultate = true;
    }
    else
    {
        resultate = false;
        printf("the winner is: %s\n", winner);
    }
    return resultate;
}

void sorting(int Wcount, w strength[])
{
    for(int i = 0; i < Wcount; i++)
    {
        for(int j = 0; j < (Wcount - 1); j++)
        {
            if(strength[j + 1].difference > strength[j].difference)
            {
                int temp = strength[j].difference;
                strength[j].difference = strength[j + 1].difference;
                strength[j + 1].difference = temp;
            }
        }
    }//da eliminare V
    printf("\nordinato:\n");
    for(int i = 0; i < Wcount; i++)
    {
        printf("w: %s | l: %s | difference: %i\n", strength[i].winner_name, strength[i].loser_name, strength[i].difference);
    }
}

bool winning_strength(w strength[], int arrow, cad candidate_coupple[])
{
    bool booleane = false;
    int winner_count = 0;
    for(int i = 0; i < arrow; i++)
    {
        if(candidate_coupple[i].vote_name1 > candidate_coupple[i].vote_name2)
        {
            strength[winner_count].winner_name = candidate_coupple[i].name1;
            strength[winner_count].loser_name = candidate_coupple[i].name2;
            strength[winner_count].difference = candidate_coupple[i].vote_name1 - candidate_coupple[i].vote_name2;

            //da eliminare v
            printf("w: %s | l: %s  |  difference: %i\n", strength[winner_count].winner_name, strength[winner_count].loser_name, strength[winner_count].difference);

            winner_count++;
        }
        else if(candidate_coupple[i].vote_name1 < candidate_coupple[i].vote_name2)
        {
            strength[winner_count].winner_name = candidate_coupple[i].name2;
            strength[winner_count].loser_name = candidate_coupple[i].name1;
            strength[winner_count].difference = candidate_coupple[i].vote_name2 - candidate_coupple[i].vote_name1;

            //da eliminare v
            printf("w: %s | l: %s  |  difference: %i\n", strength[winner_count].winner_name, strength[winner_count].loser_name, strength[winner_count].difference);

            winner_count++;
        }
    }
    if(winner_count == 1)
    {
        printf("the winner is: %s\n", strength[winner_count - 1].winner_name);
        booleane = true;
    }
    return booleane;
}

int winners_count(int arrow, cad candidate_coupple[])
{
    int winner_count = 0;
    for(int i = 0; i < arrow; i++)
    {
        if(candidate_coupple[i].vote_name1 > candidate_coupple[i].vote_name2)
        {
            winner_count++;
        }
        else if(candidate_coupple[i].vote_name1 < candidate_coupple[i].vote_name2)
        {
            winner_count++;
        }
    }
    return winner_count;
}

void ballot(int number_ballot, int candidate_count, string all_name[], cad candidate_coupple[], int arrow)
{
    string name[candidate_count];
    for(int i = 0; i < number_ballot; i++)
    {
        for(int j = 0; j < candidate_count; j++)
        {
            int invalid_vote = 0;
            name[j] = get_string("rank %i: ", j + 1);
            for(int l = 0; l < candidate_count; l++)
            {
                if(strcmp(name[j], all_name[l]) != 0)
                {
                    invalid_vote++;
                }
            }
            if(invalid_vote == candidate_count)
            {
                printf("invalide vote\n");
                j--;
            }
            for(int l = 0; l < j; l++)
            {
               if(strcmp(name[j], name[l]) == 0)
               {
                    printf("this name has already been chosen\n");
                    j--;
               }
            }
        }
        for(int j = 0; j < arrow; j++)
        {
            int position_name1 = 0;
            int position_name2 = 0;
            for(int l = 0; l < candidate_count; l++)
            {
                if(strcmp(candidate_coupple[j].name1, name[l]) == 0)
                {
                    position_name1 = l;
                }

            }
            for(int l = 0; l < candidate_count; l++)
            {
                if(strcmp(candidate_coupple[j].name2, name[l]) == 0)
                {
                    position_name2 = l;
                }
            }
            if(position_name1 < position_name2)
            {
                (candidate_coupple[j].vote_name1)++;
            }
            else if(position_name1 > position_name2)
            {
                (candidate_coupple[j].vote_name2)++;
            }
        }
        printf("\n");
    }
}

void couples(cad candidate_coupple[], string all_name[], int candidate_count)
{
    int n = 0;
    for(int i = 0; i < candidate_count - 1; i++)
    {
        for(int j = 0; j < (candidate_count - i) - 1; j++)
        {
            candidate_coupple[n].name1 = all_name[i];
            candidate_coupple[n].name2 = all_name[j + i + 1];
            candidate_coupple[n].vote_name1 = 0;
            candidate_coupple[n].vote_name2 = 0;
            n++;
        }
    }
}

void write_names(string all_name[], int candidate_count, string argv[])
{
    for(int i = 0; i < candidate_count; i++)
    {
        all_name[i] = argv[i + 1];
    }
}

int candidate_arrow(int candidate_count)
{
    if(candidate_count == 1)
    {
        return 1;
    }
    return candidate_count + candidate_arrow(candidate_count - 1);
}

bool check(int candidate_count)
{
    if(candidate_count > max)
    {
        printf("Maximum number of candidates is %i\n", max);
        return true;
    }
    if(candidate_count == 0)
    {
        printf("Usage: plurality [candidate ...]\n");
        return true;
    }
    return false;
}
