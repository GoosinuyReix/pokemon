#pragma once
#include <Raylib.h>
#include <string>
#include <vector>
#include <dos.h>
#include <iostream>
using namespace std;

struct Pokemon {
	string name;
	string special_name;
	int health;
	int damage;
	int special_damage;
	string element, weakness;
	Texture2D texture;
};

struct Button {
	Rectangle bounds;
	bool visible = true, pressed = false;
};

extern Image imLightning;
extern Image imFireball;
extern Texture2D arrow;
extern Texture2D arrow_left;
extern Texture2D texFireball;
extern Texture2D texLightning;
extern Font font;
extern bool switched;
extern unsigned int nextFrameDataOffset;
extern int currentAnimFrame;
extern int frameDelay;
extern int frameCounter;
extern int animFrames;
extern bool isPlaying;
extern Vector2 startPos;
extern Vector2 endPos;
extern Vector2 currentPos;


Color ColorFromHex(int hexValue);

Color Theme_of_element(string element);

Color Theme_of_Weakness(string weakness);

void DrawInfo(vector<Pokemon>& pokemons);

vector<Pokemon> choose_the_pokemon(vector<Pokemon>& mass, vector<Pokemon>& mass_end, int& mod, int& pos_x);

void fight(vector <Pokemon>& mass_for_me, vector <Pokemon>& mass_for_enemy, int cnt, int& pos_y, int& player_for_fight, Texture2D texLightning, Image imLightning);