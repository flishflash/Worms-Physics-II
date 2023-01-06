#pragma once
#include "Module.h"
#include "Animation.h"
#include "ModulePlayer.h"
#include "p2DynArray.h"
#include "Globals.h"

#define BOUNCER_TIME 200

struct Bouncer
{
	Bouncer() : body(NULL), texture(NULL), hit_timer(0), fx(0)
	{}

	PhysBody* body;
	SDL_Texture* texture;
	Uint32 hit_timer;
	uint fx;
};

enum lightTypes
{
	tiny,
	medium,
	big
};

class ModuleSceneIntro;

struct Light
{
	Light() : body(NULL), texture(NULL), on(false), fx(0)
	{}

	Light(ModuleSceneIntro* physics, int x, int y, lightTypes type);

	lightTypes type;
	PhysBody* body;
	SDL_Texture* texture;
	bool on;
	uint fx;
	int x, y;
};

class ModuleSceneIntro : public Module
{
public:
	ModuleSceneIntro(Application* app, bool start_enabled = true);
	~ModuleSceneIntro();

	bool Start();
	update_status Update();
	bool CleanUp();

public:

	SDL_Texture* graphics;
	PhysBody* background;

	Bouncer bouncer1;
	Bouncer bouncer2;

	Bouncer side_bouncer1;
	Bouncer side_bouncer2;

	SDL_Texture* tex_light_tiny;
	SDL_Texture* tex_light_medium;
	SDL_Texture* tex_light_big;
	
	uint fx_light_tiny;
	uint fx_light_medium;
	uint fx_light_big;

	p2DynArray<Light> lights;

	PhysBody* player_lose;
	uint player_lose_fx;

	void ModuleSceneIntro::AddBall(float x, float y, float X, float Y, int orientation);
	void ModuleSceneIntro::AddGround(float x, float y);
	void ModuleSceneIntro::AddWater(float x, float y);
	void ModuleSceneIntro::AddAir(float x, float y);
	void ModuleSceneIntro::delay(int secs);

	bool turns;
	bool vientesito;
	bool choose_material;
	bool coef;

	// Font score index
	uint score = 000;
	float scoreFont = -1.0f;
	char scoreText[10] = { "\0" };

	uint highscore = 000;
	char GravityT[10] = { "\0" };
	char WindX[10] = { "\0" };
	char WindY[10] = { "\0" };
	char Friction[10] = { "\0" };
	char BouyancyX[10] = { "\0" };
	char BouyancyY[10] = { "\0" };
	char xp[10] = { "\0" };
	char vbx[10] = { "\0" };
	char vby[10] = { "\0" };
	char fbx[10] = { "\0" };
	char fby[10] = { "\0" };
	char fps[10] = { "\0" };

private:
	bool jump;
	int material;
	bool debug = false;
	float fgcopy;
	float fwxcopy;
	float fwycopy;
	float faxcopy;
	float faycopy;
	bool debugWater;
};
