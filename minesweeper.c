// Assignment 1 20T1 COMP1511: Minesweeper
// minesweeper.c
//
// This program was written by JAMES LEE (z5311868)
// 16/03/20 
//
// Version 1.0.0 (2020-03-08): Assignment released.
// Version 1.0.1 (2020-03-08): Fix punctuation in comment.
// Version 1.0.2 (2020-03-08): Fix second line of header comment to say minesweeper.c

#include <stdio.h>
#include <stdlib.h>

// Possible square states.
#define VISIBLE_SAFE    0
#define HIDDEN_SAFE     1
#define HIDDEN_MINE     2

// The size of the starting grid.
#define SIZE 8

// The possible command codes.
#define DETECT_ROW              1
#define DETECT_COL              2
#define DETECT_SQUARE           3
#define REVEAL_SQUARE           4
#define GAMEPLAY_MODE           5
#define DEBUG_MODE              6
#define REVEAL_RADIAL           7

// Add any extra #defines here.

void initialise_field(int minefield[SIZE][SIZE]);
void print_debug_minefield(int minefield[SIZE][SIZE]);
void print_gameplaymode_minefield(int minefield[SIZE][SIZE]); 
void print_gameplaymode_minefieldGAMEOVER(int minefield[SIZE][SIZE]);

int detect_square(int row, int column, int side_length, 
                  int minefield[SIZE][SIZE]); 
int gameover_gameplayMode(int row, int column, int minefield[SIZE][SIZE]);
void reveal_square(int row, int column, int minefield[SIZE][SIZE], 
                   int noOfMines); 
void reveal_square_gameplay(int row, int column, int minefield[SIZE][SIZE], 
                            int noOfMines);


// Place your function prototyes here.



int main(void) {
    int minefield[SIZE][SIZE];
    initialise_field(minefield);
    printf("Welcome to minesweeper!\n");
    printf("How many mines? ");
    
    // TODO: Scan in the number of pairs of mines.
   
    int noOfMines;
    scanf("%d", &noOfMines);
    
    printf("Enter pairs:\n");
    
    // TODO: Scan in the pairs of mines and place them on the grid.
 
    int counter_one = 0; 
    int row = 0;
    int column = 0;
    while (counter_one < noOfMines)  { 
        scanf("%d", &row), scanf("%d", &column); 
          
        if (row >= 8 || column >= 8 || row < 0 || column < 0)  {
        //This just makes sure no values outside the size of the 
        //minefield gets registered
        }
        else  {    
            minefield[row][column] = HIDDEN_MINE;                
        }    
        counter_one++;
    }
   
    printf("Game Started\n");
   
    print_debug_minefield(minefield);

    // TODO: Scan in commands to play the game until the game ends.
    // A game ends when the player wins, loses, or enters EOF (Ctrl+D).
    // You should display the minefield after each command has been processed.
    int hint_counter = 0;   
    int userInput;     
    
    while(scanf("%d",&userInput) == 1)  {
        
        
        if (hint_counter >= 3 && scanf("%d",&userInput) == 1)  {
            printf("Help already used\n"); 
            print_debug_minefield(minefield);                    
        }       
        
        if (userInput == DETECT_ROW && hint_counter < 3)  {
            
            scanf("%d", &row);
        
            int counter_two = 0;
            int cycleColumn = 0;
            int numOfmines_row = 0; 
       
            while(counter_two < SIZE)  {                  
                if (minefield[row][cycleColumn] == 2)  {                    
                numOfmines_row++;                                   
                }               
                cycleColumn++; 
                counter_two++;                               
            }
        
            printf("There are %d mine(s) in row %d\n", numOfmines_row, row);           
            
            print_debug_minefield(minefield);   
            hint_counter++;            
        }       
        if (userInput == DETECT_COL && hint_counter < 3)  {
        
            scanf("%d", &column);
        
            int counter_three = 0; 
            int cycleRow = 0;
            int numOfmines_col = 0;
       
            while (counter_three < SIZE)  {          
                if (minefield[cycleRow][column] == 2)  {
                    numOfmines_col++;
                }
                cycleRow++;
                counter_three++;
            }
            printf("There are %d mine(s) in column %d\n", 
                    numOfmines_col, column);
           
            print_debug_minefield(minefield);
            hint_counter++;
        }
        if (userInput == DETECT_SQUARE && hint_counter < 3)  {
            int side_length = 0;   
            int detectedMines = 0;              
           
            scanf("%d", &row), scanf("%d", &column), scanf("%d", &side_length);
            //User enters the center of the square and size of square
            
            detectedMines = detect_square(row,column,side_length,minefield);            
            //Function detects mines given the input, and returns 
            //the number of mines              
                                          
            printf("There are %d mine(s) in the square centered at row %d," 
                    "column %d of size %d\n",detectedMines, row, column,     
                    side_length);           
            
            print_debug_minefield(minefield);
            hint_counter++;
        }
        if (userInput == REVEAL_SQUARE)  { 
            
            scanf("%d", &row), scanf("%d", &column);
            
            reveal_square(row, column, minefield, noOfMines);                         
        }
        if (userInput == GAMEPLAY_MODE)  {
            
            printf("Gameplay mode activated\n");
            print_gameplaymode_minefield(minefield);
            
            int gameoverSignal = 0;
            while (scanf("%d",&userInput) == 1  && gameoverSignal != 1)  {
                
                if (userInput == DEBUG_MODE)  {
                    printf("Debug mode activated\n"); 
                    print_debug_minefield(minefield);
                    while (scanf("%d",&userInput) == 1)  {                
                        if (userInput == REVEAL_SQUARE)  {
                            
                            scanf("%d", &row), scanf("%d", &column);
            
                            reveal_square(row, column, minefield, noOfMines); 
                        }
                   
                    }
                }
                    
                    
                
                if (userInput == REVEAL_SQUARE)  { 
                                       
                    scanf("%d", &row), scanf("%d", &column);
            
                    reveal_square_gameplay(row, column, minefield, noOfMines);
                       
                    gameoverSignal = gameover_gameplayMode(row, column, 
                                                           minefield);
                    
                    if (gameoverSignal == 1)  {
                    
                    }
                    else  {
                        print_gameplaymode_minefield(minefield);     
                    }                 
                }        
            
            } 
        }  
    }       
    return 0;
}

