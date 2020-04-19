#include<stdio.h>
#include<stdlib.h>

#define SIZE 4

/**
 * Dijkstra's Algorithm
 * greedy algo, negative weight is not allowed
 * return the shortest distance betweeb src and dst
 */

int dijkstra(int src, int dst, int A[SIZE][SIZE]) {
    int visible[SIZE];
    int visited[SIZE];
    int counter = 0;
    int min = -1;

    for (int i=0; i<SIZE; i++) {
        visible[i] = 0x7fffffff;
        visited[i] = 0;
    }
    visible[src] = 0;

    int min_distance;
    while (counter < SIZE)
    {
        min_distance = 0x7fffffff;
        // find the unvisited, visible node with min distance
        for (int i=0; i<SIZE; i++) {
            if (visible[i]<min_distance && visited[i]==0) {
                min = i;
                min_distance = visible[i];
            }
        }

        visited[min] = 1;

        // undate visible
        for (int i=0; i<SIZE; i++) {
            if (A[min][i]>0 && ((visible[min]+A[min][i])<visible[i])) {
                visible[i] = visible[min] + A[min][i];
            }
        }
        counter++;
    }

    return visible[dst];
}


/**
 * Bellman-Ford Algorithm
 * dynamic programming, negative weight is allowed, but negative cycle is not allowed
 * return the shortest distance betweeb src and dst
 */
int BF(int src, int dst, int A[SIZE][SIZE]) {
    int visible[SIZE];
    int updated; // a flag for earlier return

    for (int i=0; i<SIZE; i++) {
        visible[i] = 0x7fffffff;
    }
    visible[src] = 0;

    // we need at most SIZE-1 iterations
    for (int k=0; k<SIZE-1; k++) {

        updated = 0;

        // for each visible node if we see a shorter path to it's neighbors, update.
        for (int i=0; i<SIZE; i++) {
            if (visible[i] == 0x7fffffff)
                continue;
            
            for (int j=0; j<SIZE; j++) {
                if (A[i][j]>0 && (visible[i]+A[i][j])<visible[j]) {
                    visible[j] = visible[i] + A[i][j];
                    updated = 1;
                }
            }
        }

        // if we don't see any improvement, we can exit earlier
        if (updated == 0)
            break;
    }

    return visible[dst];
}


/**
 * Floyed-Warshall Algorithm
 * dynamic programming, all shortest path, negative weight is allowed, but negative cycle is not allowed
 * return the shortest distance betweeb src and dst
 */
int FW(int src, int dst, int A[SIZE][SIZE]) {
    // c(i, j, 0)
    int result[SIZE][SIZE];
    for (int i=0; i<SIZE; i++) {
        for (int j=0; j<SIZE; j++) {
            if (i == j) {
                result[i][j] = 0;
            } else if (A[i][j] == 0) {
                result[i][j] = 0x7fffffff;
            } else {
                result[i][j] = A[i][j];
            }
        }
    }

    for (int k=0; k<SIZE; k++) {
        for (int i=0; i<SIZE; i++) {
            for (int j=0; j<SIZE; j++) {
                if (result[i][k]==0x7fffffff || result[k][j]==0x7fffffff)
                    continue;
                
                if(result[i][k] + result[k][j] < result[i][j]) {
                    result[i][j] = result[i][k] + result[k][j];
                }
            }
        }
    }
    return result[src][dst];
}



int main() {

    int A[SIZE][SIZE] = {{0, 4, 2, 7}, 
                         {1, 0, 5, 0}, 
                         {2, 0, 0, 4}, 
                         {0, 3, 0, 0}};

    //printf("%d\n", dijkstra(1, 3, A));
    //printf("%d\n", BF(1, 3, A));
    printf("%d\n", FW(1, 3, A));

    return 0;
}
