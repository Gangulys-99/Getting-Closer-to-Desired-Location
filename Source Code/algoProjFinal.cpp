#include <limits.h>
#include <stdio.h>

//Total number of vertex in the graph
#define V 6

//Method to calculate the minimum distance between source and other vertices
int minDistance(int dist[], bool sptSet[])
{
	int min = INT_MAX, min_index;

	for (int v = 0; v < V; v++)
		if (sptSet[v] == false && dist[v] <= min)
			min = dist[v], min_index = v;

	return min_index;
}

/*Method to calculate the shortest distances from source to all other vertices and returning the shortest
distance from source to the destination*/
int dijkstra(int graph[V][V], int src, int des)
{
	int dist[V];

	bool sptSet[V];

	for (int i = 0; i < V; i++)
		dist[i] = INT_MAX, sptSet[i] = false;

	dist[src] = 0;

	for (int count = 0; count < V - 1; count++) {

		int u = minDistance(dist, sptSet);

		sptSet[u] = true;

		for (int v = 0; v < V; v++)
        {
			if (!sptSet[v] && graph[u][v] && dist[u] != INT_MAX
				&& dist[u] + graph[u][v] < dist[v])
				dist[v] = dist[u] + graph[u][v];
        }
	}
	return dist[des];
}

//Method to calculate the node which is closer to the destination and thus printing the correct sequence
void getSolution(int graph[V][V], int src, int des, int clen[V])
{
    int nds[V+10],i=0;
    int min = INT_MAX, minval = 0, temp;
	int dist[V];

	bool sptSet[V];

	for (int i = 0; i < V; i++)
		dist[i] = INT_MAX, sptSet[i] = false;

	dist[src] = 0;
	int u = minDistance(dist, sptSet);
	min = clen[u];

	while(u!=des)
	{
	    sptSet[u] = true;
	    nds[i] = u;
	    i++;

	    temp = 9999;

        for(int v = 0; v < V; v++)
        {
            if(v!=des)
            {
                if(graph[u][v] && !sptSet[v])
                {
                    minval = clen[v];

                    if(minval<min)
                    {
                        min = minval;
                        temp=v;
                    }
                }
            }
        }
        u = temp;
        if(u == 9999)
        {
            sptSet[des] = true;
            nds[i] = des;
            break;
        }
	}
	printf("The path is: \n");

    for(int j = 0; j <= i; j++)
    {
        if(j==i)
            printf("%d",nds[j]);
        else
            printf("%d ---> ",nds[j]);
    }
    printf("\n");
}

//Driver method
int main()
{
    FILE *fp;
    fp = fopen("input.txt", "r");      //The file which contains the adjacency matrix of the graph

    if(fp == NULL)
    {
        printf("File failed to open");
        return 0;
    }

    int graph[V][V];
    for(int i = 0; i < V; i++)          //Reading the values into the graph[][] array
    {
        for(int j = 0; j < V; j++)
        {
            fscanf(fp, "%d", &graph[i][j]);
        }
    }
    int clen[V];                        //clen[] array  to store the shortest distance from vertices(sparing source and destination) to the destination
    for(int i = 0; i < V; i++)
    {
        clen[i] = 0;
    }
    int src,des;
    printf("***** Choose from 0 to %d *****\n",(V-1));
    printf("Enter the source ---> ");
    scanf("%d",&src);
    if(src>(V-1) || src<0)
    {
        printf("Source does not  exist!!!!\n");
        return 0;
    }
    printf("\n");
    printf("Enter the destination ---> ");
    scanf("%d",&des);
    if(des>(V-1) || des<0)
    {
        printf("Destination does not  exist!!!!\n");
        return 0;
    }
    printf("\n");

    if(src == des)
    {
        printf("No routes found!!");
        printf("\n");
        return 0;
    }


    for(int i = 0; i < V; i++)
    {
        if(i!=des)
        clen[i] = dijkstra(graph,i,des);
    }

    getSolution(graph,src,des,clen);
    fclose(fp);

	return 0;
}