// Set the entire minefield to HIDDEN_SAFE.
void initialise_field(int minefield[SIZE][SIZE]) {
    int i = 0;
    while (i < SIZE) {
        int j = 0;
        while (j < SIZE) {
            minefield[i][j] = HIDDEN_SAFE;
            j++;
        }
        i++;
    }
}

// Print out the actual values of the minefield.
void print_debug_minefield(int minefield[SIZE][SIZE]) {
    int i = 0;
    while (i < SIZE) {
        int j = 0;
        while (j < SIZE) {
            printf("%d ", minefield[i][j]);
            j++;
        }
        printf("\n");
        i++;
    }
}
//Stage 3 function indicates when game is over
int gameover_gameplayMode(int row, int column, int minefield[SIZE][SIZE])  {
    int var = 0; 
    if (minefield[row][column] == 2)  {
       var = 1; 
    }
    return var; 
}


//Stage 3 function print minefield in gameplay mode when it's GAMEOVER
void print_gameplaymode_minefieldGAMEOVER(int minefield[SIZE][SIZE])  {
    printf("xx\n");
    printf("/\\\n"); 
    printf("    ");
    printf("00");
    printf(" ");
    printf("01"); 
    printf(" ");
    printf("02");
    printf(" ");
    printf("03");
    printf(" ");
    printf("04");
    printf(" ");
    printf("05");
    printf(" ");
    printf("06");
    printf(" ");
    printf("07\n"); 

    printf("   ");
    
    printf("-------------------------\n");
    int i = 0; 
    while (i < SIZE)  {                      
        
        printf("0%d", i);
        printf(" ");
        printf("|"); 
        
        int j = 0;
        while (j < SIZE)  {
                       
            if (minefield[i][j] == 1 && j != 7)  {
                printf("## "); 
            }
            if (minefield[i][j] == 2 && j !=7)  {
                printf("() ");
            }
            if (j == 7 && minefield[i][j] == 1)  {
                printf("##|");
            }
            if (j == 7 && minefield[i][j] == 2)  {
                printf("()|"); 
            }
           
            if (minefield[i][j] == 0)  {
                int row;
                int column;
                int h = 0;
                row = i; 
                column = j; 
                // Check if there are any mines around the given center which 
                //are NOT on the edges
                if (row != 0 && row != 7 && column != 0 && column != 7)  {
                    h = 0;         
                if (minefield[row - 1][column - 1] == 2)  {
                    h++;
                }
                if (minefield[row - 1][column + 1] == 2)  {
                    h++;
                }
                if (minefield[row - 1][column] == 2)  {
                    h++;
                }
                if (minefield[row + 1][column + 1] == 2)  {
                    h++;
                }
                if (minefield[row + 1][column - 1] == 2)  {
                    h++;
                }
                if (minefield[row + 1][column] == 2)  {
                    h++;
                }
                if (minefield[row][column - 1] == 2)  {
                    h++;
                }
                if (minefield[row][column + 1] == 2)  { 
                    h++;
                }
                if (minefield[row][column] == 2)  {
                    h++;            
                }                
            } 
              
            
            //Check if there are any mines within the given center that ARE 
            //on the CORNERs of the minefield 
            //top left corner
                if (row == 0 && column == 0)  {
                    h = 0;
                    if (minefield[row + 1][column] == 2)  {
                        h++;
                    }
                    if (minefield[row + 1][column + 1] == 2)  {
                        h++;
                    }
                    if (minefield[row][column + 1] == 2)  {
                        h++;
                    }
                    if (minefield[row][column] == 2)  {
                        h++;
                    }                                      
                }
            //top right corner
            if (row == 0 && column == 7)  {
                h = 0;
                if (minefield[row + 1][column] == 2)  {
                    h++;
                }
                if (minefield[row + 1][column - 1] == 2)  {
                    h++;
                }
                if (minefield[row][column - 1] == 2)  {
                    h++;
                }
                if (minefield[row][column] == 2)  {
                    h++;
                }
            }
            //bottom left corner 
            if (row == 7 && column == 0)  {
                h = 0;
                if (minefield[row][column] == 2)  {
                    h++;
                }
                if (minefield[row - 1][column] == 2)  {
                    h++;
                }
                if (minefield[row - 1][column + 1] == 2)  {
                    h++;
                }
                if (minefield[row][column + 1] == 2)  {
                    h++;
                }
            }
            //bottom right corner 
            if (row == 7 && column == 7)  {
                h = 0;
                if (minefield[row][column] == 2)  {
                    h++;
                }
                if (minefield[row][column - 1] == 2)  {
                    h++;
                }
                if (minefield[row - 1][column] == 2)  {
                    h++;
                }
                if (minefield[row - 1][column - 1] == 2)  {
                    h++; 
                }
            }
              
              
            //Check if there are any mines within the given center that ARE 
            //on the EDGEs of the minefield 
            //left side 
            if (row != 0 && row != 7 && column == 0)  {
                h = 0;
                if (minefield[row][column] == 2)  {
                    h++;
                }
                if (minefield[row][column + 1] == 2)  {
                    h++;
                }
                if (minefield[row + 1][column] == 2)  {
                    h++;
                }
                if (minefield[row + 1][column + 1] == 2)  {
                    h++;
                }
                if (minefield[row - 1][column] == 2)  {
                    h++;
                }
                if (minefield[row - 1][column + 1] == 2)  {
                    h++;
                }
            }
            //right side 
            if (row != 0 && row != 7 && column == 7)  {
                h = 0;
                if (minefield[row][column] == 2)  {
                    h++;
                }
                if (minefield[row][column - 1] == 2)  {
                    h++;
                }
                if (minefield[row + 1][column] == 2)  {
                    h++; 
                }
                if (minefield[row + 1][column - 1] == 2)  {
                    h++;
                }
                if (minefield[row - 1][column] == 2)  {
                    h++;
                }
                if (minefield[row - 1][column - 1] == 2)  {
                    h++;
                }
            }
            //top side 
            if (row == 0 && column != 0 && column != 7)  {
                h = 0; 
                if (minefield[row][column] == 2)  {
                    h++;
                }
                if (minefield[row][column - 1] == 2)  {
                    h++;
                }
                if (minefield[row][column + 1] == 2)  {
                    h++;
                }
                if (minefield[row + 1][column] == 2)  {
                    h++;
                }
                if (minefield[row + 1][column - 1] == 2)  {
                    h++; 
                }
                if (minefield[row + 1][column + 1] == 2)  {
                    h++;
                }
            }
            //bottom side
            if (row == 7 && column != 0 && column != 7)  {
                h = 0;
                if (minefield[row][column] == 2)  {
                    h++;
                }
                if (minefield[row][column - 1] == 2)  {
                    h++;
                }
                if (minefield[row][column + 1] == 2)  {
                    h++;
                }
                if (minefield[row - 1][column] == 2)  {
                    h++;
                }
                if (minefield[row - 1][column - 1] == 2)  {
                    h++;
                }
                if (minefield[row - 1][column + 1] == 2)  {
                    h++;
                }
            }
           
            if (h > 0)  {
                printf("0%d ", h);             
            }
            if (h == 0)  {
                printf("   ");
            }             
             
            }
            j++;
        }
      
        printf("\n");
        i++;
    }
    printf("   ");
    printf("-------------------------\n");

}

