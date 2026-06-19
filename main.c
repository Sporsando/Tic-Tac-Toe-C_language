#include <stdio.h>
#include <stdlib.h>
#include <time.h>


#define turnOnColoredText(colorNumber) printf("\033[%dm", (colorNumber))
#define turnOffAnyColor printf("\033[0m")
#define messageSelectCorrectIcon turnOnColoredText(31); \
        printf("%sSelect correct icon (X or O)!\n", slashTFormat); \
        turnOffAnyColor
#define messageSelectCorrectOption turnOnColoredText(31); \
        printf("%sSelect correct option (1 or 2)!\n", slashTFormat); \
        turnOffAnyColor
#define messageSelectCorrectChoice turnOnColoredText(31); \
        printf("%sSelect correct option (0 or 1)!\n", slashTFormat); \
        turnOffAnyColor
#define messageSelectCorrectRow turnOnColoredText(31); \
        printf("%sSelect correct row (1-3)!\n", slashTFormat); \
        turnOffAnyColor
#define messageSelectCorrectColumn turnOnColoredText(31); \
        printf("%sSelect correct column (1-3)!\n", slashTFormat); \
        turnOffAnyColor
#define messageIconsSelected if (gameData->selectedGameType == 1) \
                { \
                    printf("%sYou are playing \033[33m%c\033[0m side!\n", slashTFormat, gameData->selectedPlayer1Icon); \
                } else \
                { \
                    printf("%s\033[33mFirst\033[0m player are playing \033[33m%c\033[0m side!\n", slashTFormat, gameData->selectedPlayer1Icon); \
                    printf("%s\033[33mSecond\033[0m player are playing \033[33m%c\033[0m side!\n", slashTFormat, gameData->selectedPlayer2Icon); \
                } \
                printf("\n");
#define playerTurnNegation gameData->playerTurn = !gameData->playerTurn
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
#define winMessageParameter(winIcon) winMessage(gameData, (winIcon), gameData->selectedPlayer1Icon); \
            break;



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


void printCurrentField(struct PlayingField *playingField, struct currentGameData *gameData);
void playerMove(struct currentGameData *gameData, struct PlayingField *playingField);

void startGreeting()
{
    printf("\n\n\n");
    turnOnColoredText(1);
    printf("%sTic-Tac-Toe game!\n", slashTFormat);
    turnOffAnyColor;
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
    turnOnColoredText(32);
    printf("%sChoose game type:\n", slashTFormat);
    turnOffAnyColor;
    printf("%s1. Play with computer\n", slashTFormat);
    printf("%s2. Play with another player\n", slashTFormat);
    printf("%s", slashTFormat);

    turnOnColoredText(33);
    char inputChar = getchar();
    turnOffAnyColor;
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
    turnOnColoredText(32);
    printf("%sEnter icon to play (X or O):\n", slashTFormat);
    turnOffAnyColor;
    printf("%s", slashTFormat);

    turnOnColoredText(33);
    char inputChar = getchar();
    turnOffAnyColor;
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
                messageIconsSelected
                break;
            case 'O':
                gameData->selectedPlayer1Icon = 'O';
                gameData->selectedPlayer2Icon = 'X';
                messageIconsSelected
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
    turnOnColoredText(33);
    char row = getchar();
    turnOffAnyColor;
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
    turnOnColoredText(33);
    char column = getchar();
    turnOffAnyColor;
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

char changeTurnPlayerIcon(struct currentGameData *gameData)
{
    if (gameData->playerTurn == 1)
    {
        return gameData->selectedPlayer1Icon;
    }
    return gameData->selectedPlayer2Icon;
}

void selectConfirmChoice(struct currentGameData *gameData, struct PlayingField *playingField, int currentChoiceRecursionState)
{
    printSlashNInRecursive(currentChoiceRecursionState);
    turnOnColoredText(32);
    printf("%sConfirm choice? (0 or 1)\n", slashTFormat);
    turnOffAnyColor;
    printf("%s", slashTFormat);
    turnOnColoredText(33);
    char confirmChoice = getchar();
    turnOffAnyColor;
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
                printCurrentField(playingField, gameData);
                playerMove(gameData, playingField);
                break;
            case '1':
                printf("\n");
                playingField->field[gameData->selectedRow][gameData->selectedColumn] = changeTurnPlayerIcon(gameData);
                playingField->availableFields[gameData->selectedRow][gameData->selectedColumn] = '1';
                turnOnColoredText(32);
                printf("%sIcon placed!\n", slashTFormat);
                turnOffAnyColor;
                printCurrentField(playingField, gameData);
                playerTurnNegation;
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
        turnOnColoredText(32);
        printf("%sPlace is available!\n", slashTFormat);
        turnOffAnyColor;
        printCurrentField(playingField, gameData);
        selectConfirmChoice(gameData, playingField, 0);
        break;
    case '1':
        turnOnColoredText(31);
        printf("%sPlace is unavailable!\n", slashTFormat);
        turnOffAnyColor;
        printCurrentField(playingField, gameData);
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
        turnOnColoredText(31);
        printf("%sComputer turn:\n%sRow %d\n%sColumn %d\n", slashTFormat, slashTFormat, availableCoordComputerField[randomNumber][0] + 1, slashTFormat, availableCoordComputerField[randomNumber][1] + 1);
        turnOffAnyColor;
        playingField->field[availableCoordComputerField[randomNumber][0]][availableCoordComputerField[randomNumber][1]] = gameData->selectedPlayer2Icon;
        playingField->availableFields[availableCoordComputerField[randomNumber][0]][availableCoordComputerField[randomNumber][1]] = '1';
        printCurrentField(playingField, gameData);
        playerTurnNegation;
    } else
    {
        printf("cannot move icon by computer\n");
    }


}


