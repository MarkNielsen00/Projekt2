#include <stdio.h>
#include <stdlib.h>
#include<time.h>
/**
 * Yukon: Play the traditional card-game in C.
 */

struct Column {
    int height;
    int id;
    struct Card* next;
};
struct Card {
    char suit; // 1. Spar, 2. Ruder, 3. Klør, 4. Hjerter
    char value; // 1. Es, 11. Knægt, 12. Dame, 13. Konge
    int shown;
    struct Card* next;
    struct Card* prev;
};

// Create Test Columns
struct Card* columnArray[7];
struct Card* foundationArray[4];
struct Card* column_test = NULL;

// Create Test Cards
int card_num = 0;
int cards_placed = 0;
int cardsInColumn = 1;
struct Card* deck[52];
struct Card* card_new = NULL;
struct Card* card_old = NULL;

void printPrevList(struct Card *pCard);
void readTwoCommand(char fromChar, char fromNumber, char cardValue, char cardSuit, char toChar, char toNumber);
struct Card* searchSpecificCard(struct Card* n, char cardSuit, char cardValue);
struct Card* searchLastCard(struct Card* n, char cardSuit, char cardValue);

void mixCards();

void doCommand();

// Play the game
int main()
{
    // Create Columns
    for (int i = 0; i < 7; ++i)
    {
        // Create a Column Start
        column_test = (struct Card*)malloc(sizeof(struct Card));
        column_test->value = 0; // Top
        column_test->suit = '0'; // Top
        column_test->next = NULL; // Top
        column_test->prev = NULL; // Top
        // Save card in array
        columnArray[i] = column_test;
    }

    // Create foundations
    for (int i = 0; i < 4; ++i)
    {
        // Create a Column Start
        column_test = (struct Card*)malloc(sizeof(struct Card));
        column_test->value = 0; // Top
        column_test->suit = '0'; // Top
        column_test->next = NULL; // Top
        column_test->prev = NULL; // Top
        // Save card in array
        foundationArray[i] = column_test;
    }

    // Create Deck of Cards
    for (int i = 1; i < 5; ++i)
    {
        char suit_type;
        switch (i)
        {
            case 1:
                suit_type = 'S';
                break;
            case 2:
                suit_type = 'R';
                break;
            case 3:
                suit_type = 'K';
                break;
            case 4:
                suit_type = 'H';
                break;
        }

        for (int i = 1; i < 14; ++i)
        {
            //struct Card* card_1 = NULL;
            card_new = (struct Card*)malloc(sizeof(struct Card));
            card_new->value = i; // assign data in first node
            card_new->suit = suit_type; // assign data in first node
            deck[card_num] = card_new;
            card_num++;
        }
    }

    // Shuffle deck randomly
    srand(time(0));
    for (int i = 0; i < 1000; ++i) {
        //mixCards(deck);
    }

    // Create 7 columns of cards (set-up game)
    for (int i = 0; i < 7; ++i)
    {
        card_old = columnArray[i];
        for (int j = 0; j < cardsInColumn; ++j)
        {
            card_new = deck[cards_placed];
            card_new->next = card_old; // Link first node with'
            card_new->prev = NULL; // Link first node with'
            card_old->prev = card_new; // Link first node with'
            card_old = card_new;
            cards_placed++;
        }
        // Print Column
        printPrevList(columnArray[i]);
        printf("%c\n", "");
        // How big is the next column
        switch(cards_placed)
        {
            case 1:
                cardsInColumn = 6;
                break;
            case 7:
                cardsInColumn = 7;
                break;
            case 14:
                cardsInColumn = 8;
                break;
            case 22:
                cardsInColumn = 9;
                break;
            case 31:
                cardsInColumn = 10;
                break;
            case 41:
                cardsInColumn = 11;
                break;
        }
    }


    // Print Colums
    for (int i = 0; i < 6; ++i) {
        //printPrevList(columnArray[i]);
    }

    // Play the game
    char *input[8];
    while (1)
    {
        for (int i = 0; i < 7; ++i) {
            //input[i] = NULL;
        }
        for (int i = 0; i < 9; ++i)
        {
            scanf("%c",&input[i]);
        }
        //printf("%c", input[1]);

        //scanf("%c",&input);
        printf("%c%c%c%c%c%c \n",input[0], input[1], input[3], input[4], input[6], input[7]);
        readTwoCommand(input[0], input[1], input[3], input[4], input[6], input[7]);

        for (int i = 0; i < 7; i++) {
            printPrevList(columnArray[i]);
            printf("%c\n", "");
        }
    }

    //return 0;
}

