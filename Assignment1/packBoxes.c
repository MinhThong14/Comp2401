/*******************************************************************************************/
/*                                                                                         */
/* packBoxes.c                                                                             */
/*                                                                                         */
/* This program generates 24 packages at random and pack these packages into boxes         */
/* such that the number of boxes used to pack is minimum                                   */
/*                                                                                         */
/* The program will display the order information, a breakdown of costs and show how each  */
/* individual box is packed                                                                */
/*                                                                                         */
/*******************************************************************************************/

#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<math.h>
//Define the maximum number of carboard boxes to 6
#define BOXES 6 
// Defining the maximum number of rows and column in a cardboad box to 5 and 4
#define ROW 5
#define COL 4
// Defining the maximum number of boxes
#define MAX_BOXES 24
// Create a 3D array with 6 layers, each layer has 5 row and 4 columns representing card board boxes
char cardBoard[BOXES][ROW][COL];

/* This function generate a random number using the formula:                               */
/* number = (rand() % (left - right + 1)) + left                                           */
int randomNumber(int left, int right);
int packLargeBoxes(char cardBoard[BOXES][ROW][COL], int boxes, int largeBoxes);
int packMediumBoxes(char cardBoard[BOXES][ROW][COL], int boxes, int mediumBoxes);
int packSmallBoxes(char cardBoard[BOXES][ROW][COL], int boxes, int smallBoxes);


int main(int argc, char **argv){
    // Declaring the number of large boxes, medium boxes and small boxes
    int largeBoxes = 0;
    int mediumBoxes = 0;
    int smallBoxes = 0;

    // Finding random number of large boxes, medium boxes and small boxes
    // Current time that look for a random number
    srand(time(0));
    // Find the number of large boxes
    largeBoxes = randomNumber(0, MAX_BOXES);
    // The remaining boxes
    int remainBoxes = MAX_BOXES - largeBoxes;
    // Find the number of medium boxes
    if (remainBoxes > 0){
       mediumBoxes = randomNumber(0, remainBoxes); 
    }
    // Find the number of small boxes
    smallBoxes = remainBoxes - mediumBoxes;

    // Copy the number of large, medium, small boxes to print out
    int largePrint = largeBoxes;
    int mediumPrint = mediumBoxes;
    int smallPrint = smallBoxes;

    // Declaring the number of used boxes
    int boxes = 0; 

    // Pack large boxes into carboard boxes
    boxes = packLargeBoxes(cardBoard, boxes, largeBoxes);

    // Pack medium boxes into cardboard boxes
    boxes = packMediumBoxes(cardBoard, boxes, mediumBoxes);

    // Pack small boxes into cardboard boxes
    boxes = packSmallBoxes(cardBoard, boxes, smallBoxes);
    
    // Display the order information, costs, and how each individual box is packed
    // Print out  order information
    printf("\n");
    printf("Order:  Large = %d, Medium = %d, Small = %d\n", largePrint, mediumPrint, smallPrint);
    printf("\n");
    // Calculate the cost of smalll boxes and print it out
    float smallCost = (smallPrint * 5.99);
    printf("Small (%02d units)          $ %0.2f\n", smallPrint, smallCost);
    // Calculate the cost of medium boxes and print it out
    float mediumCost = (mediumPrint * 10.99);
    printf("Medium (%02d units)         $ %0.2f\n", mediumPrint, mediumCost);
    // Calculate the cost of large boxes and print it out
    float largeCost = (largePrint * 19.99);
    printf("Large (%02d units)          $ %0.2f\n", largePrint, largeCost);
    printf("-----------------------------------------------\n");
    // Calculate the total amount and print it out
    float total = (smallCost + mediumCost + largeCost);
    printf("Total                     $ %0.2f\n", total);
    // Calculate shipping fee and print it out
    float shipping = boxes * 1.49;
    printf("Shipping                  $ %0.2f\n", shipping);  
    // Calculate taxes and print it out
    float tax = (total * 13) / 100;
    printf("HST                       $ %0.2f\n", tax);
    printf("-----------------------------------------------\n");
    // Calculate taxes and print it out
    float amount = (total + shipping + tax);
    printf("Amount Charged            $ %0.2f\n", amount); 
    printf("\n");
    printf("Individual boxes are packed as follows:\n");
    printf("\n");
    // Print out how each individual box is packed 
    for (int i = 0; i < BOXES; i++){
        for (int j = 0; j < ROW; j++){
            for (int w = 0; w < COL; w++){
                if (cardBoard[i][j][w] == 0 && (j == 0 && w == 0)){
                    printf("-----------------------------------------------\n");
                    printf("\n");
                    return 0;
                }
                if (i == 5 && j == 4 && w == 3 && cardBoard[i][j][w] == 0){
                    printf("-----------------------------------------------\n");
                    printf("\n");
                    return 0;
                }
                printf("%c", cardBoard[i][j][w]);
            }
            printf("\n");
        }
        printf("\n");
    }

    return(0);
}

