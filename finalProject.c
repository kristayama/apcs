// Krista Yamamoto-Chin
// APCSP 2020-2021
// 6-2 Final Project Create Task

#define _DEFAULT_SOURCE
#include <cs50.h>
#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>


// defining variables
int bankAccount = 0;
int gameRound = 0;
int categoriesAndMoney[2][5];
int askedQ[40];
int corCatOrMoney = 0;
int quesAsked = 0;

string topBar = ("⎺");
string bottomBar = ("⎽");
string jeopardyTitle = ("JEOPARDY");
string question = ("");
string answer = ("");
string intro = ("Hello! Welcome to Jeopardy! Your goal is to answer questions correctly\n");
string intro1 = ("and add money to your bank. Incorrect answers will result in money\n");
string intro2 = ("subtracted from your bank. All answers are case sensitive so make sure\n");
string intro3 = ("to be careful. You will have 180s to play and earn as much money as\n");
string intro4 = ("possible. After you've chosen your question, you will have 10 seconds to\n");
string intro5 = ("think and 10 seconds to type. Answers submitted after 10s have passed\n");
string intro6 = ("will be forfeited and you will lose money so be sure to have your answer\n");
string intro7 = ("ready. You will not be able to type while the 10s thinking timer is\n");
string intro8 = ("counting down. Good luck!\n");


int printSpaces(int num) // print # of spaces needed
{
    for (int i = 0; i<num; i++)
    {
        printf(" ");
    }

    return 0;
}

// borrowed code from Q2 Unit Project BEGIN CODE
int randomNumber (int maxInt) // function to generate a random number with a inputted maximum
{
      int number = (random() / ((double) RAND_MAX + 1)) * maxInt;
      return number;
}
// borrowed code from Q2 Unit Project END CODE

// function to draw title
int titleDraw(string name)
{
    printf("⎡");
    for (int i = 0; i<46; i++)
    {
        printf("%s", topBar);
    }
    printf("⎤\n");

    // code to print centered and evenly spaced out name
    int nameWithApos = strlen(name) + 2;
    int totalSpaces = nameWithApos - 1;
    int numSpaces = 0;

    if (strlen(name) > 8)
    {
        numSpaces = 1;
    }
    else
    {
        numSpaces = 2;
    }
    totalSpaces = totalSpaces*numSpaces;

    int spacesB4 = ((44 - (totalSpaces + nameWithApos)) / 2) + 1;

    printf("|");
    printSpaces(spacesB4);
    for (int i = 0; i<strlen(name); i++)
    {
        printf("%c", name[i]);
        printSpaces(numSpaces);
    }
    printf("'");
    printSpaces(numSpaces);
    printf("s");
    if (strlen(name) % 2 == 1)
    {
        printSpaces(spacesB4+1);
    }
    else
    {
        printSpaces(spacesB4);
    }
    printf("|\n");

    // for loop to print centered and evenly spaced out "Jeopardy"
    printf("|");
    for (int i = 0; i<11; i++)
    {
        printf(" ");
    }
    for (int i = 0; i<8; i++)
    {
        char letter = jeopardyTitle[i];
        printf("%c  ", letter);
    }
    printSpaces(11);
    printf("|\n");

    // print bottom of box
    printf("⎣");
    for (int i = 0; i<46; i++)
    {
        printf("%s", bottomBar);
    }
    printf("⎦\n");
    return 0;
}

// function to draw top or bottom ascii art of box
int boxDraw (int side, string input)
{
    for (int a = 0; a<4; a++)
    {
        if (side == 1)
        {
            printf("⎡");
        }
        else if (side == 2)
        {
            printf("⎣");
        }

        for (int b = 0; b<10; b++)
        {
            printf("%s", input);
        }

        if (side == 1)
        {
            printf("⎤");
        }
        else if (side == 2)
        {
            printf("⎦");
        }
    }

    printf("\n");
    return 0;
}

// function to draw top part of box
int topDraw (void)
{
    boxDraw(1, topBar);
    return 0;
}

// function to draw bottom part of box
int bottomDraw (void)
{
    boxDraw(2, bottomBar);
    return 0;
}

// function to draw money amounts on game board
int moneyDraw (void)
{
    for (int a = 1; a<=4; a++) // for loop drawing $200, $400, $600, and $800 boxes
    {
        topDraw();
        for (int b = 0; b<4; b++)
        {
            printf("|");
            printSpaces(3);
            printf("$%i00", 2*a);
            printSpaces(3);
            printf("|");
        }

        printf("\n");
        bottomDraw();
    }

    topDraw();
    for (int b = 0; b<4; b++) // for loop drawing $1000 (new code to account for extra character)
    {
        printf("|");
        printSpaces(2);
        printf("$1000");
        printSpaces(3);
        printf("|");
    }

    printf("\n");
    bottomDraw();

    return 0;
}

