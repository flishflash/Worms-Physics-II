#include "Globals.h"
#include "Application.h"
#include "ModuleSceneIntro.h"
#include "ModuleFonts.h"
#include "ModulePhysics.h"
#include<ctime>


ModuleSceneIntro::ModuleSceneIntro(Application* app, bool start_enabled) : Module(app, start_enabled)
{
	graphics = NULL;
}

ModuleSceneIntro::~ModuleSceneIntro()
{}

// Load assets
bool ModuleSceneIntro::Start()
{
	LOG("Loading Intro assets");
	bool ret = true;

	App->renderer->camera.x = 1024;
	App->renderer->camera.y = 0;
	turns = true;
	jump = true;
	material = 1;
	choose_material = false;
	vientesito = false;
	coef = true;
	debugWater = false;

	//Pantallas
	texture = App->textures->Load("Assets/Worms_Map.png");
	Grupo = App->textures->Load("Assets/ElGrupo4LogoXD.png");
	Intro = App->textures->Load("Assets/Title.png");
	Player1 = App->textures->Load("Assets/GreenWins.png");
	Player2 = App->textures->Load("Assets/RedWins.png");

	//Ball Map 
	// Create a ball
	PhysBall ball_ = PhysBall();

	// Set static properties of the ball
	ball_.mass = 0.0f; // [kg]
	ball_.surface = 4.0f; // [m^2]
	ball_.radius = PIXEL_TO_METERS(60); // [m]
	ball_.cd = 0.4f; // [-]
	ball_.cl = 1.2f; // [-]
	ball_.b = 10.0f; // [...]
	ball_.coef_friction = 0.9f; // [-]
	ball_.coef_restitution = 0.8f; // [-]
	// Set initial position and velocity of the ball
	ball_.x = PIXEL_TO_METERS(512);
	ball_.y = PIXEL_TO_METERS(325);

	ball_.vx = 0.0f;
	ball_.vy = 0.0f;

	// Add ball to the collection
	App->physics->bally.emplace_back(ball_);

	fPs = App->physics->FPS;

	char lookupTable[] = { "ABCDEFGHIJKLNOPKRSTUVXYZ0123456789:- " };
	scoreFont = App->fonts->Load("Assets/ABC.png", lookupTable, 1);

	return ret;
}

// Load assets
bool ModuleSceneIntro::CleanUp()
{
	LOG("Unloading Intro scene");

	return true;
}

