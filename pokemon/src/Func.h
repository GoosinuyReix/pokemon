#pragma once
#include <Raylib.h>
#include <string>
#include <vector>
#include <dos.h>
#include <iostream>
using namespace std;

enum Class {
	CLASS_ELECTRIC,
	CLASS_FIRE,
	CLASS_NATURE,
	CLASS_WATER,
	CLASS_SOUND,
	CLASS_POISON,
};

enum NameOfSuper {
	Electric_stan,
	Fireball,
	Entangling_vine,
	Tsunami,
	Sound_Attack,
	Poisonous_cloud,
};

struct Pokemon {
	string name;
	NameOfSuper special_name;
	int health;
	int damage;
	int mana;
	int special_damage;
	Class element, weakness;
	Texture2D texture;
	bool isDead = false;
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


extern Image imLightning;
extern Image imFireball;
extern Image imFireball2;
extern Image imWave;
extern Image imWave2;
extern Image imGrass;
extern Image imCloud;
extern Image imSound;
extern Image imClaw;
extern Texture2D texClaw;
extern Texture2D texGrass;
extern Texture2D texCloud;
extern Texture2D texSound;
extern Texture2D arrow;
extern Texture2D arrow_left;
extern Texture2D texFireball;
extern Texture2D texFireball2;
extern Texture2D texLightning;
extern Texture2D texWave;
extern Texture2D texWave2;
extern Sound sndHit;
extern Sound sndLight;
extern Sound sndFire;
extern Sound sndTsunami;
extern Sound sndGrass;
extern Sound sndSound;
extern Sound sndPoison;
extern Sound sndChoose;
extern Sound sndMana;
extern Sound sndIChooseYou;
extern Font font;
extern GameState state;
extern bool switched;
extern bool isShowing;
extern bool choosed_pokemon1;
extern bool choosed_pokemon2;
extern bool show;
extern bool block;
extern bool isDying1;
extern bool isDying2;
extern vector <int> vec;
extern float timer;
extern const float displayDuration;
extern int i1;
extern int i2;
extern int win_player;
extern unsigned int nextFrameDataOffset;
extern int currentAnimFrame;
extern int frameDelay;
extern int frameDelay_for_cloud;
extern int frameCounter;
extern int animFrames_for_light;
extern int animFrames_for_fire;
extern int animFrames_for_water;
extern bool isPlaying;
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
extern Vector2 position1;
extern Vector2 position2;

Color ColorFromHex(int hexValue);

Color Theme_of_element(string element);

Color Theme_of_Weakness(string weakness);

void DrawInfo(vector<Pokemon>& pokemons);

vector<Pokemon> choose_the_pokemon(vector<Pokemon>& mass, vector<Pokemon>& mass_end, int& mod, int& pos_x);

int chooseNextAlivePokemonIndex(vector<Pokemon>& pokemons, int currentIndex);

void fight(vector <Pokemon>& mass_for_me, vector <Pokemon>& mass_for_enemy, int cnt, int& pos_y, int& pos_x, int& player_for_fight);

Vector2 get_mouse_pos();
