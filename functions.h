#include<iostream>
#include<functional>        
#include<math.h>        
#include<float.h>
#include<vector>
#include<set>
#define num 20
using namespace std;
using namespace sf;
typedef pair<int, int> Point;
vector<pair<int, int>> path;        
bool explored[num][num];


void find_minimal(float dist[num][num], int& min_x, int& min_y) {
    float min = 100000;
    for (int i = 0; i < num; i++)
        for (int j = 0; j < num; j++)
            if (explored[i][j] == false && dist[i][j] < min) {
                min = dist[i][j];
                min_x = i;
                min_y = j;
            }
}
bool reached_end(int row, int col, Point end) {
    if (row == end.first && col == end.second)
        return true;
    else
        return false;
}