void printCurrentField(struct PlayingField *playingField, struct currentGameData *gameData)
{
    turnOnColoredText(1);
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
            if (playingField->field[i][j] == '*')
            {
                turnOffAnyColor;
                turnOnColoredText(33);
                printf("%c ", playingField->field[i][j]);
                turnOffAnyColor;
                turnOnColoredText(1);
            } else if (playingField->field[i][j] == '?' || playingField->field[i][j] == gameData->selectedPlayer1Icon)
            {
                turnOffAnyColor;
                turnOnColoredText(32);
                printf("%c ", playingField->field[i][j]);
                turnOffAnyColor;
                turnOnColoredText(1);
            } else
            {
                turnOffAnyColor;
                turnOnColoredText(31);
                printf("%c ", playingField->field[i][j]);
                turnOffAnyColor;
                turnOnColoredText(1);
            }

        }
        printf("\n");
    }
    turnOffAnyColor;
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

void winMessage(struct currentGameData *gameData, char iconToCheck, char iconCondition)
{
    gameData->gameEnd = 1;
    if (gameData->selectedGameType == 1)
    {
        if (iconToCheck == iconCondition)
        {
            turnOnColoredText(32);
            printf("%sYou win!\n", slashTFormat);
            turnOffAnyColor;
        } else
        {
            printf("%sComputer win!\n", slashTFormat);
        }
    } else
    {

        if (iconToCheck == iconCondition)
        {
            turnOnColoredText(32);
            printf("%sFirst player win!\n", slashTFormat);
        } else
        {
            turnOnColoredText(31);
            printf("%sSecond player win!\n", slashTFormat);
        }
        turnOffAnyColor;
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
            winMessageParameter(diagonalWinArray[0])
        }

        if (columnWin == 2)
        {
            winMessageParameter(columnWinArray[0])
        }

        if (rowWin == 2)
        {
            winMessageParameter(playingField->field[i][0])
        }
    }

    //Check for draw
    if (gameData->gameEnd == 0)
    {

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
            printf("%sDraw!\n", slashTFormat);
            gameData->gameEnd = 1;
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
    printCurrentField(&playingField, &gameData);
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
                turnOnColoredText(32);
                printf("%sFirst player move!\n", slashTFormat);
                turnOffAnyColor;
                playerMove(&gameData, &playingField);
            } else
            {
                //another player move
                turnOnColoredText(31);
                printf("%sSecond player move!\n", slashTFormat);
                turnOffAnyColor;
                playerMove(&gameData, &playingField); // when second player placed his icon the turn goes to first player
            }
        }

        checkForEnding(&gameData, &playingField);

    }
    turnOnColoredText(1);
    printf("%sEnd of game!\n", slashTFormat);
    turnOffAnyColor;

    return 0;
}