// Update: draw background
update_status ModuleSceneIntro::Update()
{
	App->renderer->Blit(texture, 0, 0);
	App->renderer->Blit(Grupo, -1024, 0);
	App->renderer->Blit(Intro, -2048, 0);
	App->renderer->Blit(Player1, -3072, 0);
	App->renderer->Blit(Player2, -4096, 0);

	if (App->input->GetKey(SDL_SCANCODE_F3) == KEY_DOWN) {
		debug = !debug;
		LOG("Debug");
	}
	if (debug == true) {
		//GRAVITY
		if (App->input->GetKey(SDL_SCANCODE_G) == KEY_REPEAT) {
			if (App->input->GetKey(SDL_SCANCODE_UP) == KEY_DOWN) {
				/// PRINT ///
				App->physics->gry += 0.5;
			}
			if (App->input->GetKey(SDL_SCANCODE_DOWN) == KEY_DOWN) {
				/// PRINT ///
				App->physics->gry -= 0.5;
			}
			if (App->input->GetKey(SDL_SCANCODE_0) == KEY_DOWN) {
				fgcopy = App->physics->gry;
				App->physics->gry = 0;
			}
			if (App->input->GetKey(SDL_SCANCODE_R) == KEY_DOWN && App->physics->gry == 0) {
				App->physics->gry = fgcopy;
			}
		}
		//WIND
		if (App->input->GetKey(SDL_SCANCODE_W) == KEY_REPEAT)
		{
			if (App->input->GetKey(SDL_SCANCODE_UP) == KEY_DOWN) {
				/// PRINT ///
				App->physics->atmosphere.windy += 0.5f;
			}
			if (App->input->GetKey(SDL_SCANCODE_DOWN) == KEY_DOWN) {
				/// PRINT ///
				App->physics->atmosphere.windy -= 0.5f;
			}
			if (App->input->GetKey(SDL_SCANCODE_RIGHT) == KEY_DOWN) {
				/// PRINT ///
				App->physics->atmosphere.windx += 0.5f;
			}
			if (App->input->GetKey(SDL_SCANCODE_LEFT) == KEY_DOWN) {
				/// PRINT ///
				App->physics->atmosphere.windx -= 0.5f;
			}
			if (App->input->GetKey(SDL_SCANCODE_0) == KEY_DOWN) {
				fwxcopy = App->physics->atmosphere.windx;
				fwycopy = App->physics->atmosphere.windy;
				App->physics->atmosphere.windy = 0;
				App->physics->atmosphere.windx = 0;
			}
			if (App->input->GetKey(SDL_SCANCODE_R) == KEY_DOWN) {
				if (App->physics->atmosphere.windy == 0) {
					App->physics->atmosphere.windy = fwycopy;
				}
				if (App->physics->atmosphere.windx == 0) {
					App->physics->atmosphere.windx = fwxcopy;
				}
			}
			if (App->input->GetKey(SDL_SCANCODE_V) == KEY_DOWN)
			{
				vientesito = !vientesito;
			}

		}
		//WATER
		if (App->input->GetKey(SDL_SCANCODE_B) == KEY_REPEAT)
		{
			if (App->input->GetKey(SDL_SCANCODE_UP) == KEY_DOWN) {
				/// PRINT ///
				App->physics->vy += 0.5f;
			}
			if (App->input->GetKey(SDL_SCANCODE_DOWN) == KEY_DOWN) {
				/// PRINT ///
				App->physics->vy -= 0.5f;
			}
			if (App->input->GetKey(SDL_SCANCODE_RIGHT) == KEY_DOWN) {
				/// PRINT ///
				App->physics->vx += 0.5f;
			}
			if (App->input->GetKey(SDL_SCANCODE_LEFT) == KEY_DOWN) {
				/// PRINT ///
				App->physics->vx -= 0.5f;
			}
			if (App->input->GetKey(SDL_SCANCODE_0) == KEY_DOWN) {
				faxcopy = App->physics->vx;
				faycopy = App->physics->vy;
				App->physics->vx = 0;
				App->physics->vy = 0;
			}
			if (App->input->GetKey(SDL_SCANCODE_R) == KEY_DOWN) {
				if (App->physics->vy == 0) {
					App->physics->vy = faycopy;
				}
				if (App->physics->vx == 0) {
					App->physics->vx = faxcopy;
				}
			}
			if (App->input->GetKey(SDL_SCANCODE_A) == KEY_DOWN)
			{
				debugWater = !debugWater;
			}
			if (debugWater)
			{
				App->physics->debug_water.clear();

				App->physics->water.x = 0; // Start where ground ends [m]
				App->physics->water.y = 0; // [m]
				App->physics->water.w = PIXEL_TO_METERS(SCREEN_WIDTH); // [m]
				App->physics->water.h = PIXEL_TO_METERS(SCREEN_HEIGHT/2); // [m]

				App->physics->debug_water.emplace_back(App->physics->water);
			}
			if (!App->physics->debug_water.empty() && !debugWater)
			{
				App->physics->debug_water.clear();
			}
		}
		if (App->input->GetKey(SDL_SCANCODE_C) == KEY_DOWN)
		{
			coef = !coef;
		}if (App->input->GetKey(SDL_SCANCODE_F) == KEY_REPEAT)
		{
			if (App->input->GetKey(SDL_SCANCODE_UP) == KEY_DOWN) {
				/// PRINT ///
				App->physics->FPS -= 10.0f;
				fPs += 10.0f;
			}
			if (App->input->GetKey(SDL_SCANCODE_DOWN) == KEY_DOWN) {
				/// PRINT ///
				App->physics->FPS += 10.0f;
				fPs -= 10.0f;
			}
		}if (App->input->GetKey(SDL_SCANCODE_I) == KEY_REPEAT)
		{
			if (App->input->GetKey(SDL_SCANCODE_1) == KEY_DOWN) {
				
				App->physics->integrator = 1;
			}
			if (App->input->GetKey(SDL_SCANCODE_2) == KEY_DOWN) {
				
				App->physics->integrator = 2;
			}
			if (App->input->GetKey(SDL_SCANCODE_3) == KEY_DOWN) {
				
				App->physics->integrator = 3;
			}
		}
	}
	switch (turns)
	{
	case true:
		if (choose_material == false)
		{
			if (App->input->GetKey(SDL_SCANCODE_1) == KEY_UP) material = 1;
			if (App->input->GetKey(SDL_SCANCODE_2) == KEY_UP) material = 2;
			if (App->input->GetKey(SDL_SCANCODE_3) == KEY_UP) material = 3;

			switch (material)
			{
			case 1:
				//ground
				App->renderer->DrawQuad({ App->input->GetMouseX() - 10, App->input->GetMouseY() - 10, 20, 20 }, 0, 255, 0, 50);
				if (App->input->GetMouseButtonDown(SDL_BUTTON_RIGHT) == KEY_UP)
				{
					AddGround(PIXEL_TO_METERS((App->input->GetMouseX() - 10)), 36 - PIXEL_TO_METERS((App->input->GetMouseY() + 10)));
					choose_material = true;
				}
				break;
			case 2:
				//water
				App->renderer->DrawQuad({ App->input->GetMouseX() - 20, App->input->GetMouseY() - 20, 40, 40 }, 0, 0, 255, 80);
				if (App->input->GetMouseButtonDown(SDL_BUTTON_RIGHT) == KEY_UP)
				{
					AddWater(PIXEL_TO_METERS((App->input->GetMouseX() - 10)), 36 - PIXEL_TO_METERS((App->input->GetMouseY() + 10)));
					choose_material = true;
				}
				break;
			case 3:
				//air
				App->renderer->DrawQuad({ App->input->GetMouseX() - 20, App->input->GetMouseY() - 20, 40, 40 }, 0, 120, 200, 100);
				if (App->input->GetMouseButtonDown(SDL_BUTTON_RIGHT) == KEY_UP)
				{
					AddAir(PIXEL_TO_METERS((App->input->GetMouseX() - 10)), 36 - PIXEL_TO_METERS((App->input->GetMouseY() + 10)));
					choose_material = true;
				}
				break;
			}
		}

		if (choose_material == true)
		{
			if (App->input->GetKey(SDL_SCANCODE_A) == KEY_REPEAT)
			{
				App->physics->player_1.x -= 0.05f;
			}
			if (App->input->GetKey(SDL_SCANCODE_SPACE) == KEY_DOWN && jump == true)
			{
				App->physics->player_1.y += 1.0f;
				jump = false;
				AddGround(App->physics->player_1.x, App->physics->player_1.y - 1.0f);
			}
			if (App->input->GetKey(SDL_SCANCODE_D) == KEY_REPEAT)
			{
				App->physics->player_1.x += 0.05f;
			}
			if (App->input->GetMouseButtonDown(SDL_BUTTON_LEFT) == KEY_UP)
			{
				AddBall((App->physics->player_1.x + App->physics->player_1.w), App->physics->player_1.h + App->physics->player_1.y, App->input->GetMouseX(), App->input->GetMouseY(), 0);
				turns = !turns; choose_material = false;
			}
		}
		break;

	case false:

		if (choose_material == false)
		{
			if (App->input->GetKey(SDL_SCANCODE_1) == KEY_UP) material = 1;
			if (App->input->GetKey(SDL_SCANCODE_2) == KEY_UP) material = 2;
			if (App->input->GetKey(SDL_SCANCODE_3) == KEY_UP) material = 3;

			switch (material)
			{
			case 1:
				//ground
				App->renderer->DrawQuad({ App->input->GetMouseX() - 10, App->input->GetMouseY() - 10, 20, 20 }, 0, 255, 0, 50);
				if (App->input->GetMouseButtonDown(SDL_BUTTON_RIGHT) == KEY_UP)
				{
					AddGround(PIXEL_TO_METERS((App->input->GetMouseX() - 10)), 36 - PIXEL_TO_METERS((App->input->GetMouseY() + 10)));
					choose_material = true;
				}
				break;
			case 2:
				//water
				App->renderer->DrawQuad({ App->input->GetMouseX() - 20, App->input->GetMouseY() - 20, 40, 40 }, 0, 0, 255, 80);
				if (App->input->GetMouseButtonDown(SDL_BUTTON_RIGHT) == KEY_UP)
				{
					AddWater(PIXEL_TO_METERS((App->input->GetMouseX() - 10)), 36 - PIXEL_TO_METERS((App->input->GetMouseY() + 10)));
					choose_material = true;
				}
				break;
			case 3:
				//air
				App->renderer->DrawQuad({ App->input->GetMouseX() - 20, App->input->GetMouseY() - 20, 40, 40 }, 0, 120, 200, 100);
				if (App->input->GetMouseButtonDown(SDL_BUTTON_RIGHT) == KEY_UP)
				{
					AddAir(PIXEL_TO_METERS((App->input->GetMouseX() - 10)), 36 - PIXEL_TO_METERS((App->input->GetMouseY() + 10)));
					choose_material = true;
				}
				break;
			}
		}
		else {
			if (App->input->GetKey(SDL_SCANCODE_A) == KEY_REPEAT)
			{
				App->physics->player_2.x -= 0.05f;
			}
			if (App->input->GetKey(SDL_SCANCODE_SPACE) == KEY_DOWN && jump == false)
			{
				App->physics->player_2.y += 1.0f;
				jump = true;
				AddGround(App->physics->player_2.x, App->physics->player_2.y - 1.0f);
			}
			if (App->input->GetKey(SDL_SCANCODE_D) == KEY_REPEAT)
			{
				App->physics->player_2.x += 0.05f;
			}

			if (App->input->GetMouseButtonDown(SDL_BUTTON_LEFT) == KEY_UP)
			{
				AddBall((App->physics->player_2.x + App->physics->player_2.w), App->physics->player_2.h + App->physics->player_2.y, App->input->GetMouseX(), App->input->GetMouseY(), 1);
				turns = !turns;
				choose_material = false;
			}
			break;
		}
	}
		if (App->input->GetKey(SDL_SCANCODE_M) == KEY_UP)
		{
			App->physics->balls.clear();
			App->physics->airs.clear();
			App->physics->scene_grounds.clear();
			App->physics->scene_waters.clear();
		}
		if (App->input->GetKey(SDL_SCANCODE_F1) == KEY_UP)
		{
			turns = true;
			jump = true; choose_material = false;
		}
		if (App->input->GetKey(SDL_SCANCODE_F2) == KEY_UP)
		{
			turns = false;
			jump = false; choose_material = false;
		}
		if (App->input->GetKey(SDL_SCANCODE_F4) == KEY_UP)
		{
			//Player1 Wins
			App->player->vida_2 = 0;
			AddBall((App->physics->player_1.x + App->physics->player_1.w), App->physics->player_1.h + App->physics->player_1.y, App->input->GetMouseX(), App->input->GetMouseY(), 0);
		}
		if (App->input->GetKey(SDL_SCANCODE_F5) == KEY_UP)
		{
			//Player2 Wins
			App->player->vida_1 = 0;
			AddBall((App->physics->player_2.x + App->physics->player_2.w), App->physics->player_2.h + App->physics->player_2.y, App->input->GetMouseX(), App->input->GetMouseY(), 1);
		}

	int gry = App->physics->gry;
	int windx = App->physics->atmosphere.windx;
	int windy = App->physics->atmosphere.windy;
	int vx = App->physics->vx;
	int vy = App->physics->vy;

	sprintf_s(GravityT, 10, "%7d", gry);
	sprintf_s(WindX, 10, "%7d", windx);
	sprintf_s(WindY, 10, "%7d", windy);
	sprintf_s(Friction, 10, "%7d", coef);
	sprintf_s(BouyancyX, 10, "%7d", vx);
	sprintf_s(BouyancyY, 10, "%7d", vy);
	sprintf_s(vbx, 10, "%7d", App->physics->bvx);
	sprintf_s(vby, 10, "%7d", App->physics->bvy);
	sprintf_s(fbx, 10, "%7d", App->physics->bfx);
	sprintf_s(fby, 10, "%7d", App->physics->bfy);
	sprintf_s(fps, 10, "%7d", fPs);

	switch (pantallas)
	{
	case 0:
		break;
	case 1:
		break;
	case 2:
		App->fonts->BlitText(40, 35, scoreFont, "GRAVITY:");
		App->fonts->BlitText(40, 70, scoreFont, "WIND X:");
		App->fonts->BlitText(40, 105, scoreFont, "WIND Y:");
		App->fonts->BlitText(40, 140, scoreFont, "FRICTION:");
		App->fonts->BlitText(40, 175, scoreFont, "BOUYANCY X:");
		App->fonts->BlitText(40, 210, scoreFont, "BOUYANCY Y:");
		App->fonts->BlitText(40, 245, scoreFont, "VELOCITY BALL X:");
		App->fonts->BlitText(40, 280, scoreFont, "VELOCITY BALL Y:");
		App->fonts->BlitText(40, 315, scoreFont, "TOTAL FX BALL:");
		App->fonts->BlitText(40, 350, scoreFont, "TOTAL FY BALL:");
		App->fonts->BlitText(40, 385, scoreFont, "FPS:");

		//Datos
		App->fonts->BlitText(90, 35, scoreFont, GravityT);
		App->fonts->BlitText(90, 70, scoreFont, WindX);
		App->fonts->BlitText(90, 105, scoreFont, WindY);
		App->fonts->BlitText(90, 140, scoreFont, Friction);
		App->fonts->BlitText(90, 175, scoreFont, BouyancyX);
		App->fonts->BlitText(90, 210, scoreFont, BouyancyY);
		App->fonts->BlitText(120, 245, scoreFont, vbx);
		App->fonts->BlitText(120, 280, scoreFont, vby);
		App->fonts->BlitText(120, 315, scoreFont, fbx);
		App->fonts->BlitText(120, 350, scoreFont, fby);
		App->fonts->BlitText(90, 385, scoreFont, fps);
		break;
	case 3:
		break;
	case 4:
		break;
	}

	if (App->input->GetKey(SDL_SCANCODE_RETURN) == KEY_UP)
	{
		switch (pantallas)
		{
			case 0:
				pantallas++;
				App->renderer->camera.x = 2048;
				break;
			case 1:
				pantallas++;
				App->renderer->camera.x = 0;
				break;
			case 2:
				break;
			case 3:
				pantallas--;
				App->renderer->camera.x = 0;
				break;
			case 4:
				pantallas=2;
				App->renderer->camera.x = 0;
				break;
		}
	}

	return UPDATE_CONTINUE;
}

