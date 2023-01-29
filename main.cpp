#include <iostream>
#include <sstream>
#include <unistd.h>

using namespace std;

void ClearScreen() {
    #ifdef _WIN32
        system("cls");
    #else
        system ("clear");
    #endif
}

void DrawScreen(short int screen[7][6]) {
    //clear screen
    ClearScreen();

    //draww
    cout<<"\n\n";
    for (int i=5;i>-1;i--) {
        cout << "\t|";
        for (int j=0;j<7;j++) {
            /**if (screen[j][i] == 0) cout<<" -";
            else if (screen[j][i] == 10) cout<<" O";
            else if (screen[j][i] == 20) cout<<" 0";
            else cout<<" "<<screen[j][i];*/
            if (screen[j][i] == 10) cout<<" O";
            else if (screen[j][i] == 20) cout<<" X";
            else cout<<" -";
        }
        cout << "\t|" << endl;
    }
    cout << "\t^'^'^'^'^'^'^'^'^\n\t  1 2 3 4 5 6 7\n\n";
}

void DrawScreenFloppoBotto(short int screen[7][6]) {
    //clear screen
    ClearScreen();

    //draww
    cout<<"\n\n";
    for (int i=5;i>-1;i--) {
        cout << "\t|";
        for (int j=0;j<7;j++) {
            /**if (screen[j][i] == 0) cout<<" -";
            else if (screen[j][i] == 10) cout<<" O";
            else if (screen[j][i] == 20) cout<<" 0";
            else cout<<" "<<screen[j][i];*/
            if (screen[j][i] == 10) cout<<" O";
            else if (screen[j][i] == 20) cout<<" X";
            else cout<<" -";
        }
        cout << "\t|" << endl;
    }
    cout << "\t ^'^'^'^'^'^'^'^'^\n\t  1 2 3 4 5 6 7\n\n";
}

short int checkWeight(short int model[7][6], short int x, short int y, short int checkType) {
    //check for player stuff (represented by short int 10)
    int checkFor = 10;

    //but if checkType 4, 5, 6, 7 then check for computer stuff
    if (checkType > 3) {
        checkType %= 4;
        checkFor = 20;
    }
    short int computerCalculation = 0;

    //checkTypes: -5=check all, 0=Horizontal, 1=Vertical, 2=/diagonal, 3=\diagonal
    if (checkType == -5) {
        //reuse checkType to store the max value instead of type
        checkType = 0;

        //check
        for (int i=0;i<4;i++) {
            //reset computerCalculation for this cycle
            computerCalculation = 0;
            switch(i) {
                case 0:
                    for (int i=x-1;i>=0;i--) {
                        if (model[i][y]==checkFor) computerCalculation++; else break;
                    }
                    for (int i=x+1;i<7;i++) {
                        if (model[i][y]==checkFor) computerCalculation++; else break;
                    }
                    break;
                case 1:
                    for (int i=y-1;i>=0;i--) {
                        if (model[x][i]==checkFor) computerCalculation++; else break;
                    }
                    for (int i=y+1;i<6;i++) {
                        if (model[x][i]==checkFor) computerCalculation++; else break;
                    }
                    break;
                case 2:
                    for (int i=-1;x+i>=0&&y+i>=0;i--) {
                        if (model[x+i][y+i]==checkFor) computerCalculation++; else break;
                    }
                    for (int i=1;x+i<7&&y+i<6;i++) {
                        if (model[x+i][y+i]==checkFor) computerCalculation++; else break;
                    }
                    break;
                case 3:
                    for (int i=-1;x+i>=0&&y-i<6;i--) {
                        if (model[x+i][y-i]==checkFor) computerCalculation++; else break;
                    }
                    for (int i=1;x+i<7&&y-i>=0;i++) {
                        if (model[x+i][y-i]==checkFor) computerCalculation++; else break;
                    }
                    break;
            }
            //if the current computerCalculation is bigger, then make the total go up
            if (checkType < computerCalculation) checkType = computerCalculation;
        }
        //set computerCalculation to the total so it will be returned
        computerCalculation = checkType;

    } else
    switch(checkType) {
        case 0:
            for (int i=x-1;i>=0;i--) {
                if (model[i][y]==checkFor) computerCalculation++; else break;
            }
            for (int i=x+1;i<7;i++) {
                if (model[i][y]==checkFor) computerCalculation++; else break;
            }
            break;
        case 1:
            for (int i=y-1;i>=0;i--) {
                if (model[x][i]==checkFor) computerCalculation++; else break;
            }
            for (int i=y+1;i<6;i++) {
                if (model[x][i]==checkFor) computerCalculation++; else break;
            }
            break;
        case 2:
            for (int i=-1;x+i>=0&&y+i>=0;i--) {
                if (model[x+i][y+i]==checkFor) computerCalculation++; else break;
            }
            for (int i=1;x+i<7&&y+i<6;i++) {
                if (model[x+i][y+i]==checkFor) computerCalculation++; else break;
            }
            break;
        case 3:
            for (int i=-1;x+i>=0&&y-i<6;i--) {
                if (model[x+i][y-i]==checkFor) computerCalculation++; else break;
            }
            for (int i=1;x+i<7&&y-i>=0;i++) {
                if (model[x+i][y-i]==checkFor) computerCalculation++; else break;
            }
            break;
    }
    return computerCalculation;
}

