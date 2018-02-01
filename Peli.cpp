#include "Pokitto.h"

#define BLINKYPERIOD 500

Pokitto::Core game;

int score = 0;
int hiscore = 0;



int gameover(){
    game.display.color=3;
    game.display.setCursor(50,70);
    game.display.print("Game Over");
    game.display.setCursor(50,90);
    game.display.print("Score: ");
    game.display.print(score);
    game.display.setCursor(50,100);
    game.display.print("Hiscore: ");
    game.display.print(hiscore);
    score=0;
    game.display.setCursor(50,120);
    game.display.print("A: Pelaa uudestaan");
    game.display.setCursor(50,130);
    game.display.print("B: Palaa paavalikkoon");
    game.display.setCursor(50,140);

    if (game.buttons.held(BTN_A,0)){
        return 1;
    }

    if (game.buttons.held(BTN_B,0)){
        return 2;
    }
}

void peli() {

    int x = 1;
    int y = 11;
    char suunta = 'O';


    while (game.isRunning()) {
        if (game.update()) {

            if (game.buttons.held(BTN_UP,0) and suunta != 'A'){
                suunta = 'Y';
            }
            if (game.buttons.held(BTN_DOWN,0) and suunta != 'Y'){
                suunta = 'A';
            }
            if (game.buttons.held(BTN_RIGHT,0) and suunta != 'V'){
                suunta = 'O';
            }
            if (game.buttons.held(BTN_LEFT,0) and suunta != 'O'){
                suunta = 'V';
            }

            game.display.color = 1;
            game.display.drawRectangle(0,10,200,160);
            game.display.color = 3;
            game.display.setCursor(100,0);
            game.display.print("Score: ");
            game.display.print(score);
            game.display.setCursor(0,0);
            game.display.print("Hiscore: ");
            game.display.print(hiscore);
            game.display.color = 2;
            game.display.fillRectangle(x,y,5,5);

            if (x>194 or x<1 or y<11 or y>164){
                if (gameover() == 1){
                    peli();
                }
                if (gameover() == 2){
                    return;
                }

            }

            else{
                if (suunta == 'Y') {
                    y = y-5;
                }
                if (suunta == 'A') {
                    y = y+5;
                }
                if (suunta == 'O') {
                    x = x+5;
                }
                if (suunta == 'V'){
                    x = x-5;
                }
            }

        game.wait(100);
        }
    }
}


bool valikko() {

    int kursori = 0;
    int blinkybox = 0;
    long blinkytime = game.getTime();

    while (game.isRunning()) {
        if (game.update()) {
            //siirretään kursoria valikossa
            if (game.buttons.held(BTN_DOWN,0) and kursori < 2) {
                kursori = kursori+16;
            }
            if (game.buttons.held(BTN_UP,0) and kursori > 1) {
                kursori = kursori-16;
            }
            //avataan kursorin osoittama peli
            if (game.buttons.held(BTN_A,0)) {
                if (kursori==0){
                    peli();
                }
                if (kursori==16){
                    return false;
                }
            }

            game.display.setCursor(0,0);
            game.display.println("snake");
            game.display.println("");
            game.display.println("lopeta");

            if (game.getTime()>blinkytime+BLINKYPERIOD) {
                blinkybox = 1 - blinkybox; //toggle blinky
                blinkytime = game.getTime(); // store new time
            }

            game.display.setCursor(0,kursori);
            if (blinkybox) {
                game.display.bgcolor = 1; // reverse whitespace color
                game.display.print(" ");  // print whitespace
                game.display.bgcolor = 0; // put color the right way again
            }
        }
    }
}
//Valikosta pelaaja voi valita pelattavan pelin ja sulkea ohjelman
int main() {
    game.begin();
    if (valikko ());
    else game.quit();
}
