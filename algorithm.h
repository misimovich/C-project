#include "functions.h"
using namespace std;
#define MAX 100000

void find_path(pair<int, int> previous[num][num], float dist[num][num], int end_x, int end_y, int start_x, int start_y) {
    while (previous[end_x][end_y].first != start_x || previous[end_x][end_y].second != start_y) {          
        path.push_back(make_pair(previous[end_x][end_y].first, previous[end_x][end_y].second));
        int last_x = end_x, last_y = end_y;
        end_x = previous[last_x][last_y].first;
        end_y = previous[last_x][last_y].second;
    }
}
void dijkstra_algorithm(int begin_x, int begin_y, int end_x, int end_y, int grid[num][num]) {
    pair<int, int> previous[num][num];
    float dist[num][num];
    for (int i = 0; i < num; i++)
        for (int j = 0; j < num; j++)
            dist[i][j] = MAX;
    dist[begin_x][begin_y] = 0.0;
    int found_end = 0;
    for (int i = 0; i < num && found_end == 0; i++)
        for (int j = 0; j < num && found_end == 0; j++) {
            int min_x = 0, min_y = 0;
            find_minimal(dist, min_x, min_y);
            explored[min_x][min_y] = true;
            if (explored[end_x][end_y] == true) {
                found_end = 1;
                break;
            }
            sf::sleep(milliseconds(1));

            //север
            if (grid[min_x - 1][min_y] == 1 && explored[min_x - 1][min_y] == false && dist[min_x - 1][min_y] > dist[min_x][min_y] + 1.0) {
                dist[min_x - 1][min_y] = dist[min_x][min_y] + 1.0;
                previous[min_x - 1][min_y] = make_pair(min_x, min_y);
                
            }
            //юг
            if (grid[min_x + 1][min_y] == 1 && explored[min_x + 1][min_y] == false && dist[min_x + 1][min_y] > dist[min_x][min_y] + 1.0) {
                dist[min_x + 1][min_y] = dist[min_x][min_y] + 1.0;
                previous[min_x + 1][min_y] = make_pair(min_x, min_y);
            }
            //запад
            if (grid[min_x][min_y - 1] == 1 && explored[min_x][min_y - 1] == false && dist[min_x][min_y - 1] > dist[min_x][min_y] + 1.0) {
                dist[min_x][min_y - 1] = dist[min_x][min_y] + 1.0;
                previous[min_x][min_y - 1] = make_pair(min_x, min_y);
            }
            //восток
            if (grid[min_x][min_y + 1] == 1 && explored[min_x][min_y + 1] == false && dist[min_x][min_y + 1] > dist[min_x][min_y] + 1.0) {
                dist[min_x][min_y + 1] = dist[min_x][min_y] + 1.0;
                previous[min_x][min_y + 1] = make_pair(min_x, min_y);
            }
            //северо-восток(диагоналъно)
            if (grid[min_x - 1][min_y + 1] == 1 && explored[min_x - 1][min_y + 1] == false &&
                dist[min_x - 1][min_y + 1] > dist[min_x][min_y] + sqrt(2) && !(grid[min_x - 1][min_y] == 0 && grid[min_x][min_y + 1] == 0)) {
                dist[min_x - 1][min_y + 1] = dist[min_x][min_y] + sqrt(2);
                previous[min_x - 1][min_y + 1] = make_pair(min_x, min_y);
            }
            //юго-восток(диагоналъно)
            if (grid[min_x + 1][min_y + 1] == 1 && explored[min_x + 1][min_y + 1] == false &&
                dist[min_x + 1][min_y + 1] > dist[min_x][min_y] + sqrt(2) && !(grid[min_x + 1][min_y] == 0 && grid[min_x][min_y + 1] == 0)) {
                dist[min_x + 1][min_y + 1] = dist[min_x][min_y] + sqrt(2);
                previous[min_x + 1][min_y + 1] = make_pair(min_x, min_y);
            }
            //северо-запад(диагоналъно)
            if (grid[min_x + 1][min_y - 1] == 1 && explored[min_x + 1][min_y - 1] == false &&
                dist[min_x + 1][min_y - 1] > dist[min_x][min_y] + sqrt(2) && !(grid[min_x + 1][min_y] == 0 && grid[min_x][min_y - 1] == 0)) {
                dist[min_x + 1][min_y - 1] = dist[min_x][min_y] + sqrt(2);
                previous[min_x + 1][min_y - 1] = make_pair(min_x, min_y);
            }
            //юго-запад(диагоналъно)
            if (grid[min_x - 1][min_y - 1] == 1 && explored[min_x - 1][min_y - 1] == false &&
                dist[min_x - 1][min_y - 1] > dist[min_x][min_y] + sqrt(2) && !(grid[min_x - 1][min_y] == 0 && grid[min_x][min_y - 1] == 0)) {
                dist[min_x - 1][min_y - 1] = dist[min_x][min_y] + sqrt(2);
                previous[min_x - 1][min_y - 1] = make_pair(min_x, min_y);
            }
        }
    find_path(previous, dist, end_x, end_y, begin_x, begin_y);
}