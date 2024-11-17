#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <string.h>

// Function prototypes
void login(char *);
void heading();
void displayMenu();
void vote(int, char *, char *, char *);
void listVoters();
void liveCount(char *);
void listCandidates(char *);

/*

*************************************************
*                                               *
*                  VOTING SYSTEM                *
*                                               *
*  Developed by: Faizan Fareed (BSE-24S-030)    *
*                Nabiha Raja (BSE-24S-036)      *
*                Shoaib Malik (BSE-24S-012)     *
*                Zubia Ghulamullah (BSE-24S-042)* 
*************************************************

*/

// Main function
int main()
{
    int Socresp, year, no, ch, back = 1, log;
    char name1[80], branch[20], society[20], ID[30];

    heading();
    fflush(stdin); // Flush the standard input buffer

    printf("\n\t\t\tWelcome to the Login_System\n");
    printf("\n\t\t-------------------------------------------\n");
    printf("Enter 1 for Login\n");
    scanf("%d", &log);

    if (log == 1)
    {
        login(ID);
    }
    else
    {
        exit(0);
    }

Society:
    printf(" \n\t\t In which society you want to enroll yourself\n\n");
    printf(" \t\t 1. Science Society\n");
    printf(" \t\t 2. Art Society\n");
    printf(" \t\t 3. Sport Society\n");
    scanf(" %d", &Socresp);

    switch (Socresp)
    {
    case 1:
        strcpy(society, "Science");
        break;
    case 2:
        strcpy(society, "Art");
        break;
    case 3:
        strcpy(society, "Sport");
        break;
    default:
        printf("Invalid choice. Please enter a valid option.\n");
        goto Society;
    }

    printf("\n\n\t\t\t  ENTER NAME:");
    getchar(); // Consume the newline character left in the buffer
    fgets(name1, sizeof(name1), stdin);
    name1[strcspn(name1, "\n")] = 0;

    int len = strlen(name1);
    for (int i = 0; i < len; i++)
    {
        if (name1[i] == ' ')
        {
            for (int j = i; j < len; j++)
            {
                name1[j] = name1[j + 1];
            }
            len--;
        }
    }

    printf("\t\t\t  ENTER DOB:");
    scanf("%d", &year);
    printf("\t\t\t  ENTER DEPARTMENT:");
    scanf("%s", branch);

    system("cls");
    heading();
    printf("Rule Book:\n\n");
    printf("1. You can vote only once.\n2. Enter names as per registered in college.\n3. You can add new candidates but those must be from 4th year.\n");
    printf("4. Student from any branch can participate.\n5. Please be fair and impartial in voting.\n");
    printf("\n\n\n\n\n\n\n\nEnter 1 to continue:");
    scanf("%d", &no);

    if (no != 1)
    {
        exit(0);
    }

    system("cls");
    heading();
    printf("\n\nWELCOME :  %s\n\n", name1);

go:
    system("cls");
    displayMenu();
    printf("\n\n\nEnter Response: ");
    scanf(" %d", &ch);
    system("cls");

    switch (ch)
    {
    case 1:
        vote(Socresp, society, name1, ID);
        exit(0);
        break;
    case 2:
        listVoters();
        printf(" Enter 1 to go back:");
        scanf("%d", &back);
        if (back == 1)
        {
            goto go;
        }
        break;
    case 3:
        liveCount(society);
        printf(" Enter 1 to go back:");
        scanf("%d", &back);
        if (back == 1)
        {
            goto go;
        }
        break;
    case 4:
        listCandidates(society);
        printf(" \n\nEnter 1 to go back: ");
        scanf(" %d", &back);
        if (back == 1)
        {
            goto go;
        }
        break;
    case 5:
        exit(0);
    default:
    {
        printf("Invalid choice. Please enter a valid option.\n");
        goto Society;
    }
    }
    getch();
    return 0;
}

void heading()
{
    system("cls");
    printf("\n\t\t   SINDH MADRESSATUL ISLAM UNIVERSITY\n");
    printf("------------------------------------------------------------------------------------\n\n");
    printf("\t\t  WELCOME TO THE SMIU STUDENT ELECTION 2024\n\n");
    printf("\t\t\t   **********\n");
    printf("\n\n\n");
}

// For login
void login(char *ID)
{
    FILE *log;
    FILE *voted;
    char password[20], u[30], p[20];

    printf("Enter ID: ");
    scanf("%s", ID);
    printf("Enter password: ");
    scanf("%s", password);

    // Check if the user has already voted
    voted = fopen("voted.txt", "r");
    if (voted != NULL)
    {
        while (fscanf(voted, "%s", u) != EOF)
        {
            if (strcmp(u, ID) == 0)
            {
                printf("You have already voted.\n");
                fclose(voted);
                exit(0);
                return;
            }
        }
        fclose(voted);
    }

    // For login
    log = fopen("login.txt", "r");
    if (log == NULL)
    {
        printf("Error opening file login.txt\n");
        exit(1);
    }

    int loginSuccess = 0;
    while (fscanf(log, "%s %s", u, p) != EOF)
    {
        if ((strcmp(u,ID) == 0) && (strcmp(p, password) == 0))
        {
            loginSuccess = 1;
            break;
        }
    }

    fclose(log);

    if (loginSuccess == 1)
    {
        printf("Login successful.\n");
    }
    else
    {
        printf("Invalid ID or password.\n");
        exit(0);
    }
}

