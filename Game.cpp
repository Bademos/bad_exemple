#include "Game.h"
#include<iostream>
#include <SFML/Graphics.hpp>
#include <time.h>
#include <vector>
#include <string>
#include "Point.h"
using namespace std;

const void menu() {

    RenderWindow window(VideoMode(N * w, M * w), "TETIS_vadique_edition");

    sf::Texture texture;
    texture.loadFromFile("C:/Users/user/Desktop/Paint/hui.jpg");

    sf::Sprite sprite;
    sprite.setTexture(texture);
    sprite.setPosition(0.f, 0.f);
    sprite.setScale(1.f,1.3f);
    sprite.setColor(sf::Color(255, 255, 255, 58));
    
    
    
    
    
    
    sf::Font font;
    font.loadFromFile("C:/Users/user/Desktop/Paint/AlumniSansCollegiateOne-Regular.ttf");


    sf::Text title("TETRIS", font, 150);
    title.setFillColor(sf::Color::Red);
    title.setPosition(25.f, 1.f);


    sf::Text copyright("Created by Vadique 12.2023", font, 20);
    copyright.setFillColor(sf::Color::Red);
    copyright.setPosition(150.f, 600.f);

    sf::Text text("Start", font, 100);
    text.setFillColor(sf::Color::Red);
    text.setPosition(100.f, 200.f);

    // “екст с обозначением клавиш
    sf::Text text1("Exit", font, 100);
    text1.setFillColor(sf::Color::Red);
    text1.setPosition(100.f, 350.f);


    bool isMenu = 1;
    int menuNum = 0;

    while (isMenu) {
        menuNum = 0;
        window.clear(Color(129, 181, 221));

        Event event;
        while (window.pollEvent(event))
        {
            // ѕользователь нажал на Ђкрестикї и хочет закрыть окно?
            if (event.type == Event::Closed)
                // тогда закрываем его
                window.close();

            if (event.type == Event::Resized)
                // тогда закрываем его
                window.close();
        }




        if (IntRect(100, 230, 150, 280).contains(Mouse::getPosition(window))) { text.setFillColor(Color::Cyan); menuNum = 1; }
        else {
            text.setFillColor(Color::Red);
        }
    
        if (IntRect(100, 280, 150, 350).contains(Mouse::getPosition(window))) {
        text.setFillColor(Color::Red);
    }


        if (IntRect(100, 370, 150, 420).contains(Mouse::getPosition(window))) { text1.setFillColor(Color::Cyan); menuNum = 2; }
        else {
            text1.setFillColor(Color::Red);
        }
        if (IntRect(100, 440, 150, 490).contains(Mouse::getPosition(window))) {
            text1.setFillColor(Color::Red);
        }

        if (Mouse::isButtonPressed(Mouse::Left))
        {
            //if (menuNum == 1) isMenu = false;//если нажали первую кнопку, то выходим из меню 
            if (menuNum == 1) {
                window.close();
                Game game;
                game.Draw();
            }
            if (menuNum == 2) { window.close(); isMenu = false; }

        }
        window.draw(sprite);
        window.draw(text);
        window.draw(text1);
        window.draw(title);
        window.draw(copyright);
       
        window.display();
    }
}




Game::Game()
{
	srand(time(0));
	font.loadFromFile("C:/Users/user/Desktop/Paint/AlumniSansCollegiateOne-Regular.ttf");
    
    Init();
}

void Game::Init() {
  
	for (int i=0; i < 4; i++) {
		Point h;
        h.x = 0;
        h.y = 0;
		a.push_back(h);
	}

	for (int i=0; i < 4; i++) {
		Point h;
        h.x = 0;
        h.y = 0;
		b.push_back(h);
	}

    text.setFont(font);
    text.setString("Wasted ");
    text.setCharacterSize(100);
    text.setFillColor(sf::Color::Red);
    text.setPosition(50.f, 250.f);


    text_count.setString("count");
    text_count.setFont(font);
    text_count.setCharacterSize(45);
    text_count.setFillColor(sf::Color::Red);
    text_count.setLetterSpacing(2.f);
    text_count.setPosition(10.f, 10.f);




}

bool Game::check() {
	for (int i = 0; i < 4; i++)
		if (a[i].x < 0 || a[i].x >= N || a[i].y >= M) { // проверка на грfницы игрового пол€
			return 0;
		}
		else if (field[a[i].y][a[i].x]) { // проверка на столкновени с другими фигурами
			last_y = a[i].y;

			return 0;
		}

	return 1;
 }