int categoryPrint(int num) // switch case for each category
{
    switch (num)
    {
        case 1:
            printf ("Category 1: Quick Maths!\n");
            break;
        case 2:
            printf ("Category 2: Name That Person (First Last *CASE SENSITIVE*)\n");
            break;
        case 3:
            printf ("Category 3: 'Iolani Info\n");
            break;
        case 4:
            printf ("Category 4: Class of 2021\n");
            break;
        case 5:
            printf ("Category 5: Random Tidbits\n");
            break;
        case 6:
            printf ("Category 6: Film Facts\n");
            break;
        case 7:
            printf ("Category 7: APCS (Multiple Choice)\n");
            break;
        case 8:
            printf ("Category 8: APCS (Free Response)\n");
            break;
    }
    return 0;
}

// some of the following questions were adapted from tutorified.com, an APCSP practice exam, and parade.com
string returnQ (int category, int money) // function to return string answer that corresponds with inputted number
{
    switch (category)
    {
        case 1:
            switch (money)
            {
                case 2:
                    question = ("250*3");
                    answer = ("750");
                    quesAsked = 1;
                    break;
                case 4:
                    question = ("310*3");
                    answer = ("930");
                    quesAsked = 2;
                    break;
                case 6:
                    question = ("15*80");
                    answer = ("1200");
                    quesAsked = 3;
                    break;
                case 8:
                    question = ("230*60");
                    answer = ("13800");
                    quesAsked = 4;
                    break;
                case 10:
                    question = ("470*4.3");
                    answer = ("2021");
                    quesAsked = 5;
                    break;
            }
            break;
        case 2:
            switch (money)
            {
                case 2:
                    question = ("Who is known for playing the piano in Weinberg during passing periods?");
                    answer = ("Michael Park");
                    quesAsked = 6;
                    break;
                case 4:
                    question = ("Who is married to Justin Beiber? (use maiden name)");
                    answer = ("Hailey Baldwin");
                    quesAsked = 7;
                    break;
                case 6:
                    question = ("Who is the youngest member of Congress? (Initials OK)");
                    answer = ("AOC");
                    quesAsked = 8;
                    break;
                case 8:
                    question = ("Who was the yearbook dedicated to in 2017?");
                    answer = ("Alan Suemori");
                    quesAsked = 9;
                    break;
                case 10:
                    question = ("Who is #30 on the Golden State Warriors? (Real Name)");
                    answer = ("Wardell Curry");
                    quesAsked = 10;
                    break;
            }
            break;
        case 3:
            switch (money)
            {
                case 2:
                    question = ("What does ‘Iolani mean?");
                    answer = ("Heavenly Hawk");
                    quesAsked = 11;
                    break;
                case 4:
                    question = ("Who is a famous Chinese alumnus of ‘Iolani?");
                    answer = ("Sun Yat Sen");
                    quesAsked = 12;
                    break;
                case 6:
                    question = ("What was the name of ‘Iolani School before it was ‘Iolani school?");
                    answer = ("St. Alban’s College");
                    quesAsked = 13;
                    break;
                case 8:
                    question = ("Who is the Lower School Head of School?");
                    answer = ("Zachary Linnert");
                    quesAsked = 14;
                    break;
                case 10:
                    question = ("What year were girls allowed to attend ‘Iolani?");
                    answer = ("1979");
                    quesAsked = 15;
                    break;
            }
            break;
        case 4:
            switch (money)
            {
                case 2:
                    question = ("What day is our graduation? (MM/DD/YYYY)");
                    answer = ("06/05/2021");
                    quesAsked = 16;
                    break;
                case 4:
                    question = ("What was the date of our senior sunrise and dinner? (MM/DD/YYYY)");
                    answer = ("09/25/2020");
                    quesAsked = 17;
                    break;
                case 6:
                    question = ("What was our Sophomore Banquet Theme?");
                    answer = ("Aurora");
                    quesAsked = 18;
                    break;
                case 8:
                    question = ("What grade were we in when we had our first dorm students?");
                    answer = ("10");
                    quesAsked = 19;
                    break;
                case 10:
                    question = ("What was the order of our spirit week this year?");
                    answer = ("43521");
                    quesAsked = 20;
                    break;
            }
            break;
        case 5:
            switch (money)
            {
                case 2:
                    question = ("What is the last letter of our first president's first name?");
                    answer = ("E");
                    quesAsked = 21;
                    break;
                case 4:
                    question = ("What are the first 6 digits of e?");
                    answer = ("2.171828");
                    quesAsked = 22;
                    break;
                case 6:
                    question = ("Which US state’s postal code is “MD”?");
                    answer = ("Maryland");
                    quesAsked = 23;
                    break;
                case 8:
                    question = ("Where is Le Bourget Airport? (Country)");
                    answer = ("France");
                    quesAsked = 24;
                    break;
                case 10:
                    question = ("What did HBO originally stand for?");
                    answer = ("Home Box Office");
                    quesAsked = 25;
                    break;
            }
            break;
        case 6:
            switch (money)
            {
                case 2:
                    question = ("In The Matrix, which color pill does Neo take? (ie green)");
                    answer = ("red");
                    quesAsked = 26;
                    break;
                case 4:
                    question = ("What was the first feature-length animated movie ever released?");
                    answer = ("Snow White and the Seven Dwarfs");
                    quesAsked = 27;
                    break;
                case 6:
                    question = ("What song does Tom Cruise sing and dance to in Risky Business?");
                    answer = ("Old Time Rock and Roll");
                    quesAsked = 28;
                    break;
                case 8:
                    question = ("”Girls like me don’t make invitations like this to just anyone” - ?");
                    answer = ("Pulp Fiction");
                    quesAsked = 29;
                    break;
                case 10:
                    question = ("What song do you hear during the opening credits of Guardians of the Galaxy?");
                    answer = ("Come and Get Your Love");
                    quesAsked = 30;
                    break;
            }
            break;
        case 7:
            switch (money)
            {
                case 2:
                    question = ("Which of these is a Boolean expression?\nA. X=57\nB. (temp>32)");
                    answer = ("B");
                    quesAsked = 31;
                    break;
                case 4:
                    question = ("400: T or F: Functions cannot make calls to other functions within the same program.");
                    answer = ("F");
                    quesAsked = 32;
                    break;
                case 6:
                    question = ("What is a valid unit of code that resolves to a value?\nA. Expression\nB. Equation\nC. Program");
                    answer = ("A");
                    quesAsked = 33;
                    break;
                case 8:
                    question = ("Can you tell the representation of binary numbers without knowing the context of their use?");
                    answer = ("No");
                    quesAsked = 34;
                    break;
                case 10:
                    question = ("Which color is #50C878, given the decimal equivalents (RGB)?\nA. (32,76,414)\nB. (50,118,78)\nC. (80,200,12)");
                    answer = ("C");
                    quesAsked = 35;
                    break;
            }
            break;
        case 8:
            switch (money)
            {
                case 2:
                    question = ("What is displayed after the following code is run?\nline 1 = “Good luck”\nline 2 = “ on the AP exam!”\nDISPLAY (line1 + line2)");
                    answer = ("Good luck on the AP exam!");
                    quesAsked = 36;
                    break;
                case 4:
                    question = ("If Susie wants to email a photo, how should she compress the image to preserve quality?");
                    answer = ("Lossless");
                    quesAsked = 37;
                    break;
                case 6:
                    question = ("Is this statement true or false?\n\nTCP guarantees that no packets are ever dropped (Answer with T or F)");
                    answer = ("F");
                    quesAsked = 38;
                    break;
                case 8:
                    question = ("What type of compression do zip files use?");
                    answer = ("Lossless");
                    quesAsked = 39;
                    break;
                case 10:
                    question = ("Convert 10011011 to decimal.");
                    answer = ("155");
                    quesAsked = 40;
                    break;
            }
            break;
    }
    return question;
}

