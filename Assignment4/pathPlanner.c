/*******************************************************************************************/
/*                                                                                         */
/* pathPlanner.c                                                                           */
/*                                                                                         */
/* The program is to simulate vertices, edges in an environment.                           */
/*                                                                                         */
/* The program do creating obstacles, vertices, complete graph                             */
/* and reduced visibility graph, then cleaning up by freeing allocated memory              */
/*                                                                                         */
/*******************************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <X11/Xlib.h>

#include "obstacles.h"
#include "display.h"

// function that create vertices
int createVertices(Environment *environment){
  environment->numVertices = environment->numObstacles * 4;
	environment->vertices = (Vertex *)malloc(environment->numVertices*sizeof(Vertex));
  int index = 0;
  // iterate through every obstacles and creating edges related to this obstacle
	for (int i=0; i<environment->numObstacles; i++) {
    for (int j = 0; j < 4; j++){
      if (j == 0){
        environment->vertices[index].x = environment->obstacles[i].x;
        environment->vertices[index].y = environment->obstacles[i].y;
        environment->vertices[index].belongObs = &(environment->obstacles[i]);
        environment->vertices[index].firstNeighbour = NULL;
        environment->vertices[index].linkedList = NULL;
        environment->vertices[index].lastNeighbour = NULL;
      }else if (j == 1){
        environment->vertices[index].x = environment->obstacles[i].x + environment->obstacles[i].w ;
        environment->vertices[index].y = environment->obstacles[i].y;
        environment->vertices[index].belongObs = &(environment->obstacles[i]);
        environment->vertices[index].firstNeighbour = NULL;
        environment->vertices[index].linkedList = NULL;
        environment->vertices[index].lastNeighbour = NULL;
      }else if (j == 2){
        environment->vertices[index].x = environment->obstacles[i].x ;
        environment->vertices[index].y = environment->obstacles[i].y - environment->obstacles[i].h;
        environment->vertices[index].belongObs = &(environment->obstacles[i]);
        environment->vertices[index].firstNeighbour = NULL;
        environment->vertices[index].linkedList = NULL;
        environment->vertices[index].lastNeighbour = NULL;
      }else if (j == 3){
        environment->vertices[index].x = environment->obstacles[i].x + environment->obstacles[i].w;
        environment->vertices[index].y = environment->obstacles[i].y - environment->obstacles[i].h;
        environment->vertices[index].belongObs = &(environment->obstacles[i]);
        environment->vertices[index].firstNeighbour = NULL;
        environment->vertices[index].linkedList = NULL;
        environment->vertices[index].lastNeighbour = NULL;
      }
      index++;
    }
	}
  return environment->numVertices;
}

// function that create edges
int createEdges(Environment *environment){
  int numEdges = 0;
  // iterate through every vertices and connect this vertex with all other vertices
	for (int i = 0; i < environment->numVertices; i++){
    environment->vertices[i].linkedList = NULL;
    for (int j = 0; j < environment->numVertices; j++){
      if (i != j){
          if (environment->vertices[i].linkedList == NULL){
            environment->vertices[i].firstNeighbour = (Neighbour *)malloc(sizeof(Neighbour));
            environment->vertices[i].firstNeighbour->vertex = &(environment->vertices[j]);
            environment->vertices[i].firstNeighbour->next = NULL;
            environment->vertices[i].linkedList = environment->vertices[i].firstNeighbour;
            environment->vertices[i].lastNeighbour = environment->vertices[i].firstNeighbour;
            numEdges++;
          }else{
            environment->vertices[i].linkedList->next = (Neighbour *)malloc(sizeof(Neighbour));
            environment->vertices[i].linkedList->next->vertex = &(environment->vertices[j]);
            environment->vertices[i].linkedList->next->next = NULL;
            environment->vertices[i].linkedList =  environment->vertices[i].linkedList->next;
            environment->vertices[i].lastNeighbour =  environment->vertices[i].linkedList;
            numEdges++;
          }
      }
    }
  }
  return numEdges;
}

// function that remove invalid edges
int removeEdges(Environment *environment){
  int numEdges = 0;
  int reInter = 0;
  int reDiagonal = 0;
  // iterate through every vertices
  // interate through every neighbours of current vertex
  // remove the neighbours is the edge is invalid
  for (int i=0; i < environment->numVertices; i++) {
    Neighbour *n = environment->vertices[i].firstNeighbour;
    Neighbour *prev = NULL;
    while (n != NULL) {
      int isIntersect = 0;
      // remove diagonal edges
      if (environment->vertices[i].belongObs == n->vertex->belongObs && environment->vertices[i].x != n->vertex->x && environment->vertices[i].y != n->vertex->y){
        if (prev == NULL){
          Neighbour *temp = n;
          environment->vertices[i].firstNeighbour = temp->next;
          n = n->next;
          reDiagonal++;
          free(temp);
          continue;
        }else{
          Neighbour *temp = n;
          prev->next = temp->next;
          n = n->next;
          reDiagonal++;
          free(temp);
          continue;
        }
      }

      // remove edges that intersec with an obstacle
      short x1 = environment->vertices[i].x;
      short y1 = environment->vertices[i].y;
      short x2 = n->vertex->x;
      short y2 = n->vertex->y;
      for (int j = 0; j < environment->numObstacles; j++){
        for (int k = 0; k < 4; k++){
          // check the first edge of the obstacle
          if (k == 0){
            short x3 = environment->obstacles[j].x;
            short y3 = environment->obstacles[j].y;
            short x4 = environment->obstacles[j].x;
            short y4 = environment->obstacles[j].y - environment->obstacles[j].h;

            double u_a = 0;
            double u_b = 0;
            if (((y4-y3)*(x2-x1) - (x4-x3)*(y2-y1)) != 0){
                u_a = (double)((x4-x3)*(y1-y3) - (y4-y3)*(x1-x3)) / (double)((y4-y3)*(x2-x1) - (x4-x3)*(y2-y1));
                u_b = (double)((x2-x1)*(y1-y3) - (y2-y1)*(x1-x3)) / (double)((y4-y3)*(x2-x1) - (x4-x3)*(y2-y1));
            }

            // Remove vextex if 0<u_a<1 and 0<u_b<1
            if (u_a > 0 && u_a < 1 && u_b > 0 && u_b < 1){
              if (prev == NULL){
                Neighbour *temp = n;
                environment->vertices[i].firstNeighbour = temp->next;
                n = n->next;
                isIntersect = 1;
                reInter++;
                free(temp);
                break;
              }else{
                Neighbour *temp = n;
                prev->next = temp->next;
                n = n->next;
                isIntersect = 1;
                reInter++;
                free(temp);
                break;
              }
            }
          }else if (k == 1){
            short x3 = environment->obstacles[j].x;
            short y3 = environment->obstacles[j].y;
            short x4 = environment->obstacles[j].x + environment->obstacles[j].w;
            short y4 = environment->obstacles[j].y;

            double u_a = 0;
            double u_b = 0;
            if (((y4-y3)*(x2-x1) - (x4-x3)*(y2-y1)) != 0){
                u_a = (double)((x4-x3)*(y1-y3) - (y4-y3)*(x1-x3)) / (double)((y4-y3)*(x2-x1) - (x4-x3)*(y2-y1));
                u_b = (double)((x2-x1)*(y1-y3) - (y2-y1)*(x1-x3)) / (double)((y4-y3)*(x2-x1) - (x4-x3)*(y2-y1));
            }

            // Remove vextex if 0<u_a<1 and 0<u_b<1
            if (u_a > 0 && u_a < 1 && u_b > 0 && u_b < 1){
              if (prev == NULL){
                Neighbour *temp = n;
                environment->vertices[i].firstNeighbour = temp->next;
                n = n->next;
                isIntersect = 1;
                reInter++;
                free(temp);
                break;
              }else{
                Neighbour *temp = n;
                prev->next = temp->next;
                n = n->next;
                isIntersect = 1;
                reInter++;
                free(temp);
                break;
              }
            }
          }else if (k == 2){
            short x3 = environment->obstacles[j].x;
            short y3 = environment->obstacles[j].y - environment->obstacles[j].h;
            short x4 = environment->obstacles[j].x + environment->obstacles[j].w;
            short y4 = environment->obstacles[j].y - environment->obstacles[j].h;

            double u_a = 0;
            double u_b = 0;
            if (((y4-y3)*(x2-x1) - (x4-x3)*(y2-y1)) != 0){
                u_a = (double)((x4-x3)*(y1-y3) - (y4-y3)*(x1-x3)) / (double)((y4-y3)*(x2-x1) - (x4-x3)*(y2-y1));
                u_b = (double)((x2-x1)*(y1-y3) - (y2-y1)*(x1-x3)) / (double)((y4-y3)*(x2-x1) - (x4-x3)*(y2-y1));
            }

            // Remove vextex if 0<u_a<1 and 0<u_b<1
            if (u_a > 0 && u_a < 1 && u_b > 0 && u_b < 1){
              if (prev == NULL){
                Neighbour *temp = n;
                environment->vertices[i].firstNeighbour = temp->next;
                n = n->next;
                isIntersect = 1;
                reInter++;
                free(temp);
                break;
              }else{
                Neighbour *temp = n;
                prev->next = temp->next;
                n = n->next;
                isIntersect = 1;
                reInter++;
                free(temp);
                break;
              }
            }
          }else if (k == 3){
            short x3 = environment->obstacles[j].x + environment->obstacles[j].w;
            short y3 = environment->obstacles[j].y;
            short x4 = environment->obstacles[j].x + environment->obstacles[j].w;
            short y4 = environment->obstacles[j].y - environment->obstacles[j].h;

            double u_a = 0;
            double u_b = 0;
            if (((y4-y3)*(x2-x1) - (x4-x3)*(y2-y1)) != 0){
                u_a = (double)((x4-x3)*(y1-y3) - (y4-y3)*(x1-x3)) / (double)((y4-y3)*(x2-x1) - (x4-x3)*(y2-y1));
                u_b = (double)((x2-x1)*(y1-y3) - (y2-y1)*(x1-x3)) / (double)((y4-y3)*(x2-x1) - (x4-x3)*(y2-y1));
            }
            // Remove vextex if 0<u_a<1 and 0<u_b<1
            if (u_a > 0 && u_a < 1 && u_b > 0 && u_b < 1){
              if (prev == NULL){
                Neighbour *temp = n;
                environment->vertices[i].firstNeighbour = temp->next;
                n = n->next;
                isIntersect = 1;
                reInter++;
                free(temp);
                break;
              }else{
                Neighbour *temp = n;
                prev->next = temp->next;
                n = n->next;
                isIntersect = 1;
                reInter++;
                free(temp);
                break;
              }
            }
          }
        }
        if (isIntersect == 1){
          break;
        }
      }
      if (isIntersect == 0){
        numEdges++;
        prev = n;
        n = n->next;
      }
    }
  }
  return numEdges;
}

// function that clean every allocating memory
void cleanupEverything(Environment *environment){
  // clean numVertices
  Vertex *array = environment->vertices;
  for (int i=0; i < environment->numVertices; i++) {
    Neighbour *n = environment->vertices[i].firstNeighbour;
    // clean allocating memory of neighbours of a vertex
    while (n != NULL) {
      Neighbour *temp = n;
      environment->vertices[i].firstNeighbour = temp->next;
      n = n->next;
      free(temp);
    }
  }
  // clean allocating memory of the array of vertices
  free(array);
  // clean allocating memory of the array of obstacles
  Obstacle *delObstacle = environment->obstacles;
  free(delObstacle);
}
