#include <stdio.h>
#include <string.h>

#define TOTAL_QUESTIONS 10
#define MAX_RAW_SCORE 110

/* Function prototype */
void menu(void);
void startTest(void);
int askQuestion(char text[], int weight);
int calculateScore(int answers[], int pointValues[]);
void showResult(char name[], int rawScore, int answers[], int pointValues[]);
void showMeter(int score);
void showHighestRedFlag(int answers[], int pointValues[]);
void saveResult(char name[], int score, char result[]);
void viewHistory(void);
void about(void);
void clearInputBuffer(void);
int getYesNo(void);

/* Question database */
char question[TOTAL_QUESTIONS][200] =
{
    "Do they reply after more than 3 days?",
    "Do they still talk to their ex?",
    "Do they suddenly become protective of their phone when you ask to use it?",
    "Do they only call you after 11 PM?",
    "Do they leave you on seen regularly?",
    "Do they cancel plans at the last minute?",
    "Do they avoid introducing you to their friends?",
    "Do they make you feel guilty for having boundaries?",
    "Do they flirt with other people and call it 'just being friendly'?",
    "Do they disappear whenever you need them?"
};

/* Point values for each question */
int points[TOTAL_QUESTIONS] =
{
    10,
    15,
    10,
    15,
    10,
    10,
    10,
    5,
    15,
    10
};

/* Main Function */
int main(void)
{
    int choice;

    printf("\n");
    printf("===========================================\n");
    printf("             ELSE, MOVE ON\n");
    printf("            RED FLAG DETECTOR\n");
    printf("===========================================\n");

    while (1)
    {
        menu();

        printf("Enter your choice: ");

        if (scanf("%d", &choice) != 1)
        {
            printf("\nInvalid input. Please enter a number.\n");
            clearInputBuffer();
            continue;
        }

        clearInputBuffer();

        switch (choice)
        {
            case 1:
            startTest();
            break;

            case 2:
            viewHistory();
            break;

            case 3:
            about();
            break;

            case 4:
            printf("\nThank you for using ELSE, MOVE ON!\n");
            printf("Stay safe and trust your instincts.\n\n");
            return 0;

            default:
                printf("\nInvalid choice. Please select 1-4.\n");
            }
      }
}

/* Display the main menu */
void menu(void)
{
    printf("\n");
    printf("-----------------------------------------------\n");
    printf("1. Start test\n");
    printf("2. View Previous Results\n");
    printf("3. About\n");
    printf("4. Exit\n");
    printf("-----------------------------------------------\n");
}

/* Start the Red Flag Test */
void startTest(void)
{
    char name[50];
    int answers[TOTAL_QUESTIONS];
    int score;

    printf("\n");
    printf("=================================================\n");
    printf("             START RED FLAG TEST\n");
    printf("=================================================\n");

    printf("\nEnter your name: ");

    fgets(name, sizeof(name), stdin);

    name[strcspn(name, "\n")] = '\0';

    if (strlen(name) == 0)
    {
        strcpy(name, "Anonymous");
    }

    printf("\nHello, %s!\n", name);
    printf("Answer every question with Y or N.\n");
    printf("Be honest. We are judging them, not you.\n");

    for (int i = 0; i < TOTAL_QUESTIONS; i++)
    {
        answers[i] = askQuestion(question[i], points[i]);
    }

    score = calculateScore(answers, points);

    showResult(name, score, answers, points);
}


/* Ask one question */
int askQuestion(char text[], int weight)
{
    int answer;

    printf("\n%s\n", text);
    printf("Red Flag Weight: %d points\n", weight);

    answer = getYesNo();

    return answer;
}

/* Get a Valid Answer */
int getYesNo(void)
{
    char answer;

    while (1)
    {
        printf("Your answer [Y/N]: ");

        scanf(" %c", &answer);
        clearInputBuffer();

        if (answer == 'Y' || answer == 'y')
        {
            return 1;
        }

        if (answer == 'N' || answer == 'n')
        {
            return 0;
        }

        printf("Invalid answer. Please enter Y or N.\n");
    }
}

/* Calculate the total red flag score */
int calculateScore(int answers[], int pointValues[])
{
    int score = 0;

    for (int i = 0; i < TOTAL_QUESTIONS; i++)
    {
        if (answers[i] == 1)
        {
            score = score + pointValues[i];
        }
    }

    return score;
}


