#include <fstream>
#include <vector>
#include <sstream>
#include <iostream>
#include "Func.h"
#include <rlgl.h>
#include <raymath.h>

Image imFireball;
Image imFireball2;
Image imWave;
Image imWave2;
Image imGrass;
Image imCloud;
Image imSound;
Image imLightning;
Image imClaw;
Texture2D texClaw;
Texture2D texCloud;
Texture2D texFireball;
Texture2D texFireball2;
Texture2D texLightning;
Texture2D texWave;
Texture2D texWave2;
Texture2D texGrass;
Texture2D texSound;
Texture2D arrow;
Texture2D arrow_left;
Sound sndHit;
Sound sndLight;
Sound sndFire;
Sound sndTsunami;
Sound sndGrass;
Sound sndSound;
Sound sndPoison;
Sound sndChoose;
Sound sndMana;
Sound sndIChooseYou;
Font font;
bool isShowing = false;
bool isDying1 = false;
bool isDying2 = false;
float timer = 0.0f;
const float displayDuration = 3.0f;
bool end_of_choose;
bool switched;
bool choosed_pokemon1 = false;
bool choosed_pokemon2 = false;
bool block = false;
bool show = false;
int i1 = 0;
int i2 = 0;
unsigned int nextFrameDataOffset = 0;
int currentAnimFrame = 0;
int frameDelay = 6;
int frameDelay_for_cloud = 2;
int frameCounter = 0;
int animFrames_for_light = 5;
int animFrames_for_claw = 9;
int animFrames_for_fire = 0;
int animFrames_for_water = 11;
bool isPlaying = false;
vector <int> vec;
Vector2 startPos1 = { 200, 550 };
Vector2 endPos1 = { 1600, 550 };
Vector2 currentPos1 = startPos1;
Vector2 startPos2 = { 1600, 550 };
Vector2 endPos2 = { 200, 550 };
Vector2 currentPos2 = startPos2;
Vector2 startPos_for_wave = { 200.0f, 460.0f };
Vector2 endPos_for_wave = { 1600.0f, 460.0f };
Vector2 currentPos_for_wave = startPos_for_wave;
Vector2 startPos2_for_wave = { 1600.0f, 460.0f };
Vector2 endPos2_for_wave = { 200.0f, 460.0f };
Vector2 currentPos2_for_wave = startPos2_for_wave;
Vector2 position1 = { 1430, 380 };
Vector2 position2 = { 0, 380 };