//Stage 3 function reveal square in gameplay mode 
void reveal_square_gameplay(int row, int column, int minefield[SIZE][SIZE], 
                            int noOfMines)  {
    int h = -1;
    int feedback = 0;
    
    if(minefield[row][column] == 2)  {
        printf("Game over\n");
        print_gameplaymode_minefieldGAMEOVER(minefield);    
    }
    
    if (minefield[row][column] != 2)  {                  
        //Checks the squares that aren't the edges of the minefield 
        if (row != 0 && row != 7 && column != 0 && column != 7)  {
            h = 0;         
            if (minefield[row - 1][column - 1] == 2)  {
                h++;
            }
            if (minefield[row - 1][column + 1] == 2)  {
                h++;
            }
            if (minefield[row - 1][column] == 2)  {
                h++;
            }
            if (minefield[row + 1][column + 1] == 2)  {
                h++;
            }
            if (minefield[row + 1][column - 1] == 2)  {
                h++;
            }
            if (minefield[row + 1][column] == 2)  {
                h++;
            }
            if (minefield[row][column - 1] == 2)  {
                h++;
            }
            if (minefield[row][column + 1] == 2)  { 
                h++;
            }
            if (minefield[row][column] == 2)  {
                h++;            
            }                
        } 
          
        
        //Check if there are any mines within the given center that ARE 
        //on the CORNERs of the minefield 
        //top left corner
        if (row == 0 && column == 0)  {
            h = 0;
            if (minefield[row + 1][column] == 2)  {
                h++;
            }
            if (minefield[row + 1][column + 1] == 2)  {
                h++;
            }
            if (minefield[row][column + 1] == 2)  {
                h++;
            }
            if (minefield[row][column] == 2)  {
                h++;
            }                                      
        }
        //top right corner
        if (row == 0 && column == 7)  {
            h = 0;
            if (minefield[row + 1][column] == 2)  {
                h++;
            }
            if (minefield[row + 1][column - 1] == 2)  {
                h++;
            }
            if (minefield[row][column - 1] == 2)  {
                h++;
            }
            if (minefield[row][column] == 2)  {
                h++;
            }
        }
        //bottom left corner 
        if (row == 7 && column == 0)  {
            h = 0;
            if (minefield[row][column] == 2)  {
                h++;
            }
            if (minefield[row - 1][column] == 2)  {
                h++;
            }
            if (minefield[row - 1][column + 1] == 2)  {
                h++;
            }
            if (minefield[row][column + 1] == 2)  {
                h++;
            }
        }
        //bottom right corner 
        if (row == 7 && column == 7)  {
            h = 0;
            if (minefield[row][column] == 2)  {
                h++;
            }
            if (minefield[row][column - 1] == 2)  {
                h++;
            }
            if (minefield[row - 1][column] == 2)  {
                h++;
            }
            if (minefield[row - 1][column - 1] == 2)  {
                h++; 
            }
        }
          
          
        //Check if there are any mines within the given center that ARE 
        //on the EDGEs of the minefield 
        //left side 
        if (row != 0 && row != 7 && column == 0)  {
            h = 0;
            if (minefield[row][column] == 2)  {
                h++;
            }
            if (minefield[row][column + 1] == 2)  {
                h++;
            }
            if (minefield[row + 1][column] == 2)  {
                h++;
            }
            if (minefield[row + 1][column + 1] == 2)  {
                h++;
            }
            if (minefield[row - 1][column] == 2)  {
                h++;
            }
            if (minefield[row - 1][column + 1] == 2)  {
                h++;
            }
        }
        //right side 
        if (row != 0 && row != 7 && column == 7)  {
            h = 0;
            if (minefield[row][column] == 2)  {
                h++;
            }
            if (minefield[row][column - 1] == 2)  {
                h++;
            }
            if (minefield[row + 1][column] == 2)  {
                h++; 
            }
            if (minefield[row + 1][column - 1] == 2)  {
                h++;
            }
            if (minefield[row - 1][column] == 2)  {
                h++;
            }
            if (minefield[row - 1][column - 1] == 2)  {
                h++;
            }
        }
        //top side 
        if (row == 0 && column != 0 && column != 7)  {
            h = 0; 
            if (minefield[row][column] == 2)  {
                h++;
            }
            if (minefield[row][column - 1] == 2)  {
                h++;
            }
            if (minefield[row][column + 1] == 2)  {
                h++;
            }
            if (minefield[row + 1][column] == 2)  {
                h++;
            }
            if (minefield[row + 1][column - 1] == 2)  {
                h++; 
            }
            if (minefield[row + 1][column + 1] == 2)  {
                h++;
            }
        }
        //bottom side
        if (row == 7 && column != 0 && column != 7)  {
            h = 0;
            if (minefield[row][column] == 2)  {
                h++;
            }
            if (minefield[row][column - 1] == 2)  {
                h++;
            }
            if (minefield[row][column + 1] == 2)  {
                h++;
            }
            if (minefield[row - 1][column] == 2)  {
                h++;
            }
            if (minefield[row - 1][column - 1] == 2)  {
                h++;
            }
            if (minefield[row - 1][column + 1] == 2)  {
                h++;
            }
        }
                         
        
        if (h >= 1)  {//the square has adjacent mines
            feedback = 1;
        }
        if (h < 1)  { //the square has no adjacent mines
            feedback = 0;
        }
        
        //when the input of the square has 1 OR MORE adjacent mines 
        if (feedback == 1)  {
            minefield[row][column] = 0;              
        }
        //when the input of the square is not on the edge of the 
        //minefield and has NO adjacent mines
        if (feedback == 0 && row != 0 && row != 7 && column != 0 && 
            column != 7)  {
            minefield[row][column] = 0; 
            minefield[row][column - 1] = 0;
            minefield[row][column + 1] = 0;
            minefield[row + 1][column] = 0; 
            minefield[row + 1][column - 1] = 0; 
            minefield[row + 1][column + 1] = 0; 
            minefield[row - 1][column] = 0; 
            minefield[row - 1][column - 1] = 0;
            minefield[row - 1][column + 1] = 0; 
        }
        //when the input of the square is one of the CORNERS of 
        //the minefield and has NO adjacent mines
        //this one is when [0,0] top left corner
        if (feedback == 0 && row == 0 && column == 0)  {
            minefield[row][column] = 0;
            minefield[row][column + 1] = 0;
            minefield[row + 1][column] = 0;
            minefield[row + 1][column + 1] = 0;
        }
        //this is when [0,7] top right corner
        if (feedback == 0 && row == 0 && column == 7)  {
            minefield[row][column] = 0;
            minefield[row][column - 1] = 0;
            minefield[row + 1][column] = 0;
            minefield[row + 1][column - 1] = 0;       
        }
        //when [7,0] bottom left corner
        if (feedback == 0 && row == 7 && column == 0)  {
            minefield[row][column] = 0;
            minefield[row][column + 1] = 0;
            minefield[row - 1][column] = 0;
            minefield[row - 1][column + 1] = 0;            
        }
        //when [7,7] bottom right corner
        if (feedback == 0 && row == 7 && column == 7)  {
            minefield[row][column] = 0;
            minefield[row][column - 1] = 0;
            minefield[row - 1][column] = 0;
            minefield[row - 1][column - 1] = 0; 
        }
        //if the input is ON the edge but not one of the CORNERS of
        // the minefield and has NO adjacent mines 
        //for top row
        if (feedback == 0 && row == 0 && column != 0 && column != 7)  {
            minefield[row][column] = 0; 
            minefield[row][column - 1] = 0;
            minefield[row][column + 1] = 0; 
            minefield[row + 1][column] = 0;
            minefield[row + 1][column - 1] = 0; 
            minefield[row + 1][column + 1] = 0 ;
        } 
        //for bottom row 
        if (feedback == 0 && row == 7 && column != 0 && column != 7)  { 
            minefield[row][column] = 0; 
            minefield[row][column - 1] = 0;
            minefield[row][column + 1] = 0; 
            minefield[row - 1][column] = 0;
            minefield[row - 1][column - 1] = 0; 
            minefield[row - 1][column + 1] = 0 ;    
        }
        //for left side of minefield
        if (feedback == 0 && column == 0 && row != 0 && row != 7)  {
            minefield[row][column] = 0;
            minefield[row][column + 1] = 0; 
            minefield[row + 1][column] = 0; 
            minefield[row + 1][column + 1] = 0; 
            minefield[row - 1][column] = 0; 
            minefield[row - 1][column + 1] = 0; 
        }
        //right side 
        if (feedback == 0 && column == 7 && row != 0 && row != 7)  {
            minefield[row][column] = 0;
            minefield[row][column - 1] = 0; 
            minefield[row + 1][column] = 0; 
            minefield[row + 1][column - 1] = 0; 
            minefield[row - 1][column] = 0; 
            minefield[row - 1][column - 1] = 0; 
        }

    }
}


