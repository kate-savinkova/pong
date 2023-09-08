#include <stdio.h>

void drawField(int y_left, int y_right, int x_ball, int y_ball, int score_left, int score_right);
void score(int player_1, int player_2);
void clearScreen();
int racket_left(char command, int start);
int racket_right(char command, int start);
char checker();
void drawWinning(int player_1, int player_2);
int vector_func(int x_ball, int vector_x);

int main() {
    // координаты верхних границ ракеток
    int y_left = 12, y_right = 12;
    // координаты мяча
    int x_ball = 30, y_ball = 9;
    // направление мяча (1 - мяч двигается слева направо; 0 - мяч двигается справа налево)
    int vector_x = 1;
    // точка последнего попадания мяча на ракетку (1 - в центр; 0 - на край)
    int last_hit = 1;
    // направление движение мяча относительно оси Y (0 - движение сверху вних; 1 - движение снизу вверх)
    int vector_y = 0;
    // угол движения мяча после столкновения с ракеткой
    int angle_center = 11, angle_side = 8;
    // счет
    int score_left = 0, score_right = 0;
    // цикл игры
    while (score_left != 21 && score_right != 21) {
        clearScreen();
        char command_left, command_right, try;
        drawField(y_left, y_right, x_ball, y_ball, score_left, score_right);
        command_left = getchar();
        command_right = getchar();
        try = getchar();
        if (try == '\n') {
            if (command_left == ' ' || command_left == 'a' || command_left == 'z') {
                y_left = racket_left(command_left, y_left);
            } else {
                continue;
            }
            if (command_right == ' ' || command_right == 'k' || command_right == 'm') {
                y_right = racket_right(command_right, y_right);
            } else {
                continue;
            }
        } else {
            continue;
        }
        //если мяч находится не на вертикальных границах (в основном поле)
        if (x_ball > 3 && x_ball < 78) {
            //мяч находится на горизонтальных границах
            if (y_ball == 1 || y_ball == 25) {
                if (vector_x) {  // мяч движется слева направо (->): промазал 1-й игрок
                    score_right += 1;
                    x_ball = 78;  // мяч ставится на середину ракетки
                    y_ball = y_right + 1;
                    vector_x = 0;
                } else {  // мяч движется справа налево (<-): промазал 2-й игрок
                    score_left += 1;
                    x_ball = 3;
                    y_ball = y_left + 1;
                    vector_x = 1;
                }
            } else {
                // мяч движется снизу вверх
                if (vector_y) {
                    // мяч попал в центр
                    if (last_hit) {
                        // угол движения от центра
                        if (angle_center) {
                            angle_center -= 1;
                            x_ball = vector_func(x_ball, vector_x);
                        } else {
                            y_ball += 1;
                            angle_center = 11;
                        }
                        // мяч попал на край
                    } else {
                        // угол движения от края
                        if (angle_side) {
                            angle_side -= 1;
                            ;
                            x_ball = vector_func(x_ball, vector_x);
                        } else {
                            y_ball += 1;
                            angle_side = 9;
                        }
                    }
                    // мяч движется сверху вниз
                } else {
                    // мяч попал в центр
                    if (last_hit) {
                        // угол движения от центра
                        if (angle_center) {
                            angle_center -= 1;
                            x_ball = vector_func(x_ball, vector_x);
                        } else {
                            y_ball -= 1;
                            angle_center = 11;
                        }
                        // мяч попал на край
                    } else {
                        // угол движения от края
                        if (angle_side) {
                            angle_side -= 1;
                            x_ball = vector_func(x_ball, vector_x);
                        } else {
                            y_ball -= 1;
                            angle_side = 9;
                        }
                    }
                }
            }
            // мяч находится на границе с ракетками
        } else {
            // проверка на касания мяча с левой ракеткой
            if (x_ball == 3) {
                // мяч касается края ракетки
                if ((y_ball == y_left) || (y_ball == y_left + 2)) {
                    vector_x = 1;
                    last_hit = 0;
                    angle_side = 9;
                    x_ball += 1;
                    if (vector_y && y_ball == y_left) {
                        vector_y = 0;
                    } else if (!vector_y && y_ball == y_left + 2) {
                        vector_y = 1;
                    }
                    // мяч касается центра ракетки
                } else if (y_ball == y_left + 1) {
                    // мяч двигался снизу вверх
                    if (vector_y) {
                        y_ball -= 1;
                        vector_y = 0;
                        // мяч двигался сверху вниз
                    } else {
                        y_ball += 1;
                        vector_y = 1;
                    }
                    vector_x = 1;
                    last_hit = 1;
                    angle_center = 11;
                    x_ball += 1;
                    // промах -> гол 2-го игрока
                } else {
                    score_right += 1;
                    x_ball = 78;
                    y_ball = y_right + 1;
                    last_hit = 1;
                    vector_x = 0;
                    vector_y = 1;
                    angle_center = 11;
                }
                // проверка на касания мяча с правой ракеткой
            } else if (x_ball == 78) {
                // мяч касается края ракетки
                if ((y_ball == y_right) || (y_ball == y_right + 2)) {
                    vector_x = 0;
                    last_hit = 0;
                    angle_side = 9;
                    x_ball -= 1;
                    if (vector_y && y_ball == y_right) {
                        vector_y = 0;
                    } else if (!vector_y && y_ball == y_left + 2) {
                        vector_y = 1;
                    }
                    // мяч касается центра ракетки
                } else if (y_ball == y_right + 1) {
                    // мяч двигался снизу вверх
                    if (vector_y) {
                        y_ball -= 1;
                        vector_y = 0;
                        // мяч двигался сверху вниз
                    } else {
                        y_ball += 1;
                        vector_y = 1;
                    }
                    vector_x = 0;
                    last_hit = 1;
                    angle_center = 11;
                    x_ball -= 1;
                } else {
                    score_left += 1;
                    x_ball = 3;
                    y_ball = y_left + 1;
                    last_hit = 1;
                    vector_x = 1;
                    vector_y = 1;
                    angle_center = 11;
                }
                // мяч двигается в противоположную по оси Y сторону
                if (vector_y) {
                    vector_y = 0;
                } else {
                    vector_y = 1;
                }
                // промах -> увеличение счета у выигравшего игрока
            } else {
                // промах -> гол 2-го игрока
                if (x_ball == 2) {
                    score_right += 1;
                    x_ball = 78;
                    y_ball = y_right + 1;
                    vector_x = 0;
                    last_hit = 1;
                    angle_center = 11;
                    // промах -> гол 1-го игрока
                } else {
                    score_left += 1;
                    x_ball = 3;
                    y_ball = y_left + 1;
                    vector_x = 1;
                    last_hit = 1;
                    angle_center = 11;
                }
            }
        }
    }
    drawWinning(score_left, score_right);
    return 0;
}

