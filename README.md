# SimpleNavigator

## Description

In this project implemented some basic algorithms on graphs.

## Command line interface

- Run `make nav_cli` command from `src` directory.
- Executable file `nav` will be built to `build` directory of project root
- CLI synopsys (from `build` directory): `./nav [-f] [path/to/graph/file] [any option]`. The next options implemented for the CLI:
    - `[-m] [algorithm]` sets one of next algorithms:
        1. `DFS` - non-recursive depth-first search in the graph from a given vertex. It needs additional start vertex specified as `[-s] [3]` where `3` is vertex number.
        2. `BFS` - breadth-first search in the graph from a given vertex. It needs additional start vertex specified as `[-s] [3]`.
        3. `SPBV` - searching for the shortest path between two vertices in a graph using Dijkstra's algorithm. It needs additional start and end vertexes specified as `[-s] [3] [-e] [4]`.
        4. `SPBA` - searching for the shortest paths between all pairs of vertices in a graph using the Floyd-Warshall algorithm.
        5. `LST` - searching for the minimal spanning tree in a graph using Prim's algorithm.
        6. `TSP` - solving the traveling salesman's problem using the ant colony algorithm.
    - `[-o] [path/to/file.dot]` export graph to `dot` format file.
- Graph file format must be like:
```
11
0   29  20  21  16  31  100 12  4   31  18
29  0   15  29  28  40  72  21  29  41  12
20  15  0   15  14  25  81  9   23  27  13
21  29  15  0   4   12  92  12  25  13  25
16  28  14  4   0   16  94  9   20  16  22
31  40  25  12  16  0   95  24  36  3   37
100 72  81  92  94  95  0   90  101 99  84
12  21  9   12  9   24  90  0   15  25  13
4   29  23  25  20  36  101 15  0   35  18
31  41  27  13  16  3   99  25  35  0   38
18  12  13  25  22  37  84  13  18  38  0
```
> Here, the first number `11` equals to rows and cols of the matrix - is amount of graph vertexes, and each number of matrix on `i` row and `j` col is edge length value on the way from `i` to `j` vertex.