int gameboardDraw(string name, int key, int category) // function to print gameboard
{
    titleDraw(name);

    topDraw();
    for (int i = 0; i<4; i++)
    {
        printf("|");
        printSpaces(4);

        categoriesAndMoney[0][i] = (((category + i*key) % 7) + 1);

        printf("%i", categoriesAndMoney[0][i]);

        printSpaces(5);
        printf("|");
    }
    printf("\n");
    bottomDraw();
    moneyDraw();

    for (int i = 0; i<4; i++)
    {
        categoryPrint(categoriesAndMoney[0][i]);
    }

    return 0;
}
// function to check if category input or money input is OK to use
int checkCatAndMoney(int type, int input)
{
    int num = 0;
    string inputType = "";

    // money amounts
    for (int i = 1; i<=5; i++)
    {
        categoriesAndMoney[1][i-1] = i*200;
    }

    if (type == 1) // if checking category
    {
        num = 4; // 4 categories available
        inputType = "category";
    }
    else if (type == 2) // if checking money amount
    {
        num = 5; // 5 money amounts available
        inputType = "money amount";
    }

    for (int i = 0; i<num; i++)
    {
        if (input == categoriesAndMoney[type-1][i]) // if the category inputted is one of the 4 available
        {
            corCatOrMoney = 1;
        }
    }
    if (corCatOrMoney == 0) // if the input is not one of the acceptable categories
    {
        printf("Sorry, %i is not an acceptable %s. Please choose one of the %i above.\n", input, inputType, num);
    }

    return 0;
}