int main()
{
    short int GameScreen[7][6] = {0};
    short int ComputerView[7][6][4] = {0};
    short int fakescreen[7][6];
    int input = 0;
    string directInput = "";
    bool playerTurn = true;
    int possibleChoices[7][2];
    int selection = 4;
    int animationlocation[7][2];
    bool exitfor = false;

    for (bool gameRunning=true;gameRunning;) {
        for (bool playing = true;playing;) {
            //draw screen
            DrawScreen(GameScreen);

            //if playerturn do this
            if (playerTurn) {
                cout<<"\t\tIt is your turn. Where do you choose to play?\n\t";
                input = -1;
                while (input < 1 || input > 7) {
                    cin >> directInput;
                    istringstream in(directInput);
                    if (in >> input && in.eof()) {
                        input = stoi(directInput);
                        if (input < 1 || input > 7) cout << "\t\tINVALID RESPONSE. Using numbers '1' to '7', which spot do you choose?\n\t";
                        else if (GameScreen[input-1][5] > 5) {
                            cout << "\t\tINVALID RESPONSE. COLUMN IS FULL. Which other spot do you choose?\n\t";
                            input = -1;
                        }
                    } else cout << "\t\tINVALID RESPONSE. Using numbers '1' to '7', which spot do you choose?\n\t";
                }

                //place input (CHART: [10 = player], [20 = computer], [1, 2, 3 = computer data priority ranking])
                //animation
                for (int x=0;x<7;x++) for(int y=0;y<6;y++) fakescreen[x][y] = GameScreen[x][y];
                for (int i=5;i>-1;i--) {
                    fakescreen[input-1][i] = 10;
                    DrawScreen(fakescreen);
                    sleep(0.5);
                    if (i==0 || GameScreen[input-1][i-1] > 9) {
                        GameScreen[input-1][i] = 10;
                        break;
                    }
                    fakescreen[input-1][i] = 0;
                }

                //set player turn off so that computer can play next round
                playerTurn = false;
            } else {

                //wait a little bit
                sleep(1);

                //COMPUTERIN TIME SO SCAN OVER EVERYTHING(i know computin is a word but just let me have this)
                for (int i=0;i<7;i++)
                    for(int j=0;j<6;j++) {
                        //only check if empty
                        if (GameScreen[i][j] < 7) {
                            //computerview 0=Horizontal, 1=Vertical, 2=/diagonal, 3=\diagonal
                            ComputerView[i][j][0] = checkWeight(GameScreen, i, j, 0);
                            ComputerView[i][j][1] = checkWeight(GameScreen, i, j, 1);
                            ComputerView[i][j][2] = checkWeight(GameScreen, i, j, 2);
                            ComputerView[i][j][3] = checkWeight(GameScreen, i, j, 3);

                            //check which one is highest for the display
                            GameScreen[i][j] = ComputerView[i][j][0];
                            if (ComputerView[i][j][1] > GameScreen[i][j]) GameScreen[i][j] = ComputerView[i][j][1];
                            if (ComputerView[i][j][2] > GameScreen[i][j]) GameScreen[i][j] = ComputerView[i][j][2];
                            if (ComputerView[i][j][3] > GameScreen[i][j]) GameScreen[i][j] = ComputerView[i][j][3];
                            if (GameScreen[i][j] < 0) GameScreen[i][j] = 0;
                        }
                        //quickly clear screen and draw
                        //DrawScreen(GameScreen);
                    }
                //Computer selecting the next spot in which to move
                selection = rand() % 7;
                //use input variable as failsafe as computer checks all options
                input = 0;
                while (GameScreen[selection][5] > 9 && GameScreen[selection][possibleChoices[selection][1]+1]) selection = rand() % 7;
                for (int i=0;i<7;i++) for (int y=0;y<6;y++) if (GameScreen[i][y] < 7) {possibleChoices[i][0] = GameScreen[i][y];possibleChoices[i][1]=y;break;}
                for (int i=0;i<7&&input<14;i++) if (GameScreen[selection][5] > 9 || (possibleChoices[i][0] > possibleChoices[selection][0] && GameScreen[i][5] < 9) || checkWeight(GameScreen, i, possibleChoices[i][1]+1, -5) >= 3) {
                    //check all weights (type = -5)
                    if (checkWeight(GameScreen, i, possibleChoices[i][1]+1, -5) < 3) {
                        //debuggy thingy cout<<checkWeight(GameScreen, i, possibleChoices[i][1]+1, -5)<<endl;sleep(1);
                        selection = i;
                    } else if (selection == i) {
                        //dang it right above the randomly selected spot is a potential spot in which the opponent wins :(
                        //guess I'll set the selection to some random other spot and then start over
                        while (selection == i)selection = (selection + 1) % 7;
                        i=0; input++;
                    }
                }

                //check if can get 4 in row rn if so then take it now
                //possibleChoices[][0] = weight of position at x value, possibleChoices[][1] y value
                if (possibleChoices[selection][0] < 3) for (int i=0;i<7;i++) for(int t=4;t<8;t++) if (possibleChoices[i][0] < 10 && checkWeight(GameScreen, i, possibleChoices[i][1], t) >= 3 && GameScreen[i][possibleChoices[i][1]] < 9) selection = i;
                //else for (int i=0;i<7;i++) for(int t=4;t<8;t++) if (possibleChoices[i][0] < 10 && checkWeight(GameScreen, i, possibleChoices[i][1], t) >= 3 && GameScreen[i][5] < 9) selection = i;
                for (int i=0;i<7;i++) for(int t=4;t<8;t++) if (checkWeight(GameScreen, i, possibleChoices[i][1], t) >= 3 && GameScreen[i][5] < 9) selection = i;

                //now if its full then try randomly because why not
                for(int i=0;GameScreen[selection][5] > 9 && i<8;i++) selection = (selection+1)%7;

                //set position of computer thing to that spot
                //animation
                for (int x=0;x<7;x++) for(int y=0;y<6;y++) fakescreen[x][y] = GameScreen[x][y];
                for (int i=5;i>-1;i--) {
                    fakescreen[selection][i] = 20;
                    DrawScreen(fakescreen);
                    sleep(0.5);
                    if (i==0 || GameScreen[selection][i-1] > 9) {
                        GameScreen[selection][i] = 20;
                        break;
                    }
                    fakescreen[selection][i] = 0;
                }

                //clear screen, draw and wait a while
                DrawScreen(GameScreen);
                //cout<<possibleChoices[selection][0]<<endl;
                sleep(1);

                //set player turn on so that player can play next round
                playerTurn = true;
            }

            //check between turns if anyone got 4 in a row
            for (int x=0;x<7&&playing;x++)
                    for(int y=0;y<6&&playing;y++)
                        if (GameScreen[x][y] == 10) {
                            for(int t=0;t<4;t++)
                                if (checkWeight(GameScreen, x, y, t) >= 3) {
                                    //player won so set playerTurn to true
                                    animationlocation[0][0] = x;
                                    animationlocation[0][1] = y;
                                    playerTurn = true;
                                    playing = false;
                                }
                        } else if (GameScreen[x][y] == 20) for(int t=4;t<8;t++)
                            if (checkWeight(GameScreen, x, y, t) >= 3) {
                                //player lost so set playerTurn to false
                                animationlocation[0][0] = x;
                                animationlocation[0][1] = y;
                                playerTurn = false;
                                playing = false;
                            }
            //check if there was a tie
            exitfor = false;
            for (int x=0;x<7&&!exitfor;x++) if (GameScreen[x][5]<9) {
                exitfor = true;
            } else if (x==6) {
                //selection = 100 is the code for a tie
                playing = false;
                selection = 100;
            }

        } //end game loop

        //ending animation
        /**for (int i=0;i<4;i++) {
            for (int x=animationlocation[0];x<7;x++)
                if (GameScreen[x][animationlocation[1]]==4)*/
        short int nextspot = 1;
        if (playerTurn) { for (int x=0;x<7;x++) for(int y=0;y<6;y++) for(int t=0;t<4;t++) if (GameScreen[x][y] == 10 && checkWeight(GameScreen, x, y, t) >= 3) {
                animationlocation[nextspot][0] = x;
                animationlocation[nextspot][1] = y;
                nextspot++;
            }
        } else for (int x=0;x<7;x++) for(int y=0;y<6;y++) for(int t=4;t<8;t++) if (GameScreen[x][y] == 20 && checkWeight(GameScreen, x, y, t) >= 3) {
            animationlocation[nextspot][0] = x;
            animationlocation[nextspot][1] = y;
            nextspot++;
        }

        //create screen with the winning pieces missing
        for (int x=0;x<7;x++) for(int y=0;y<6;y++) fakescreen[x][y] = GameScreen[x][y];
        for (int i=0;i<nextspot;i++) {
            fakescreen[animationlocation[i][0]][animationlocation[i][1]] = 0;
        }

        //if there was a tie then selection is 100
        if (selection == 100) {
            DrawScreen(GameScreen);
            cout<<"\n\n\tIt's a tie!"<<endl;
            sleep(1);
        } else if (playerTurn) for (int i=0;i<9;i++) {
            //if player won, say you won on a loop while recycling the playerTurn boolean
            if (playerTurn) DrawScreen(GameScreen);
            else DrawScreen(fakescreen);
            cout << "\n\n\tYou win! Congratulations, winner!"<<endl;
            usleep(500000);
            playerTurn = !playerTurn;
        } else for (int i=0;i<9;i++) {
            //if player lost, say you lost on a loop while recycling the playerTurn boolean
            playerTurn = !playerTurn;
            if (playerTurn) DrawScreen(GameScreen);
            else DrawScreen(fakescreen);
            cout << "\n\n\tYou lose! Too bad!"<<endl;
            usleep(500000);
        }
        cout<<"\tWould you like to play again? (1=Yes, 2=Exit)\n\t";
        cin >> input;
        if (input % 2 == 0) gameRunning = false;
        else {
            //wait a bit before starting
            DrawScreenFloppoBotto(GameScreen);
            usleep(80000);

            for (int fallloop=0;fallloop<6;fallloop++) {
                //falloop animation
                for (int x=0;x<7;x++) for(int y=0;y<5;y++) GameScreen[x][y] = GameScreen[x][y+1];
                if(fallloop == 0) {
                    GameScreen[0][5]=0;GameScreen[1][5]=0;GameScreen[2][5]=0;GameScreen[3][5]=0;GameScreen[4][5]=0;GameScreen[5][5]=0;GameScreen[6][5]=0;
                }

                DrawScreenFloppoBotto(GameScreen);
                switch(fallloop){
                    case 0: usleep(100000); break;
                    case 1: usleep(50000); break;
                    case 2: usleep(30000); break;
                    case 3: usleep(10000); break;
                    case 4: usleep(5000); break;
                    case 5: usleep(500000); break;
                }
            }
        }
        playerTurn = true;
    }

    return 0;
} // end main method