void displayMenu()
{
    printf("1. For voting\n");
    printf("2. List of voters\n");
    printf("3. Live count\n");
    printf("4. List of Candidates\n");
    printf("5. Exit\n");
}

// For voting
void vote(int Socresp, char *society, char *name1, char *ID)
{
    char candidatesFile[30], votesFile[30], cand[20];
    int n = 0, res, a[50] = {0}, m = 1;

    sprintf(candidatesFile, "%s_candidates.txt", society);
    sprintf(votesFile, "%s_votes.txt", society);

    FILE *fp1 = fopen(candidatesFile, "r");
    if (fp1 == NULL)
    {
        printf("Error opening file %s\n", candidatesFile);
        exit(1);
    }

    while (fgets(cand, sizeof(cand), fp1))
    {
        n++;
    }
    fclose(fp1);

    system("cls");
    heading();
    printf("\n LIST OF CONTESTING CANDIDATES IN %s SOCIETY:\n\n", society);
    fp1 = fopen(candidatesFile, "r");
    for (int i = 0; i < n; i++)
    {
        if (fgets(cand, sizeof(cand), fp1))
        {
            printf("%d. %s", m, cand);
            m++;
        }
    }
    fclose(fp1);

    FILE *fp3 = fopen(votesFile, "r");
    if (fp3 != NULL)
    {
        for (int i = 0; i < n; i++)
        {
            fscanf(fp3, "%d", &a[i]);
        }
        fclose(fp3);
    }

    printf("\n\nEnter Your Response:");
    scanf("%d", &res);
    if (res < 1 || res > n)
    {
        printf("Invalid response. Please enter a valid option.\n");
        return;
    }
    a[res - 1]++;

    fp3 = fopen(votesFile, "w");
    for (int i = 0; i < n; i++)
    {
        fprintf(fp3, "%d\n", a[i]);
    }
    fclose(fp3);
    printf("\nYour response has been submitted successfully\n");

    // Mark the user as having voted
    fp3 = fopen("voters.txt", "a");
    if (fp3 == NULL)
    {
        printf("Error opening voters.txt\n");
        exit(1);
    }
    fprintf(fp3, "%s\n", name1);
    fclose(fp3);

    // Mark the user as having voted in the voted file
    fp3 = fopen("voted.txt", "a");
    if (fp3 == NULL)
    {
        printf("Error opening voted.txt\n");
        exit(1);
    }
    fprintf(fp3, "%s\n", ID);
    fclose(fp3);

    // Display the updated vote counts and exit
    system("cls");
    heading();
    m = 1;
    printf("\nUpdated LIST OF CONTESTING CANDIDATES IN %s SOCIETY:\n\n", society);
    fp1 = fopen(candidatesFile, "r");
    for (int i = 0; i < n; i++)
    {
        if (fgets(cand, sizeof(cand), fp1))
        {
            printf("%d. %s", m, cand);
            printf(" Votes: %d\n\n", a[i]);
            m++;
        }
    }
    fclose(fp1);
}

void listVoters()
{
    FILE *fp = fopen("voters.txt", "r");
    if (fp == NULL)
    {
        printf("Error opening file voters.txt\n");
        return;
    }

    char voter[20];
    int num = 1;
    while (fscanf(fp, "%s", voter) != EOF)
    {
        printf("%d. %s\n", num, voter);
        num++;
    }

    fclose(fp);
}

// For live count
void liveCount(char *society)
{
    char candidatesFile[30], votesFile[30], cand[20];
    int n = 0, a[50] = {0}, m = 1;

    sprintf(candidatesFile, "%s_candidates.txt", society);
    sprintf(votesFile, "%s_votes.txt", society);

    FILE *fp1 = fopen(candidatesFile, "r");
    if (fp1 == NULL)
    {
        printf("Error opening file %s\n", candidatesFile);
        exit(1);
    }

    while (fgets(cand, sizeof(cand), fp1))
    {
        n++;
    }
    fclose(fp1);

    FILE *fp3 = fopen(votesFile, "r");
    if (fp3 == NULL)
    {
        printf("Error opening file %s\n", votesFile);
        exit(1);
    }

    for (int i = 0; i < n; i++)
    {
        fscanf(fp3, "%d", &a[i]);
    }
    fclose(fp3);

    system("cls");
    heading();
    printf("\n LIVE COUNT OF %s SOCIETY:\n\n", society);

    fp1 = fopen(candidatesFile, "r");
    for (int i = 0; i < n; i++)
    {
        if (fgets(cand, sizeof(cand), fp1))
        {
            printf("%d. %s", m, cand);
            printf("Votes: %d\n", a[i]);
            m++;
        }
    }
    fclose(fp1);
}

// For list of candidates
void listCandidates(char *society)
{
    char candidatesFile[30], cand[20];
    int m = 1;

    sprintf(candidatesFile, "%s_candidates.txt", society);

    FILE *fp1 = fopen(candidatesFile, "r");
    if (fp1 == NULL)
    {
        printf("Error opening file %s\n", candidatesFile);
        return;
    }

    system("cls");
    heading();
    printf("\n LIST OF CONTESTING CANDIDATES IN %s SOCIETY:\n\n", society);
    while (fgets(cand, sizeof(cand), fp1))
    {
        printf("%d. %s", m, cand);
        m++;
    }

    fclose(fp1);
}