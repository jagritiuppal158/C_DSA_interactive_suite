#include "graph_traversals.h"
#include "telemetry.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static void verify_telemetry_file(const char* expected_algo_name)
{
    FILE* fp = fopen("test_binaries/graph_trace.json", "r");
    assert(fp != NULL);

    char buffer[65536];
    size_t bytes_read = fread(buffer, 1, sizeof(buffer) - 1, fp);
    buffer[bytes_read] = '\0';
    fclose(fp);

    // Verify it is a valid JSON array and has the correct algorithm name
    assert(buffer[0] == '[');
    assert(strstr(buffer, expected_algo_name) != NULL);
    assert(strstr(buffer, "\"step\":") != NULL);
    assert(strstr(buffer, "\"message\":") != NULL);

    int len = strlen(buffer);
    while (len > 0 &&
           (buffer[len - 1] == '\n' || buffer[len - 1] == ' ' || buffer[len - 1] == '\r'))
    {
        len--;
    }
    assert(buffer[len - 1] == ']');

    // Clean up
    remove("test_binaries/graph_trace.json");
}

static void test_dfs_telemetry(void)
{
    set_telemetry_enabled(true);
    set_telemetry_filepath("test_binaries/graph_trace.json");

    Graph* g = create_graph(4);
    add_edge_undirected(g, 0, 1);
    add_edge_undirected(g, 0, 2);
    add_edge_undirected(g, 1, 2);
    add_edge_undirected(g, 2, 0);
    add_edge_undirected(g, 2, 3);
    add_edge_undirected(g, 3, 3);

    dfs(g, 2);

    verify_telemetry_file("dfs");
    free_graph(g);
}

static void test_bfs_telemetry(void)
{
    set_telemetry_enabled(true);
    set_telemetry_filepath("test_binaries/graph_trace.json");

    Graph* g = create_graph(4);
    add_edge_undirected(g, 0, 1);
    add_edge_undirected(g, 0, 2);
    add_edge_undirected(g, 1, 2);
    add_edge_undirected(g, 2, 0);
    add_edge_undirected(g, 2, 3);
    add_edge_undirected(g, 3, 3);

    bfs(g, 2);

    verify_telemetry_file("bfs");
    free_graph(g);
}

int main(void)
{
    printf("Starting Graph Telemetry integration tests...\n");
    test_dfs_telemetry();
    test_bfs_telemetry();
    printf("All Graph Telemetry integration tests passed successfully!\n");
    return 0;
}
