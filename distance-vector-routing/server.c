#include <stdio.h>  // Include standard input/output library

int costMatrix[20][20], n;  // Define a global cost matrix and a variable for the number of nodes

struct routers  // Define a structure to hold routing information for each node
{
    int distance[20];  // Distance from this node to other nodes
    int adjNodes[20];  // Adjacent nodes for routing
} node[20];  // Array of routers

// Function to read the cost matrix
void readCostMatrix()
{
    int i, j;  // Loop variables
    printf("\nEnter cost matrix\n");  // Prompt user to enter the cost matrix
    for (i = 0; i < n; ++i)  // Loop through rows of the cost matrix
    {
        for (j = 0; j < n; ++j)  // Loop through columns of the cost matrix
        {
            scanf("%d", &costMatrix[i][j]);  // Read cost from user input
            costMatrix[i][i] = 0;  // Distance from a node to itself is 0
            node[i].distance[j] = costMatrix[i][j];  // Initialize distance array in the node structure
            node[i].adjNodes[j] = j;  // Initialize adjacent nodes array
        }
    }
}

// Function to calculate the routing table using the Distance Vector algorithm
void calcRoutingTable()
{
    int i, j, k;  // Loop variables
    for (i = 0; i < n; ++i)  // Loop through all nodes
    {
        for (j = 0; j < n; ++j)  // Loop through all destinations
        {
            for (k = 0; k < n; ++k)  // Loop through all possible intermediate nodes
            {   
                // If the cost from node i to j through k is less than the direct cost from i to j
                if (node[i].distance[j] > costMatrix[i][k] + node[k].distance[j])
                {
                    // Update the distance to the minimum cost
                    node[i].distance[j] = costMatrix[i][k] + node[k].distance[j];
                    // Update the adjacent node to the intermediate node k
                    node[i].adjNodes[j] = k;
                }
            }
        }
    }
}

// Function to display the routing tables
void displayRoutes()
{
    int i, j;  // Loop variables
    for (i = 0; i < n; ++i)  // Loop through all nodes
    {
        printf("\nRouter %d\n", i + 1);  // Print router number
        for (j = 0; j < n; ++j)  // Loop through all destinations
        {
            // Print the route and distance from router i to node j
            printf("Node %d via %d : Distance %d\n", j + 1, node[i].adjNodes[j] + 1, node[i].distance[j]);
        }
        printf("\n");
    }
}

int main()
{
    int i, j;  // Loop variables
    printf("Number of nodes: ");  // Prompt user to enter the number of nodes
    scanf("%d", &n);  // Read the number of nodes
    readCostMatrix();  // Call function to read the cost matrix
    calcRoutingTable();  // Call function to calculate the routing table
    displayRoutes();  // Call function to display the routing tables

    return 0;  // Return 0 to indicate successful execution
}
