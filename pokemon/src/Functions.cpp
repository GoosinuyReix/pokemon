#include "Func.h"

Color ColorFromHex(int hexValue) {
	unsigned char r = (hexValue >> 16) & 0xFF;
	unsigned char g = (hexValue >> 8) & 0xFF;
	unsigned char b = hexValue & 0xFF;
	return Color{ r, g, b, 255 };
}

string enumToString(Class attack) {
	string a;
	if (attack == 0) a = "ELECTRIC";
	else if (attack == 1) a = "FIRE";
	else if (attack == 2) a = "NATURE";
	else if (attack == 3) a = "WATER";
	else if (attack == 4) a = "SOUND";
	else if (attack == 5) a = "POISON";
	return a;
}
string enumToString1(NameOfSuper attack) {
	string a;
	if (attack == 0) a = "Electric stan";
	else if (attack == 1) a = "Fireball";
	else if (attack == 2) a = "Entangling_vine";
	else if (attack == 3) a = "Tsunami";
	else if (attack == 4) a = "Sound Attack";
	else if (attack == 5) a = "Poison Cloud";
	return a;
}

Color Theme_of_element(Class element) {
	if (element == CLASS_ELECTRIC) return ColorFromHex(0xEED626);
	if (element == CLASS_FIRE) return ORANGE;
	if (element == CLASS_NATURE) return GREEN;
	if (element == CLASS_SOUND) return GRAY;
	if (element == CLASS_WATER) return BLUE;
	if (element == CLASS_POISON) return PURPLE;
}

Color Theme_of_Weakness(Class weakness) {
	if (weakness == CLASS_ELECTRIC) return ColorFromHex(0xEED626);
	if (weakness == CLASS_FIRE) return ORANGE;
	if (weakness == CLASS_NATURE) return GREEN;
	if (weakness == CLASS_SOUND) return GRAY;
	if (weakness == CLASS_WATER) return BLUE;
	if (weakness == CLASS_POISON) return PURPLE;
}

void DrawInfo(vector<Pokemon>& pokemons) {
	for (int i = 0; i < 6; i++) {
		DrawTexture(pokemons[i].texture, i * 360, 320, WHITE);
		string info_name = "Name: " + pokemons[i].name;
		string info_health = "Health: " + to_string(pokemons[i].health);
		string info_damage = "Damage: " + to_string(pokemons[i].damage);
		string info_mana1 = "Mana: ";
		string info_mana2 = to_string(pokemons[i].mana);
		string info_element1 = "Element: ";
		string info_element2 = enumToString(pokemons[i].element);
		string info_weakness1 = "Weakness: ";
		string info_weakness2 = enumToString(pokemons[i].weakness);
		DrawTextEx(font, info_name.c_str(), Vector2{ float(i * 360 + 30), 620 }, 40, 0, BLACK);
		DrawTextEx(font, info_health.c_str(), Vector2{ float(i * 360 + 30), 670 }, 40, 0, BLACK);
		DrawTextEx(font, info_damage.c_str(), Vector2{ float(i * 360 + 30), 720 }, 40, 0, BLACK);
		DrawTextEx(font, info_mana1.c_str(), Vector2{ float(i * 360 + 30), 770 }, 40, 0, BLACK);
		DrawTextEx(font, info_mana2.c_str(), Vector2{ float(i * 360 + 130), 770 }, 40, 0, BLUE);
		DrawTextEx(font, info_element1.c_str(), Vector2{ float(i * 360 + 30), 820 }, 40, 0, BLACK);
		DrawTextEx(font, info_element2.c_str(), Vector2{ float(i * 360 + 165), 820 }, 40, 0, Theme_of_element(pokemons[i].element));
		DrawTextEx(font, info_weakness1.c_str(), Vector2{ float(i * 360 + 30), 870 }, 40, 0, BLACK);
		DrawTextEx(font, info_weakness2.c_str(), Vector2{ float(i * 360 + 200), 870 }, 40, 0, Theme_of_Weakness(pokemons[i].weakness));
	}
}


vector<Pokemon> choose_the_pokemon(vector<Pokemon>& mass, vector<Pokemon>& mass_end, int& mod, int& pos_x) {
	if (mod > 0) {
		DrawTexture(arrow, pos_x, 940, WHITE);
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
					if (!IsSoundPlaying(sndChoose)) {
						PlaySound(sndChoose);
					}
					break;
				case 480:
					mass_end.push_back(mass[1]);
					if (!IsSoundPlaying(sndChoose)) {
						PlaySound(sndChoose);
					}
					break;
				case 840:
					mass_end.push_back(mass[2]);
					if (!IsSoundPlaying(sndChoose)) {
						PlaySound(sndChoose);
					}
					break;
				case 1200:
					mass_end.push_back(mass[3]);
					if (!IsSoundPlaying(sndChoose)) {
						PlaySound(sndChoose);
					}
					break;
				case 1560:
					mass_end.push_back(mass[4]);
					if (!IsSoundPlaying(sndChoose)) {
						PlaySound(sndChoose);
					}
					break;
				case 1920:
					mass_end.push_back(mass[5]);
					if (!IsSoundPlaying(sndChoose)) {
						PlaySound(sndChoose);
					}
					break;
				default:
					break;
			}
			mod--;
		}
	}
	return mass_end;
}

int chooseNextAlivePokemonIndex(vector<Pokemon>& pokemons, int currentIndex) {
	int size = pokemons.size();
	for (int i = 1; i < size; ++i) {
		int nextIndex = (currentIndex + i) % size;
		if (!pokemons[nextIndex].isDead) {
			return nextIndex;
		}
	}
	return currentIndex;
}


