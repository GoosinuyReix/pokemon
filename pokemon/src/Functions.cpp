#include "Func.h"

Color ColorFromHex(int hexValue) {
	unsigned char r = (hexValue >> 16) & 0xFF;
	unsigned char g = (hexValue >> 8) & 0xFF;
	unsigned char b = hexValue & 0xFF;
	return Color{ r, g, b, 255 };
}

Color Theme_of_element(string element) {
	if (element == "ELECTRIC") return ColorFromHex(0xEED626);
	if (element == "FIRE") return ORANGE;
	if (element == "NATURE") return GREEN;
	if (element == "PSYCHIC") return GRAY;
	if (element == "WATER") return BLUE;
	if (element == "POISON") return PURPLE;
}

Color Theme_of_Weakness(string weakness) {
	if (weakness == "ELECTRIC") return ColorFromHex(0xEED626);
	if (weakness == "FIRE") return ORANGE;
	if (weakness == "NATURE") return GREEN;
	if (weakness == "PSYCHIC") return GRAY;
	if (weakness == "WATER") return BLUE;
	if (weakness == "POISON") return PURPLE;
}

void DrawInfo(vector<Pokemon>& pokemons) {
	for (int i = 0; i < 6; i++) {
		DrawTexture(pokemons[i].texture, i * 360, 320, WHITE);
		string info_name = "Name: " + pokemons[i].name;
		string info_health = "Health: " + to_string(pokemons[i].health);
		string info_damage = "Damage: " + to_string(pokemons[i].damage);
		string info_element1 = "Element: ";
		string info_element2 = pokemons[i].element;
		string info_weakness1 = "Weakness: ";
		string info_weakness2 = pokemons[i].weakness;
		DrawTextEx(font, info_name.c_str(), Vector2{ float(i * 360 + 30), 620 }, 40, 0, BLACK);
		DrawTextEx(font, info_health.c_str(), Vector2{ float(i * 360 + 30), 670 }, 40, 0, BLACK);
		DrawTextEx(font, info_damage.c_str(), Vector2{ float(i * 360 + 30), 720 }, 40, 0, BLACK);
		DrawTextEx(font, info_element1.c_str(), Vector2{ float(i * 360 + 30), 770 }, 40, 0, BLACK);
		DrawTextEx(font, info_element2.c_str(), Vector2{ float(i * 360 + 165), 770 }, 40, 0, Theme_of_element(pokemons[i].element));
		DrawTextEx(font, info_weakness1.c_str(), Vector2{ float(i * 360 + 30), 820 }, 40, 0, BLACK);
		DrawTextEx(font, info_weakness2.c_str(), Vector2{ float(i * 360 + 200), 820 }, 40, 0, Theme_of_Weakness(pokemons[i].weakness));
	}
}


vector<Pokemon> choose_the_pokemon(vector<Pokemon>& mass, vector<Pokemon>& mass_end, int& mod, int& pos_x) {
	if (mod > 0) {
		DrawTexture(arrow, pos_x, 900, WHITE);
		if (pos_x != 120 && pos_x != 1920) {
			if (IsKeyPressed(KEY_RIGHT)) {
				pos_x += 360;
			}
			if (IsKeyPressed(KEY_LEFT)) {
				pos_x -= 360;
			}
		}
		if (pos_x == 120) {
			if (IsKeyPressed(KEY_RIGHT)) {
				pos_x += 360;

			}
		}
		if (pos_x == 1920) {
			if (IsKeyPressed(KEY_LEFT)) {
				pos_x -= 360;
			}
		}

		if (IsKeyPressed(KEY_ENTER)) {
			switch (pos_x)
			{
				case 120:
					mass_end.push_back(mass[0]);
					break;
				case 480:
					mass_end.push_back(mass[1]);
					break;
				case 840:
					mass_end.push_back(mass[2]);
					break;
				case 1200:
					mass_end.push_back(mass[3]);
					break;
				case 1560:
					mass_end.push_back(mass[4]);
					break;
				case 1920:
					mass_end.push_back(mass[5]);
					break;
				default:
					break;
			}
			mod--;
		}
	}
	/*if (!mass_end.empty()) {
		for (int i = 0; i < mass_end.size(); i++) {
			if (pokemon_is_choosed) {
				string message = "You choosed: " + mass_end[i].name;
				DrawTextEx(font, message.c_str(), Vector2{ 850, 1200 }, 64, 0, BLACK);
			}
		}
	}*/
	return mass_end;
}



