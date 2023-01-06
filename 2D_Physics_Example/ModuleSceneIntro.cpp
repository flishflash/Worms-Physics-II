#include "Globals.h"
#include "Application.h"
#include "ModuleSceneIntro.h"
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

	App->renderer->camera.x = App->renderer->camera.y = 0;
	turns = true;
	jump = true;
	material = 1;
	choose_material = false;
	vientesito = false;
	coef = true;
	debugWater = false;

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
	if (App->input->GetKey(SDL_SCANCODE_F3) == KEY_DOWN) {
		debug = true;
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
				/// PRINT ///
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
				/// PRINT ///
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
			if (App->input->GetKey(SDL_SCANCODE_W) == KEY_DOWN && jump == false)
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
	ball.radius = 0.5f; // [m]
	ball.cd = 0.4f; // [-]
	ball.cl = 1.2f; // [-]
	ball.b = 10.0f; // [...]
	ball.coef_friction = 0.9f; // [-]
	ball.coef_restitution = 0.8f; // [-]

	if (orientation == true)
	{
		ball.vx = PIXEL_TO_METERS(X)-(x);
		ball.vy = y/(PIXEL_TO_METERS(Y)/10);
		ball.id = 1;
	}
	else
	{
		ball.vx = PIXEL_TO_METERS(X)-x;
		ball.vy = y/(PIXEL_TO_METERS(Y)/30);
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

	App->physics->grounds.emplace_back(ground);
}
void ModuleSceneIntro::AddWater(float x, float y)
{
	App->physics->water.x = x; // Start where ground ends [m]
	App->physics->water.y = y; // [m]
	App->physics->water.w = 2.0f; // [m]
	App->physics->water.h = 2.0f; // [m]

	App->physics->waters.emplace_back(App->physics->water);
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