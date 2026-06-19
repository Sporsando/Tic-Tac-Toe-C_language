#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define messageSelectCorrectIcon printf("%sSelect correct icon (X or O)!\n", slashTFormat)
#define messageSelectCorrectOption printf("%sSelect correct option (1 or 2)!\n", slashTFormat)
#define messageSelectCorrectChoice printf("%sSelect correct option (0 or 1)!\n", slashTFormat)
#define messageSelectCorrectRow printf("%sSelect correct row (1-3)!\n", slashTFormat)
#define messageSelectCorrectColumn printf("%sSelect correct column (1-3)!\n", slashTFormat)
#define startRecursionIcon messageSelectCorrectIcon; \
                currentRecursionState += 1; \
                selectIcon(gameData, currentRecursionState);\
                currentRecursionState -= 1;
#define startRecursionOption messageSelectCorrectOption; \
        currentRecursionState += 1; \
        chooseGameType(gameData, currentRecursionState); \
        currentRecursionState -= 1;
#define startRecursionRow messageSelectCorrectRow; \
        currentRowRecursionState += 1; \
        selectRow(gameData, playingField, currentRowRecursionState); \
        currentRowRecursionState -= 1;
#define startRecursionColumn messageSelectCorrectColumn; \
        currentColumnRecursionState += 1; \
        selectColumn(gameData, playingField, currentColumnRecursionState); \
        currentColumnRecursionState -= 1;
#define startRecursionConfirmChoice messageSelectCorrectChoice; \
        currentChoiceRecursionState += 1; \
        selectConfirmChoice(gameData, playingField, currentChoiceRecursionState); \
        currentChoiceRecursionState -= 1;


const char slashTFormat[] = "\t\t";
//int isStdinClear = 1;

typedef struct currentGameData
{
    int selectedGameType;
    char selectedPlayer1Icon;
    char selectedPlayer2Icon;
    int playerTurn; // bool
    int selectedRow;
    int selectedColumn;
    int gameEnd; // bool

};

typedef struct PlayingField
{
    char field[3][3];
    char availableFields[3][3];
    int rowPlayingField;
    int countRowsPlayingField;
    char possiblePlayerPositions[3];
};

int calculateMatrixRow(struct PlayingField *playingField)
{
    return sizeof(playingField->field[0]) / sizeof(playingField->field[0][0]);
}

int calculateMatrixCountRows(struct PlayingField *playingField)
{
    return sizeof(playingField->field) / sizeof(playingField->field[0]);
}

void fitArrayIndexPlusOne(char arrayToFit[], int lengthArrayToFit)
{
    for (int i = 0; i < lengthArrayToFit; ++i)
    {
        arrayToFit[i] = (char) i + 1 + '0';
    }
}


void printCurrentField(struct PlayingField *playingField);
void playerMove(struct currentGameData *gameData, struct PlayingField *playingField);

void startGreeting()
{
    printf("\n\n\n");
    printf("%sTic-Tac-Toe game!\n", slashTFormat);
}

int in(char string[], int stringLength, char characterToCheck)
{
    for (int i = 0; i < stringLength; ++i)
    {
        if (characterToCheck == string[i])
        {
            return 1;
        }
    }
    return 0;
}

void printSlashNInRecursive(int recursionState)
{
    if (recursionState != 0)
    {
        printf("\n");
    }
}

void clearStdin()
{
    char character;
    while ((character = getchar()) != '\n' && (character != EOF));
}



void chooseGameType(struct currentGameData *gameData, int currentRecursionState)
{
    printSlashNInRecursive(currentRecursionState);
    printf("%sChoose game type:\n", slashTFormat);
    printf("%s1. Play with computer\n", slashTFormat);
    printf("%s2. Play with another player\n", slashTFormat);

    printf("%s", slashTFormat);


    char inputChar = getchar();
    if (inputChar == '\n')
    {
        startRecursionOption
    } else
    {
        if ((getchar()) == '\n')
        {
            switch (inputChar)
            {
            case '1':
                gameData->selectedGameType = 1;
                printf("%sPlaying with computer!\n", slashTFormat); //we will play against computer
                printf("\n");
                break;
            case '2':
                gameData->selectedGameType = 2;
                printf("%sPlaying with other player!\n", slashTFormat); //we will play against player
                printf("\n");
                break;
            default:
                startRecursionOption
                break;
            }
        } else
        {
            clearStdin();
            startRecursionOption
        }


    }

}


