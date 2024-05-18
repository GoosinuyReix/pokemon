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
	int mana;
	int special_damage;
	string element, weakness;
	Texture2D texture;
};

struct Button {
	Rectangle bounds;
	bool visible = true, pressed = false;
};

enum GameState {
	STATE_CHOOSE_MODE,
	STATE_CHOOSE_POKEMON,
	STATE_FIGHT,
};

enum NameOfSuper {
	Electric_stan,
	Fireball,
	Entangling_vine,
	Tsunami,
	Mind_Attack,
	Poisonous_cloud,
};

extern Image imLightning;
extern Image imFireball;
extern Image imFireball2;
extern Image imWave;
extern Image imWave2;
extern Image imClaw;
extern Image imGrass;
extern Image imPoison;
extern Texture2D texClaw;
extern Texture2D texGrass;
extern Texture2D texPoison;
extern Texture2D arrow;
extern Texture2D arrow_left;
extern Texture2D texFireball;
extern Texture2D texFireball2;
extern Texture2D texLightning;
extern Texture2D texWave;
extern Texture2D texWave2;
extern Font font;
extern bool switched;
extern bool isShowing;
extern bool choosed_pokemon1;
extern bool choosed_pokemon2;
extern bool show;
extern vector <int> vec;
extern float timer;
extern const float displayDuration;
extern int i1;
extern int i2;
extern unsigned int nextFrameDataOffset;
extern int currentAnimFrame;
extern int frameDelay;
extern int frameCounter;
extern int animFrames_for_light;
extern int animFrames_for_fire;
extern int animFrames_for_water;
extern int animFrames_for_claw;
extern bool isPlaying;
//extern bool isDamageApplied;
extern Vector2 startPos1;
extern Vector2 endPos1;
extern Vector2 currentPos1;
extern Vector2 startPos2;
extern Vector2 endPos2;
extern Vector2 currentPos2;
extern Vector2 startPos_for_wave;
extern Vector2 endPos_for_wave;
extern Vector2 startPos2_for_wave;
extern Vector2 endPos2_for_wave;
extern Vector2 currentPos_for_wave;
extern Vector2 currentPos2_for_wave;
extern Vector2 startPos_for_claw;
extern Vector2 endPos_for_claw;
extern Vector2 currentPos_for_claw;
extern Vector2 startPos2_for_claw;
extern Vector2 endPos2_for_claw;
extern Vector2 currentPos2_for_claw;
extern Vector2 currentPos_for_cloud;
extern Vector2 currentPos2_for_cloud;

Color ColorFromHex(int hexValue);

Color Theme_of_element(string element);

Color Theme_of_Weakness(string weakness);

void DrawInfo(vector<Pokemon>& pokemons);

vector<Pokemon> choose_the_pokemon(vector<Pokemon>& mass, vector<Pokemon>& mass_end, int& mod, int& pos_x);

void fight(vector <Pokemon>& mass_for_me, vector <Pokemon>& mass_for_enemy, int cnt, int& pos_y, int& pos_x, int& player_for_fight, Texture2D texLightning, Image imLightning);

Vector2 get_mouse_pos();
