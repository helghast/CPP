/**
http://en.wikipedia.org/wiki/A*
original code from https://stackoverflow.com/questions/26210108/a-star-shortest-path-algorithm 
(added some improvements and optimizations)

In computer science, A* (pronounced "A star") is a computer algorithm that is widely used in pathfinding and graph traversal, which is 
the process of finding a path between multiple points, called "nodes". It enjoys widespread use due to its performance and accuracy. 
However, in practical travel-routing systems, it is generally outperformed by algorithms which can pre-process the graph to attain 
better performance, although other work has found A* to be superior to other approaches. */
#include <istream>
#include <iostream>
#include <iomanip>
#include <queue>
#include <string>
#include <math.h>
#include <ctime>
using namespace std;

#define mapWidth 60 // horizontal size of the map
#define mapHeight 60 // vertical size size of the map
static int map[mapWidth][mapHeight]; //grid
static int closedNodesMap[mapWidth][mapHeight]; // map of closed (tried-out) nodes
static int openNodesMap[mapWidth][mapHeight]; // map of open (not-yet-tried) nodes
static int directionsMap[mapWidth][mapHeight]; // map of directions
#define directions 8 // number of possible directions to go at any position. Using 4 directions increase speed.
#if directions == 4
static int dx[directions]={1, 0, -1, 0};
static int dy[directions]={0, 1, 0, -1};
#elif directions == 8
static int dx[directions] = {1, 1, 0, -1, -1, -1, 0, 1};
static int dy[directions] = {0, 1, 1, 1, 0, -1, -1, -1};
#endif // directions
static char tips[5] = {'.', 'O'/*obstacle*/, 'S'/*start*/, 'R'/*route*/, 'F'/*finish*/};
static int x, y;

class Node
{
private:
    int xPos, yPos; // current position
    int level; // total distance already travelled to reach the Node
    int priority;  // priority=level+remaining distance estimate // smaller: higher priority
public:
    Node(const int xPos, const int yPos, const int level, const int priority) 
		: xPos(xPos), yPos(yPos), level(level), priority(priority){}
    int getxPos() const {return xPos;}
    int getyPos() const {return yPos;}
    int getLevel() const {return level;}
    int getPriority() const {return priority;}
    void updatePriority(const int xDest, const int yDest) { priority = level + estimate(xDest, yDest) * 10; /*A**/ }

    // give better priority to going strait instead of diagonally
    void nextLevel(const int direction)
    {
        level += (directions == 8 ? (direction % 2 == 0 ? 10 : 14) : 10);
    }

    // Estimation function for the remaining distance to the goal.
    int estimate(const int xDest, const int yDest) const
    {
        const int xd = xDest - xPos;
        const int yd = yDest - yPos;
        const int distance = static_cast<int>(sqrt(xd * xd + yd * yd)); // Euclidian Distance. Pitagoras: h^2=a^2+b^2
        //const int distance = abs(xd) + abs(yd); // Manhattan distance
        //const int distance = max(abs(xd), abs(yd)); // Chebyshev distance
        return distance;
    }
};

// Determine priority (in the priority queue)
bool operator<(const Node& a, const Node& b) { return a.getPriority() > b.getPriority(); }

int updateDirection(const int Value){ return (Value + directions / 2) % directions; }

// A-star algorithm. // The route returned is a string of direction digits.
string pathFind(const int xStart, const int yStart, const int xFinish, const int yFinish)
{
    static priority_queue<Node> pq[2]; // list of open (not-yet-tried) nodes
    static int pqi; // pq index
    static Node* n0;
    static Node* m0;
    static int i, j, xdx, ydy;
    static char c;
    pqi = 0;

    // reset the Node maps
    for (y = 0; y < mapHeight; ++y)
    {
        for (x = 0; x < mapWidth; ++x)
        {
            closedNodesMap[x][y] = 0;
            openNodesMap[x][y] = 0;
        }
    }

    // create the start Node and push into list of open nodes
    n0 = new Node(xStart, yStart, 0, 0);
    n0->updatePriority(xFinish, yFinish);
    pq[pqi].push(*n0);
    openNodesMap[x][y] = n0->getPriority(); // mark it on the open nodes map

    // A* search
    while (!pq[pqi].empty())
    {
        // get the current Node w/ the highest priority from the list of open nodes
        const Node& currentNode = pq[pqi].top();
        n0 = new Node(currentNode.getxPos(), currentNode.getyPos(), currentNode.getLevel(), currentNode.getPriority());

        x = n0->getxPos();
        y = n0->getyPos();

        pq[pqi].pop(); // remove the Node from the open list
        openNodesMap[x][y] = 0;
        closedNodesMap[x][y] = 1; // mark it on the closed nodes map

        // quit searching when the goal state is reached
        //if((*n0).estimate(xFinish, yFinish) == 0)
        if (x == xFinish && y == yFinish)
        {
            // generate the path from finish to start by following the directions
            string path = "";
            while (!(x == xStart && y == yStart))
            {
                j = directionsMap[x][y];
                c = '0' + updateDirection(j);
                path = c + path;
                x += dx[j];
                y += dy[j];
            }

            delete n0; // garbage collection
            // empty the leftover nodes
            while (!pq[pqi].empty()) { pq[pqi].pop(); }
            return path;
        }

        // generate moves (child nodes) in all possible directions
        for (i = 0; i < directions; ++i)
        {
            xdx = x + dx[i];
            ydy = y + dy[i];

            if (!(xdx < 0 || xdx > mapWidth - 1 || ydy < 0 || ydy > mapHeight - 1 || map[xdx][ydy] == 1 
				|| closedNodesMap[xdx][ydy] == 1))
            {
                m0 = new Node(xdx, ydy, n0->getLevel(), n0->getPriority()); // generate a child Node
                m0->nextLevel(i);
                m0->updatePriority(xFinish, yFinish);

                // if it is not in the open list then add into that
                int& openNode = openNodesMap[xdx][ydy];
                int& direction = directionsMap[xdx][ydy];
                const int& m0Priority = m0->getPriority();
                if (openNode == 0)
                {
                    openNode = m0Priority; // update the priority info
                    pq[pqi].push(*m0);
                    direction = updateDirection(i); // mark its parent Node direction
                }
                else if (openNode > m0Priority)
                {
                    openNode = m0Priority; // update the priority info
                    direction = updateDirection(i); // update the parent direction info

                    /* replace the Node by emptying one pq to the other one except the Node to be replaced will be ignored and the 
					new Node will be pushed in instead */
                    const Node& replaceNode = pq[pqi].top();
                    while (!(replaceNode.getxPos() == xdx && replaceNode.getyPos() == ydy))
                    {
                        pq[1 - pqi].push(replaceNode);
                        pq[pqi].pop();
                    }
                    pq[pqi].pop(); // remove the wanted Node

                    // empty the larger size pq to the smaller one
                    if (pq[pqi].size() > pq[1 - pqi].size()) { pqi = 1 - pqi; }
                    while (!pq[pqi].empty())
                    {
                        pq[1 - pqi].push(pq[pqi].top());
                        pq[pqi].pop();
                    }
                    pqi = 1 - pqi;
                    pq[pqi].push(*m0); // add the better Node instead
                }
                else { delete m0; } // garbage collection
            }
        }
        delete n0; // garbage collection
    }
    return ""; // no route found
}

