#include <SFML/Graphics.hpp>
#include <vector>
#include <deque>
#include <random>
#include <string>

using namespace sf;
using namespace std;

// Константы игры
const int WINDOW_WIDTH = 800;
const int WINDOW_HEIGHT = 600;
const int CELL_SIZE = 20;
const int GRID_WIDTH = WINDOW_WIDTH / CELL_SIZE;
const int GRID_HEIGHT = WINDOW_HEIGHT / CELL_SIZE;
const float INITIAL_SPEED = 0.15f; // секунды между движениями

// Цвета
const Color SNAKE_HEAD_COLOR(50, 205, 50);      // Лаймовый
const Color SNAKE_BODY_COLOR(34, 139, 34);      // Лесной зеленый
const Color BACKGROUND_COLOR(15, 15, 35);       // Темно-синий
const Color GRID_COLOR(30, 30, 60);             // Сетка
const Color TEXT_COLOR(255, 255, 255);          // Белый
const Color GAME_OVER_COLOR(220, 20, 60, 180);  // Полупрозрачный красный

class Game {
private:
    RenderWindow window;
    Font font;
    
    // Игровые объекты
    vector<Vector2i> snake;
    Vector2i food;
    Vector2i direction;
    Vector2i nextDirection;
    
    // Игровое состояние
    int score;
    bool gameOver;
    bool paused;
    float moveTimer;
    float speed;
    
