#include "graph_traversals.h"
#include "safe_input.h"
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>

/**
 * prim_mst - Implements Prim's algorithm to find the Minimum Spanning Tree (MST).
 * @graph: The weighted undirected graph.
 * @start_node: The starting node for the algorithm.
 * 
 * Returns the total weight of the MST, or -1 on error.
 */
int prim_mst(weightedGraph* graph, int start_node) {
    if (graph == NULL || start_node < 0 || start_node >= graph->V) {
        return -1;
    }

    int V = graph->V;
    int* key = (int*)malloc(V * sizeof(int));
    int* parent = (int*)malloc(V * sizeof(int));
    bool* in_mst = (bool*)malloc(V * sizeof(bool));

    if (!key || !parent || !in_mst) {
        free(key);
        free(parent);
        free(in_mst);
        return -1;
    }

    for (int i = 0; i < V; i++) {
        key[i] = INT_MAX;
        parent[i] = -1;
        in_mst[i] = false;
    }

    PQ_graph pq;
    init_pq_graph(&pq, V);
    if (!pq.heap) {
        free(key);
        free(parent);
        free(in_mst);
        return -1;
    }

    key[start_node] = 0;
    insert_pq_graph(&pq, start_node, 0);

    int mst_weight = 0;
    int nodes_in_mst = 0;

    printf("Edges in the Minimum Spanning Tree (Prim's Algorithm):\n");
    printf("Source -- Destination == Weight\n");

    while (pq.size > 0) {
        PQ_graph_node top;
        if (!extractTop_pq_graph(&pq, &top)) break;

        int u = top.vertex;

        if (in_mst[u]) continue;

        in_mst[u] = true;
        mst_weight += top.distance;
        nodes_in_mst++;

        if (parent[u] != -1) {
            printf("%d -- %d == %d\n", parent[u], u, top.distance);
        }

        Edge* curr = graph->array[u];
        while (curr) {
            int v = curr->destination;
            int weight = curr->weight;

            if (!in_mst[v] && weight < key[v]) {
                key[v] = weight;
                parent[v] = u;
                insert_pq_graph(&pq, v, key[v]);
            }
            curr = curr->next;
        }
    }

    if (nodes_in_mst < V) {
        printf("Warning: The graph is disconnected. The result is a Minimum Spanning Forest.\n");
    }

    printf("Total Weight of MST: %d\n", mst_weight);

    free_pq_graph(&pq);
    free(key);
    free(parent);
    free(in_mst);

    return mst_weight;
}

void prim_demo(void) {
    int V, E, start;
    printf("\n--- Prim's MST Demo ---\n");
    if (safe_input_int(&V, "Enter number of vertices: ", 1, 1000) != 0) return;
    if (safe_input_int(&E, "Enter number of edges: ", 0, 10000) != 0) return;

    weightedGraph* graph = create_weightedGraph(V);
    if (!graph) return;

    printf("Enter edges (source destination weight):\n");
    for (int i = 0; i < E; i++) {
        int u, v, w;
        printf("Edge %d:\n", i + 1);
        if (safe_input_int(&u, "  Source: ", 0, V - 1) != 0) break;
        if (safe_input_int(&v, "  Destination: ", 0, V - 1) != 0) break;
        if (safe_input_int(&w, "  Weight: ", 0, 10000) != 0) break;
        
        // Prim's algorithm is typically for undirected graphs
        add_edge_directed(graph, u, v, w);
        add_edge_directed(graph, v, u, w);
    }

    if (safe_input_int(&start, "Enter starting node: ", 0, V - 1) == 0) {
        prim_mst(graph, start);
    }

    free_weightedGraph(graph);
}
