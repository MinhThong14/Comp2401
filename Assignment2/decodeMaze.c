
/*******************************************************************************************/
/*                                                                                         */
/* decodeMaze.c                                                                            */
/*                                                                                         */
/* This program display mazes where each char is 1 for a wall or 0 for a space             */
/*                                                                                         */
/* The program also do encoded mazes, merger mazes, and check if a path is fit a maze      */
/*                                                                                         */
/*******************************************************************************************/
#include<stdio.h>
#include<stdlib.h>

//Size of maxArray
#define MAXARRAY  32
#define MAXBITS  32

// size of an array;
int sizeArray;

//function that displays the endcoded array
void printEncodedMaze(int mazeArray[], unsigned char wall);
//function that displays the endcoded array with path
void printEncodedMazeWithPath(int mazeArray[], int path[], unsigned char wall);
//function that endcode 8x8 maze into an array of 8 ints
void encode8by8Maze(char inputMaze[8][8], int endcodedMaze[8]);
//fucntion merge 8x8 maze together
void merge8by8mazes(int topLeft[8], int topRight[8], int bottomLeft[8], int bottomRight[8], int finalMaze[14]);
//function that check if the path is fit in a maze
char isPathInMaze(int encodedMaze[], int path[], unsigned char dimension);





int main(int argc, char **argv){

    // Hardcode 32x32 maze
    int mazeArray[MAXARRAY] = {-1, -2146430423, -1109928277, -1525661045, -1602496045, -1358950569, -1451509759, -1927115297, -1578180479, -1354977603, -1476294999, -2084818261, -1163749757, -1964319689, -1341614619, -1750141691, -1256060947, -1515522751, -1204136611, -1955867371, -1190652827, -1553272339, -1100839163, -1999963019, -631368865, -1882138047, -1172944163, -1412279803, -1567107339, -164346691, -2138762879, -1};
    // Hardcode a path 32x32 maze
    int path[MAXARRAY] = {0, 0, 0, 0, 12, 8, 56, 32, 8032, 4416, 134115648, 67354944, 67109184, 67109312, 133169152, 1048576, 1835008, 262144, 262144, 262144, 458752, 65536, 65536, 65536, 65536, 983040, 67633152, 67633152, 201850880, 164102144, 259522560, 0};

    // Hardcode 8x8 mazes
    char maze1[8][8] =   {{1,1,1,1,1,1,1,1},
                        {1,0,0,0,1,0,0,1},
                        {1,0,1,0,1,1,0,1},
                        {1,0,1,0,0,0,0,1},
                        {1,0,1,1,1,1,0,1},
                        {1,0,0,0,0,0,0,1},
                        {1,0,1,0,1,0,1,1},
                        {1,1,1,1,1,1,1,1}};

    char maze2[8][8] =   {{1,1,1,1,1,1,1,1},
                        {1,0,0,0,0,1,0,1},
                        {1,1,1,1,0,1,0,1},
                        {1,0,0,1,0,1,1,1},
                        {1,1,0,0,0,0,0,1},
                        {1,1,1,1,0,1,1,1},
                        {1,0,0,0,0,1,0,1},
                        {1,1,1,1,1,1,1,1}};

    char maze3[8][8] =   {{1,1,1,1,1,1,1,1},
                        {1,0,1,0,0,0,1,1},
                        {1,0,1,0,1,0,0,1},
                        {1,0,1,0,1,0,1,1},
                        {1,0,1,0,1,0,1,1},
                        {1,0,1,0,1,0,1,1},
                        {1,0,0,0,1,0,0,1},
                        {1,1,1,1,1,1,1,1}};

    char maze4[8][8] =   {{1,1,1,1,1,1,1,1},
                        {1,0,1,0,1,0,1,1},
                        {1,0,1,0,0,0,0,1},
                        {1,0,0,0,1,1,1,1},
                        {1,1,1,0,1,0,0,1},
                        {1,0,0,0,0,0,1,1},
                        {1,1,0,1,1,0,0,1},
                        {1,1,1,1,1,1,1,1}};


    // Find the size of the array maze 32x32
    sizeArray = sizeof(mazeArray)/ sizeof(int);
    
    // Print the endcoded 32x32 maze
    printEncodedMaze(mazeArray,'@');
    printf("\n");

    // Print the the encoded 32x32 maze with a path inside
    printEncodedMazeWithPath(mazeArray, path, '@');
    printf("\n");

    // Check if a path is fits in a maze 32x32
    printf("Check if the path is fit: %d\n", isPathInMaze(mazeArray, path, 32));
    printf("\n");

    int result1[8];
    // Encode 8x8 maze1
    encode8by8Maze(maze1, result1);
    // Change the global sizeArray variable to size of 8x8 maze print
    sizeArray = sizeof(result1) / sizeof(int);
    // Print endconded 8x8 maze 1
    printEncodedMaze(result1, '@');
    printf("\n");

    int result2[8];
    // Encode 8x8 maze2
    encode8by8Maze(maze2, result2);
    // Change the global sizeArray variable to size of 8x8 maze to print
    sizeArray = sizeof(result2) / sizeof(int);
    // Print endconded 8x8 maze 2
    printEncodedMaze(result2, '@');
    printf("\n");

    int result3[8];
    // Encode 8x8 maze3
    encode8by8Maze(maze3, result3);
    // Change the global sizeArray variable to size of 8x8 maze to print
    sizeArray = sizeof(result3) / sizeof(int);
    // Print endconded 8x8 maze 3
    printEncodedMaze(result3, '@');
    printf("\n");

    int result4[8];
    // Encode 8x8 maze4
    encode8by8Maze(maze4, result4);
    // Change the global sizeArray variable to size of 8x8 maze to print
    sizeArray = sizeof(result4) / sizeof(int);
    // Print endconded 8x8 maze 4
    printEncodedMaze(result4, '@');
    printf("\n");

    int mergeMaze[14];
    // Merge 8x8 mazes
    merge8by8mazes(result1, result2, result3, result4, mergeMaze);
    // Change the global sizeArray variable to size of 14x14 maze to print
    sizeArray = sizeof(mergeMaze)/ sizeof(int);
    printEncodedMaze(mergeMaze, '@');
    printf("\n\n");

    // 2D array contains all 4 mazes
    int mergeMazeList[4][8] = {{result1[0], result1[1], result1[2], result1[3], result1[4], result1[5], result1[6], result1[7]}, 
                               {result2[0], result2[1], result2[2], result2[3], result2[4], result2[5], result2[6], result2[7]}, 
                               {result3[0], result3[1], result3[2], result3[3], result3[4], result3[5], result3[6], result3[7]}, 
                               {result4[0], result4[1], result4[2], result4[3], result4[4], result4[5], result4[6], result4[7]}};
    // Harcode a path of 14x14 maze
    int newPath[14] = {0, 4096, 4096, 4096, 4096, 7936, 256, 256, 448, 112, 16, 28, 6, 0};
    // Generate all 256 combinations of 14x14 mazes
    for (int i = 0; i < 4; i++){
        for(int j = 0; j < 4; j++){
            for(int k = 0; k < 4; k++){
                for(int w = 0; w < 4; w++){
                    int mergeMazeCombi[14];
                    // Do a merge 8x8 mazes
                    merge8by8mazes(mergeMazeList[i], mergeMazeList[j], mergeMazeList[k], mergeMazeList[w], mergeMazeCombi);
                    int sizeArrayCombi = sizeof(mergeMazeCombi) / sizeof(int);
                    printf("%d, %d, %d, %d\n", i+1, j+1, k+1, w+1);
                    // Print econded mazes
                    printEncodedMaze(mergeMazeCombi, '@');
                    // Check if the path is fit in the maze
                    if (isPathInMaze(mergeMazeCombi, newPath, 14)){
                        printf("Check if the path is fit: %d\n", isPathInMaze(mergeMazeCombi, newPath, 14));
                    }
                    printf("\n\n");
                }
            }
        }
    }
    

    return 0;
}
//Function that displays the endcoded array
void printEncodedMaze(int mazeArray[], unsigned char wall){
    // Iterate throguh each row of maze
    for(int i = 0; i < sizeArray; i++){
        int number = mazeArray[i];
        // Check each bit of mazeArray
        // If bit is set then print @
        // Else print a space 
        for (int j = sizeArray-1; j >=0; j--){
            int isBitSet = (number & (1 << j));
            if (isBitSet){
                printf("%c", wall);
            }else{
                printf(" ");
            }
        }
        printf("\n");
    }
}
//Function that displays the endcoded array with path
void printEncodedMazeWithPath(int mazeArray[], int path[], unsigned char wall){
    // Iterate throuh each row of maze
    for(int i = 0; i < MAXARRAY; i++){
        int numberMaze = mazeArray[i];
        int numberPath = path[i];
        // Check each bit of mazeArray and path
        // If bit is set in maze then print @
        // Else if bit is et in path then print .
        // Else print a space
        for (int j = MAXBITS-1; j >=0; j--){
            int isBitSetMaze = (numberMaze & (1 << j));
            int isBitSetPath = (numberPath & (1 << j));
            if (isBitSetMaze){
                printf("%c", wall);
            }else if(isBitSetPath){
                printf(".");
            }else{
                printf(" ");
            }
        }
        printf("\n");
    }
}
//Function that endcode 8x8 maze into an array of 8 ints
void encode8by8Maze(char inputMaze[8][8], int endcodedMaze[8]){
    // Iterate through each row of input Maze
    for(int i = 0; i < 8; i++){
        int result = 0;
        int power = 1;
        // Encode each row then add into endCodedMaze 
        for(int j = 7; j >= 0; j--){
            int number = 0;
            if (inputMaze[i][j]){
                number = 1;
            }
            result += number * power;
            power *= 2;
        }
        endcodedMaze[i] = result;
    }
   
}
//Fucntion merge 8x8 maze together
void merge8by8mazes(int topLeft[8], int topRight[8], int bottomLeft[8], int bottomRight[8], int finalMaze[14]){
    // Merge each row of 8x8 maze and add to finalMaze
    for (int i = 0; i < 14; i++){
        // Add half top of the maze
        if(i < 7){
            int numberLeftTop = topLeft[i];
            int numberRightTop = topRight[i];
            // Clear the right most bit of number left
            numberLeftTop &= ~1;
            // Shift numberLeft bits by 7
            numberLeftTop = numberLeftTop << 6;
            // Clear the left most bit of number right 
            numberRightTop &= ~(1 << 7);
            int numberTop = numberLeftTop | numberRightTop;
            finalMaze[i] = numberTop;
        }
        // Add half bottom of the maze
        else{
            int numberLeftBottom = bottomLeft[i-6];
            int numberRightBottom = bottomRight[i-6];
            // Clear the right most bit of number left
            numberLeftBottom &= ~1;
            // Shift numberLeft bits by 7
            numberLeftBottom = numberLeftBottom << 6;
            // Clear the left most bit of number right 
            numberRightBottom &= ~(1 << 7);
                
            int numberBottom = numberLeftBottom | numberRightBottom;
            finalMaze[i] = numberBottom; 
        }
        
    }

}
//Function that check if the path is fit in a maze
char isPathInMaze(int encodedMaze[], int path[], unsigned char dimension){
    // Innitialize result to 1
    char result = 1;
    // Iterate through maza and path
    for(int i = 0; i < (int)dimension; i++){
        int numberMaze = encodedMaze[i];
        int numberPath = path[i];
        // Check if the bit in path is fit in maze by iterate through bits of maze and path
        for (int j = (int)dimension-1; j >=0; j--){
            // Check if a bit is set in maze
            int isBitSetMaze = (numberMaze & (1 << j));
            // Check if a bit is set in path
            int isBitSetPath = (numberPath & (1 << j));
            // If a bit is both set in Maze and Path then return 0
            if (isBitSetMaze && isBitSetPath){
                result = 0;
                return result;
            }
        }
    }
    return result;
}