void doCommand(char string[])
{
    char firstColumnNumber = '0';
    // If the card is from a column
    if (string[0] == 'C')
    {
        firstColumnNumber = string[1];
    }
    for (int j = 0; j < 1; ++j) {
        //printf("%c\n", string[j]);
    }
    printf("%c\n", string);
}

//void readTwoCommand(char firstChar, char secChar);

void mixCards(struct Card* deck[]) {
    struct Card *mixCard;

    int random_index1 = rand() % (52 + 1 - 0) + 0;
    int random_index2 = rand() % (52 + 1 - 0) + 0;

    // Flip
    mixCard = deck[random_index1];
    deck[random_index1] = deck[random_index2];
    deck[random_index2] = mixCard;

    //printf("(%d ",deck[random_index1]->value);
    //printf("%d)\n",deck[random_index2]->value);
    //printf("%d \n","");
}
/*
void mixCards (struct Card* deck[])
{
    struct Card mixCard;

    int random_index = rand() % (52 + 1 - 0) + 0;
    printf("%d",random_index)
}
 */

void printPrevList(struct Card *pCard) {
    while (pCard != NULL) {
        printf(" %d ", pCard->value);
        printf("(%c)", pCard->suit);
        pCard = pCard->prev;
    }
}

void readTwoCommand(char fromChar, char fromNumber, char cardValue, char cardSuit, char toChar, char toNumber) {

    // Variables
    int toColumnNumber = 0;
    int fromColumnNumber = 0;
    int convertedCardValue = 0;

    // Read what column number you are taking from
    if (fromChar == 'C')
    {
        fromColumnNumber = (int)(fromNumber-'0');
    }

    // Read what card you are taking
    convertedCardValue = (int)(cardValue-'0');

    // Read location to move the card
    if (toChar == 'C')
    {
        toColumnNumber = (int)(toNumber-'0');
    }

    // Find the first card to take
    struct Card* firstCard = searchSpecificCard(columnArray[fromColumnNumber], cardSuit, toNumber);


    // What is the first card on the to column/foundation
    struct Card* targetCard = searchLastCard(columnArray[toColumnNumber], toChar, toNumber);

    // Can you move the card?

    // Move the card
    firstCard->next->prev = NULL;
    firstCard->next = targetCard;
    targetCard->prev = firstCard;

    //printf("%c", firstChar);
    //printf("%d\n", columnNumber+10);
    //printf("%c\n", 'K');
}

void printList(struct Card* n)
{
    while (n != NULL) {
        printf(" %d ", n->value);
        printf("(%c)", n->suit);
        n = n->next;
    }
}

void printDeck()
{
    // Print Deck
    for (int i = 0; i < 52; ++i)
    {
        struct Card* n = deck[i];
        printf(" %d ", n->value);
        printf("(%c)", n->suit);
    }
}

struct Card* searchSpecificCard(struct Card* n, char cardSuit, char cardValue)
{
    struct Card* foundCard = columnArray[6]->prev;

    // Print Deck
    while (n != NULL)
    {
        if (n->suit == cardSuit)// && n->value == cardValue)
        {
            foundCard = n;
            return foundCard;
        }
        n = n->prev;
    }
    return foundCard;
}

struct Card* searchLastCard(struct Card* n, char cardSuit, char cardValue)
{
    struct Card* foundCard = columnArray[6]->prev;

    // Print Deck
    while (n != NULL)
    {
        if (n->prev == NULL)
        {
            foundCard = n;
            return foundCard;
        }
        n = n->prev;
    }
    return foundCard;
}


//C0:1S:C1
//C0:1S:C1