/* Display the final result */
void showResult(char name[], int rawScore, int answers[], int pointValues[])
{
     char result[50];
     int score;


     /*
      * Convert the raw score out of 110
      * into a percentage out of 100.
      */
     score = (rawScore * 100) / MAX_RAW_SCORE;

     printf("\n");
     printf("===========================================\n");
     printf("                 RESULTS\n");
     printf("===========================================\n");

     printf("\n%s's Red Flag Score:\n", name);
     printf("\n              %d / 100\n", score);

     showMeter(score);

     /* Determine result category */

     if (score <= 20)
     {
        strcpy(result, "GREEN FLAG");

        printf("\nGREEN FLAG\n");
        printf("Probably safe.\n");
        printf("No major warning signs detected.\n");
     }
     else if (score <= 50)
     {

         strcpy(result, "PROCEED CAREFULLY");

         printf("\nPROCEED CAREFULLY\n");
         printf("There are some warning signs here.\n");
         printf("Keep your eyes open.\n");
     }
     else if (score <= 75)
     {
         strcpy(result, "WARNING");

         printf("\nWARNING\n");
         printf("This relationship comes with warning labels.\n");
         printf("Emergency exit recommended.\n");
     }
     else
     {
         strcpy(result, "RUN");

         printf("\nRUN\n");
         printf("There are WAY too many red flags.\n");
         printf("Emergency exit recommended.\n");
     }

     showHighestRedFlag(answers, pointValues);


     /*
      * Creative Feature:
      * Ask whether the user would ignore the red flags.
      */
     printf("\nWould you ignore these red flags anyway? [Y/N]\n");

     if (getYesNo() == 1)
     {
        printf("\nAnalysis complete:\n");
        printf("The problem is not them anymore.\n");
     }
     else
     {
        printf("\nGood decision.\n");
        printf("Your future self thanks you.\n");
     }

     /* Save result to file */
     saveResult(name, score, result);

     printf("\nYour result has been saved to results.txt.\n");
}

/* Display a visual score meter */
void showMeter(int score)
{
    int bars;

    bars = score / 5;

    printf("\nRed Flag Meter:\n");
    printf("[");

    for (int i = 0; i < 20; i++)
    {
        if(i < bars)
        {
            printf("#");
        }
        else
        {
            printf("-");
        }
    }

    printf("] %d%%\n", score);
}


/* Find the highest-weighted red flag */
void showHighestRedFlag(int answers[], int pointValues[])
{
    int highestPoints = 0;
    int highestIndex = -1;

    for (int i = 0; i < TOTAL_QUESTIONS; i++)
    {
        if (answers[i] == 1 && pointValues[i] > highestPoints)
        {
            highestPoints = pointValues[i];
            highestIndex = i;
        }
    }

    if (highestIndex != -1)
    {
        printf("\n");
        printf("------------------------------------------------\n");
        printf("             BIGGEST WARNING SIGN\n");
        printf("------------------------------------------------\n");

        printf("\nQuestion number: %d\n", highestIndex + 1);
        printf("Red Flag Weight: %d points\n", highestPoints);
        printf("This was one of the most serious warning signs.\n");
    }
    else
    {
        printf("\nNo major red flags detected!\n");
    }
}


/* Save the result to a text file */
void saveResult(char name[], int score, char result[])
{
     FILE *file;

     file = fopen("results.txt", "a");

     if (file == NULL)
     {
        printf("Error: Could not open results.txt.\n");
        return;
     }

     fprintf(file, "Name: %s | Score: %d/100 | Result: %s\n", name, score, result);

     fclose(file);
}


/* Display previous results */
void viewHistory(void)
{
    FILE *file;
    char line[300];

    file = fopen("results.txt", "r");

    if (file == NULL)
    {
        printf("\nNo previous results found.\n");
        printf("Take the test first!\n");
        return;
    }

    printf("\n");
    printf("=============================================\n");
    printf("            PREVIOUS RESULTS\n");
    printf("=============================================\n\n");

    while (fgets(line, sizeof(line), file) != NULL)
    {
        printf("%s", line);
    }

    fclose(file);
}


/* Display information about the project */
void about(void)
{
    printf("\n");
    printf("===============================================\n");
    printf("                ABOUT\n");
    printf("===============================================\n");

    printf("\n");
    printf("            ELSE, MOVE ON\n");
    printf("        A Relationship Red Flag Detector\n\n");

    printf("This is a console based C program that\n");
    printf("evaluates relationship warning signals.\n\n");

    printf("The user answers 10 Yes/No questions.\n");
    printf("Each question has a different point value.\n");
    printf("converts it to a percentage, and displays\n");
    printf("a final result.\n\n");

    printf("Programming concepts used:\n");
    printf("- Constants\n");
    printf("- Variables and data types\n");
    printf("- Operators and expressions\n");
    printf("- Input and output\n");
    printf("- Arrays\n");
    printf("- Strings\n");
    printf("- Functions\n");
    printf("- Conditional statements\n");
    printf("- Iterations\n");
    printf("- File input/output\n\n");

    printf("Because love is blind but C isnt.\n");
}


/* Clear unwanted input fromthe input buffer */
void clearInputBuffer(void)
{
    int c;

    while ((c = getchar()) != '\n' && c != EOF)
    {
        /* Remove unwanted characters */
    }
}