int main(int argc, char* args[]) {
	InitAudioDevice();
	vector <Pokemon> pokemons;
	ifstream data("pokemon_data.txt");
	string line;
	int tempClass;
	int tempWeakness;
	int tempAttack;
	while (getline(data, line)) {
		istringstream k(line);
		Pokemon pokemon;
		k >> pokemon.name >> pokemon.health >> pokemon.damage >> pokemon.mana >> pokemon.special_damage;
		k >> tempClass;
		pokemon.element = (Class)tempClass;
		k >> tempWeakness;
		pokemon.weakness = (Class)tempWeakness;
		k >> tempAttack;
		pokemon.special_name = (NameOfSuper)tempAttack;
		pokemons.push_back(pokemon);
	}

	vector <Pokemon> choosed_pokemon_for_me;
	vector <Pokemon> choosed_pokemon_for_enemy;

	const int screenWidth = 1600;
	const int screenHeight = 900;
	InitWindow(screenWidth, screenHeight, "Pokemashki");
	SetTargetFPS(60);

	font = LoadFont("data/Roboto-Regular.ttf");

	int textureWidth = 350;
	int textureHeight = 175;
	Image img_vs_1 = LoadImage("data/1_vs_1.png");
	Image img_vs_3 = LoadImage("data/3_vs_3.png");
	ImageResize(&img_vs_1, textureWidth, textureHeight);
	ImageResize(&img_vs_3, textureWidth, textureHeight);
	Texture2D vs_1 = LoadTextureFromImage(img_vs_1);
	Texture2D vs_3 = LoadTextureFromImage(img_vs_3);


	imClaw = LoadImage("data/claw_sprite.png");
	texClaw = LoadTextureFromImage(imClaw);
	imLightning = LoadImage("data/light_sprite.png");
	texLightning = LoadTextureFromImage(imLightning);
	imFireball = LoadImageAnim("data/fireball1.gif", &animFrames_for_fire);
	texFireball = LoadTextureFromImage(imFireball);
	imFireball2 = LoadImageAnim("data/fireball2.gif", &animFrames_for_fire);
	texFireball2 = LoadTextureFromImage(imFireball2);
	imWave = LoadImage("data/wave_sprite.png");
	texWave= LoadTextureFromImage(imWave);
	imWave2 = LoadImage("data/wave_sprite2.png");
	texWave2= LoadTextureFromImage(imWave2);
	imGrass = LoadImage("data/grass.png");
	texGrass= LoadTextureFromImage(imGrass);
	imCloud = LoadImage("data/poison_sprite.png");
	texCloud= LoadTextureFromImage(imCloud);
	imSound = LoadImage("data/sound_sprite.png");
	texSound= LoadTextureFromImage(imSound);
	sndHit = LoadSound("sound/ooh.mp3");
	//SetSoundVolume(sndHit, 0.2f);
	sndLight = LoadSound("sound/light.mp3");
	sndFire = LoadSound("sound/fire.mp3");
	//SetSoundVolume(sndFire, 0.2f);
	sndFire = LoadSound("sound/fire.mp3");
	//SetSoundVolume(sndFire, 0.2f);
	sndTsunami = LoadSound("sound/water.mp3");
	//SetSoundVolume(sndTsunami, 0.2f);
	sndGrass = LoadSound("sound/grass.mp3");
	//SetSoundVolume(sndGrass, 0.2f);
	sndPoison = LoadSound("sound/poison.mp3");
	//SetSoundVolume(sndPoison, 0.2f);
	sndSound = LoadSound("sound/sound.mp3");
	//SetSoundVolume(sndSound, 0.2f);
	sndChoose = LoadSound("sound/choose.mp3");
	//SetSoundVolume(sndChoose, 0.2f);
	sndMana = LoadSound("sound/mana.mp3");
	//SetSoundVolume(sndMana, 0.2f);
	Sound sndMusic = LoadSound("sound/music.mp3");
	SetSoundVolume(sndMusic, 0.2f);
	sndIChooseYou = LoadSound("sound/ichooseyou.mp3");

	Texture2D charmander = LoadTexture("data/charmander.png");
	pokemons[1].texture = charmander;
	Texture2D bulbasaur = LoadTexture("data/bulbasaur.png");
	pokemons[2].texture = bulbasaur;
	Texture2D blastoise = LoadTexture("data/blastoise.png");
	pokemons[3].texture = blastoise;
	Texture2D genrar = LoadTexture("data/genrar.png");
	pokemons[5].texture = genrar;
	Texture2D mewtwo = LoadTexture("data/mewtwo.png");
	pokemons[4].texture = mewtwo;
	Texture2D pikachu = LoadTexture("data/pikachu.png");
	pokemons[0].texture = pikachu;

	arrow = LoadTexture("data/strelka.png");
	arrow_left = LoadTexture("data/strelka_left.png");

	int mod, mod1;
	bool choosed = false;
	Button button_1 = { { 470, 400, 350, 175 }, true };
	Button button_3 = { { 1280, 400, 350, 175 }, true };
	int pos_x = 120;
	int pos_x_choosed = 250;
	int pos_y = 430;
	int player = 1;
	int player_for_fight = 1;
	end_of_choose = false;
	switched = false;
	bool pause = false;

	GameState state = STATE_CHOOSE_MODE;

	while (!WindowShouldClose()) {
		BeginDrawing();

		{
			rlDrawRenderBatchActive();
			Matrix proj = MatrixOrtho(0, 2160, 1370, 0, -1, 1);
			rlSetMatrixProjection(proj);
		}

		ClearBackground(WHITE);

		if (!IsSoundPlaying(sndMusic)) {
			PlaySound(sndMusic);
		}

		switch (state) {
			case STATE_CHOOSE_MODE: {
				string mod_message = "Choose fight mod";
				DrawTextEx(font, mod_message.c_str(), Vector2{ 850,150 }, 64, 0, BLACK);
				DrawTexture(vs_1, button_1.bounds.x, button_1.bounds.y, WHITE);
				DrawTexture(vs_3, button_3.bounds.x, button_3.bounds.y, WHITE);
				if (CheckCollisionPointRec(get_mouse_pos(), button_1.bounds)) {
					if (button_1.visible && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
						mod = 1;
						mod1 = 1;
						button_1.pressed = true;
						state = STATE_CHOOSE_POKEMON;
					}
				}
				else if (CheckCollisionPointRec(get_mouse_pos(), button_3.bounds)) {
					if (button_3.visible && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
						mod = 3;
						mod1 = 3;
						button_3.pressed = true;
						state = STATE_CHOOSE_POKEMON;
					}
				}
				break;
			}

			case STATE_CHOOSE_POKEMON: {
				if (mod == 1) {
					mod1 = 1;
					string message = "Player " + to_string(player) + " choose your pokemon";
					DrawTextEx(font, message.c_str(), Vector2{ 750, 150 }, 64, 0, BLACK);
					DrawInfo(pokemons);
					if (choosed_pokemon_for_me.empty()) {
						choose_the_pokemon(pokemons, choosed_pokemon_for_me, mod1, pos_x);
					}
					if (!choosed_pokemon_for_me.empty() && choosed_pokemon_for_enemy.size() != 1) {
						player = 2;
						choose_the_pokemon(pokemons, choosed_pokemon_for_enemy, mod1, pos_x);
						if (choosed_pokemon_for_enemy.size() == 1) state = STATE_FIGHT;
					}
				}
				if (mod == 3) {
					mod1 = 3;
					string message = "Player " + to_string(player) + " choose your pokemons";
					DrawTextEx(font, message.c_str(), Vector2{ 750, 150 }, 64, 0, BLACK);
					DrawInfo(pokemons);
					if (choosed_pokemon_for_me.size() != 3) {
						choose_the_pokemon(pokemons, choosed_pokemon_for_me, mod1, pos_x);
					}
					else {
						if (choosed_pokemon_for_me.size() == 3 && choosed_pokemon_for_enemy.size() != 3) {
							player = 2;
							choose_the_pokemon(pokemons, choosed_pokemon_for_enemy, mod1, pos_x);
							if (choosed_pokemon_for_enemy.size() == 3) state = STATE_FIGHT;
						}
					}
				}
				break;
			}
			case STATE_FIGHT: {
				fight(choosed_pokemon_for_me, choosed_pokemon_for_enemy, mod, pos_y, pos_x_choosed, player_for_fight);
				break;
			}
		}

		EndDrawing();
	};
	UnloadTexture(vs_1);
	UnloadTexture(vs_3);
	UnloadTexture(charmander);
	UnloadTexture(pikachu);
	UnloadTexture(blastoise);
	UnloadTexture(bulbasaur);
	UnloadTexture(mewtwo);
	UnloadTexture(genrar);
	UnloadTexture(arrow);
	UnloadTexture(arrow_left);
	UnloadTexture(texLightning);
	UnloadTexture(texFireball);
	UnloadTexture(texFireball2);
	UnloadTexture(texGrass);
	UnloadTexture(texWave);
	UnloadTexture(texWave2);
	UnloadTexture(texCloud);
	UnloadTexture(texSound);
	UnloadImage(img_vs_1);
	UnloadImage(img_vs_3);
	UnloadImage(imLightning);
	UnloadImage(imGrass);
	UnloadImage(imSound);
	UnloadImage(imCloud);
	UnloadImage(imWave2);
	UnloadImage(imWave);
	UnloadImage(imFireball);
	UnloadImage(imFireball2);
	CloseWindow();
	return 0;
}