void selectIcon(struct currentGameData *gameData, int currentRecursionState)
{
    printSlashNInRecursive(currentRecursionState);
    printf("%sEnter icon to play (X or O):\n", slashTFormat);

    printf("%s", slashTFormat);

    char inputChar = getchar();
    if (inputChar == '\n')
    {
        startRecursionIcon
    } else
    {
        if ((getchar()) == '\n')
        {
            switch (inputChar)
            {
            case 'X':
                gameData->selectedPlayer1Icon = 'X';
                gameData->selectedPlayer2Icon = 'O';
                printf("%sYou are playing X side!\n", slashTFormat);
                printf("\n");
                break;
            case 'O':
                gameData->selectedPlayer1Icon = 'O';
                gameData->selectedPlayer2Icon = 'X';
                printf("%sYou are playing O side!\n", slashTFormat);
                printf("\n");
                break;
            default:
                startRecursionIcon
                break;
            }
        } else
        {
            clearStdin();
            startRecursionIcon
        }
    }
}

void selectRow(struct currentGameData *gameData, struct PlayingField *playingField, int currentRowRecursionState)
{
    printSlashNInRecursive(currentRowRecursionState);
    printf("%sEnter row to place your icon (1-3):\n", slashTFormat);
    printf("%s", slashTFormat);

    char row = getchar();

    if (row == '\n')
    {
        startRecursionRow
    } else
    {
        if ((getchar()) == '\n')
        {
            if (in(playingField->possiblePlayerPositions, playingField->countRowsPlayingField, row) == 1)
            {
                gameData->selectedRow = (int) (row - '0');
                gameData->selectedRow -= 1;
                printf("\n");
            } else
            {
                startRecursionRow
            }
        } else
        {
            clearStdin();
            startRecursionRow
        }
    }
}

void selectColumn(struct currentGameData *gameData, struct PlayingField *playingField, int currentColumnRecursionState)
{
    printSlashNInRecursive(currentColumnRecursionState);
    printf("%sEnter column to place your icon (1-3):\n", slashTFormat);
    printf("%s", slashTFormat);
    char column = getchar();

    if (column == '\n')
    {
        startRecursionColumn
    } else
    {
        if ((getchar()) == '\n')
        {
            if (in(playingField->possiblePlayerPositions, playingField->rowPlayingField, column) == 1)
            {
                gameData->selectedColumn = (int) (column - '0');
                gameData->selectedColumn -= 1;
                printf("\n");
            } else
            {
                startRecursionColumn
            }
        } else
        {
            clearStdin();
            startRecursionColumn
        }
    }
}

void selectConfirmChoice(struct currentGameData *gameData, struct PlayingField *playingField, int currentChoiceRecursionState)
{
    printSlashNInRecursive(currentChoiceRecursionState);
    printf("%sConfirm choice? (0 or 1)\n", slashTFormat);
    printf("%s", slashTFormat);
    char confirmChoice = getchar();

    if (confirmChoice == '\n')
    {
        startRecursionConfirmChoice
    } else
    {
        if ((getchar()) == '\n')
        {
            switch (confirmChoice)
            {
            case '0':
                playingField->field[gameData->selectedRow][gameData->selectedColumn] = '*';
                printCurrentField(playingField);
                playerMove(gameData, playingField);
                break;
            case '1':
                printf("\n");
                playingField->field[gameData->selectedRow][gameData->selectedColumn] = gameData->selectedPlayer1Icon;
                playingField->availableFields[gameData->selectedRow][gameData->selectedColumn] = '1';
                printf("%sIcon placed!\n", slashTFormat);
                printCurrentField(playingField);
                gameData->playerTurn = 0;
                break;
            default:
                startRecursionConfirmChoice
                break;
            }
        } else
        {
            clearStdin();
            startRecursionConfirmChoice
        }
    }
}

