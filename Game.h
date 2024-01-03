#include<iostream>
#include <SFML/Graphics.hpp>
#include <time.h>
#include <vector>
#include <string>
#include "Point.h"

#pragma once

using namespace std;
using namespace sf;


static const int M = 20;// ������ �������� ����
static const int N = 10;
static const vector <vector <int>> figures = { // ������� ����� ���������
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

    sf::Font font; //�����
    sf::Texture t; //��������� �������� ��� �����������
    sf::Text text;// �������
    sf::Text text1;
    sf::Text text_count;
    sf::Sprite tiles;
    sf::RenderWindow window;// ���� 

    int field[M][N] = { 0 };// ������� ����
    int last_y = 0; // ����� ������� ���� ������� ���������

    vector <Point> a;// ������ ��������� ������
    vector <Point> b; // ��������� ������ ��������� ������, ��������� ��� �����������


    // ���������� ��� ��������������� ����������� � ��������
    int dx = 0;//N / 2;// ���������� ��� ��������������� ����������� ���������
    int colorNum = 1; //����� ��������� �������� ������
    bool rotate = false;// ���������� ��� �������� ���������
    // ���������� ��� ������� � ��������
    float timer = 0, delay = 0.01;
    // ���� (������)
    Clock clock;
    bool ad = true; //���� ������ �����
    int counter = 0; // ������� �����


    bool check();
    void eventManager();
    void move();
    void strike();
    void drawFigure();
    void drawField();
};