void Game::Draw()
{
    window.create(VideoMode(N * w, M * w), "Tetris");

    Texture bg;
    bg.loadFromFile("C:/Users/user/Desktop/Paint/ded.jpg");
    Sprite sprite_bg(bg);
    sprite_bg.setPosition(0.f, 0.f);
    sprite_bg.setScale(1.f, 1.7f);
    sprite_bg.setColor(sf::Color(255, 255, 255, 58));
    srand(time(0));
    t.loadFromFile("C:/Users/user/Desktop/Paint/tiles.png");


    std::string str = "count:" + to_string(counter);
    text_count.setString(str);
    
    tiles.setTexture(t);

    while (window.isOpen()) {

        float time = clock.getElapsedTime().asSeconds(); //врем€ прошедшее с последнего вызова часов clock
        clock.restart(); //обнуление часов
        timer += time; 

        eventManager();

        move();

        strike();

        dx = 0; // горизонтальное перемещение
        rotate = false;// вращение
        delay = 0.3;// задержка

        // ќтрисовка окна
        window.clear(Color::White);

        str = "count:" + to_string(counter);
        text_count.setString(str);
        window.draw(sprite_bg);

        drawFigure();

        drawField();

        window.draw(text_count);
        
        if (last_y == 1) {

            window.draw(text);
            window.display();
            sf::sleep(sf::seconds(2));
            window.clear(Color::Blue);
            for (int i = 0; i < M; i++) {
                for (int j = 0; j < N; j++) {
                    field[i][j] = 0;
                }
            }
            window.clear(Color::White);
            window.display();
            window.close();
            menu();
            break;

        }

        // ќтрисовка окна
        window.display();

    }
    
}

void Game::eventManager()
{

	Event event;
	while (window.pollEvent(event))
	{
		// ѕользователь нажал на Ђкрестикї и хочет закрыть окно?
		if (event.type == Event::Closed)
			// тогда закрываем его
			window.close();

		if (event.type == Event::Resized)
			// тогда закрываем его
			window.close();

		// Ѕыла ли нажата клавиша на клавиатуре?
		if (event.type == Event::KeyPressed)
			// Ёта кнопка Ц стрелка вверх?
			if (event.key.code == Keyboard::Up)
				rotate = true;
		// »ли стрелка вправо?
			else if (event.key.code == Keyboard::Right)
				dx = 1;
		// »ли может стрелка влево?
			else if (event.key.code == Keyboard::Left)
				dx = -1;
	}

	if (Keyboard::isKeyPressed(Keyboard::Down))
		delay = 0.001;

}

void Game::move() {
    for (int i = 0; i < 4; i++) {
        b[i] = a[i];
        a[i].x += dx;
    }

    // ≈сли вышли за пределы пол€ после перемещени€, то возвращаем старые координаты 
    if (!check()) {
        for (int i = 0; i < 4; i++)
            a[i] = b[i];
    }

    // ¬ращение
    if (rotate) {
        Point p = a[1];// указываем центр вращени€
        for (int i = 0; i < 4; i++) {
            int x = a[i].y - p.y;// y - y0
            int y = a[i].x - p.x;// x - x0

            a[i].x = p.x - x;
            a[i].y = p.y + y;
        }

        // ≈сли вышли за пределы пол€ после поворота, то возвращаем старые координаты 
        if (!check()) {
            for (int i = 0; i < 4; i++)
                a[i] = b[i];
            //return 0;
        }
    }

    // ƒвижение тетрамино вниз (Ђтикї таймера)
    if (timer > delay) {
        // √оризонтальное перемещение
        for (int i = 0; i < 4; i++) {
            b[i] = a[i];
            a[i].y += 1;
        }

        // ≈сли вышли за пределы пол€ после перемещени€, то возвращаем старые координаты
        if (!check()) {
            //cout << last_y << endl;
            for (int i = 0; i < 4; i++)
                field[b[i].y][b[i].x] = colorNum;
            colorNum = 1 + rand() % 7;
            int n = rand() % 7;// задаем тип тетрамино
            // ѕервое по€вление тетрамино на поле?
            for (int i = 0; i < 4; i++) {
                a[i].x = figures[n][i] % 2 + N / 2 - 1;
                a[i].y = figures[n][i] / 2;
            }
        }

        timer = 0;
    }

    // ѕервое по€вление тетрамино на поле?
    if (ad) {
        int n = rand() % 7;// указываем тип тетрамино
        // ѕервое по€вление тетрамино на поле?
        if (a[0].x == 0)
            for (int i = 0; i < 4; i++) {
                a[i].x = figures[n][i] % 2 + N / 2 + 1;
                a[i].y = figures[n][i] / 2;
            }
        ad = false;
    }
}

void Game::strike() {
    int k = M - 1;

    for (int i = M - 1; i > 0; i--) {
        int count = 0;
        for (int j = 0; j < N; j++) {
            if (field[i][j])
                count++;
            field[k][j] = field[i][j]; //перерисовываем строка за строкой 
                                       //игрового пол€

        }
        if (count < N) {
            k--;//если строка не сплошна€ спускаемс€ дальше
        } else {
            counter += 1;//иначе на месте это строки запишетс€ следующа€
                         // и будет добавлено очко
        }
    }

}

void Game::drawField()
{
    for (int i = 0; i < M; i++)
        for (int j = 0; j < N; j++) {
            if (field[i][j] == 0)
                continue;
            tiles.setTextureRect(IntRect(field[i][j] * w, 0, w, w));
            tiles.setPosition(j * w, i * w);
            window.draw(tiles);
        }
}

void Game::drawFigure()
{
    for (int i = 0; i < 4; i++) {
        tiles.setTextureRect(IntRect(colorNum * w, 0, w, w));
        // ”станавливаем позицию каждого кусочка тетрамино
        tiles.setPosition(a[i].x * w, a[i].y * w);
        // ќтрисовка спрайта
        window.draw(tiles);
    }
}



