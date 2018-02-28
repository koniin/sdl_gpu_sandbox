#ifndef _MAZE_H
#define _MAZE_H

#include <vector>
#include <random>

enum Directions {
	North = 1,
	South = 2,
	West = 4,
	East = 8
};
inline Directions operator|(Directions a, Directions b) {
	return static_cast<Directions>(static_cast<int>(a) | static_cast<int>(b));
}
inline Directions operator&(Directions a, Directions b) {
	return static_cast<Directions>(static_cast<int>(a) & static_cast<int>(b));
}

struct Cell {
	bool IsOpen = false;
	bool IsLeftWallOpen = false;
	bool IsTopWallOpen = false;
	Directions Openings;
};

struct Maze {
	Cell* buffer;
	int cols;
	int rows;
	size_t index(int x, int y) const { return x + cols * y; }
	Cell cell(int x, int y) {
		return buffer[index(x, y)];
	}
};

Maze* generateMaze(int cols, int rows) {
	Cell* maze = new Cell[cols*rows];
	Maze* m = new Maze();
	m->buffer = maze;
	m->cols = cols;
	m->rows = rows;
	return m;
}

std::random_device seed;
std::mt19937 rng(seed());

struct Point {
	int x;
	int y;
	Point(int xPos, int yPos) {
		x = xPos;
		y = yPos;
	}
};

Point randomPoint(int max) {
	std::uniform_int_distribution<int> gen(0, max);
	Point p(gen(rng), gen(rng));
	return p;
}

std::vector<Cell> cellsToVisit;
void growTree(Maze* maze) {
	cellsToVisit.clear();

	//Point start = randomPoint(
	
	// var start = RNG.PointInRectangle(Bounds);
	// cells[start.Y, start.X].IsOpen = true;
	maze->buffer[maze->index(1, 0)].IsLeftWallOpen = true;
	// cellsToVisit.Add(start);
}

void printMaze(Maze* maze) {
	maze->buffer[maze->index(1, 0)].IsLeftWallOpen = true;
	for (int y = 0; y < maze->rows; y++) {
		for (int x = 0; x < maze->cols; x++) {
			printf("y:%d, x:%d leftwall: %s | ", y, x, maze->buffer[maze->index(x, y)].IsLeftWallOpen ? "true" : "false");
		}
		printf("\n");
	}
	//maze[y*rows + x]
	// or 
	//maze[x*cols + y]
	// for(int i = 0; i < 
}

void freeMaze(Maze* maze) {
	delete[] maze->buffer;
	delete maze;
}

/*

public static class MazeDir {
public static Point North = new Point(0, -1);
public static Point South = new Point(0, 1);
public static Point West = new Point(-1, 0);
public static Point East = new Point(1, 0);
public static Point[] PointDirections = { North, South, East, West };
public static int N = 1;
public static int S = 2;
public static int E = 4;
public static int W = 8;
public static Directions[] AllDirections = { Directions.North, Directions.South, Directions.West, Directions.East };
}

[Flags]
public enum Directions {
North = 1,
South = 2,
West = 4,
East = 8
}

// Define other methods and classes here
public class Maze {
public Rectangle Bounds;
private readonly Cell[,] cells;
private List<Point> cellsToVisit = new List<Point>();

public readonly int Height;
public readonly int Width;

public struct Cell {
public bool IsOpen;
public bool IsLeftWallOpen;
public bool IsTopWallOpen;
public Directions Openings;
}

public Maze(int width, int height) {
Width = width;
Height = height;

Bounds = new Rectangle(0, 0, width, height);
// pad by one for the outer bottom and right walls
cells = new Cell[width, height];
}

public ref Cell this[Point p] => ref cells[p.Y, p.X];
public ref Cell this[int x, int y] => ref cells[y, x];

/// <summary>
/// Generates the maze with random selection from unvisited nodes
/// How to selected the next cell to visit can make a big difference in how the maze looks
/// </summary>
public void GrowTree() {
cellsToVisit.Clear();

// start with a random cell
var start = RNG.PointInRectangle(Bounds);
cells[start.Y, start.X].IsOpen = true;
cellsToVisit.Add(start);

while (cellsToVisit.Count > 0) {
// How we select the next cell determines the properties of the maze
// Selection is important !!
int index = RNG.NextInt(cellsToVisit.Count);

// Select a neighbour from this cell if any by shuffling the directions we go in
RNG.Shuffle(MazeDir.PointDirections);
foreach (var direction in MazeDir.PointDirections) {
var neighbour = cellsToVisit[index] + direction;
if (Bounds.Contains(neighbour) && !this[neighbour].IsOpen) {
this[neighbour].IsOpen = true;

var current = cellsToVisit[index];

if (direction == MazeDir.North) {
this[current].IsTopWallOpen = true;

this[current].Openings |= Directions.North;
this[neighbour].Openings |= Directions.South;
} else if (direction == MazeDir.South) {
this[neighbour].IsTopWallOpen = true;

this[current].Openings |= Directions.South;
this[neighbour].Openings |= Directions.North;
} else if (direction == MazeDir.West) {
this[current].IsLeftWallOpen = true;

this[current].Openings |= Directions.West;
this[neighbour].Openings |= Directions.East;
} else if (direction == MazeDir.East) {
this[neighbour].IsLeftWallOpen = true;

this[current].Openings |= Directions.East;
this[neighbour].Openings |= Directions.West;
}

cellsToVisit.Add(neighbour);
index = -1;
break;
}
}

if (index >= 0)
cellsToVisit.RemoveAt(index);
}
}
*/

#endif