int vector_func(int x_ball, int vector_x) {
    if (vector_x) {
        return x_ball + 1;
    } else {
        return x_ball - 1;
    }
}

void drawField(int y_left, int y_right, int x_ball, int y_ball, int score_left,
               int score_right) {  // рисуем поле
    //рисуем верхнюю секцию со счетом
    for (int x = 1; x <= 5; x++) {
        for (int y = 1; y <= 80; y++) {
            if (x == 5)
                printf(".");  // верхняя линия секции
            else {
                if (x == 3 && y == 38) {
                    score(score_left, score_right);  // счет игры
                    y += 4;
                    continue;
                } else {
                    printf(" ");
                }
            }
        }
        printf("\n");
    }
    // рисуем основную секцию
    for (int y = 1; y <= 25; y++) {
        for (int x = 1; x <= 80; x++) {
            // рисуем мяч
            if (y == y_ball && x == x_ball) {
                printf("©");
                continue;
            }
            // рисуем сетку по середине
            if (x == 40) {
                printf(":");
                continue;
            }
            // рисуем левую ракетку
            if (x == 2) {
                if (y_left == y || y_left + 1 == y || y_left + 2 == y)
                    printf("|");
                else
                    printf(" ");
                continue;
            }
            // рисуем правую ракетку
            if (x == 79) {
                if (y_right == y || y_right + 1 == y || y_right + 2 == y)
                    printf("|");
                else
                    printf(" ");
                continue;
            }
            // рисуем грани поля
            if (x == 1 || x == 80) {
                printf("|");
            } else {
                printf(" ");
            }
        }
        printf("\n");
    }
    // рисуем нижнюю грань поля
    for (int x = 0; x < 80; x++) {
        printf(".");
    }
    printf("\n");
}

// изменение координаты левой ракетки
int racket_left(char command, int start) {
    if (command == 'a') {
        if (start == 1)
            return start;
        else
            return start - 1;
    } else if (command == 'z') {
        if (start == 23) {
            return start;
        } else {
            return start + 1;
        }
    } else {
        return start;
    }
}

// изменение координаты правой ракетки
int racket_right(char command, int start) {
    if (command == 'k') {
        if (start == 1)
            return start;
        else
            return start - 1;
    } else if (command == 'm') {
        if (start == 23) {
            return start;
        } else {
            return start + 1;
        }
    } else {
        return start;
    }
}

// вывод счета игры
void score(int player_1, int player_2) { printf("%d | %d", player_1, player_2); }

// очистка терминала
void clearScreen() { printf("\33[0d\33[2J"); }

//вывод итога игры
void drawWinning(int player_1, int player_2) {
    for (int i = 1; i <= 80; i++) {
        printf("×");
    }
    printf("\n");
    for (int i = 1; i <= 25; i++) {
        for (int j = 1; j <= 80; j++) {
            if (i == 12 && j == 31) {
                if (player_1 > player_2) {
                    printf("!!!PLAYER 1 WON!!!");
                    j += 17;
                    continue;
                } else if (player_2 > player_1) {
                    printf("!!!PLAYER 2 WON!!!");
                    j += 18;
                    continue;
                } else {
                    printf("!!!FRIENDSHIP WON!!!");
                    j += 19;
                    continue;
                }
            }
            if (j == 1 || j == 80) {
                printf("×");
            } else {
                printf(" ");
            }
        }
        printf("\n");
    }
    for (int i = 1; i <= 80; i++) {
        printf("×");
    }
}
