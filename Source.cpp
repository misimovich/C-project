#include<SFML/Graphics.hpp>
#include<SFML/Window.hpp>
#include"algorithm.h"
#include "constants.h"
using namespace std;
using namespace sf;
bool _list[num][num];


struct grid_cell {
    int previous_x, previous_y;
    float value1, value2, value3;
    grid_cell() : value1(MAX), value2(MAX), value3(MAX), previous_x(-1), previous_y(-1) {
    };
};

int main() {
    int visited[num][num];      
    int grid[grid_size][grid_size];
    for (int i = 0; i < grid_size; i++)
        for (int j = 0; j < grid_size; j++) {
            if (i == 0 || i == grid_size - 1 || j == 0 || j == grid_size - 1)
                grid[i][j] = 0;
            else
                grid[i][j] = 1;
        }
    for (int i = 0; i < grid_size; i++)
        for (int j = 0; j < grid_size; j++) {
            explored[i][j] = false;   
            visited[i][j] = 0;     
        }
  
    Thread thread_draw_djikstra(std::bind(&dijkstra_algorithm, begin_x, begin_y, end_x, end_y, grid));

    RenderWindow window(VideoMode(width, height), "Shortest_path");

    sf::Font font;
    RectangleShape buttonStart(Vector2f(button_size, button_size));
    buttonStart.setFillColor(Color::Green);
    RectangleShape display(Vector2f(display_width, display_height));
    display.setFillColor(Color::White);

    RectangleShape rectangle(Vector2f(scale, scale));                           //рисует квадраты фона
    rectangle.setFillColor(Color::White);

    RectangleShape border_rectangle(Vector2f(scale, scale));                    //рисует рамку
    border_rectangle.setFillColor(Color::Black);

    RectangleShape path_rectangle(Vector2f(scale, scale));                      //рисует путь
    path_rectangle.setFillColor(Color::Green);
    path_rectangle.setOutlineThickness(2);
    path_rectangle.setOutlineColor(Color::Black);

    RectangleShape start_rectangle(Vector2f(scale, scale));                     //рисует квадрат начала
    start_rectangle.setFillColor(Color::Blue);
    start_rectangle.setOutlineThickness(2);
    start_rectangle.setOutlineColor(Color::Red);

    RectangleShape end_rectangle(Vector2f(scale, scale));                       //рисует квадрат конца
    end_rectangle.setFillColor(Color::Red);
    end_rectangle.setOutlineThickness(2);
    end_rectangle.setOutlineColor(Color::Red);

    RectangleShape explored_rectangle(Vector2f(scale, scale));                  //квадраты которые алгоритм проверил
    explored_rectangle.setFillColor(Color::Cyan);
    
    while (window.isOpen()) {
        Event event;
        while (window.pollEvent(event)) {
            if (event.type == Event::Closed)
                window.close();
            if (event.type == Event::KeyPressed && event.key.code == Keyboard::Space)
                window.close();
            if (event.type == Event::MouseButtonPressed && event.mouseButton.button == Mouse::Left) {
                int X = event.mouseButton.x;
                int Y = event.mouseButton.y;
                int row = Y / scale;      
                int column = X / scale;
                if (grid[row][column] == 0 && row < num && column < num)
                    grid[row][column] = 1;
                else if (row < num && column < num)
                    grid[row][column] = 0;
                
                if (X > height && X < width - display_width && Y>0 && Y < display_height) {
                    thread_draw_djikstra.launch();
                  
                }
            }
        }
        window.clear();
        buttonStart.setPosition(height, 0);
        window.draw(buttonStart);      
        display.setPosition(width + display_height, 0);     
        window.draw(display);
      

        if (!path.empty()) {
            for (int i = 0; i < path.size(); i++) {
                path_rectangle.setPosition(path[i].second * scale, path[i].first * scale);    
                window.draw(path_rectangle);        
                visited[path[i].first][path[i].second] = 1;
            }
        }
        start_rectangle.setPosition(begin_y * scale, begin_x * scale);
        window.draw(start_rectangle);     
        visited[begin_x][begin_y] = 1;
        end_rectangle.setPosition(end_y * scale, end_x * scale);
        window.draw(end_rectangle);      
        visited[end_x][end_y] = 1;
        for (int i = 0; i <= height - 10; i += scale)
            for (int j = 0; j <= height - 10; j += scale) {

                if (grid[i / scale][j / scale] == 1 && explored[i / scale][j / scale] == false && _list[i / scale][j / scale] == false && visited[i / scale][j / scale] == 0) {     
                    rectangle.setOutlineThickness(2);
                    rectangle.setOutlineColor(Color::Blue);
                    rectangle.setPosition(j, i);
                    window.draw(rectangle);     
                }
                if (grid[i / scale][j / scale] == 0) {
                    border_rectangle.setOutlineThickness(2);
                    border_rectangle.setOutlineColor(Color::Blue);
                    border_rectangle.setPosition(j, i);
                    window.draw(border_rectangle);       
                }
                if (explored[i / scale][j / scale] == true && visited[i / scale][j / scale] == 0) {
                    explored_rectangle.setOutlineThickness(2);
                    explored_rectangle.setOutlineColor(Color::Blue);
                    explored_rectangle.setPosition(j, i);
                    window.draw(explored_rectangle);     
                }
               
              
            }
        window.display();
    }
    return 0;
}