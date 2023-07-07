#include <iostream>
#include <vector>
#include <queue>
#include <climits>

using namespace std;

// Structure to represent a cell in the maze
struct Cell {
    int row;
    int col;
    int distance;

    Cell(int r, int c, int d) : row(r), col(c), distance(d) {}
};

// Helper function to calculate the Manhattan distance between two cells
int manhattanDistance(const Cell& cell1, const Cell& cell2) {
    return abs(cell1.row - cell2.row) + abs(cell1.col - cell2.col);
}

// Function to find the shortest path using Dijkstra's algorithm
int dijkstra(vector<vector<char>>& maze, const Cell& start, const Cell& end) {
    int rows = maze.size();
    int cols = maze[0].size();

    // Initialize distances with infinity
    vector<vector<int>> distances(rows, vector<int>(cols, INT_MAX));
    distances[start.row][start.col] = 0;

    // Priority queue for Dijkstra's algorithm
    priority_queue<Cell, vector<Cell>, function<bool(const Cell&, const Cell&)>> pq([](const Cell& c1, const Cell& c2) {
        return c1.distance > c2.distance;
    });

    // Add the start cell to the priority queue
    pq.push(start);

    while (!pq.empty()) {
        Cell currentCell = pq.top();
        pq.pop();

        // Check if we reached the end point
        if (currentCell.row == end.row && currentCell.col == end.col) {
            return distances[end.row][end.col];
        }

        // Explore neighbors
        vector<Cell> neighbors = {
            Cell(currentCell.row - 1, currentCell.col, currentCell.distance + 1),
            Cell(currentCell.row + 1, currentCell.col, currentCell.distance + 1),
            Cell(currentCell.row, currentCell.col - 1, currentCell.distance + 1),
            Cell(currentCell.row, currentCell.col + 1, currentCell.distance + 1)
        };

        for (const Cell& neighbor : neighbors) {
            int row = neighbor.row;
            int col = neighbor.col;

            // Check if the neighbor is within the maze bounds
            if (row >= 0 && row < rows && col >= 0 && col < cols) {

                // Calculate the new distance to the neighbor
                int newDistance = currentCell.distance + manhattanDistance(currentCell, neighbor);

                // Update the distance if it's shorter
                if (newDistance < distances[row][col] && maze[row][col] != '#') {
                    distances[row][col] = newDistance;
                    pq.push(Cell(row, col, newDistance));
                }
            }
        }
    }

    // No path found
    return -1;
}

int main() {
    vector<vector<char>> maze = {
        {'S', '.', '.', '#', '.', '.', '.'},
        {'.', '#', '.', '#', '.', '#', '.'},
        {'.', '#', '.', '.', '.', '.', '.'},
        {'.', '.', '#', '#', '#', '.', '.'},
        {'.', '#', '#', 'E', '#', '#', '.'},
    };

    Cell start(0, 0, 0);  // Start position (row, column, distance)
    Cell end(4, 3, 0);    // End position (row, column, distance)

    int shortestDistance = dijkstra(maze, start, end);
    cout << "Shortest distance: " << shortestDistance << endl;

    return 0;
}