//Stage 3 function print gameplay mode
void print_gameplaymode_minefield(int minefield[SIZE][SIZE])  {
    
    printf("..\n");
    printf("\\/\n"); 
    printf("    ");
    printf("00");
    printf(" ");
    printf("01"); 
    printf(" ");
    printf("02");
    printf(" ");
    printf("03");
    printf(" ");
    printf("04");
    printf(" ");
    printf("05");
    printf(" ");
    printf("06");
    printf(" ");
    printf("07\n"); 

    printf("   ");
    
    printf("-------------------------\n");
    int i = 0; 
    while (i < SIZE)  {                      
        
        printf("0%d", i);
        printf(" ");
        printf("|"); 
        
        int j = 0;
        while (j < SIZE)  {
                       
            if (minefield[i][j] == 1 && j != 7)  {
                printf("## "); 
            }
            if (minefield[i][j] == 2 && j !=7)  {
                printf("## ");
            }
            if (j == 7 && minefield[i][j] == 1)  {
                printf("##|");
            }
            if (j == 7 && minefield[i][j] == 2)  {
                printf("##|"); 
            }
           
            if (minefield[i][j] == 0)  {
                int row;
                int column;
                int h = 0;
                row = i; 
                column = j; 
                // Check if there are any mines around the given center which 
                //are NOT on the edges
                if (row != 0 && row != 7 && column != 0 && column != 7)  {
                    h = 0;         
                if (minefield[row - 1][column - 1] == 2)  {
                    h++;
                }
                if (minefield[row - 1][column + 1] == 2)  {
                    h++;
                }
                if (minefield[row - 1][column] == 2)  {
                    h++;
                }
                if (minefield[row + 1][column + 1] == 2)  {
                    h++;
                }
                if (minefield[row + 1][column - 1] == 2)  {
                    h++;
                }
                if (minefield[row + 1][column] == 2)  {
                    h++;
                }
                if (minefield[row][column - 1] == 2)  {
                    h++;
                }
                if (minefield[row][column + 1] == 2)  { 
                    h++;
                }
                if (minefield[row][column] == 2)  {
                    h++;            
                }                
            } 
              
            
            //Check if there are any mines within the given center that ARE on
            // the CORNERs of the minefield 
            //top left corner
            if (row == 0 && column == 0)  {
                h = 0;
                if (minefield[row + 1][column] == 2)  {
                    h++;
                }
                if (minefield[row + 1][column + 1] == 2)  {
                    h++;
                }
                if (minefield[row][column + 1] == 2)  {
                    h++;
                }
                if (minefield[row][column] == 2)  {
                    h++;
                }                                      
            }
            //top right corner
            if (row == 0 && column == 7)  {
                h = 0;
                if (minefield[row + 1][column] == 2)  {
                    h++;
                }
                if (minefield[row + 1][column - 1] == 2)  {
                    h++;
                }
                if (minefield[row][column - 1] == 2)  {
                    h++;
                }
                if (minefield[row][column] == 2)  {
                    h++;
                }
            }
            //bottom left corner 
            if (row == 7 && column == 0)  {
                h = 0;
                if (minefield[row][column] == 2)  {
                    h++;
                }
                if (minefield[row - 1][column] == 2)  {
                    h++;
                }
                if (minefield[row - 1][column + 1] == 2)  {
                    h++;
                }
                if (minefield[row][column + 1] == 2)  {
                    h++;
                }
            }
            //bottom right corner 
            if (row == 7 && column == 7)  {
                h = 0;
                    if (minefield[row][column] == 2)  {
                        h++;
                    }
                    if (minefield[row][column - 1] == 2)  {
                        h++;
                    } 
                    if (minefield[row - 1][column] == 2)  {
                        h++;
                    }
                    if (minefield[row - 1][column - 1] == 2)  {
                        h++; 
                    }
                }
              
              
                //Check if there are any mines within the given center that 
                //ARE on the EDGEs of the minefield 
                //left side 
                if (row != 0 && row != 7 && column == 0)  {
                    h = 0;
                    if (minefield[row][column] == 2)  {
                        h++;
                    }
                    if (minefield[row][column + 1] == 2)  {
                        h++;
                    }
                    if (minefield[row + 1][column] == 2)  {
                        h++;
                    }
                    if (minefield[row + 1][column + 1] == 2)  {
                        h++;
                    }
                    if (minefield[row - 1][column] == 2)  {
                        h++;
                    }
                    if (minefield[row - 1][column + 1] == 2)  {
                        h++;
                    }
                }
                //right side 
                if (row != 0 && row != 7 && column == 7)  {
                    h = 0;
                    if (minefield[row][column] == 2)  {
                        h++;
                    }
                    if (minefield[row][column - 1] == 2)  {
                        h++;
                    }
                    if (minefield[row + 1][column] == 2)  {
                        h++; 
                    }
                    if (minefield[row + 1][column - 1] == 2)  {
                        h++;
                    }
                    if (minefield[row - 1][column] == 2)  {
                        h++;
                    }
                    if (minefield[row - 1][column - 1] == 2)  {
                        h++;
                    }
                }
                //top side 
                if (row == 0 && column != 0 && column != 7)  {
                    h = 0; 
                    if (minefield[row][column] == 2)  {
                        h++;
                    }
                    if (minefield[row][column - 1] == 2)  {
                        h++;
                    }
                    if (minefield[row][column + 1] == 2)  {
                        h++;
                    }
                    if (minefield[row + 1][column] == 2)  {
                        h++;
                    }
                    if (minefield[row + 1][column - 1] == 2)  {
                        h++; 
                    }
                    if (minefield[row + 1][column + 1] == 2)  {
                        h++;
                    }
                }
                //bottom side
                if (row == 7 && column != 0 && column != 7)  {
                    h = 0;
                    if (minefield[row][column] == 2)  {
                        h++;
                    }
                    if (minefield[row][column - 1] == 2)  {
                        h++;
                    }
                    if (minefield[row][column + 1] == 2)  {
                        h++;
                    }
                    if (minefield[row - 1][column] == 2)  {
                        h++;
                    }
                    if (minefield[row - 1][column - 1] == 2)  {
                        h++;
                    }
                    if (minefield[row - 1][column + 1] == 2)  {
                        h++;
                    }
                }               
                if (h > 0)  {
                    printf("0%d ", h);             
                }
                if (h == 0)  {
                    printf("   ");
                }                             
            }
            j++;
        }
          
        printf("\n");
        i++;
    }
    printf("   ");
    printf("-------------------------\n");
    }



