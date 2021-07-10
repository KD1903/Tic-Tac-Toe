#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<time.h>

void onePlayer();
void twoPlayer();
int playComp(int co, char p1, char p2);
void printBoard(char p1, char p2);
int takeInput(char p1, char p2);
int updateBoard(int n, char p1, char p2);
int checkWin();

char box[3][3];
int i,j, player=1;

/////////////////////////////////////////////////////////   MAIN FUNCTION

int main() {
    char choise='y', gamemode;

    while(1) {

        for(i=0; i<3; i++) {
            for(j=0; j<3; j++) {
                box[i][j] = '-';
            }
        }

        system("clear");
        printf("TIC - TAC - TOE\n");
        printf("================\n");

        printf("Enter your choise\n");
        printf("1. One Player (vs computer)\n2. Two Player\n3. Exit\n");
        scanf("%s", &gamemode);

        if(gamemode == '1')
            onePlayer();

        else if(gamemode == '3') {
            printf("Thanks for playing!!\n\n");
            break;
        }
        else
            twoPlayer();

        printf("\nDo you want to play again? (y or n)\n");
        scanf("%s", &choise);

        if(choise == 'n') {
            printf("Thanks for playing!!\n\n");
            break;
        }
        else
            continue;
    }

    return 0;
}

//////////////////////////////////////////////////////////////// One Player

void onePlayer() {
    char player1='O', player2='X';
    int count = 0, temp;

    printf("Enter symbol you want to take: ");

    while(1) {
        scanf("%s", &player1);

        if(player1 == 'o' || player1 == 'O') {
            player1 = 'O';
            player2 = 'X';
            break;
        }
        else if(player1 == 'x' || player1 == 'X') {
            player1 = 'X';
            player2 = 'O';
            break;
        }
        else
            printf("Enter a valid symbol (O or X): ");
    }

    srand(time(0));
    player = (rand() % 2) + 1;
    temp = player;
    
    if(player == 2) {
        playComp(count, player1, player2);
        player = 1;
        count++;
    }

    while(count < 9) {
        printBoard(player1, player2);

        printf("Player 1: %c\n", player1);
        printf("Enter number(1 to 9) to play\n");
        printf("Enter 0 to exit\n");

        if(takeInput(player1, player2) == 0)
            break;

        count++;

        if(count > 4) {
            if(checkWin() == 1) {
                printBoard(player1, player2);
                printf("Player %d: %c won\n", player, player1);
                count++;
                break;
            }
        }

        if(count == 9 && temp == 1) {
            break;
        }
        else {
            if(player == 1)
                player = 2;
            else
                player = 1;

            if(playComp(count, player1, player2) == 1) {
                count++;
                break;
            }

            count++;

            if(player == 1)
                player = 2;
            else
                player = 1;
        }
    }

    if(count == 9) {
        printBoard(player1, player2);
        printf("Match Draw\n");
    }
    
}

///////////////////////////////////////////////////////////////////// Computer's Turn

int playComp(int co, char p1, char p2) {
    int corner[4] = {1, 3, 7, 9}, num, x, y;

    if(co < 3) {
        if(box[1][1] == '-')
            box[1][1] = p2;

        else {
            if(box[0][0] != '-' || box[2][2] != '-') {
                box[0][2] = p2;
            }

            else if(box[0][2] != '-' || box[2][0] != '-') {
                box[0][0] = p2;
            }

            else {
                num = corner[(rand() % 4)];
                updateBoard(num-1, p1, p2);
            }
        }
    }
    else {
        ////////////////////////////////////////////////To win
        for(x=0; x<3; x++) {
            for(y=0; y<3; y++) {

                if(box[x][y] == '-') {

                    box[x][y] = p2;

                    if(checkWin() == 1) {
                        printBoard(p1, p2);
                        printf("Computer won");
                        return 1;
                    }
                    else {
                        box[x][y] = '-';
                    }
                }
            }
        }

        //////////////////////////////////////////////////To defend
        for(x=0; x<3; x++) {
            for(y=0; y<3; y++) {

                if(box[x][y] == '-') {

                    box[x][y] = p1;

                    if(checkWin() == 1) {
                        box[x][y] = p2;
                        return 0;
                    }
                    else {
                        box[x][y] = '-';
                    }
                }
            }
        }

        if(box[1][1] == p1 && (box[0][0] == p1 || box[2][2] == p1)) {
            if(box[0][2] == '-') {
                box[0][2] = p2;
                return 0;
            }
            else if(box[2][0] == '-') {
                box[2][0] = p2;
                return 0;
            }
        }
        else if(box[1][1] == p1 && (box[2][0] == p1 || box[0][2] == p1)) {
            if(box[0][0] == '-') {
                box[0][0] = p2;
                return 0;
            }
            else if(box[2][2] == '-') {
                box[2][2] = p2; 
                return 0;
            }
        }

        while(1) {
            for(x=0; x<3; x++) {
                for(y=0; y<3; y++) {
                    
                    if(box[x][y] == '-') {
                        box[x][y] = p2;
                        return 0;
                    }
                }
            }
        }
    }
    return 0;
}

