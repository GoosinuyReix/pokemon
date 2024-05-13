#include <fstream>
#include <vector>
#include <sstream>
#include <iostream>
#include "Func.h"

Texture2D arrow;
Texture2D arrow_left;
Image imFireball;
Image imLightning;
Texture2D texFireball;
Texture2D texLightning;
Font font;
bool end_of_choose;
bool switched;
unsigned int nextFrameDataOffset = 0;
int currentAnimFrame = 0;
int frameDelay = 6;
int frameCounter = 0;
int animFrames = 0;
bool isPlaying = false;
Vector2 startPos = {200, 550};
Vector2 endPos = {1600, 550};
Vector2 currentPos = startPos;

int main(int argc, char* args[]) {
	setlocale(LC_ALL, "ru");

	vector <Pokemon> pokemons;
	ifstream data("pokemon_data.txt");
	string line;
	while (getline(data, line)) {
		istringstream k(line);
		Pokemon pokemon;
		k >> pokemon.name >> pokemon.health >> pokemon.damage >> pokemon.element >> pokemon.weakness >> pokemon.special_name >> pokemon.special_damage;
		pokemons.push_back(pokemon);
	}

	vector <Pokemon> choosed_pokemon_for_me;
	vector <Pokemon> choosed_pokemon_for_enemy;

	const int screenWidth = 2160;
	const int screenHeight = 1370;
	InitWindow(screenWidth, screenHeight, "Pokemons with Raylib");
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

	Image imLightning = LoadImageAnim("data/lightning.gif", &animFrames);
	Texture2D texLightning = LoadTextureFromImage(imLightning);
	imFireball = LoadImageAnim("data/fireball1.gif", &animFrames);
	texFireball = LoadTextureFromImage(imFireball);


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
	int pos_y = 430;
	int player = 1;
	int player_for_fight = 1;
	end_of_choose = false;
	switched = false;
	while (!WindowShouldClose()) {
		BeginDrawing();
		ClearBackground(WHITE);
		if (!choosed) {
			string mod_message = "Choose fight mod";
			DrawTextEx(font, mod_message.c_str(), Vector2{ 850,150 }, 64, 0, BLACK);

			DrawTexture(vs_1, button_1.bounds.x, button_1.bounds.y, WHITE);
			DrawTexture(vs_3, button_3.bounds.x, button_3.bounds.y, WHITE);

			if (CheckCollisionPointRec(GetMousePosition(), button_1.bounds)) {
				if (button_1.visible && IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
				{
					mod = 1;
					mod1 = 1;
					choosed = true;
					button_1.pressed = true;
				}
			}
			else if (CheckCollisionPointRec(GetMousePosition(), button_3.bounds)) {
				if (button_3.visible && IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
				{
					mod = 3;
					mod1 = 3;
					choosed = true;
					button_3.pressed == true;
				}
			}
		}
		else {
			if (mod == 1) {
				mod1 = 1;
				string message = "Player " + to_string(player) + " choose your pokemon";
				if (!end_of_choose) {
					DrawTextEx(font, message.c_str(), Vector2{ 750, 150 }, 64, 0, BLACK);
					DrawInfo(pokemons);

				}
				if (choosed_pokemon_for_me.empty()) {
					choose_the_pokemon(pokemons, choosed_pokemon_for_me, mod1, pos_x);
				}
				if (!choosed_pokemon_for_me.empty() && choosed_pokemon_for_enemy.size() != 1) {
					player = 2;
					choose_the_pokemon(pokemons, choosed_pokemon_for_enemy, mod1, pos_x);
					if (choosed_pokemon_for_enemy.size() == 1) end_of_choose = true;
				}
				if (end_of_choose) {
					fight(choosed_pokemon_for_me, choosed_pokemon_for_enemy, mod, pos_y, player_for_fight, texLightning, imLightning);
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
				if (choosed_pokemon_for_me.size() == 3 && choosed_pokemon_for_enemy.size() != 3) {
					player = 2;
					choose_the_pokemon(pokemons, choosed_pokemon_for_enemy, mod1, pos_x);
					if (choosed_pokemon_for_enemy.size() == 3) end_of_choose = true;
				}
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
	CloseWindow();
	return 0;
}