//Stage 2 functions 

int detect_square(int row, int column,int side_length, 
                  int minefield[SIZE][SIZE])  {   
    int g = 0;
     
    if (side_length == 3 && row != 0 && row != 7 && column != 0 && column != 7)  
    { 
        //Detect mines in a square with length 3 
        g = -1; 
                                    
        if (minefield[row - 1][column - 1] == 2)  {
            g++;
        }
        if (minefield[row - 1][column + 1] == 2)  {
            g++;
        }           
        if (minefield[row - 1][column] == 2)  {
            g++;
        }
        if (minefield[row + 1][column + 1] == 2)  {
            g++;
        }           
        if (minefield[row + 1][column - 1])  {
            g++;
        }           
        if (minefield[row + 1][column] == 2)  {
            g++;
        }           
        if (minefield[row][column - 1] == 2)  {
            g++;
        }           
        if (minefield[row][column + 1] == 2)  { 
            g++;
        }           
        if (minefield[row][column] == 2)  {
            g++;            
        }                                                 
    }
    if (side_length == 5 && row != 0 && row != 1 && row != 6 && row != 7 
        && column != 0 && column != 1 && column != 6 && column != 7)  {
        //Detect mines in a square with length 5
        g = -1;                  
  
        //Row is fixed on the row below the input row, while columns are cycled through 
        if (minefield[row - 1][column - 1] == 2)  {
            g++;
        }
        if (minefield[row - 1][column + 1] == 2)  {
            g++;
        }
        if (minefield[row - 1][column] == 2)  {
            g++;
        }
        if (minefield[row - 1][column - 2] == 2)  {
            g++;
        }
        if (minefield[row - 1][column + 2] == 2)  {
            g++;
        }
        //starting with the row above center row while cycling columns
        if (minefield[row + 1][column + 1] == 2)  {
            g++;
        }
        if (minefield[row + 1][column - 1])  {
            g++;
        }
        if (minefield[row + 1][column] == 2)  {
            g++;
        }
        if (minefield[row + 1][column + 2] == 2)  {
            g++;
        }
        if (minefield[row + 1][column - 2] == 2)  {
            g++;
        }
        //starting in the center row while cycling columns 
        if (minefield[row][column - 1] == 2)  {
            g++;
        }
        if (minefield[row][column + 1] == 2)  { 
            g++;
        }
        if (minefield[row][column - 2] == 2)  {
            g++;
        }
        if (minefield[row][column + 2] == 2)  {
            g++;
        }
        //testing center point 
        if (minefield[row][column] == 2)  {
            g++;            
        }
        //The top and bottom rows of the 5x5 square
        //starting the first 5 if statements with the very bottom row 
        //cycling columns
        if (minefield[row - 2][column - 2] == 2)  {
            g++; 
        }
        if (minefield[row - 2][column - 1] == 2)  {
            g++;
        }
        if (minefield[row - 2][column + 1] == 2)  {
            g++;
        }
        if (minefield[row - 2][column + 2] == 2)  {
            g++;
        }
        if (minefield[row - 2][column] == 2)  { 
            g++;
        }
        //starting the first 5 if statements with the very top row whilst 
        //cycling columns
        if (minefield[row + 2][column - 2] == 2)  {
            g++; 
        }
        if (minefield[row + 2][column - 1] == 2)  {
            g++;
        }
        if (minefield[row + 2][column + 1] == 2)  {
            g++;
        }
        if (minefield[row + 2][column + 2] == 2)  {
            g++;
        }
        if (minefield[row + 2][column] == 2)  { 
            g++;
        }
    }     

    if (side_length == 7 && row != 0 && row != 1 && row != 6 && row != 7
        && column != 0 && column != 1 && column != 6 && column != 7)  { 
        //Detecting mines within a square with length 7
        g = -1;
        //the row below center row
        if (minefield[row - 1][column - 1] == 2)  {
            g++;
        }
        if (minefield[row - 1][column + 1] == 2)  {
            g++;
        }
        if (minefield[row - 1][column] == 2)  {
            g++;
        }
        if (minefield[row - 1][column - 2] == 2)  {
            g++;
        }
        if (minefield[row - 1][column + 2] == 2)  {
            g++;
        }
        if (minefield[row - 1][column - 3] == 2)  {
            g++;
        }
        if (minefield[row - 1][column + 3] == 2)  {
            g++;
        }
        //starting with the row above center row while cycling columns
        if (minefield[row + 1][column + 1] == 2)  {
            g++;
        }
        if (minefield[row + 1][column - 1])  {
            g++;
        }
        if (minefield[row + 1][column] == 2)  {
            g++;
        }
        if (minefield[row + 1][column + 2] == 2)  {
            g++;
        }
        if (minefield[row + 1][column - 2] == 2)  {
            g++;
        }
        if (minefield[row + 1][column + 3] == 2)  {
            g++; 
        }
        if (minefield[row + 1][column - 3] == 2)  {
            g++;
        }           
        //starting in the center row while cycling columns 
        if (minefield[row][column - 1] == 2)  {
            g++;
        }
        if (minefield[row][column + 1] == 2)  { 
            g++;
        }
        if (minefield[row][column - 2] == 2)  {
            g++;
        }
        if (minefield[row][column + 2] == 2)  {
            g++;
        }
        if (minefield[row][column - 3] == 2)  {
            g++;
        }
        if (minefield[row][column + 3] == 2)  {
            g++;
        }
        //testing center point 
        if (minefield[row][column] == 2)  {
            g++;            
        }
        //The second bottom and top rows of the 7x7 square from the center row
        //starting the first 7 if statements with the second bottom row 
        //cycling columns
        if (minefield[row - 2][column - 3] == 2)  { 
            g++;
        }
        if (minefield[row - 2][column - 2] == 2)  {
            g++; 
        }
        if (minefield[row - 2][column - 1] == 2)  {
            g++;
        }
        if (minefield[row - 2][column + 1] == 2)  {
            g++;
        }
        if (minefield[row - 2][column + 2] == 2)  {
            g++;
        }
        if (minefield[row - 2][column + 3] == 2)  {
            g++;
        }
        if (minefield[row - 2][column] == 2)  { 
            g++; 
        }         
        //starting the first 7 if statements with the second top row whilst 
        //cycling columns
        if (minefield[row + 2][column - 3] == 2)  {
            g++;
        }
        if (minefield[row + 2][column - 2] == 2)  {
            g++; 
        }
        if (minefield[row + 2][column - 1] == 2)  {
            g++;
        }
        if (minefield[row + 2][column + 1] == 2)  {
            g++;
        }
        if (minefield[row + 2][column + 2] == 2)  {
            g++;
        }
        if (minefield[row + 2][column + 3] == 2)  {
            g++;
        }
        if (minefield[row + 2][column] == 2)  { 
            g++;
        }
        //Now, the very bottom and top row's columns will be cycled 
        //bottom:
        if (minefield [row - 3][column - 3] == 2)  {
            g++;
        }
        if (minefield[row - 3][column - 2] == 2)  {
            g++; 
        }
        if (minefield[row - 3][column - 1] == 2)  {
            g++;
        }
        if (minefield[row - 3][column + 1] == 2)  {
            g++;
        }
        if (minefield[row - 3][column + 2] == 2)  {
            g++;
        }
        if (minefield[row - 3][column + 3] == 2)  {
            g++;
        }
        if (minefield[row - 3][column] == 2)  { 
            g++;
        }
        //top: 
        if (minefield[row + 3][column - 3] == 2)  {
            g++;
        }
        if (minefield[row + 3][column - 2] == 2)  {
            g++; 
        }
        if (minefield[row + 3][column - 1] == 2)  {
            g++;
        }
        if (minefield[row + 3][column + 1] == 2)  {
            g++;
        }
        if (minefield[row + 3][column + 2] == 2)  {
            g++;
        }
        if (minefield[row + 3][column + 3] == 2)  {
            g++;
        }
        if (minefield[row + 3][column] == 2)  { 
            g++;
        }
    }            
    return g;     
}
void reveal_square(int row, int column, int minefield[SIZE][SIZE], 
                   int noOfMines)  {
    int h = -1;
    int feedback = 0;
    //The square length is always 3, check if there are any mines within the  
    //given center that is not on the edge of the minefield
    if(minefield[row][column] == 2)  {
        printf("Game over\n");
        print_debug_minefield(minefield); 
    }   
    if(minefield[row][column] != 2)  {                  
        //inside the edges of minefield 
        if (row != 0 && row != 7 && column != 0 && column != 7)  {
            h = 0;         
            if (minefield[row - 1][column - 1] == 2)  {
                h++;
            }
            if (minefield[row - 1][column + 1] == 2)  {
                h++;
            }
            if (minefield[row - 1][column] == 2)  {
                h++;
            }
            if (minefield[row + 1][column + 1] == 2)  {
                h++;
            }
            if (minefield[row + 1][column - 1] == 2)  {
                h++;
            }
            if (minefield[row + 1][column] == 2)  {
                h++;
            }
            if (minefield[row][column - 1] == 2)  {
                h++;
            }
            if (minefield[row][column + 1] == 2)  { 
                h++;
            }
            if (minefield[row][column] == 2)  {
                h++;            
            }                
        } 
              
            
        //Check if there are any mines within the given center that 
        //ARE on the CORNERs of the minefield 
        //top left corner
        if (row == 0 && column == 0)  {
            h = 0;
            if (minefield[row + 1][column] == 2)  {
                h++;
            }
            if (minefield[row + 1][column + 1] == 2)  {
                h++;
            }
            if (minefield[row][column + 1] == 2)  {
                h++;
            }
            if (minefield[row][column] == 2)  {
                h++;
            }                                      
        }
        //top right corner
        if (row == 0 && column == 7)  {
            h = 0;
            if (minefield[row + 1][column] == 2)  {
                h++;
            }
            if (minefield[row + 1][column - 1] == 2)  {
                h++;
            }
            if (minefield[row][column - 1] == 2)  {
                h++;
            }
            if (minefield[row][column] == 2)  {
                h++;
            }
        }
        //bottom left corner 
        if (row == 7 && column == 0)  {
            h = 0;
            if (minefield[row][column] == 2)  {
                h++;
            }
            if (minefield[row - 1][column] == 2)  {
                h++;
            }
            if (minefield[row - 1][column + 1] == 2)  {
                h++;
            }
            if (minefield[row][column + 1] == 2)  {
                h++;
            }
        }
        //bottom right corner 
        if (row == 7 && column == 7)  {
            h = 0;
            if (minefield[row][column] == 2)  {
                h++;
            }
            if (minefield[row][column - 1] == 2)  {
                h++;
            }
            if (minefield[row - 1][column] == 2)  {
                h++;
            }
            if (minefield[row - 1][column - 1] == 2)  {
                h++; 
            }
        }
              
              
        //Check if there are any mines within the given center that 
        //ARE on the EDGEs of the minefield 
        //left side 
        if (row != 0 && row != 7 && column == 0)  {
            h = 0;
            if (minefield[row][column] == 2)  {
                h++;
            }
            if (minefield[row][column + 1] == 2)  {
                h++;
            }
            if (minefield[row + 1][column] == 2)  {
                h++;
            }
            if (minefield[row + 1][column + 1] == 2)  {
                h++;
            }
            if (minefield[row - 1][column] == 2)  {
                h++;
            }
            if (minefield[row - 1][column + 1] == 2)  {
                h++;
            }
        }
        //right side 
        if (row != 0 && row != 7 && column == 7)  {
            h = 0;
            if (minefield[row][column] == 2)  {
                h++;
            }
            if (minefield[row][column - 1] == 2)  {
                h++;
            }
            if (minefield[row + 1][column] == 2)  {
                h++; 
            }
            if (minefield[row + 1][column - 1] == 2)  {
                h++;
            }
            if (minefield[row - 1][column] == 2)  {
                h++;
            }
            if (minefield[row - 1][column - 1] == 2)  {
                h++;
            }
        }
        //top side 
        if (row == 0 && column != 0 && column != 7)  {
            h = 0; 
            if (minefield[row][column] == 2)  {
                h++;
            }
            if (minefield[row][column - 1] == 2)  {
                h++;
            }
            if (minefield[row][column + 1] == 2)  {
                h++;
            }
            if (minefield[row + 1][column] == 2)  {
                h++;
            }
            if (minefield[row + 1][column - 1] == 2)  {
                h++; 
            }
            if (minefield[row + 1][column + 1] == 2)  {
                h++;
            }
        }
        //bottom side
        if (row == 7 && column != 0 && column != 7)  {
            h = 0;
            if (minefield[row][column] == 2)  {
                h++;
            }
            if (minefield[row][column - 1] == 2)  {
                h++;
            }
            if (minefield[row][column + 1] == 2)  {
                h++;
            }
            if (minefield[row - 1][column] == 2)  {
                h++;
            }
            if (minefield[row - 1][column - 1] == 2)  {
                h++;
            }
            if (minefield[row - 1][column + 1] == 2)  {
                h++;
            }
        }
                             
            
        if (h >= 1)  {//the square has adjacent mines
            feedback = 1;
        }
        if (h < 1)  { //the square has no adjacent mines
            feedback = 0;
        }
        
        //when the input of the square has 1 OR MORE adjacent mines 
        if (feedback == 1)  {
            minefield[row][column] = 0;              
        }
        //when the input of the square is not on the edge of the
        // minefield and has NO adjacent mines
        if (feedback == 0 && row != 0 && row != 7 && column != 0 
            && column != 7)  {
            minefield[row][column] = 0; 
            minefield[row][column - 1] = 0;
            minefield[row][column + 1] = 0;
            minefield[row + 1][column] = 0; 
            minefield[row + 1][column - 1] = 0; 
            minefield[row + 1][column + 1] = 0; 
            minefield[row - 1][column] = 0; 
            minefield[row - 1][column - 1] = 0;
            minefield[row - 1][column + 1] = 0; 
        }
        //when the input of the square is one of the CORNERS of 
        //the minefield and has NO adjacent mines
        //this one is when [0,0] top left corner
        if (feedback == 0 && row == 0 && column == 0)  {
            minefield[row][column] = 0;
            minefield[row][column + 1] = 0;
            minefield[row + 1][column] = 0;
            minefield[row + 1][column + 1] = 0;
        }
        //this is when [0,7] top right corner
        if (feedback == 0 && row == 0 && column == 7)  {
            minefield[row][column] = 0;
            minefield[row][column - 1] = 0;
            minefield[row + 1][column] = 0;
            minefield[row + 1][column - 1] = 0;       
        }
        //when [7,0] bottom left corner
        if (feedback == 0 && row == 7 && column == 0)  {
            minefield[row][column] = 0;
            minefield[row][column + 1] = 0;
            minefield[row - 1][column] = 0;
            minefield[row - 1][column + 1] = 0;            
        }
        //when [7,7] bottom right corner
        if (feedback == 0 && row == 7 && column == 7)  {
            minefield[row][column] = 0;
            minefield[row][column - 1] = 0;
            minefield[row - 1][column] = 0;
            minefield[row - 1][column - 1] = 0; 
        }
        //if the input is ON the edge but not one of the CORNERS of 
        //the minefield and has NO adjacent mines 
        //for top row
        if (feedback == 0 && row == 0 && column != 0 && column != 7)  {
            minefield[row][column] = 0; 
            minefield[row][column - 1] = 0;
            minefield[row][column + 1] = 0; 
            minefield[row + 1][column] = 0;
            minefield[row + 1][column - 1] = 0; 
            minefield[row + 1][column + 1] = 0 ;
        } 
        //for bottom row 
        if (feedback == 0 && row == 7 && column != 0 && column != 7)  { 
            minefield[row][column] = 0; 
            minefield[row][column - 1] = 0;
            minefield[row][column + 1] = 0; 
            minefield[row - 1][column] = 0;
            minefield[row - 1][column - 1] = 0; 
            minefield[row - 1][column + 1] = 0 ;    
        }
        //for left side of minefield
        if (feedback == 0 && column == 0 && row != 0 && row != 7)  {
            minefield[row][column] = 0;
            minefield[row][column + 1] = 0; 
            minefield[row + 1][column] = 0; 
            minefield[row + 1][column + 1] = 0; 
            minefield[row - 1][column] = 0; 
            minefield[row - 1][column + 1] = 0; 
        }
        //right side 
        if (feedback == 0 && column == 7 && row != 0 && row != 7)  {
            minefield[row][column] = 0;
            minefield[row][column - 1] = 0; 
            minefield[row + 1][column] = 0; 
            minefield[row + 1][column - 1] = 0; 
            minefield[row - 1][column] = 0; 
            minefield[row - 1][column - 1] = 0; 
        }
                  
        int counter_4 = 0;            
        int tally = 0;
        while (counter_4 < SIZE)  {                
            int counter_5 = 0;           
            while (counter_5 < SIZE)  {
                if(minefield[counter_4][counter_5] == 0)  {
                    tally++;
                }
                counter_5++;
            }              
            counter_4++;
        }
        int WIN = 64 - noOfMines; 
        if (tally == WIN)  {
            printf("Game Won!\n"); 
            print_debug_minefield(minefield);
        }  
        else  {
            print_debug_minefield(minefield);
        }

    }
}

            
             






   
     
        