int main (void)
{
    srandom(time(NULL)); // necessary code so that each game has different categories
    int category = 0;
    int money = 0;
    int quesAskedAlready = 1; // 0 = true, 1 = false (if T, continue w code, if F, tell user question already chosen)

    printf("%s%s%s%s%s%s%s%s%s", intro, intro1, intro2, intro3, intro4, intro5, intro6, intro7, intro8); // print instructions

    string name;
    do {
        name = get_string("(MAX 20 CHARACTERS) Name: ");
    }
    while (strlen(name) > 20);

    int ranNum = randomNumber(7);
    int key = 0;

    do {
        key = randomNumber(7);
    }
    while (key == 4 || key == 0);

    printf("Bank: $%i\nYour time starts now.\n", bankAccount);
    long gameStartTime = time(NULL);

    do
    {
        gameboardDraw(name, key, ranNum);
        gameRound++;

        do
        {
            corCatOrMoney = 0;
            quesAskedAlready = 1;

            do
            {
                category = get_int("Category Number: "); // prompt user for category and check if OK
                checkCatAndMoney(1, category);
            }
            while (corCatOrMoney == 0);

            corCatOrMoney = 0;

            do
            {
                money = get_int("Monetary Amount: "); // prompt user for money amt and check if OK
                checkCatAndMoney(2, money);
            }
            while (corCatOrMoney == 0);

            returnQ(category, money/100); // run function to designate quesAsked with corresponding question #

            for (int i = 0; i<gameRound; i++) // check if question has already been attempted
            {
                if (quesAsked == askedQ[i])
                {
                    quesAskedAlready = 0;
                }
            }
            if (quesAskedAlready == 0)
            {
                printf("Sorry, you've already attempted that question. Please choose another one.\n");
            }
        }
        while (quesAskedAlready == 0);

        askedQ[gameRound] = quesAsked; // add question to askedQ[] list
        printf("\n%s\n\nYour 10 second timer to think of an answer starts now.\n", returnQ(category, money/100)); // print question

        long initialTime = time(NULL); // designate initial time variable
        long timeElapsed = 0;
        for (int i = 0; i<10; i++) // timer
        {
            timeElapsed = time(NULL) - initialTime;
            printf("%li\n", 10 - timeElapsed);
            sleep(1);
        }
        printf("Time is up!\nYou have 10 seconds to type your answer.\n");

        string inputAnswer = get_string("");
        timeElapsed = time(NULL);
        if (timeElapsed - initialTime >20) // check to see if user answered in correct amount of time
        {
            printf("Sorry! You took too long to type your answer and have forfeited the question.\n");
            bankAccount = bankAccount - money;
        }
        if (timeElapsed - initialTime <= 20)
        {

            //this code segment is adapted from my quarter 2 unit project BEGIN CODE
            if (strcmp(inputAnswer, answer) == 0) // if correct anwer given, money added to bank
            {
                printf ("Correct!\n");
                bankAccount = bankAccount + money;
            }

            if (strcmp(inputAnswer, answer) != 0) // if wrong anwer given, money subtracted from bank
            {
                printf("Wrong answer!\nThe correct answer was: \n\n%s\n\n", answer);
                bankAccount = bankAccount - money;
            }
            //this code segment is adapted from my quarter 2 unit project END CODE

        }

        printf("Time Elapsed (sec): %li\n", time(NULL) - gameStartTime);
        printf("Bank: $%i\n", bankAccount);

    }
    while (time(NULL) - gameStartTime < 180); // 3 minutes to play

    if (bankAccount > 0)
    {
        printf("Time is up!\n\nCongratulations! You've won a hefty sum of $%i. Thanks for playing!\n", bankAccount);
    }
    if (bankAccount <= 0)
    {
        printf("Time is up!\n\nUnfortunately, you ended the game with a balance of $%i and will be going home empty handed.\n", bankAccount);
    }

}