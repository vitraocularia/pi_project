#include "menuHandler.h"

const int activitiesCount = 7;
const char * activities[] = {"change samplerate", "decrease volume", "increase volume", "cut a part", "reverse", "save", "quit"};

/* In this function we show the user all possible activities and instruct them how to choose one.*/

void printMainMenu()
{
    char * underline = " ----------------------------------------\n";
    
    printf("\nEnter correct number to choose activity or display more info:\n");
    printf("%s", underline);
    printf("|          ACTIVITY|       RUN|      INFO|\n");
    printf("%s", underline);

    for (int i = 0; i < activitiesCount; i++)
    {
        printf("|%18s|%10d|%10d|\n", activities[i], i + 1, (i + 1) * 10);
        printf("%s", underline);
    }
}

/* This function asks the user for their choice until they choose a correct number.*/

int getActivity()
{
    int activityNumber;
    
    while(scanf("%d", &activityNumber) != 1 || (checkActivityNumber(activityNumber) != 1))
    {
        printf("Enter a correct number from the menu:\n");
        fflush(stdin);
    }

    return activityNumber;
}

int checkActivityNumber(int num)
{
    if ((num > 0 && num < activitiesCount + 1) || (num/10 > 0 && num/10 < (activitiesCount + 1) && num%10 == 0)) return 1;

    return -1;
}