void fight(vector <Pokemon>& mass_for_me, vector <Pokemon>& mass_for_enemy, int cnt, int& pos_y, int& player_for_fight, Texture2D texLightning, Image imLightning) {
	if (cnt == 1) {
		string message = "Player " + to_string(player_for_fight) + " attack the enemy";
		DrawTextEx(font, message.c_str(), Vector2{ 750, 150 }, 64, 0, BLACK);
		DrawTexture(mass_for_me[0].texture, 200, 520, WHITE);
		DrawTextEx(font, ("Health: " + to_string(mass_for_me[0].health)).c_str(), Vector2{ 200, 820 }, 64, 0, BLACK);
		DrawTexture(mass_for_enemy[0].texture, 1650, 520, WHITE);
		DrawTextEx(font, ("Health: " + to_string(mass_for_enemy[0].health)).c_str(), Vector2{ 1650, 820 }, 64, 0, BLACK);
		if (player_for_fight == 1) {
			string message1 = "Defolt attack";
			DrawTextEx(font, message1.c_str(), Vector2{ 900, 520 }, 74, 0, BLACK);
			DrawTexture(arrow_left, 1200, pos_y, WHITE);
			string message2 = "Super attack";
			DrawTextEx(font, message2.c_str(), Vector2{ 900, 620 }, 74, 0, BLACK);
			if (pos_y == 430) {
				if (IsKeyPressed(KEY_DOWN)) {
					pos_y += 100;
				}
				string message3 = "Damage: " + to_string(mass_for_me[0].damage);
				DrawTextEx(font, message3.c_str(), { 900, 800 }, 80, 0, BLACK);
				if (IsKeyPressed(KEY_SPACE)) {
					mass_for_enemy[0].health -= mass_for_me[0].damage;
					if (mass_for_enemy[0].health < 0) {
						mass_for_enemy[0].health = 0;
					}
					player_for_fight = 2;
				}
			}
			if (pos_y == 530) {
				if (IsKeyPressed(KEY_UP)) {
					pos_y -= 100;
				}
				string message4 = mass_for_me[0].special_name;
				DrawTextEx(font, message4.c_str(), { 900, 800 }, 80, 0, BLACK);
				if (IsKeyPressed(KEY_SPACE)) {
					isPlaying = true;
					currentAnimFrame = 0;
					frameCounter = 0;
					currentPos = startPos;
					mass_for_enemy[0].health -= mass_for_me[0].special_damage;
					if (mass_for_enemy[0].health - mass_for_me[0].special_damage < 0) {
						mass_for_enemy[0].health = 0;
					}
				}
				if (mass_for_me[0].special_name == "Electric_stan") {
					if (isPlaying) {
						frameCounter++;
						if (frameCounter >= frameDelay) {
							currentAnimFrame++;
							if (currentAnimFrame >= animFrames) {
								currentAnimFrame = 0;
								isPlaying = false;
								player_for_fight = 2;
							}
							nextFrameDataOffset = imLightning.width * imLightning.height * 4 * currentAnimFrame;
							UpdateTexture(texLightning, ((unsigned char*)imLightning.data) + nextFrameDataOffset);
							frameCounter = 0;
						}
						DrawTexture(texLightning, 1560, 380, WHITE);
					}
				}
				if (mass_for_me[0].special_name == "Fireball") {
					if (isPlaying) {
						frameCounter++;
						if (frameCounter >= frameDelay) {
							currentAnimFrame++;
							if (currentAnimFrame >= animFrames) {
								currentAnimFrame = 0;
							}
							nextFrameDataOffset = imFireball.width * imFireball.height * 4 * currentAnimFrame;
							UpdateTexture(texFireball, ((unsigned char*)imFireball.data) + nextFrameDataOffset);
							frameCounter = 0;
						}
						if (currentPos.x < endPos.x)
						{
							currentPos.x += 5;
							if (currentPos.x >= endPos.x)
							{
								currentPos = endPos;
								isPlaying = false;
								player_for_fight = 2;
							}
						}
						DrawTexture(texFireball, (int)currentPos.x, (int)currentPos.y, WHITE);
					}
				}
			}
		}
		if (player_for_fight == 2) {
			string message1 = "Defolt attack"; // »зменено сообщение дл€ игрока 2
			DrawTextEx(font, message1.c_str(), Vector2{ 900, 520 }, 74, 0, BLACK);
			DrawTexture(arrow_left, 1200, pos_y, WHITE);
			string message2 = "Super attack"; // »зменено сообщение дл€ игрока 2
			DrawTextEx(font, message2.c_str(), Vector2{ 900, 620 }, 74, 0, BLACK);
			if (pos_y == 430) {
				if (IsKeyPressed(KEY_DOWN)) {
					pos_y += 100;
				}
				string message3 = "Damage: " + to_string(mass_for_enemy[0].damage);
				DrawTextEx(font, message3.c_str(), { 900, 800 }, 80, 0, BLACK);
				if (IsKeyPressed(KEY_SPACE)) {
					mass_for_me[0].health -= mass_for_enemy[0].damage;
					if (mass_for_me[0].health < 0) {
						mass_for_me[0].health = 0;
					}
					player_for_fight = 1;
				}
			}
			if (pos_y == 530) {
				if (IsKeyPressed(KEY_UP)) {
					pos_y -= 100;
				}
				string message4 = mass_for_enemy[0].special_name; // ”читываем массив дл€ врага
				DrawTextEx(font, message4.c_str(), { 900, 800 }, 80, 0, BLACK);
				if (IsKeyPressed(KEY_SPACE)) {
					isPlaying = true;
					currentAnimFrame = 0;
					frameCounter = 0;
					currentPos = startPos;
					mass_for_me[0].health -= mass_for_enemy[0].special_damage; // Ќанесение специального урона игроку 1 (mass_for_me) со стороны игрока 2 (mass_for_enemy)
					if (mass_for_me[0].health - mass_for_enemy[0].special_damage < 0) {
						mass_for_me[0].health = 0;
					}
				}
				if (mass_for_enemy[0].special_name == "Electric_stan") {
					if (isPlaying) {
						frameCounter++;
						if (frameCounter >= frameDelay) {
							currentAnimFrame++;
							if (currentAnimFrame >= animFrames) {
								currentAnimFrame = 0;
								isPlaying = false;
								player_for_fight = 1; // —мена игрока после завершени€ анимации игрока 2
							}
							frameCounter = 0;
						}
						float frameWidth = (float)(texWave.width / animFrames_for_water);
						Rectangle frameRec = { frameWidth * currentAnimFrame, 0, frameWidth, (float)texWave.height };
						if (player_for_fight == 1) {
							if (currentPos_for_wave.x < endPos_for_wave.x) {
								currentPos_for_wave.x += 20;
								if (currentPos_for_wave.x >= endPos_for_wave.x) {
									currentPos_for_wave = endPos_for_wave;
									isPlaying = false;
									player_for_fight = 2;
				}
				if (mass_for_enemy[0].special_name == "Fireball") {
					if (isPlaying) {
						frameCounter++;
						if (frameCounter >= frameDelay) {
							currentAnimFrame++;
							if (currentAnimFrame >= animFrames) {
								currentAnimFrame = 0;
							}
							nextFrameDataOffset = imFireball.width * imFireball.height * 4 * currentAnimFrame;
							UpdateTexture(texFireball, ((unsigned char*)imFireball.data) + nextFrameDataOffset);
							frameCounter = 0;
						}
						if (currentPos.x < endPos.x)
						{
							currentPos.x += 5;
							if (currentPos.x >= endPos.x)
							{
								currentPos = endPos;
								isPlaying = false;
								player_for_fight = 1;
							}
						}
						DrawTexture(texFireball, (int)currentPos.x, (int)currentPos.y, WHITE);
					}
				}
			}
		}

		if (mass_for_enemy[0].health == 0) {
			DrawTextEx(font, "Player 1 win", Vector2{ 700, 1100 }, 150, 0, BLACK);
		}
		if (mass_for_me[0].health == 0) {
			DrawTextEx(font, "Player 2 win", Vector2{ 700, 1100 }, 150, 0, BLACK);
		}
	}
}