    // Генератор случайных чисел
    mt19937 rng;
    uniform_int_distribution<int> foodDistX;
    uniform_int_distribution<int> foodDistY;

public:
    Game() : window(VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Snake Game - Burger Eater"),
             score(0), gameOver(false), paused(false), 
             moveTimer(0), speed(INITIAL_SPEED),
             rng(random_device{}()),
             foodDistX(0, GRID_WIDTH - 1),
             foodDistY(0, GRID_HEIGHT - 1) {
        
        // Настройка окна
        window.setFramerateLimit(60);
        
        // Загрузка шрифта
        if (!font.loadFromFile("arial.ttf")) {
            // Попытка загрузить стандартный шрифт
            font.loadFromFile("/usr/share/fonts/truetype/dejavu/DejaVuSans.ttf");
        }
        
        initGame();
    }

    void initGame() {
        // Инициализация змейки - начинаем с 3 сегментов в центре
        snake.clear();
        snake.push_back(Vector2i(GRID_WIDTH / 2, GRID_HEIGHT / 2));
        snake.push_back(Vector2i(GRID_WIDTH / 2 - 1, GRID_HEIGHT / 2));
        snake.push_back(Vector2i(GRID_WIDTH / 2 - 2, GRID_HEIGHT / 2));
        
        // Начальное направление - вправо
        direction = Vector2i(1, 0);
        nextDirection = direction;
        
        // Сброс состояния игры
        score = 0;
        gameOver = false;
        paused = false;
        speed = INITIAL_SPEED;
        
        // Создание первой еды
        spawnFood();
    }

    void spawnFood() {
        bool foodOnSnake;
        do {
            food.x = foodDistX(rng);
            food.y = foodDistY(rng);
            
            // Проверяем, не появилась ли еда на змейке
            foodOnSnake = false;
            for (const auto& segment : snake) {
                if (segment.x == food.x && segment.y == food.y) {
                    foodOnSnake = true;
                    break;
                }
            }
        } while (foodOnSnake);
    }

    void drawBurger(const Vector2i& position) {
        float x = position.x * CELL_SIZE;
        float y = position.y * CELL_SIZE;
        
        // Нижняя булочка
        RectangleShape bottomBun(Vector2f(CELL_SIZE - 2, CELL_SIZE * 0.2f));
        bottomBun.setPosition(x + 1, y + CELL_SIZE * 0.8f);
        bottomBun.setFillColor(Color(210, 180, 140)); // Пшеничный цвет
        window.draw(bottomBun);
        
        // Котлета
        RectangleShape patty(Vector2f(CELL_SIZE - 4, CELL_SIZE * 0.25f));
        patty.setPosition(x + 2, y + CELL_SIZE * 0.55f);
        patty.setFillColor(Color(101, 67, 33)); // Коричневый
        window.draw(patty);
        
        // Сыр
        RectangleShape cheese(Vector2f(CELL_SIZE - 6, CELL_SIZE * 0.15f));
        cheese.setPosition(x + 3, y + CELL_SIZE * 0.4f);
        cheese.setFillColor(Color(255, 215, 0)); // Золотой
        window.draw(cheese);
        
        // Салат
        RectangleShape lettuce(Vector2f(CELL_SIZE - 2, CELL_SIZE * 0.1f));
        lettuce.setPosition(x + 1, y + CELL_SIZE * 0.3f);
        lettuce.setFillColor(Color(50, 205, 50)); // Салатовый
        window.draw(lettuce);
        
        // Верхняя булочка
        RectangleShape topBun(Vector2f(CELL_SIZE - 2, CELL_SIZE * 0.2f));
        topBun.setPosition(x + 1, y + CELL_SIZE * 0.1f);
        topBun.setFillColor(Color(210, 180, 140)); // Пшеничный цвет
        window.draw(topBun);
        
        // Кунжутные семечки на верхней булочке
        CircleShape sesame1(1.5f);
        sesame1.setPosition(x + 5, y + 5);
        sesame1.setFillColor(Color(255, 255, 255));
        window.draw(sesame1);
        
        CircleShape sesame2(1.5f);
        sesame2.setPosition(x + CELL_SIZE - 8, y + 7);
        sesame2.setFillColor(Color(255, 255, 255));
        window.draw(sesame2);
        
        CircleShape sesame3(1.5f);
        sesame3.setPosition(x + CELL_SIZE / 2, y + 3);
        sesame3.setFillColor(Color(255, 255, 255));
        window.draw(sesame3);
    }

    void handleInput() {
        Event event;
        while (window.pollEvent(event)) {
            if (event.type == Event::Closed) {
                window.close();
            }
            
            if (event.type == Event::KeyPressed) {
                if (gameOver) {
                    if (event.key.code == Keyboard::Space || 
                        event.key.code == Keyboard::R) {
                        initGame();
                    }
                } else {
                    if (event.key.code == Keyboard::P) {
                        paused = !paused;
                    }
                    if (event.key.code == Keyboard::Space) {
                        paused = !paused;
                    }
                    
                    // Обработка управления змейкой
                    if (!paused) {
                        if (event.key.code == Keyboard::Up && direction.y == 0) {
                            nextDirection = Vector2i(0, -1);
                        }
                        else if (event.key.code == Keyboard::Down && direction.y == 0) {
                            nextDirection = Vector2i(0, 1);
                        }
                        else if (event.key.code == Keyboard::Left && direction.x == 0) {
                            nextDirection = Vector2i(-1, 0);
                        }
                        else if (event.key.code == Keyboard::Right && direction.x == 0) {
                            nextDirection = Vector2i(1, 0);
                        }
                    }
                }
            }
        }
    }

    void update(float deltaTime) {
        if (gameOver || paused) return;
        
        moveTimer += deltaTime;
        
        if (moveTimer >= speed) {
            moveTimer = 0;
            
            // Обновляем направление
            direction = nextDirection;
            
            // Вычисляем новую позицию головы
            Vector2i newHead = snake[0] + direction;
            
            // Проверка столкновения со стенами
            if (newHead.x < 0 || newHead.x >= GRID_WIDTH || 
                newHead.y < 0 || newHead.y >= GRID_HEIGHT) {
                gameOver = true;
                return;
            }
            
            // Проверка столкновения с собой
            for (size_t i = 0; i < snake.size(); i++) {
                if (snake[i].x == newHead.x && snake[i].y == newHead.y) {
                    gameOver = true;
                    return;
                }
            }
            
            // Добавляем новую голову
            snake.insert(snake.begin(), newHead);
            
            // Проверка поедания бургера
            if (newHead.x == food.x && newHead.y == food.y) {
                score += 10;
                spawnFood();
                
                // Увеличиваем скорость каждые 50 очков
                if (score % 50 == 0 && speed > 0.05f) {
                    speed *= 0.9f;
                }
            } else {
                // Удаляем хвост, если не съели бургер
                snake.pop_back();
            }
        }
    }

    void draw() {
        window.clear(BACKGROUND_COLOR);
        
        drawGrid();
        drawBurger(food);
        drawSnake();
        drawUI();
        
        if (gameOver) {
            drawGameOver();
        }
        else if (paused) {
            drawPaused();
        }
        
        window.display();
    }

    void drawGrid() {
        // Вертикальные линии
        for (int x = 0; x <= GRID_WIDTH; x++) {
            RectangleShape line(Vector2f(1, WINDOW_HEIGHT));
            line.setPosition(x * CELL_SIZE, 0);
            line.setFillColor(GRID_COLOR);
            window.draw(line);
        }
        
        // Горизонтальные линии
        for (int y = 0; y <= GRID_HEIGHT; y++) {
            RectangleShape line(Vector2f(WINDOW_WIDTH, 1));
            line.setPosition(0, y * CELL_SIZE);
            line.setFillColor(GRID_COLOR);
            window.draw(line);
        }
    }

    void drawSnake() {
        for (size_t i = 0; i < snake.size(); i++) {
            RectangleShape segment(Vector2f(CELL_SIZE - 1, CELL_SIZE - 1));
            segment.setPosition(snake[i].x * CELL_SIZE + 0.5f, 
                               snake[i].y * CELL_SIZE + 0.5f);
            
            if (i == 0) {
                segment.setFillColor(SNAKE_HEAD_COLOR);
                
                // Рисуем глаза у головы
                CircleShape eye(CELL_SIZE * 0.15f);
                eye.setFillColor(Color::Black);
                
                // Левый глаз
                Vector2f eyeOffset;
                if (direction.x == 1) { // Вправо
                    eyeOffset = Vector2f(CELL_SIZE * 0.7f, CELL_SIZE * 0.3f);
                } else if (direction.x == -1) { // Влево
                    eyeOffset = Vector2f(CELL_SIZE * 0.2f, CELL_SIZE * 0.3f);
                } else if (direction.y == 1) { // Вниз
                    eyeOffset = Vector2f(CELL_SIZE * 0.3f, CELL_SIZE * 0.7f);
                } else { // Вверх
                    eyeOffset = Vector2f(CELL_SIZE * 0.3f, CELL_SIZE * 0.2f);
                }
                
                eye.setPosition(snake[i].x * CELL_SIZE + eyeOffset.x, 
                               snake[i].y * CELL_SIZE + eyeOffset.y);
                window.draw(eye);
                
                // Правый глаз
                if (direction.x == 1 || direction.x == -1) {
                    eyeOffset.y = CELL_SIZE * 0.7f;
                } else {
                    eyeOffset.x = CELL_SIZE * 0.7f;
                }
                
                eye.setPosition(snake[i].x * CELL_SIZE + eyeOffset.x, 
                               snake[i].y * CELL_SIZE + eyeOffset.y);
                window.draw(eye);
                
            } else {
                segment.setFillColor(SNAKE_BODY_COLOR);
            }
            
            window.draw(segment);
        }
    }

    void drawUI() {
        // Счет
        Text scoreText("Burgers eaten: " + to_string(score / 10), font, 24);
        scoreText.setPosition(10, 10);
        scoreText.setFillColor(TEXT_COLOR);
        window.draw(scoreText);
        
        // Длина змейки
        Text lengthText("Length: " + to_string(snake.size()), font, 24);
        lengthText.setPosition(10, 40);
        lengthText.setFillColor(TEXT_COLOR);
        window.draw(lengthText);
        
        // Скорость
        Text speedText("Speed: " + to_string(static_cast<int>((INITIAL_SPEED / speed) * 100)) + "%", font, 24);
        speedText.setPosition(10, 70);
        speedText.setFillColor(TEXT_COLOR);
        window.draw(speedText);
        
        // Подсказки
        if (!gameOver) {
            Text controlsText("P - Pause | Arrows - Move", font, 18);
            controlsText.setPosition(WINDOW_WIDTH - controlsText.getLocalBounds().width - 10, 10);
            controlsText.setFillColor(Color(200, 200, 200));
            window.draw(controlsText);
        }
    }

    void drawGameOver() {
        // Полупрозрачный фон
        RectangleShape overlay(Vector2f(WINDOW_WIDTH, WINDOW_HEIGHT));
        overlay.setFillColor(GAME_OVER_COLOR);
        window.draw(overlay);
        
        // Текст Game Over
        Text gameOverText("GAME OVER", font, 60);
        gameOverText.setPosition(
            WINDOW_WIDTH / 2 - gameOverText.getLocalBounds().width / 2,
            WINDOW_HEIGHT / 2 - 80
        );
        gameOverText.setFillColor(Color::White);
        window.draw(gameOverText);
        
        // Финальный счет
        Text finalScore("Burgers eaten: " + to_string(score / 10), font, 36);
        finalScore.setPosition(
            WINDOW_WIDTH / 2 - finalScore.getLocalBounds().width / 2,
            WINDOW_HEIGHT / 2
        );
        finalScore.setFillColor(Color::White);
        window.draw(finalScore);
        
        // Инструкция по рестарту
        Text restartText("Press SPACE or R to restart", font, 24);
        restartText.setPosition(
            WINDOW_WIDTH / 2 - restartText.getLocalBounds().width / 2,
            WINDOW_HEIGHT / 2 + 60
        );
        restartText.setFillColor(Color::White);
        window.draw(restartText);
    }

    void drawPaused() {
        // Полупрозрачный фон
        RectangleShape overlay(Vector2f(WINDOW_WIDTH, WINDOW_HEIGHT));
        overlay.setFillColor(Color(0, 0, 0, 128));
        window.draw(overlay);
        
        // Текст Pause
        Text pauseText("PAUSED", font, 60);
        pauseText.setPosition(
            WINDOW_WIDTH / 2 - pauseText.getLocalBounds().width / 2,
            WINDOW_HEIGHT / 2 - 30
        );
        pauseText.setFillColor(Color::White);
        window.draw(pauseText);
        
        // Инструкция
        Text continueText("Press SPACE or P to continue", font, 24);
        continueText.setPosition(
            WINDOW_WIDTH / 2 - continueText.getLocalBounds().width / 2,
            WINDOW_HEIGHT / 2 + 40
        );
        continueText.setFillColor(Color::White);
        window.draw(continueText);
    }

    void run() {
        Clock clock;
        
        while (window.isOpen()) {
            float deltaTime = clock.restart().asSeconds();
            
            handleInput();
            update(deltaTime);
            draw();
        }
    }
};

int main() {
    Game game;
    game.run();
    return 0;
}