void ModuleSceneIntro::delay(int secs) {
	for (int i = (time(NULL) + secs); time(NULL) != i; time(NULL));
}

void ModuleSceneIntro::AddBall(float x, float y, float X, float Y, int orientation)
{
	// Create a ball
	PhysBall ball = PhysBall();

	// Set static properties of the ball
	ball.mass = 10.0f; // [kg]
	ball.surface = 1.0f; // [m^2]
	ball.radius = 0.25f; // [m]
	ball.cd = 0.4f; // [-]
	ball.cl = 1.2f; // [-]
	ball.b = 50.0f; // [...]
	ball.coef_friction = 0.9f; // [-]
	ball.coef_restitution = 0.8f; // [-]

	if (orientation == true)
	{
		ball.vx = PIXEL_TO_METERS(X)-(x);
		ball.vy = ((36 - PIXEL_TO_METERS(Y)) - (y));
		ball.id = 1;
	}
	else
	{
		ball.vx = PIXEL_TO_METERS(X)-(x);
		ball.vy = (36 - PIXEL_TO_METERS(Y)) - (y);
		ball.id = 0;
	}

	// Set initial position and velocity of the ball
	ball.x = x;
	ball.y = y;


	// Add ball to the collection
	App->physics->balls.emplace_back(ball);
}
void ModuleSceneIntro::AddGround(float x, float y)
{
	// Create a ball
	Ground ground = Ground();

	ground.x = x; // [m]
	ground.y = y; // [m]
	ground.w = 1.0f; // [m]
	ground.h = 1.0f; // [m]

	App->physics->scene_grounds.emplace_back(ground);
}
void ModuleSceneIntro::AddWater(float x, float y)
{
	App->physics->water.x = x; // Start where ground ends [m]
	App->physics->water.y = y; // [m]
	App->physics->water.w = 2.0f; // [m]
	App->physics->water.h = 2.0f; // [m]

	App->physics->scene_waters.emplace_back(App->physics->water);
}

void ModuleSceneIntro::AddAir(float x, float y)
{
	Air air = Air();
	air.x = x; // Start where ground ends [m]
	air.y = y; // [m]
	air.w = 2.0f; // [m]
	air.h = 2.0f; // [m]

	App->physics->airs.emplace_back(air);
}