////////////////////////////////////////////////////////////////// Two Player

void twoPlayer() {
    char player1 = 'O', player2 = 'X';
    int count = 0;

    printf("Enter symbol you want to take\n");
    printf("Player 1: ");

    while(1) {
        scanf("%s", &player1);

        if(player1 == 'o' || player1 == 'O') {
            player1 = 'O';
            player2 = 'X';
            break;
        }
        else if(player1 == 'x' || player1 == 'X') {
            player1 = 'X';
            player2 = 'O';
            break;
        }
        else
            printf("Enter a valid symbol (O or X): ");
    }
    
    while(count < 9) {
        printBoard(player1, player2);

        if(player == 1)
            printf("Player %d: %c\n", player, player1);
        else
            printf("Player %d: %c\n", player, player2);

        printf("Enter number(1 to 9) to play\n");
        printf("Enter 0 to exit\n");

        if(takeInput(player1, player2) == 0)
            break;

        count++;

        if(count > 4) {
            if(checkWin() == 1) {
                printBoard(player1, player2);

                if(player == 1)
                    printf("Player %d: %c won\n", player, player1);
                else
                    printf("Player %d: %c won\n", player, player2);

                count++;
                break;
            }
        }

        if(player == 1)
            player = 2;
        else
            player = 1;
    }
    
    if(count == 9) {
        printBoard(player1, player2);
        printf("Match Draw\n");
    }
}

//////////////////////////////////////////////////////////////// Take input from user and update in board

int takeInput(char p1, char p2) {
    char inp_num[2];
    int num;

    while(1) {
        scanf("%s", inp_num);

        if(strlen(inp_num) > 1) {
            printf("Enter a valid number(1 to 9): ");
            continue;
        }

        if(inp_num[0] == '0')
            return 0;

        if(inp_num[0] < '1' || inp_num[0] > '9') {
            printf("Enter a valid number(1 to 9): ");
            continue;
        }
  
        num = inp_num[0] - '0';

        if(updateBoard(num-1, p1, p2) == 1) {
            continue;
        }
        else
            return 1;
    }
}

//////////////////////////////////////////////////////////////// Update board 

int updateBoard(int n, char p1, char p2) {
    int count = 0;

    while(1) {
        if(n-3 < 0) {
            if(box[count][n] == '-') {
                if(player == 1) {
                    box[count][n] = p1;
                    return 0;
                }
                else {
                    box[count][n] = p2;
                    return 0;
                }
            }
            else {
                printf("It's already used, try something else: ");
                return 1;
            }                                    
        }
        else {
            n -= 3;
            count++;
        }
    }
}

//////////////////////////////////////////////////////////////// Check Win

int checkWin() {
    if(box[0][0] != '-' && (box[0][0] == box[1][1] && box[1][1] == box[2][2]))
        return 1;

    if(box[0][2] != '-' && (box[0][2] == box[1][1] && box[1][1] == box[2][0]))
        return 1;
    
    for(i=0; i<3; i++) {
        if(box[i][0] != '-' && (box[i][0] == box[i][1] && box[i][1] == box[i][2]))
            return 1;
    }

    for(i=0; i<3; i++) {
        if(box[0][i] != '-' && (box[0][i] == box[1][i] && box[1][i] == box[2][i]))
            return 1;
    }

    return 0;
}

//////////////////////////////////////////////////////////////// Print Board

void printBoard(char p1, char p2) {
    system("clear");

    printf("Player 1: %c\n", p1);
    printf("Player 2: %c\n\n", p2);

    for(i=0; i<3; i++) {
        for(j=0; j<3; j++) {
            if(box[i][j] == '-')
                printf(" []  ");
            else
                printf(" %c   ", box[i][j]);
        }
        printf("\n\n");
    }
}
