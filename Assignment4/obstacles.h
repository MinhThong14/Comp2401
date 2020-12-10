// Forward declaration
struct _obstacle;
struct _vertex;
struct _environment;
struct _neighbour;

// Obstacle struct
struct _obstacle{
  short x;
  short y;
  short w;
  short h;
};

// Neighbour type that represents an item in the linked list of vertext neighbours
struct _neighbour{
  struct _vertex *vertex;
  struct _neighbour *next;
};

//Vertice struct
struct _vertex{
  short x;
  short y;
  // linked list that keeps vertices that it connects to
  struct _neighbour *linkedList;
  struct _neighbour *firstNeighbour;
  struct _neighbour *lastNeighbour;
  struct _obstacle *belongObs;
};
// environment struct
struct _environment{
  int numObstacles;
  struct _obstacle *obstacles;
  int numVertices;
  struct _vertex *vertices;
};
//type declaration
typedef struct _obstacle Obstacle;
typedef struct _environment Environment;
typedef struct _vertex Vertex;
typedef struct _neighbour Neighbour;

// prototypes
//function that create vertices
int createVertices(Environment *environment);

//function that create createEdges
int createEdges(Environment *environment);

//function that removeEdges
int removeEdges(Environment *environment);

//function that clean up everything
void cleanupEverything(Environment *environment);
