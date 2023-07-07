#include <queue>

const int INF = 1000000;
const int MAX_ROWS = 10;
const int MAX_COLS = 10;

struct Cell {
  int row;
  int col;
  int distance;

  Cell(int r, int c, int d) : row(r), col(c), distance(d) {}
};

int dijkstra(char maze[MAX_ROWS][MAX_COLS], Cell start, Cell end) {
  int rows = MAX_ROWS;
  int cols = MAX_COLS;

  int distances[MAX_ROWS][MAX_COLS];
  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < cols; j++) {
      distances[i][j] = INF;
    }
  }
  distances[start.row][start.col] = 0;

  std::priority_queue<Cell, std::vector<Cell>, std::greater<Cell>> pq;
  pq.push(start);

  while (!pq.empty()) {
    Cell currentCell = pq.top();
    pq.pop();

    if (currentCell.row == end.row && currentCell.col == end.col) {
      return distances[end.row][end.col];
    }

    Cell neighbors[4] = {
      Cell(currentCell.row - 1, currentCell.col, currentCell.distance + 1),
      Cell(currentCell.row + 1, currentCell.col, currentCell.distance + 1),
      Cell(currentCell.row, currentCell.col - 1, currentCell.distance + 1),
      Cell(currentCell.row, currentCell.col + 1, currentCell.distance + 1)
    };

    for (int i = 0; i < 4; i++) {
      int row = neighbors[i].row;
      int col = neighbors[i].col;

      if (row >= 0 && row < rows && col >= 0 && col < cols) {
        int newDistance = currentCell.distance + 1;

        if (newDistance < distances[row][col] && maze[row][col] != '#') {
          distances[row][col] = newDistance;
          pq.push(Cell(row, col, newDistance));
        }
      }
    }
  }

  return -1;
}

void setup() {
  // Initialize maze
  char maze[MAX_ROWS][MAX_COLS] = {
    {'S', '.', '.', '#', '.', '.', '.', '.', '.', '.'},
    {'.', '#', '.', '#', '.', '#', '.', '#', '#', '.'},
    {'.', '#', '.', '.', '.', '.', '.', '#', '.', '.'},
    {'.', '#', '#', '#', '#', '#', '.', '#', '.', '.'},
    {'.', '.', '.', '.', '.', '.', '.', '#', '.', '#'},
    {'.', '#', '#', '#', '#', '#', '#', '#', '#', '#'},
    {'.', '#', '.', '.', '.', '#', '.', '.', '.', '#'},
    {'.', '#', '#', '#', '.', '#', '#', '#', '#', '#'},
    {'.', '.', '.', '#', '.', '#', '.', '.', '.', '.'},
    {'.', '#', '#', 'E', '.', '#', '#', '#', '#', '.'}
  };

  Cell start(0, 0, 0);  // Start position (row, column, distance)
  Cell end(9, 3, 0);    // End position (row, column, distance)

  int shortestDistance = dijkstra(maze, start, end);
  Serial.begin(9600);
  Serial.print("Shortest distance: ");
  Serial.println(shortestDistance);
}

void loop() {
  // Your code here
}
