#include<iostream>
#include <SFML/Graphics.hpp>
#include <time.h>
#include <vector>
#include <string>
#include "Point.h"

#pragma once

using namespace std;
using namespace sf;


static const int M = 20;// высота игрового поля
static const int N = 10;
static const vector <vector <int>> figures = { // вектора фигур тетрамино
    {1,3,5,7}, // I
    {2,4,5,7}, // S
    {3,5,4,6}, // Z
    {3,5,4,7}, // T
    {2,3,5,7}, // L
    {3,5,7,6}, // J
    {2,3,4,5} // O
};
static const int w = 34;


const void menu();


class Game
{
public:
    Game();
    void Init();
    void Draw();
    
private:

    sf::Font font; //шрифт
    sf::Texture t; //контенейр картинки для отображения
    sf::Text text;// надписи
    sf::Text text1;
    sf::Text text_count;
    sf::Sprite tiles;
    sf::RenderWindow window;// окно 

    int field[M][N] = { 0 };// игровое поле
    int last_y = 0; // самая высокая очна лежащих элементов

    vector <Point> a;// вектор элементов фигуры
    vector <Point> b; // временный вектор элементов фигуры, контейнер для перемещения


    // Переменные для горизонтального перемещения и вращения
    int dx = 0;//N / 2;// Переменная для горизонтального перемещения тетрамино
    int colorNum = 1; //номер цветового варианта фигуры
    bool rotate = false;// переменная для вращения тетрамино
    // Переменные для таймера и задержки
    float timer = 0, delay = 0.01;
    // Часы (таймер)
    Clock clock;
    bool ad = true; //флаг начала цикла
    int counter = 0; // счетчик очков


    bool check();
    void eventManager();
    void move();
    void strike();
    void drawFigure();
    void drawField();
};