void fight(vector <Pokemon>& mass_for_player1, vector <Pokemon>& mass_for_player2, int cnt, int& pos_y, int& pos_x, int& player_for_fight) {
	if (cnt == 1) {
		string message = "Player " + to_string(player_for_fight) + " attack the enemy";
		DrawTextEx(font, message.c_str(), Vector2{ 750, 150 }, 64, 0, BLACK);
		DrawTexture(mass_for_player1[0].texture, 200, 520, WHITE);
		DrawTextEx(font, ("Health: " + to_string(mass_for_player1[0].health)).c_str(), Vector2{ 200, 820 }, 64, 0, RED);
		DrawTextEx(font, ("Mana: " + to_string(mass_for_player1[0].mana)).c_str(), Vector2{ 200, 900 }, 64, 0, BLUE);
		DrawTexture(mass_for_player2[0].texture, 1650, 520, WHITE);
		DrawTextEx(font, ("Health: " + to_string(mass_for_player2[0].health)).c_str(), Vector2{ 1650, 820 }, 64, 0, RED);
		DrawTextEx(font, ("Mana: " + to_string(mass_for_player2[0].mana)).c_str(), Vector2{ 1650, 900 }, 64, 0, BLUE);

		vector <Pokemon>& mass_for_me = (player_for_fight == 1) ? mass_for_player1 : mass_for_player2;
		vector <Pokemon>& mass_for_enemy = (player_for_fight == 1) ? mass_for_player2 : mass_for_player1;

		string message1 = "Default attack";
		DrawTextEx(font, message1.c_str(), Vector2{ 900, 520 }, 74, 0, BLACK);
		DrawTexture(arrow_left, 1200, pos_y, WHITE);
		string message2 = "Super attack";
		DrawTextEx(font, message2.c_str(), Vector2{ 900, 620 }, 74, 0, BLACK);
		string message6 = "Skip";
		DrawTextEx(font, message6.c_str(), Vector2{ 900, 720 }, 74, 0, BLACK);
		bool position_changed = false;
		if (mass_for_me[0].mana < 10) pos_y = 630;
		if (!position_changed && pos_y == 430 && !block) {
			if (mass_for_me[0].mana - 25 < 0) {
				if (IsKeyPressed(KEY_DOWN)) {
					pos_y += 200;
					position_changed = true;
				}
			}
			else if (!position_changed && IsKeyPressed(KEY_DOWN)) {
				pos_y += 100;
				position_changed = true;
			}
			string message3 = "Damage: " + to_string(mass_for_me[0].damage);
			DrawTextEx(font, message3.c_str(), { 900, 900 }, 80, 0, BLACK);
			DrawTextEx(font, "Mana: -10", {900, 1000}, 80, 0, BLACK);

			if (IsKeyPressed(KEY_SPACE)) {
				if (!IsSoundPlaying(sndHit)) {
					PlaySound(sndHit);
				}
				mass_for_me[0].mana -= 10;
				if (mass_for_enemy[0].weakness == mass_for_me[0].element) {
					mass_for_enemy[0].health -= int(mass_for_me[0].damage * 1.2);
				}
				else {
					mass_for_enemy[0].health -= mass_for_me[0].damage;
				}
				if (mass_for_enemy[0].health < 0) {
					mass_for_enemy[0].health = 0;
				}
				if (player_for_fight == 1) {
					player_for_fight = 2;
				}
				else {
					player_for_fight = 1;
				}
			}
		}
		if (!position_changed && pos_y == 530 && !block) {
			if (IsKeyPressed(KEY_UP)) {
				pos_y -= 100;
				position_changed = true;
			}
			else if (!position_changed && IsKeyPressed(KEY_DOWN)) {
				pos_y += 100;
				position_changed = true;
			}
			string message4 = enumToString1(mass_for_me[0].special_name);
			string message41 = "Damage: " + to_string(mass_for_me[0].special_damage);
			DrawTextEx(font, message4.c_str(), { 900, 900 }, 80, 0, BLACK);
			DrawTextEx(font, message41.c_str(), { 900, 1000 }, 80, 0, BLACK);
			DrawTextEx(font, "Mana: -25", {900, 1100}, 80, 0, BLACK);

			if (IsKeyPressed(KEY_SPACE)) {
				isShowing = true;
				timer = 0.0f;
				isPlaying = true;
				currentAnimFrame = 0;
				frameCounter = 0;
				currentPos1 = startPos1;
				currentPos2 = startPos2;
				currentPos_for_wave = startPos_for_wave;
				currentPos2_for_wave = startPos2_for_wave;
			}
			NameOfSuper name_of_super = mass_for_me[0].special_name;

			switch (name_of_super)
			{
				case Electric_stan: {
					if (isPlaying) {
						frameCounter++;
						if (frameCounter >= frameDelay) {
							frameCounter = 0;
							currentAnimFrame++;
							if (currentAnimFrame >= 23) {
								currentAnimFrame = 0;
							}
						}
						float frameWidth = (float)(texLightning.width / 23);
						Rectangle frameRec = { frameWidth * currentAnimFrame, 0, frameWidth, (float)texLightning.height };
						
						if (!IsSoundPlaying(sndLight)) {
							PlaySound(sndLight);
						}

						if (player_for_fight == 1) {
							if (currentPos_for_wave.x < endPos_for_wave.x) {
								currentPos_for_wave.x += 20;
								if (currentPos_for_wave.x >= endPos_for_wave.x) {
									currentPos_for_wave = endPos_for_wave;
									isPlaying = false;
									StopSound(sndLight);
									if (mass_for_enemy[0].weakness == mass_for_me[0].element) {
										mass_for_enemy[0].health -= int(mass_for_me[0].special_damage * 1.2);
									}
									else {
										mass_for_enemy[0].health -= mass_for_me[0].special_damage;
									}
									mass_for_me[0].mana -= 25;
									if (mass_for_enemy[0].health - mass_for_me[0].special_damage < 0) {
										mass_for_enemy[0].health = 0;
									}
									player_for_fight = 2;
									pos_y = 430;
								}
							}
							DrawTextureRec(texLightning, frameRec, currentPos_for_wave, WHITE);
						}
						else {
							if (currentPos2_for_wave.x > endPos2_for_wave.x) {
								currentPos2_for_wave.x -= 20;
								if (currentPos2_for_wave.x <= endPos2_for_wave.x) {
									currentPos2_for_wave = endPos2_for_wave;
									isPlaying = false;
									StopSound(sndLight);
									if (mass_for_enemy[0].weakness == mass_for_me[0].element) {
										mass_for_enemy[0].health -= int(mass_for_me[0].special_damage * 1.2);
									}
									else {
										mass_for_enemy[0].health -= mass_for_me[0].special_damage;
									}
									mass_for_me[0].mana -= 25;
									if (mass_for_enemy[0].health - mass_for_me[0].special_damage < 0) {
										mass_for_enemy[0].health = 0;
									}
									player_for_fight = 1;
									pos_y = 430;
								}
							}
							DrawTextureRec(texLightning, frameRec, currentPos2_for_wave, WHITE);
						}
					}
					break;
				}
				case Fireball: {
					if (isPlaying) {
						frameCounter++;
						if (frameCounter >= frameDelay) {
							currentAnimFrame++;
							if (currentAnimFrame >= animFrames_for_fire) {
								currentAnimFrame = 0;
							}
							nextFrameDataOffset = imFireball.width * imFireball.height * 4 * currentAnimFrame;
							UpdateTexture(texFireball, ((unsigned char*)imFireball.data) + nextFrameDataOffset);
							UpdateTexture(texFireball2, ((unsigned char*)imFireball2.data) + nextFrameDataOffset);
							frameCounter = 0;
						}
						if (!IsSoundPlaying(sndFire)) {
							PlaySound(sndFire);
						}

						if (player_for_fight == 1) {
							if (currentPos1.x < endPos1.x)
							{
								currentPos1.x += 17;
								if (currentPos1.x >= endPos1.x)
								{
									currentPos1 = endPos1;
									if (mass_for_enemy[0].weakness == mass_for_me[0].element) {
										mass_for_enemy[0].health -= int(mass_for_me[0].special_damage * 1.2);
									}
									else {
										mass_for_enemy[0].health -= mass_for_me[0].special_damage;
									}
									mass_for_me[0].mana -= 25;
									if (mass_for_enemy[0].health - mass_for_me[0].special_damage < 0) {
										mass_for_enemy[0].health = 0;
									}
									isPlaying = false;
									StopSound(sndFire);
									if (player_for_fight == 1) {
										player_for_fight = 2;
										pos_y = 430;
									}
									else {
										player_for_fight = 1;
										pos_y = 430;
									}
								}
							}
							DrawTexture(texFireball, (int)currentPos1.x, (int)currentPos1.y, WHITE);
						}	
						else {
							if (currentPos2.x > endPos2.x)
							{
								currentPos2.x -= 17;
								if (currentPos2.x <= endPos2.x)
								{
									currentPos2 = endPos2;
									if (mass_for_enemy[0].weakness == mass_for_me[0].element) {
										mass_for_enemy[0].health -= int(mass_for_me[0].special_damage * 1.2);
									}
									else {
										mass_for_enemy[0].health -= mass_for_me[0].special_damage;
									}
									mass_for_me[0].mana -= 25;
									if (mass_for_enemy[0].health - mass_for_me[0].special_damage < 0) {
										mass_for_enemy[0].health = 0;
									}
									isPlaying = false;
									StopSound(sndFire);
									if (player_for_fight == 1) {
										player_for_fight = 2;
										pos_y = 430;
									}
									else {
										player_for_fight = 1;
										pos_y = 430;
									}
								}
							}
							DrawTexture(texFireball2, (int)currentPos2.x, (int)currentPos2.y, WHITE);
						}
					}
					break;
				}
				case Tsunami: {
					if (isPlaying) {
						frameCounter++;
						if (frameCounter >= frameDelay) {
							frameCounter = 0;
							currentAnimFrame++;
							if (currentAnimFrame >= 11) {
								currentAnimFrame = 0;
							}
						}
						float frameWidth = (float)(texWave.width / 11);
						Rectangle frameRec = { frameWidth * currentAnimFrame, 0, frameWidth, (float)texWave.height };
						float frameWidth2 = (float)(texWave2.width / 11);
						Rectangle frameRec2 = { frameWidth2 * currentAnimFrame, 0, frameWidth2, (float)texWave2.height };

						if (!IsSoundPlaying(sndTsunami)) {
							PlaySound(sndTsunami);
						}

						if (player_for_fight == 1) {
							if (currentPos_for_wave.x < endPos_for_wave.x) {
								currentPos_for_wave.x += 20;
								if (currentPos_for_wave.x >= endPos_for_wave.x) {
									currentPos_for_wave = endPos_for_wave;
									isPlaying = false;
									StopSound(sndTsunami);
									if (mass_for_enemy[0].weakness == mass_for_me[0].element) {
										mass_for_enemy[0].health -= int(mass_for_me[0].special_damage * 1.2);
									}
									else {
										mass_for_enemy[0].health -= mass_for_me[0].special_damage;
									}
									mass_for_me[0].mana -= 25;
									if (mass_for_enemy[0].health - mass_for_me[0].special_damage < 0) {
										mass_for_enemy[0].health = 0;
									}
									player_for_fight = 2;
									pos_y = 430;
								}
							}
							DrawTextureRec(texWave, frameRec, currentPos_for_wave, WHITE);
						}
						else {
							if (currentPos2_for_wave.x > endPos2_for_wave.x) {
								currentPos2_for_wave.x -= 20;
								if (currentPos2_for_wave.x <= endPos2_for_wave.x) {
									currentPos2_for_wave = endPos2_for_wave;
									isPlaying = false;
									StopSound(sndTsunami);
									if (mass_for_enemy[0].weakness == mass_for_me[0].element) {
										mass_for_enemy[0].health -= int(mass_for_me[0].special_damage * 1.2);
									}
									else {
										mass_for_enemy[0].health -= mass_for_me[0].special_damage;
									}
									mass_for_me[0].mana -= 25;
									if (mass_for_enemy[0].health - mass_for_me[0].special_damage < 0) {
										mass_for_enemy[0].health = 0;
									}
									player_for_fight = 1;
									pos_y = 430;
								}
							}
							DrawTextureRec(texWave2, frameRec2, currentPos2_for_wave, WHITE);
						}
					}
					break;
				}
				case Entangling_vine: {
					if (isPlaying) {
						if (!IsSoundPlaying(sndGrass)) {
							PlaySound(sndGrass);
						}
						frameCounter++;
						if (frameCounter >= frameDelay) {
							currentAnimFrame++;
							if (currentAnimFrame >= 15) {
								currentAnimFrame = 0;
								StopSound(sndGrass);
								isPlaying = false;
								if (mass_for_enemy[0].weakness == mass_for_me[0].element) {
									mass_for_enemy[0].health -= int(mass_for_me[0].special_damage * 1.2);
								}
								else {
									mass_for_enemy[0].health -= mass_for_me[0].special_damage;
								}
								mass_for_me[0].mana -= 25;
								if (mass_for_enemy[0].health < 0) {
									mass_for_enemy[0].health = 0;
								}
								player_for_fight = (player_for_fight == 1) ? 2 : 1;
								pos_y = 430;
							}
							frameCounter = 0;
						}

						if (player_for_fight == 1) {
							DrawTexture(texGrass, 1700, 670, WHITE);
						}
						else {
							DrawTexture(texGrass, 230, 670, WHITE);
						}
					}
					break;
				}
				case Poisonous_cloud: {
					if (isPlaying) {
						if (!IsSoundPlaying(sndPoison)) {
							PlaySound(sndPoison);
						}
						frameCounter++;
						if (frameCounter >= frameDelay_for_cloud) {
							frameCounter = 0;
							currentAnimFrame++;
							if (currentAnimFrame >= 18) {
								currentAnimFrame = 0;
								isPlaying = false;
								StopSound(sndPoison);
								if (mass_for_enemy[0].weakness == mass_for_me[0].element) {
									mass_for_enemy[0].health -= int(mass_for_me[0].special_damage * 1.2);
								}
								else {
									mass_for_enemy[0].health -= mass_for_me[0].special_damage;
								}
								mass_for_me[0].mana -= 25;
								if (mass_for_enemy[0].health - mass_for_me[0].special_damage < 0) {
									mass_for_enemy[0].health = 0;
								}
								if (player_for_fight == 1) player_for_fight = 2;
								else player_for_fight = 1;
								pos_y = 430;
							}
						}
						float frameWidth = (float)(texCloud.width / 18);
						Rectangle frameRec = { frameWidth * currentAnimFrame, 0, frameWidth, (float)texCloud.height };

						

						if (player_for_fight == 1) {
							DrawTextureRec(texCloud, frameRec, position1, WHITE);
						}
						else {
							DrawTextureRec(texCloud, frameRec, position2, WHITE);
						}
						break;
					}
				}
				case Sound_Attack: {
					if (isPlaying) {
						if (!IsSoundPlaying(sndSound)) {
							PlaySound(sndSound);
						}
						frameCounter++;
						if (frameCounter >= frameDelay) {
							frameCounter = 0;
							currentAnimFrame++;
							if (currentAnimFrame >= 10) {
								currentAnimFrame = 0;
								isPlaying = false;
								StopSound(sndSound);
								if (mass_for_enemy[0].weakness == mass_for_me[0].element) {
									mass_for_enemy[0].health -= int(mass_for_me[0].special_damage * 1.2);
								}
								else {
									mass_for_enemy[0].health -= mass_for_me[0].special_damage;
								}
								mass_for_me[0].mana -= 25;
								if (mass_for_enemy[0].health - mass_for_me[0].special_damage < 0) {
									mass_for_enemy[0].health = 0;
								}
								if (player_for_fight == 1) player_for_fight = 2;
								else player_for_fight = 1;
								pos_y = 430;
							}
						}
						float frameWidth = (float)(texSound.width / 10);
						Rectangle frameRec = { frameWidth * currentAnimFrame, 0, frameWidth, (float)texSound.height };

						DrawTextureRec(texSound, frameRec, Vector2{400, 460}, WHITE);
						
						break;
					}
				}
			}
		}
		if (!position_changed && pos_y == 630 && !block) {
			string message5 = "Mana +10";
			DrawTextEx(font, message5.c_str(), { 900, 900 }, 80, 0, BLACK);
			if (mass_for_me[0].mana - 10 < 0) {
				if (IsKeyPressed(KEY_SPACE)) {
					if (mass_for_me[0].mana + 10 <= 60) {
						mass_for_me[0].mana += 10;
						if (!IsSoundPlaying(sndMana)) {
							PlaySound(sndMana);
						}
						if (player_for_fight == 1) player_for_fight = 2;
						else player_for_fight = 1;
						pos_y = 430;
					}
				}
			}
			else if (mass_for_me[0].mana - 25 < 0) {
				if (IsKeyPressed(KEY_UP)) {
					pos_y -= 200;
					position_changed = true;
				}
				if (IsKeyPressed(KEY_SPACE)) {
					if (mass_for_me[0].mana + 10 <= 100) {
						mass_for_me[0].mana += 10;
						if (!IsSoundPlaying(sndMana)) {
							PlaySound(sndMana);
						}
						if (player_for_fight == 1) player_for_fight = 2;
						else player_for_fight = 1;
						pos_y = 430;
					}
				}
			}
			else {
				if (!position_changed && IsKeyPressed(KEY_UP)) {
					pos_y -= 100;
					position_changed = true;
				}
				if (IsKeyPressed(KEY_SPACE)) {
					if (mass_for_me[0].mana + 10 <= 60) {
						mass_for_me[0].mana += 10;
						if (!IsSoundPlaying(sndMana)) {
							PlaySound(sndMana);
						}
						if (player_for_fight == 1) player_for_fight = 2;
						else player_for_fight = 1;
						pos_y = 430;
					}
				}
			}
		}
		if (mass_for_player1[0].health == 0) {
			DrawTextEx(font, "Player 2 win", Vector2{ 700, 1100 }, 150, 0, BLACK);
			block = true;
		}
		else if (mass_for_player2[0].health == 0) {
			DrawTextEx(font, "Player 1 win", Vector2{ 700, 1100 }, 150, 0, BLACK);
			block = true;
		}
	}

	if (cnt == 3) {
		bool position_changed = false;
		if (!choosed_pokemon1) {
			string message = "Player 1 choose you pokemon";
			DrawTextEx(font, message.c_str(), Vector2{ 750, 150 }, 64, 0, BLACK);
			DrawTexture(mass_for_player1[0].texture, 200, 320, WHITE);
			DrawTextEx(font, ("Health: " + to_string(mass_for_player1[0].health)).c_str(), Vector2{ 200, 620 }, 64, 0, RED);
			DrawTextEx(font, ("Mana: " + to_string(mass_for_player1[0].mana)).c_str(), Vector2{ 200, 700 }, 64, 0, BLUE);
			DrawTexture(mass_for_player1[1].texture, 900, 320, WHITE);
			DrawTextEx(font, ("Health: " + to_string(mass_for_player1[1].health)).c_str(), Vector2{ 900, 620 }, 64, 0, RED);
			DrawTextEx(font, ("Mana: " + to_string(mass_for_player1[1].mana)).c_str(), Vector2{ 900, 700 }, 64, 0, BLUE);
			DrawTexture(mass_for_player1[2].texture, 1700, 320, WHITE);
			DrawTextEx(font, ("Health: " + to_string(mass_for_player1[2].health)).c_str(), Vector2{ 1700, 620 }, 64, 0, RED);
			DrawTextEx(font, ("Mana: " + to_string(mass_for_player1[2].mana)).c_str(), Vector2{ 1700, 700 }, 64, 0, BLUE);
			DrawTexture(arrow, pos_x, 850, WHITE);
			if (!position_changed && pos_x == 250) {
				if (IsKeyPressed(KEY_RIGHT)) {
					pos_x += 750;
					position_changed = true;
				}
				if (IsKeyPressed(KEY_ENTER)) {
					i1 = 0;
					if (!IsSoundPlaying(sndChoose)) {
						PlaySound(sndChoose);
					}
					choosed_pokemon1 = true;
				}
			}
			if (!position_changed && pos_x == 1000) {
				if (IsKeyPressed(KEY_RIGHT)) {
					pos_x += 750;
					position_changed = true;
				}
				if (IsKeyPressed(KEY_LEFT)) {
					pos_x -= 750;
					position_changed = true;
				}
				if (IsKeyPressed(KEY_ENTER)) {
					i1 = 1;
					if (!IsSoundPlaying(sndChoose)) {
						PlaySound(sndChoose);
					}
					choosed_pokemon1 = true;
				}
			}
			if (!position_changed && pos_x == 1750) {
				if (IsKeyPressed(KEY_LEFT)) {
					pos_x -= 750;
					position_changed = true;
				}
				if (IsKeyPressed(KEY_ENTER)) {
					i1 = 2;
					if (!IsSoundPlaying(sndChoose)) {
						PlaySound(sndChoose);
					}
					choosed_pokemon1 = true;
				}
			}
			if (choosed_pokemon1) pos_x = 250;
		}
		else if (!choosed_pokemon2) {
			string message = "Player 2 choose you pokemon";
			DrawTextEx(font, message.c_str(), Vector2{ 750, 150 }, 64, 0, BLACK);
			DrawTexture(mass_for_player2[0].texture, 200, 320, WHITE);
			DrawTextEx(font, ("Health: " + to_string(mass_for_player2[0].health)).c_str(), Vector2{ 200, 620 }, 64, 0, RED);
			DrawTextEx(font, ("Mana: " + to_string(mass_for_player2[0].mana)).c_str(), Vector2{ 200, 700 }, 64, 0, BLUE);
			DrawTexture(mass_for_player2[1].texture, 900, 320, WHITE);
			DrawTextEx(font, ("Health: " + to_string(mass_for_player2[1].health)).c_str(), Vector2{ 900, 620 }, 64, 0, RED);
			DrawTextEx(font, ("Mana: " + to_string(mass_for_player2[01].mana)).c_str(), Vector2{ 900, 700 }, 64, 0, BLUE);
			DrawTexture(mass_for_player2[2].texture, 1700, 320, WHITE);
			DrawTextEx(font, ("Health: " + to_string(mass_for_player2[2].health)).c_str(), Vector2{ 1700, 620 }, 64, 0, RED);
			DrawTextEx(font, ("Mana: " + to_string(mass_for_player2[2].mana)).c_str(), Vector2{ 1700, 700 }, 64, 0, BLUE);
			DrawTexture(arrow, pos_x, 850, WHITE);
			if (!position_changed && pos_x == 250) {
				if (IsKeyPressed(KEY_RIGHT)) {
					pos_x += 750;
					position_changed = true;
				}
				if (IsKeyPressed(KEY_ENTER)) {
					i2 = 0;
					if (!IsSoundPlaying(sndChoose)) {
						PlaySound(sndChoose);
					}
					choosed_pokemon2 = true;
				}
			}
			if (!position_changed && pos_x == 1000) {
				if (IsKeyPressed(KEY_RIGHT)) {
					pos_x += 750;
					position_changed = true;
				}
				if (IsKeyPressed(KEY_LEFT)) {
					pos_x -= 750;
					position_changed = true;
				}
				if (IsKeyPressed(KEY_ENTER)) {
					i2 = 1;
					if (!IsSoundPlaying(sndChoose)) {
						PlaySound(sndChoose);
					}
					choosed_pokemon2 = true;
				}
			}
			if (!position_changed && pos_x == 1750) {
				if (IsKeyPressed(KEY_LEFT)) {
					pos_x -= 750;
					position_changed = true;
				}
				if (IsKeyPressed(KEY_ENTER)) {
					i2 = 2;
					if (!IsSoundPlaying(sndChoose)) {
						PlaySound(sndChoose);
					}
					choosed_pokemon2 = true;
				}
			}
		}
		if (choosed_pokemon1 && choosed_pokemon2) {
			string message = "Player " + to_string(player_for_fight) + " attack the enemy";
			DrawTextEx(font, message.c_str(), Vector2{ 750, 150 }, 64, 0, BLACK);
			DrawTexture(mass_for_player1[i1].texture, 200, 520, WHITE);
			DrawTextEx(font, ("Health: " + to_string(mass_for_player1[i1].health)).c_str(), Vector2{ 200, 820 }, 64, 0, RED);
			DrawTextEx(font, ("Mana: " + to_string(mass_for_player1[i1].mana)).c_str(), Vector2{ 200, 900 }, 64, 0, BLUE);
			DrawTexture(mass_for_player2[i2].texture, 1650, 520, WHITE);
			DrawTextEx(font, ("Health: " + to_string(mass_for_player2[i2].health)).c_str(), Vector2{ 1650, 820 }, 64, 0, RED);
			DrawTextEx(font, ("Mana: " + to_string(mass_for_player2[i2].mana)).c_str(), Vector2{ 1650, 900 }, 64, 0, BLUE);

			vector <Pokemon>& mass_for_me = (player_for_fight == 1) ? mass_for_player1 : mass_for_player2;
			vector <Pokemon>& mass_for_enemy = (player_for_fight == 1) ? mass_for_player2 : mass_for_player1;

			string message1 = "Default attack";
			DrawTextEx(font, message1.c_str(), Vector2{ 850, 520 }, 74, 0, BLACK);
			string message2 = "Super attack";
			DrawTextEx(font, message2.c_str(), Vector2{ 850, 620 }, 74, 0, BLACK);
			string message6 = "Skip";
			DrawTextEx(font, message6.c_str(), Vector2{ 850, 720 }, 74, 0, BLACK);
			string message7 = "Others pokemon";
			DrawTextEx(font, message7.c_str(), Vector2{ 850, 820 }, 74, 0, BLACK);
			DrawTexture(arrow_left, 1250, pos_y, WHITE);

			for (int j = 0; j < mass_for_player1.size(); ++j) {
				if (mass_for_player1[j].health == 0 && !mass_for_player1[j].isDead) {
					mass_for_player1[j].isDead = true;
					i1 = chooseNextAlivePokemonIndex(mass_for_player1, i1);
				}
			}
			for (int j = 0; j < mass_for_player2.size(); ++j) {
				if (mass_for_player2[j].health == 0 && !mass_for_player2[j].isDead) {
					mass_for_player2[j].isDead = true;
					i2 = chooseNextAlivePokemonIndex(mass_for_player2, i2);
				}
			}
			int i = (player_for_fight == 1) ? i1 : i2;
			for (int j = 0; j < mass_for_me.size(); ++j) {
				if (mass_for_me[j].health == 0 && !mass_for_me[j].isDead) {
					mass_for_me[j].isDead = true;

					if (player_for_fight == 1) {
						i1 = chooseNextAlivePokemonIndex(mass_for_me, i1);
					}
					else {
						i2 = chooseNextAlivePokemonIndex(mass_for_me, i2);
					}
				}
			}


			if (!position_changed && pos_y == 430 && !block) {
				if (mass_for_me[i].mana - 25 < 0) {
					if (IsKeyPressed(KEY_DOWN)) {
						pos_y += 200;
						position_changed = true;
					}
				}
				else if (!position_changed && IsKeyPressed(KEY_DOWN)) {
					pos_y += 100;
					position_changed = true;
				}
				string message3 = "Damage: " + to_string(mass_for_me[i1].damage);
				DrawTextEx(font, message3.c_str(), { 850, 950 }, 80, 0, BLACK);
				DrawTextEx(font, "Mana: -10", {850, 1050}, 80, 0, BLACK);

				if (mass_for_me[i].mana - 10 < 0) {
					pos_y = 630;
				}
				else if (IsKeyPressed(KEY_SPACE)) {
					if (!IsSoundPlaying(sndHit)) {
						PlaySound(sndHit);
					}
					mass_for_me[i].mana -= 10;
					if (player_for_fight == 1) {
						if (mass_for_enemy[i2].weakness == mass_for_me[i1].element) {
							mass_for_enemy[i2].health -= int(mass_for_me[i1].damage * 1.2);
						}
						else {
							mass_for_enemy[i2].health -= mass_for_me[i1].damage;
						}
						if (mass_for_enemy[i2].health < 0) {
							mass_for_enemy[i2].health = 0;
						}
						player_for_fight = 2;
					}
					else {
						if (mass_for_enemy[i1].weakness == mass_for_me[i2].element) {
							mass_for_enemy[i1].health -= int(mass_for_me[i2].damage * 1.2);
						}
						else {
							mass_for_enemy[i1].health -= mass_for_me[i2].damage;
						}
						if (mass_for_enemy[i1].health < 0) {
							mass_for_enemy[i1].health = 0;
						}
						player_for_fight = 1;
					}
				}
			}

			if (!position_changed && pos_y == 530 && !block) {
				if (IsKeyPressed(KEY_DOWN)) {
					pos_y += 100;
					position_changed = true;
				}
				else if (IsKeyPressed(KEY_UP)) {
					pos_y -= 100;
					position_changed = true;
				}

				string message4 = enumToString1(mass_for_me[i].special_name);
				string message41 = "Damage: " + to_string(mass_for_me[i].special_damage);
				DrawTextEx(font, message4.c_str(), { 850, 950 }, 80, 0, BLACK);
				DrawTextEx(font, message41.c_str(), { 850, 1050 }, 80, 0, BLACK);
				DrawTextEx(font, "Mana: -25", {850, 1150}, 80, 0, BLACK);
				float deltaTime = GetFrameTime();
				if (IsKeyPressed(KEY_SPACE)) {
					isShowing = true;
					timer = 0.0f;
					isPlaying = true;
					currentAnimFrame = 0;
					frameCounter = 0;
					currentPos1 = startPos1;
					currentPos2 = startPos2;
					currentPos_for_wave = startPos_for_wave;
					currentPos2_for_wave = startPos2_for_wave;
				}
				NameOfSuper name_of_super = mass_for_me[i].special_name;

				switch (name_of_super)
				{
					case Electric_stan: {
						if (isPlaying) {
							frameCounter++;
							if (frameCounter >= frameDelay) {
								frameCounter = 0;
								currentAnimFrame++;
								if (currentAnimFrame >= 23) {
									currentAnimFrame = 0;
								}
							}
							float frameWidth = (float)(texLightning.width / 23);
							Rectangle frameRec = { frameWidth * currentAnimFrame, 0, frameWidth, (float)texLightning.height };

							if (!IsSoundPlaying(sndLight)) {
								PlaySound(sndLight);
							}

							if (player_for_fight == 1) {
								if (currentPos_for_wave.x < endPos_for_wave.x) {
									currentPos_for_wave.x += 20;
									if (currentPos_for_wave.x >= endPos_for_wave.x) {
										currentPos_for_wave = endPos_for_wave;
										isPlaying = false;
										StopSound(sndLight);
										if (mass_for_enemy[i2].weakness == mass_for_me[i1].element) {
											mass_for_enemy[i2].health -= int(mass_for_me[i1].special_damage * 1.2);
										}
										else {
											mass_for_enemy[i2].health -= mass_for_me[i1].special_damage;
										}
										mass_for_me[i1].mana -= 25;
										if (mass_for_enemy[i2].health - mass_for_me[i1].special_damage < 0) {
											mass_for_enemy[i2].health = 0;
										}
										player_for_fight = 2;
										pos_y = 430;
									}
								}
								DrawTextureRec(texLightning, frameRec, currentPos_for_wave, WHITE);
							}
							else {
								if (currentPos2_for_wave.x > endPos2_for_wave.x) {
									currentPos2_for_wave.x -= 20;
									if (currentPos2_for_wave.x <= endPos2_for_wave.x) {
										currentPos2_for_wave = endPos2_for_wave;
										isPlaying = false;
										StopSound(sndLight);
										if (mass_for_enemy[i1].weakness == mass_for_me[i2].element) {
											mass_for_enemy[i1].health -= int(mass_for_me[i2].special_damage * 1.2);
										}
										else {
											mass_for_enemy[i1].health -= mass_for_me[i2].special_damage;
										}
										mass_for_me[i2].mana -= 25;
										if (mass_for_enemy[i1].health - mass_for_me[i2].special_damage < 0) {
											mass_for_enemy[i1].health = 0;
										}
										player_for_fight = 1;
										pos_y = 430;
									}
								}
								DrawTextureRec(texLightning, frameRec, currentPos2_for_wave, WHITE);
							}
						}
						break;
					}
					case Fireball: {
						if (isPlaying) {
							frameCounter++;
							if (frameCounter >= frameDelay) {
								currentAnimFrame++;
								if (currentAnimFrame >= animFrames_for_fire) {
									currentAnimFrame = 0;
								}
								nextFrameDataOffset = imFireball.width * imFireball.height * 4 * currentAnimFrame;
								UpdateTexture(texFireball, ((unsigned char*)imFireball.data) + nextFrameDataOffset);
								UpdateTexture(texFireball2, ((unsigned char*)imFireball2.data) + nextFrameDataOffset);
								frameCounter = 0;
							}

							if (!IsSoundPlaying(sndFire)) {
								PlaySound(sndFire);
							}

							if (player_for_fight == 1) {
								if (currentPos1.x < endPos1.x)
								{
									currentPos1.x += 17;
									if (currentPos1.x >= endPos1.x)
									{
										currentPos1 = endPos1;
										if (mass_for_enemy[i2].weakness == mass_for_me[i1].element) {
											mass_for_enemy[i2].health -= int(mass_for_me[i1].special_damage * 1.2);
										}
										else {
											mass_for_enemy[i2].health -= mass_for_me[i1].special_damage;
										}
										mass_for_me[i1].mana -= 25;
										if (mass_for_enemy[i2].health - mass_for_me[i1].special_damage < 0) {
											mass_for_enemy[i2].health = 0;
										}
										isPlaying = false;
										StopSound(sndFire);
										if (player_for_fight == 1) {
											player_for_fight = 2;
											pos_y = 430;
										}
										else {
											player_for_fight = 1;
											pos_y = 430;
										}
									}
								}
								DrawTexture(texFireball, (int)currentPos1.x, (int)currentPos1.y, WHITE);
							}
							else {
								if (currentPos2.x > endPos2.x)
								{
									currentPos2.x -= 17;
									if (currentPos2.x <= endPos2.x)
									{
										currentPos2 = endPos2;
										if (mass_for_enemy[i1].weakness == mass_for_me[i2].element) {
											mass_for_enemy[i1].health -= int(mass_for_me[i2].special_damage * 1.2);
										}
										else {
											mass_for_enemy[i1].health -= mass_for_me[i2].special_damage;
										}
										mass_for_me[i2].mana -= 25;
										if (mass_for_enemy[i1].health - mass_for_me[i2].special_damage < 0) {
											mass_for_enemy[i1].health = 0;
										}
										isPlaying = false;
										StopSound(sndFire);
										if (player_for_fight == 1) {
											player_for_fight = 2;
											pos_y = 430;
										}
										else {
											player_for_fight = 1;
											pos_y = 430;
										}
									}
								}
								DrawTexture(texFireball2, (int)currentPos2.x, (int)currentPos2.y, WHITE);
							}
						}
						break;
					}
					case Tsunami: {
						if (isPlaying) {
							frameCounter++;
							if (frameCounter >= frameDelay) {
								frameCounter = 0;
								currentAnimFrame++;
								if (currentAnimFrame >= 11) {
									currentAnimFrame = 0;
								}
							}
							float frameWidth = (float)(texWave.width / 11);
							Rectangle frameRec = { frameWidth * currentAnimFrame, 0, frameWidth, (float)texWave.height };
							float frameWidth2 = (float)(texWave2.width / 11);
							Rectangle frameRec2 = { frameWidth2 * currentAnimFrame, 0, frameWidth2, (float)texWave2.height };

							if (!IsSoundPlaying(sndTsunami)) {
								PlaySound(sndTsunami);
							}

							if (player_for_fight == 1) {
								if (currentPos_for_wave.x < endPos_for_wave.x) {
									currentPos_for_wave.x += 20;
									if (currentPos_for_wave.x >= endPos_for_wave.x) {
										currentPos_for_wave = endPos_for_wave;
										isPlaying = false;
										StopSound(sndTsunami);
										if (mass_for_enemy[i2].weakness == mass_for_me[i1].element) {
											mass_for_enemy[i2].health -= int(mass_for_me[i1].special_damage * 1.2);
										}
										else {
											mass_for_enemy[i2].health -= mass_for_me[i1].special_damage;
										}
										mass_for_me[i1].mana -= 25;
										if (mass_for_enemy[i2].health - mass_for_me[i1].special_damage < 0) {
											mass_for_enemy[i2].health = 0;
										}
										player_for_fight = 2;
										pos_y = 430;
									}
								}
								DrawTextureRec(texWave, frameRec, currentPos_for_wave, WHITE);
							}
							else {
								if (currentPos2_for_wave.x > endPos2_for_wave.x) {
									currentPos2_for_wave.x -= 20;
									if (currentPos2_for_wave.x <= endPos2_for_wave.x) {
										currentPos2_for_wave = endPos2_for_wave;
										isPlaying = false;
										StopSound(sndTsunami);
										if (mass_for_enemy[i1].weakness == mass_for_me[i2].element) {
											mass_for_enemy[i1].health -= int(mass_for_me[i2].special_damage * 1.2);
										}
										else {
											mass_for_enemy[i1].health -= mass_for_me[i2].special_damage;
										}
										mass_for_me[i2].mana -= 25;
										if (mass_for_enemy[i1].health - mass_for_me[i2].special_damage < 0) {
											mass_for_enemy[i1].health = 0;
										}
										player_for_fight = 1;
										pos_y = 430;
									}
								}
								DrawTextureRec(texWave2, frameRec2, currentPos2_for_wave, WHITE);
							}
						}
						break;
					}
					case Entangling_vine: {
						if (isPlaying) {
							if (!IsSoundPlaying(sndGrass)) {
								PlaySound(sndGrass);
							}
							frameCounter++;
							if (frameCounter >= frameDelay) {
								currentAnimFrame++;
								if (currentAnimFrame >= animFrames_for_light) {
									currentAnimFrame = 0;
									isPlaying = false;
									StopSound(sndGrass);
									if (player_for_fight == 1) {
										if (mass_for_enemy[i2].weakness == mass_for_me[i1].element) {
											mass_for_enemy[i2].health -= int(mass_for_me[i1].special_damage * 1.2);
										}
										else {
											mass_for_enemy[i2].health -= mass_for_me[i1].special_damage;
										}
										mass_for_me[i1].mana -= 25;
										if (mass_for_enemy[i2].health - mass_for_me[i1].special_damage < 0) {
											mass_for_enemy[i2].health = 0;
										}
										player_for_fight = 2;
										pos_y = 430;
									}
									else {
										if (mass_for_enemy[i1].weakness == mass_for_me[i2].element) {
											mass_for_enemy[i1].health -= int(mass_for_me[i2].special_damage * 1.2);
										}
										else {
											mass_for_enemy[i1].health -= mass_for_me[i2].special_damage;
										}
										mass_for_me[i2].mana -= 25;
										if (mass_for_enemy[i1].health - mass_for_me[i2].special_damage < 0) {
											mass_for_enemy[i1].health = 0;
										}
										player_for_fight = 1;
										pos_y = 430;
									}
								}
								frameCounter = 0;
							}

							if (player_for_fight == 1) {
								DrawTexture(texGrass, 1700, 670, WHITE);
							}
							else {
								DrawTexture(texGrass, 230, 670, WHITE);
							}
						}
						break;
					}
					case Poisonous_cloud: {
						if (isPlaying) {
							if (!IsSoundPlaying(sndPoison)) {
								PlaySound(sndPoison);
							}
							frameCounter++;
							if (frameCounter >= frameDelay_for_cloud) {
								frameCounter = 0;
								currentAnimFrame++;
								if (currentAnimFrame >= 18) {
									currentAnimFrame = 0;
									isPlaying = false;
									StopSound(sndPoison);
									if (player_for_fight == 1) {
										if (mass_for_enemy[i2].weakness == mass_for_me[i1].element) {
											mass_for_enemy[i2].health -= int(mass_for_me[i1].special_damage * 1.2);
										}
										else {
											mass_for_enemy[i2].health -= mass_for_me[i1].special_damage;
										}
										mass_for_me[i1].mana -= 25;
										if (mass_for_enemy[i2].health - mass_for_me[i1].special_damage < 0) {
											mass_for_enemy[i2].health = 0;
										}
										player_for_fight = 2;
									}
									else {
										if (mass_for_enemy[i1].weakness == mass_for_me[i2].element) {
											mass_for_enemy[i1].health -= int(mass_for_me[i2].special_damage * 1.2);
										}
										else {
											mass_for_enemy[i1].health -= mass_for_me[i2].special_damage;
										}
										mass_for_me[i2].mana -= 25;
										if (mass_for_enemy[i1].health - mass_for_me[i2].special_damage < 0) {
											mass_for_enemy[i1].health = 0;
										}
										player_for_fight = 1;
									}
									pos_y = 430;
								}
							}
							float frameWidth = (float)(texCloud.width / 18);
							Rectangle frameRec = { frameWidth * currentAnimFrame, 0, frameWidth, (float)texCloud.height };

							if (player_for_fight == 1) {
								DrawTextureRec(texCloud, frameRec, position1, WHITE);
							}
							else {
								DrawTextureRec(texCloud, frameRec, position2, WHITE);
							}
							break;
						}
					}
					case Sound_Attack: {
						if (isPlaying){
							if (!IsSoundPlaying(sndSound)) {
								PlaySound(sndSound);
							}
							frameCounter++;
							if (frameCounter >= frameDelay) {
								frameCounter = 0;
								currentAnimFrame++;
								if (currentAnimFrame >= 10) {
									currentAnimFrame = 0;
									isPlaying = false;
									StopSound(sndSound);
									if (player_for_fight == 1) {
										if (mass_for_enemy[i2].weakness == mass_for_me[i1].element) {
											mass_for_enemy[i2].health -= int(mass_for_me[i1].special_damage * 1.2);
										}
										else {
											mass_for_enemy[i2].health -= mass_for_me[i1].special_damage;
										}
										mass_for_me[i1].mana -= 25;
										if (mass_for_enemy[i2].health - mass_for_me[i1].special_damage < 0) {
											mass_for_enemy[i2].health = 0;
										}
										player_for_fight = 2;
									}
									else {
										if (mass_for_enemy[i1].weakness == mass_for_me[i2].element) {
											mass_for_enemy[i1].health -= int(mass_for_me[i2].special_damage * 1.2);
										}
										else {
											mass_for_enemy[i1].health -= mass_for_me[i2].special_damage;
										}
										mass_for_me[i2].mana -= 25;
										if (mass_for_enemy[i1].health - mass_for_me[i2].special_damage < 0) {
											mass_for_enemy[i1].health = 0;
										}
										player_for_fight = 1;
									}
									pos_y = 430;
								}
							}
							float frameWidth = (float)(texSound.width / 10);
							Rectangle frameRec = { frameWidth * currentAnimFrame, 0, frameWidth, (float)texSound.height };

							DrawTextureRec(texSound, frameRec, Vector2{ 400, 460 }, WHITE);

							break;
						}
					}
				}
			}

			if (!position_changed && pos_y == 630 && !block) {
				string message5 = "Mana +10";
				DrawTextEx(font, message5.c_str(), { 850, 950 }, 80, 0, BLACK);
				if (mass_for_me[i].mana - 10 < 0) {
					if (IsKeyPressed(KEY_DOWN)) {
						pos_y += 100;
						position_changed = true;
					}
					if (IsKeyPressed(KEY_SPACE)) {
						if (mass_for_me[i].mana + 10 <= 60) {
							mass_for_me[i].mana += 10;
							if (!IsSoundPlaying(sndMana)) {
								PlaySound(sndMana);
							}
							if (player_for_fight == 1) player_for_fight = 2;
							else player_for_fight = 1;
							pos_y = 430;
						}
					}
				}
				else if (mass_for_me[i].mana - 25 < 0) {
					if (IsKeyPressed(KEY_UP)) {
						pos_y -= 200;
						position_changed = true;
					}
					if (IsKeyPressed(KEY_DOWN)) {
						pos_y += 100;
						position_changed = true;
					}
					if (IsKeyPressed(KEY_SPACE)) {
						if (mass_for_me[i].mana + 10 <= 60) {
							mass_for_me[i].mana += 10;
							if (!IsSoundPlaying(sndMana)) {
								PlaySound(sndMana);
							}
							if (player_for_fight == 1) player_for_fight = 2;
							else player_for_fight = 1;
							pos_y = 430;
						}
					}
				}
				else {
					if (!position_changed && IsKeyPressed(KEY_UP)) {
						pos_y -= 100;
						position_changed = true;
					}
					if (IsKeyPressed(KEY_DOWN)) {
						pos_y += 100;
						position_changed = true;
					}
					if (IsKeyPressed(KEY_SPACE)) {
						if (mass_for_me[i].mana + 10 <= 60) {
							mass_for_me[i].mana += 10;
							if (!IsSoundPlaying(sndMana)) {
								PlaySound(sndMana);
							}
							if (player_for_fight == 1) player_for_fight = 2;
							else player_for_fight = 1;
							pos_y = 430;
						}
					}
				}
			}

			if (!position_changed && pos_y == 730 && !block) {
				if (IsKeyPressed(KEY_UP)) {
					pos_y -= 100;
					position_changed = true;
				}
				if (IsKeyPressed(KEY_SPACE)) {
					if (!show) {
						vec.clear();
						for (int j = 0; j < mass_for_me.size(); j++) {
							if (j != i) {
								vec.push_back(j);
							}
						}
					}
					show = true;
				}
			}
			if (show && !position_changed && !block) {
				if (pos_y == 730) {
					if (IsKeyPressed(KEY_DOWN)) {
						pos_y += 80;
						position_changed = true;
					}
					if (IsKeyPressed(KEY_UP)) {
						pos_y -= 80;
						position_changed = true;
					}
				}
				else if (pos_y == 810) {
					if (IsKeyPressed(KEY_DOWN)) {
						pos_y += 80;
						position_changed = true;
					}
					if (IsKeyPressed(KEY_UP)) {
						pos_y -= 80;
						position_changed = true;
					}
					if (player_for_fight == 1) {
						if (IsKeyPressed(KEY_SPACE) && mass_for_me[vec[0]].health > 0) {
							int temp = i1;
							i1 = vec[0];
							vec[0] = temp;
							show = false;
							pos_y = 430;
						}
					}
					else {
						if (IsKeyPressed(KEY_SPACE) && mass_for_me[vec[0]].health > 0) {
							int temp = i2;
							i2 = vec[0];
							vec[0] = temp;
							show = false;
							pos_y = 430;
						}
					}
				}
				else if (pos_y == 890 && !block) {
					if (IsKeyPressed(KEY_UP)) {
						pos_y -= 80;
						position_changed = true;
					}
					if (player_for_fight == 1) {
						if (IsKeyPressed(KEY_SPACE) && mass_for_me[vec[1]].health > 0) {
							int temp = i1;
							i1 = vec[1];
							vec[1] = temp;
							show = false;
							pos_y = 430;
						}
					}
					else {
						if (IsKeyPressed(KEY_SPACE) && mass_for_me[vec[1]].health > 0) {
							int temp = i2;
							i2 = vec[1];
							vec[1] = temp;
							show = false;
							pos_y = 430;
						}
					}
				}
			}
			if (!position_changed && (pos_y == 810 || pos_y == 890) && show && !block) {
				if (show) {
					string messge = mass_for_me[vec[0]].name + " " + to_string(mass_for_me[vec[0]].health);
					DrawTextEx(font, messge.c_str(), Vector2{ 850, 920 }, 50, 0, BLACK);
					string messge1 = mass_for_me[vec[1]].name + " " + to_string(mass_for_me[vec[1]].health);
					DrawTextEx(font, messge1.c_str(), Vector2{ 850, 990 }, 50, 0, BLACK);
				}
			}
			if (mass_for_me[0].health == 0 && mass_for_me[1].health == 0 && mass_for_me[2].health == 0) {
				DrawTextEx(font, "Player 1 win", Vector2{ 700, 1100 }, 150, 0, BLACK);
				block = true;
			}
			else if (mass_for_enemy[0].health == 0 && mass_for_enemy[1].health == 0 && mass_for_enemy[2].health == 0) {
				DrawTextEx(font, "Player 2 win", Vector2{ 700, 1100 }, 150, 0, BLACK);
				block = true;
			}
		}
	}
}


Vector2 get_mouse_pos() {
	Vector2 pos = GetMousePosition();
	pos.x = pos.x / (float)GetScreenWidth() * 2160.0f;
	pos.y = pos.y / (float)GetScreenHeight() * 1370.0f;
	return pos;
}