void playerMove(struct currentGameData *gameData, struct PlayingField *playingField) //this function will be called if this is player1Turn or player2Turn (when game with other player)
{
    selectRow(gameData, playingField, 0);
    selectColumn(gameData, playingField, 0);
    switch (playingField->availableFields[gameData->selectedRow][gameData->selectedColumn])
    {
    case '0':
        printf("\n");
        playingField->field[gameData->selectedRow][gameData->selectedColumn] = '?';
        printf("%sPlace is available!\n", slashTFormat);
        printCurrentField(playingField);
        selectConfirmChoice(gameData, playingField, 0);
        break;
    case '1':
        printf("%sPlace is unavailable!\n", slashTFormat);
        printCurrentField(playingField);
        playerMove(gameData, playingField);
        break;
    }



}

void computerMove(struct currentGameData *gameData, struct PlayingField *playingField)
{
    int iter = 0;
    int availableCoordComputerField[8][2];
    for (int i = 0; i < playingField->countRowsPlayingField; ++i)
    {
        for (int j = 0; j < playingField->rowPlayingField; ++j)
        {
            if (playingField->availableFields[i][j] == '0')
            {
                availableCoordComputerField[iter][0] = i;
                availableCoordComputerField[iter][1] = j;
                iter += 1;
            }
        }
    }

    if (iter != 0)
    {

        srand(time(NULL));
        int randomNumber = rand() % ((iter - 1) - 0 + 1) + 0;

        printf("%sComputer turn:\n%sRow %d\n%sColumn %d\n", slashTFormat, slashTFormat, availableCoordComputerField[randomNumber][0] + 1, slashTFormat, availableCoordComputerField[randomNumber][1] + 1);
        playingField->field[availableCoordComputerField[randomNumber][0]][availableCoordComputerField[randomNumber][1]] = gameData->selectedPlayer2Icon;
        playingField->availableFields[availableCoordComputerField[randomNumber][0]][availableCoordComputerField[randomNumber][1]] = '1';
        printCurrentField(playingField);


        gameData->playerTurn = 1;
    } else
    {
        printf("cannot move icon by computer\n");
    }


}


