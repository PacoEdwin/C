/*//#include <iostream>
#include<fstream>
#include<vector>
#include<string>
#include<algorithm>
using namespace std;
int n;
struct weight
{
	struct data
	{
		int key = INT_MAX;
		int pos;
		int marked;
		data* ancestor=NULL;
	};
	data* link = new data;
	int w;
};//
vector<vector<weight*>> graph;
vector<weight::data*> v;
weight::data* extractmin()
{
	int min = INT_MAX;
	int ind = 0;
	for (int i = 0; i < v.size(); i++)
	{
		if (v[i]->key <= min && v[i]->marked == 0)
		{
			min = v[i]->key;
			ind = i;
		}
	}
	v[ind]->marked = 1;
	return v[ind];
}
void prim()
{
	v[0]->key = 0;
}
int main()
{
	int m;
	fin >> n >> m;
	v.resize(n);
	graph.resize(n);
	for (int i = 0; i < n; i++)
	{
		weight::data* u = new weight::data;
		v[i] = u;
	}
	for (int i = 0; i < m; i++)
	{
		int a, b, c;
		fin >> a >> b >> c;
		v[a - 1]->pos = a - 1;
		v[b - 1]->pos = b - 1;
		weight* u = new weight;
		weight *kek = new weight;
		u->link = v[b - 1];
		kek->link = v[a - 1];
		u->w = kek->w = c;
		graph[a - 1].push_back(u);
		graph[b - 1].push_back(kek);
	}
	prim();
	system("pause");
	return 0;
}*/
#include <iostream>
#include<fstream>
#include<vector>
#include<string>
using namespace std;
struct weight
{
	struct data
	{
		int pos;
		int key = INT_MAX;
		int marked = 0;
	};
	data* link = new data;
	int w;
};
vector<weight::data*> v;
vector<vector<weight*>> graph;
vector<weight::data*> S;
weight::data* extractmin()
{
	int min = INT_MAX;
	int ind = 0;
	for (int i = 0; i < v.size(); i++)
	{
		if (v[i]->key <= min && v[i]->marked == 0)
		{
			min = v[i]->key;
			ind = i;
		}
	}
	v[ind]->marked = 1;
	return v[ind];
}
void dijkstra(int s)
{
	v[s]->key = 0;
	v[s]->marked = 1;
	for (int i = 0; i < v.size(); i++)
	{
		weight::data *u;
		if (i == 0)
			u = v[s];
		else
			u = extractmin();
		if (u->key == INT_MAX)
			break;
		S.push_back(u);
		for (int j = 0; j < graph[u->pos].size(); j++)
		{
			if (u->key + graph[u->pos][j]->w <= graph[u->pos][j]->link->key)
				graph[u->pos][j]->link->key = u->key + graph[u->pos][j]->w;
		}
	}
}
int main()
{
	ifstream fin("pathbgep.in");
	ofstream fout("pathbgep.out");
	int n, m;
	int s = 1;
	cin >> n >> m;
	int f = n;
	v.resize(n);
	graph.resize(n);
	for (int i = 0; i < n; i++)
	{
		weight::data *u = new weight::data;
		v[i] = u;
	}
	for (int i = 0; i < m; i++)
	{
		int a, b, w;
		cin >> a >> b >> w;
		v[a - 1]->pos = a - 1;
		v[b - 1]->pos = b - 1;
		weight* u = new weight;
		weight *kek = new weight;
		u->link = v[b - 1];
		kek->link = v[a - 1];
		u->w = kek->w = w;
		graph[a - 1].push_back(u);
		graph[b - 1].push_back(kek);
	}
	dijkstra(s - 1);
	for (int i = 0; i < v.size(); i++)
	  cout << v[i]->key << " ";
	return 0;
}
//// C / C++ program for Dijkstra's shortest path algorithm for adjacency
//// list representation of graph
//
//#include <stdio.h>
//#include <stdlib.h>
//#include <limits.h>
//#include<iostream>
//#include<fstream>
//using namespace std;
//ifstream fin("pathbgep.in");
//ofstream fout("pathbgep.out");
//struct AdjListNode
//{
//	int dest;
//	int weight;
//	struct AdjListNode* next;
//};
//
//struct AdjList
//{
//	struct AdjListNode *head;  // pointer to head node of list
//};
//
//struct Graph
//{
//	int V;
//	struct AdjList* array;
//};
//
//// A utility function to create a new adjacency list node
//struct AdjListNode* newAdjListNode(int dest, int weight)
//{
//	struct AdjListNode* newNode =
//		(struct AdjListNode*) malloc(sizeof(struct AdjListNode));
//	newNode->dest = dest;
//	newNode->weight = weight;
//	newNode->next = NULL;
//	return newNode;
//}
//
//struct Graph* createGraph(int V)
//{
//	struct Graph* graph = (struct Graph*) malloc(sizeof(struct Graph));
//	graph->V = V;
//
//	graph->array = (struct AdjList*) malloc(V * sizeof(struct AdjList));
//
//	for (int i = 0; i < V; ++i)
//		graph->array[i].head = NULL;
//
//	return graph;
//}
//
//void addEdge(struct Graph* graph, int src, int dest, int weight)
//{
//	
//	struct AdjListNode* newNode = newAdjListNode(dest, weight);
//	newNode->next = graph->array[src].head;
//	graph->array[src].head = newNode;
//
//	newNode = newAdjListNode(src, weight);
//	newNode->next = graph->array[dest].head;
//	graph->array[dest].head = newNode;
//}
//
//struct MinHeapNode
//{
//	int  v;
//	int dist;
//};
//
//struct MinHeap
//{
//	int size;      // Number of heap nodes present currently
//	int capacity;  // Capacity of min heap
//	int *pos;     // This is needed for decreaseKey()
//	struct MinHeapNode **array;
//};
//
//struct MinHeapNode* newMinHeapNode(int v, int dist)
//{
//	struct MinHeapNode* minHeapNode =
//		(struct MinHeapNode*) malloc(sizeof(struct MinHeapNode));
//	minHeapNode->v = v;
//	minHeapNode->dist = dist;
//	return minHeapNode;
//}
//
//struct MinHeap* createMinHeap(int capacity)
//{
//	struct MinHeap* minHeap =
//		(struct MinHeap*) malloc(sizeof(struct MinHeap));
//	minHeap->pos = (int *)malloc(capacity * sizeof(int));
//	minHeap->size = 0;
//	minHeap->capacity = capacity;
//	minHeap->array =
//		(struct MinHeapNode**) malloc(capacity * sizeof(struct MinHeapNode*));
//	return minHeap;
//}
//
//void swapMinHeapNode(struct MinHeapNode** a, struct MinHeapNode** b)
//{
//	struct MinHeapNode* t = *a;
//	*a = *b;
//	*b = t;
//}
//
//
//void minHeapify(struct MinHeap* minHeap, int idx)
//{
//	int smallest, left, right;
//	smallest = idx;
//	left = 2 * idx + 1;
//	right = 2 * idx + 2;
//
//	if (left < minHeap->size &&
//		minHeap->array[left]->dist < minHeap->array[smallest]->dist)
//		smallest = left;
//
//	if (right < minHeap->size &&
//		minHeap->array[right]->dist < minHeap->array[smallest]->dist)
//		smallest = right;
//
//	if (smallest != idx)
//	{
//		MinHeapNode *smallestNode = minHeap->array[smallest];
//		MinHeapNode *idxNode = minHeap->array[idx];
//
//		minHeap->pos[smallestNode->v] = idx;
//		minHeap->pos[idxNode->v] = smallest;
//
//		swapMinHeapNode(&minHeap->array[smallest], &minHeap->array[idx]);
//
//		minHeapify(minHeap, smallest);
//	}
//}
//
//int isEmpty(struct MinHeap* minHeap)
//{
//	return minHeap->size == 0;
//}
//
//struct MinHeapNode* extractMin(struct MinHeap* minHeap)
//{
//	if (isEmpty(minHeap))
//		return NULL;
//
//	struct MinHeapNode* root = minHeap->array[0];
//
//	struct MinHeapNode* lastNode = minHeap->array[minHeap->size - 1];
//	minHeap->array[0] = lastNode;
//
//	minHeap->pos[root->v] = minHeap->size - 1;
//	minHeap->pos[lastNode->v] = 0;
//
//	// Reduce heap size and heapify root
//	--minHeap->size;
//	minHeapify(minHeap, 0);
//
//	return root;
//}
//
//
//void decreaseKey(struct MinHeap* minHeap, int v, int dist)
//{
//	// Get the index of v in  heap array
//	int i = minHeap->pos[v];
//
//	// Get the node and update its dist value
//	minHeap->array[i]->dist = dist;
//
//	while (i && minHeap->array[i]->dist < minHeap->array[(i - 1) / 2]->dist)
//	{
//		// Swap this node with its parent
//		minHeap->pos[minHeap->array[i]->v] = (i - 1) / 2;
//		minHeap->pos[minHeap->array[(i - 1) / 2]->v] = i;
//		swapMinHeapNode(&minHeap->array[i], &minHeap->array[(i - 1) / 2]);
//
//		// move to parent index
//		i = (i - 1) / 2;
//	}
//}
//
//
//bool isInMinHeap(struct MinHeap *minHeap, int v)
//{
//	if (minHeap->pos[v] < minHeap->size)
//		return true;
//	return false;
//}
//
//void printArr(int dist[], int n)
//{
//	for (int i = 0; i < n; ++i)
//		cout << dist[i] << " ";
//  cout << endl;
//}
//
//void dijkstra(struct Graph* graph, int src)
//{
//	int V = graph->V;// Get the number of vertices in graph
//	int *dist= new int[V];      // dist values used to pick minimum weight edge in cut
//
//	// minHeap represents set E
//	struct MinHeap* minHeap = createMinHeap(V);
//
//	// Initialize min heap with all vertices. dist value of all vertices 
//	for (int v = 0; v < V; ++v)
//	{
//		dist[v] = INT_MAX;
//		minHeap->array[v] = newMinHeapNode(v, dist[v]);
//		minHeap->pos[v] = v;
//	}
//
//	// Make dist value of src vertex as 0 so that it is extracted first
//	minHeap->array[src] = newMinHeapNode(src, dist[src]);
//	minHeap->pos[src] = src;
//	dist[src] = 0;
//	decreaseKey(minHeap, src, dist[src]);
//
//	// Initially size of min heap is equal to V
//	minHeap->size = V;
//
//	// In the followin loop, min heap contains all nodes
//	// whose shortest distance is not yet finalized.
//	while (!isEmpty(minHeap))
//	{
//		// Extract the vertex with minimum distance value
//		struct MinHeapNode* minHeapNode = extractMin(minHeap);
//		int u = minHeapNode->v; // Store the extracted vertex number
//
//		// Traverse through all adjacent vertices of u (the extracted
//		// vertex) and update their distance values
//		struct AdjListNode* pCrawl = graph->array[u].head;
//		while (pCrawl != NULL)
//		{
//			int v = pCrawl->dest;
//
//			// If shortest distance to v is not finalized yet, and distance to v
//			// through u is less than its previously calculated distance
//			if (isInMinHeap(minHeap, v) && dist[u] != INT_MAX &&
//				pCrawl->weight + dist[u] < dist[v])
//			{
//				dist[v] = dist[u] + pCrawl->weight;
//
//				// update distance value in min heap also
//				decreaseKey(minHeap, v, dist[v]);
//			}
//			pCrawl = pCrawl->next;
//		}
//	}
//
//	// print the calculated shortest distances
//	printArr(dist, V);
//}
//
//
//// Driver program to test above functions
//int main()
//{
//	int n, m;
//	cin >> n >> m;
//	struct Graph* graph = createGraph(n);
//	for (int i = 0; i < m; i++)
//	{
//		int a, b, w;
//		cin >> a >> b >> w;
//		addEdge(graph, a - 1, b - 1, w);
//	}
//
//	dijkstra(graph, 0);
//	system("pause");
//	return 0;
//}