/* Function that find a random Number                                 */
int randomNumber(int left, int right){
    int randNum = (rand() % (right - left + 1) + left);
    return randNum;
}

/* Function that pack large boxes                                     */
/* and return the number of cardboard boxes used                      */
/* Adding large boxes to cardboard boxes                              */
/* There are only four possible points to add                         */ 
/* a top-left corner of large boxes into a cardboard box              */ 
/* that is (0,0) (0,2) (2,0) (2,2)                                    */
/* If there are some remainning large boxes,                          */ 
/* but there are no rooms in cardboard boxes,                         */
/* then using a new cardboard box                                     */

int packLargeBoxes(char cardBoard[BOXES][ROW][COL], int boxes, int largeBoxes){
    // Declaring starting coordinate to add large boxes
    int xPoint = 0;
    int yPoint = 0;

    // Initialize each point in each of 6 cardboard boxes to 0
    for (int g = 0; g < BOXES; g++){
        for (int m = 0; m < ROW; m++){
            for (int k = 0; k < COL; k++){
                cardBoard[g][m][k] = 0;
            }
        }
    } 

    while (largeBoxes > 0){
        cardBoard[boxes][xPoint][yPoint] = 'L';
        cardBoard[boxes][xPoint][yPoint+1] = 'L';
        cardBoard[boxes][xPoint+1][yPoint] = 'L';
        cardBoard[boxes][xPoint+1][yPoint+1] = 'L';
        
        if (xPoint == 0 && yPoint == 0){
            xPoint = 0;
            yPoint = 2;
        }else if(xPoint == 0 && yPoint == 2){
            xPoint = 2;
            yPoint = 0;
        }else if(xPoint == 2 && yPoint == 0){
            xPoint = 2;
            yPoint = 2;
        }else if(xPoint == 2 && yPoint == 2 && (largeBoxes-1) > 0){
            xPoint = 0;
            yPoint = 0;
            boxes += 1;
        }
        largeBoxes -= 1;
    }

    // Find the number of boxes by adding 1 to boxes
    boxes++;
    return boxes;
};

/* Function that pack medium boxes                                    */
/* and return the number of cardboard boxes used                      */
/* Adding medium boxes to cardboard boxes                             */
/* Iterating through each point in a box                              */ 
/* which is able to add top-left corner of medium boxes               */ 
/* If there are some remaining medium boxes,                          */
/* but there are no rooms in cardboard boxes,                         */ 
/* then using a new cardboard box                                     */

int packMediumBoxes(char cardBoard[BOXES][ROW][COL], int boxes, int mediumBoxes){
    for(int depth = 0; depth < BOXES; depth++){
        for(int row = 0; row < ROW; row++){
            for(int col = 0; col < floor(COL/2); col++){
                col *= 2;
                if (mediumBoxes > 0 && cardBoard[depth][row][col] == 0){
                    cardBoard[depth][row][col] = 'M';
                    cardBoard[depth][row][col+1] = 'M';
                    mediumBoxes--;
                    if (depth + 1 > boxes){
                        boxes = depth + 1;
                    }
                }
            }
                    
        }
    }
    return boxes;
}

/* Function that pack small boxes                                     */
/* Adding small boxes to cardboard boxes                              */
/* Iterating through each point in a box                              */ 
/* which is able to add top-left corner of small boxes                */ 
/* If there are some remaining small boxes,                           */
/* but there are no rooms in cardboard boxes,                         */ 
/* then using a new cardboard box                                     */

int packSmallBoxes(char cardBoard[BOXES][ROW][COL], int boxes, int smallBoxes){
    
    for(int depthSmall = 0; depthSmall < BOXES; depthSmall++){
        for(int rowSmall = 0; rowSmall < ROW; rowSmall++){
            for(int colSmall = 0; colSmall < COL; colSmall++){
                if (smallBoxes > 0 && cardBoard[depthSmall][rowSmall][colSmall] == 0){
                    cardBoard[depthSmall][rowSmall][colSmall] = 'S';
                    smallBoxes --;
                    if(depthSmall + 1 > boxes){
                        boxes = depthSmall + 1;
                    }
                }
            }
        }
    }
    return boxes;
}