void printCurrentField(struct PlayingField *playingField)
{
    printf("%sCurrent play field:\n", slashTFormat);
    printf("%s  ", slashTFormat);
    for (int i = 0; i < playingField->rowPlayingField; ++i)
    {
        printf("%d ", i + 1);
    }
    printf("\n");
    for (int i = 0; i < playingField->countRowsPlayingField; ++i)
    {
        printf("%s%d ", slashTFormat, i + 1);
        for (int j = 0; j < playingField->rowPlayingField; ++j)
        {
            printf("%c ", playingField->field[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

void restartField(struct PlayingField *playingField) //for now it has debug prints
{
    //printf("field%savailableField\n", slashTFormat);
    //printf("\n");
    for (int i = 0; i < playingField->countRowsPlayingField; ++i)
    {
        for (int j = 0; j < playingField->rowPlayingField; ++j)
        {
            playingField->field[i][j] = '*';
            playingField->availableFields[i][j] = '0';
            //printf("%c ", playingField->field[i][j]);
        }
        //printf("%s", slashTFormat);
        for (int j = 0; j < playingField->rowPlayingField; ++j)
        {
            //printf("%c ", playingField->availableFields[i][j]);
        }
        //printf("\n");
    }
}

void winMessage(int *gameEndBool, char iconToCheck, char iconCondition)
{
    *gameEndBool = 1;
    if (iconToCheck == iconCondition)
    {
        printf("%sPlayer 1 win!\n", slashTFormat);
    } else
    {
        printf("%sPlayer 2 win!\n", slashTFormat);
    }
}

void checkForIdenticIcon(char currentIcon, char anotherIcon, int *variableToChange)
{
    if (currentIcon != '*' && currentIcon == anotherIcon)
    {
        *variableToChange += 1;
    }
}

void checkForEnding(struct currentGameData *gameData, struct PlayingField *playingField)
{
    //Check for draw
    int counterOne = 0;
    for (int i = 0; i < playingField->countRowsPlayingField; ++i)
    {
        for (int j = 0; j < playingField->rowPlayingField; ++j)
        {
            if (playingField->availableFields[i][j] == '1')
            {
                counterOne += 1;
            }
        }
    }
    if (counterOne == playingField->countRowsPlayingField * playingField->rowPlayingField)
    {
        gameData->gameEnd = 1;
    }


    //Checking for somebody win

    char columnWinArray[playingField->countRowsPlayingField];
    char diagonalWinArray[playingField->countRowsPlayingField];
    for (int i = 0; i < playingField->countRowsPlayingField; ++i)
    {
        int rowWin = 0;
        int columnWin = 0;
        int diagonalWin = 0;

        for (int j = 0; j < playingField->rowPlayingField; ++j)
        {

            if (i == 0)
            {
                diagonalWinArray[j] = playingField->field[j][j];
            } else if (i == 1)
            {
                diagonalWinArray[j] = playingField->field[playingField->rowPlayingField - 1 - j][j];
            }
            columnWinArray[j] = playingField->field[j][i];
            if (j != 0)
            {
                checkForIdenticIcon(diagonalWinArray[j], diagonalWinArray[j-1], &diagonalWin); //check for diagonal win
                checkForIdenticIcon(columnWinArray[j], columnWinArray[j-1], &columnWin); //check for column win
                checkForIdenticIcon(playingField->field[i][j], playingField->field[i][j-1], &rowWin); //check for row win
            }


        }

        if (diagonalWin == 2)
        {
            winMessage(&gameData->gameEnd, diagonalWinArray[0], gameData->selectedPlayer1Icon);
            break;
        }

        if (columnWin == 2)
        {
            winMessage(&gameData->gameEnd, columnWinArray[0], gameData->selectedPlayer1Icon);
            break;
        }

        if (rowWin == 2)
        {
            winMessage(&gameData->gameEnd, playingField->field[i][0], gameData->selectedPlayer1Icon);
            break;
        }
    }


}

int main()
{
    //initialization variables
    struct currentGameData gameData;
    struct PlayingField playingField;
    playingField.rowPlayingField = calculateMatrixRow(&playingField);
    playingField.countRowsPlayingField = calculateMatrixCountRows(&playingField);
    fitArrayIndexPlusOne(playingField.possiblePlayerPositions, playingField.rowPlayingField);
    restartField(&playingField);
    gameData.playerTurn = 1;
    gameData.gameEnd = 0;

    //start game
    startGreeting();
    printCurrentField(&playingField);
    chooseGameType(&gameData, 0);
    selectIcon(&gameData, 0);

    //game
    while (gameData.gameEnd == 0)
    {
        if (gameData.selectedGameType == 1) // playing with computer
        {
            if (gameData.playerTurn == 1)
            {
                playerMove(&gameData, &playingField);
            } else
            {
                //computer move
                printf("%sComputer move!\n", slashTFormat);
                computerMove(&gameData, &playingField);
            }
        } else //playing with another player
        {
            if (gameData.playerTurn == 1)
            {
                playerMove(&gameData, &playingField);
            } else
            {
                //another player move
                printf("%sAnother player move!\n", slashTFormat);
                gameData.playerTurn = 1; // when another player placed his icon the turn goes to first player
            }
        }

        checkForEnding(&gameData, &playingField);

    }
    printf("%sEnd of game!\n", slashTFormat);

    return 0;
}