int main()
{
    srand(time(0));

    // create empty map. print in every map location a dot
    for (y = 0; y < mapHeight; ++y)
    {
        for (x = 0; x < mapWidth; ++x) { map[x][y] = 0; }
    }

    //fillout the map matrix with a '+' pattern obstacles
    const int xn = mapWidth * 0.125; //1/8 = 0.125
    const int nn = xn * 7;
    const int xMapHeight = mapHeight * 0.5; //1/2 = 0.5
    const int xm = mapHeight * 0.125;
    const int mm = xm * 7;
    const int xMapWidth = mapWidth * 0.5;
    for (x = xn; x < nn; ++x) { map[x][xMapHeight] = 1; }
    for (y = xm; y < mm; ++y) { map[xMapWidth][y] = 1; }

    // randomly select start and finish locations
    int xA, yA, xB, yB;
    switch (rand() % 8)
    {
        case 0: xA = 0; yA = 0; xB = mapWidth - 1; yB = mapHeight - 1; break;
        case 1: xA = 0; yA = mapHeight - 1; xB = mapWidth - 1; yB = 0; break;
        case 2: xA = mapWidth / 2 - 1; yA = mapHeight / 2 - 1; xB = mapWidth / 2 + 1; yB = mapHeight / 2 + 1; break;
        case 3: xA = mapWidth / 2 - 1; yA = mapHeight / 2 + 1; xB = mapWidth / 2 + 1; yB = mapHeight / 2 - 1; break;
        case 4: xA = mapWidth / 2 - 1; yA = 0; xB = mapWidth / 2 + 1; yB = mapHeight - 1; break;
        case 5: xA = mapWidth / 2 + 1; yA = mapHeight - 1; xB = mapWidth / 2 - 1; yB = 0; break;
        case 6: xA = 0; yA = mapHeight / 2 - 1; xB = mapWidth - 1; yB = mapHeight / 2 + 1; break;
        case 7: xA = mapWidth - 1; yA = mapHeight / 2 + 1; xB = 0; yB = mapHeight / 2 - 1; break;
    }

    cout << "Using " << directions << " directions" << endl;
    cout << "Map Size (X,Y): " << mapWidth << "," << mapHeight << endl;
    cout << "Start: " << xA << "," << yA << endl;
    cout << "Finish: " << xB << "," << yB << endl;

    // get the route and calculate the time
    clock_t start = clock();
    const string route = pathFind(xA, yA, xB, yB);
    clock_t end = clock();
    const int length = route.size();
    if (length == 0) { cout << "An empty route generated!" << endl; }
    const double time_elapsed = static_cast<double>(end - start);
    cout << "Time to calculate the route (ms): " << time_elapsed << endl;
    cout << "Route:" << endl;
    cout << route << endl << endl;

    // follow the route on the map and display it
    if (length > 0)
    {
        int j;
        char c;
        x = xA;
        y = yA;
        map[x][y] = 2; //set the Start tip
        for (int i = 0; i < length; ++i)
        {
            c = route.at(i);
            j = atoi(&c);
            x = x + dx[j];
            y = y + dy[j];
            map[x][y] = 3; //set the Route tip
        }
        map[x][y] = 4; //set the Finish tip

        // display the map with the route
        for (y = 0; y < mapHeight; ++y)
        {
            for (x = 0; x < mapWidth; ++x){ cout << tips[map[x][y]]; }
            cout << endl;
        }
    }

    return 0;
}
