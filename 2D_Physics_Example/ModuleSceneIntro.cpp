#include "Globals.h"
#include "Application.h"
#include "ModuleSceneIntro.h"



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
	SDL_Rect rect{10,10, 10, 10};
	App->renderer->DrawQuad(rect, 255, 0, 0);
	switch (turns)
	{
		case true:
			if (App->input->GetMouseButtonDown(SDL_BUTTON_LEFT) == KEY_UP)
			{
				AddBall((App->physics->player_1.x + App->physics->player_1.w), App->physics->player_1.h + App->physics->player_1.y, App->input->GetMouseX(), App->input->GetMouseY(), 0);	
			}
		break;
		case false:
			if (App->input->GetMouseButtonDown(SDL_BUTTON_LEFT) == KEY_UP)
			{
				AddBall((App->physics->player_2.x + App->physics->player_2.w), App->physics->player_2.h + App->physics->player_2.y, App->input->GetMouseX(), App->input->GetMouseY(), 1);
			}
		break;
	}
	if (App->input->GetKey(SDL_SCANCODE_M) == KEY_UP)
	{
		App->physics->balls.clear();
	}
	if (App->input->GetKey(SDL_SCANCODE_F1) == KEY_UP)
	{
		turns = true;
	}
	if (App->input->GetKey(SDL_SCANCODE_F2) == KEY_UP)
	{
		turns = false;
	}

	return UPDATE_CONTINUE;
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
		ball.vx = PIXEL_TO_METERS(X)-(x/2);
		ball.vy = y/(PIXEL_TO_METERS(Y)/10);
	}
	else
	{
		ball.vx = PIXEL_TO_METERS(X)-x;
		ball.vy = y/(PIXEL_TO_METERS(Y)/30);
	}

	// Set initial position and velocity of the ball
	ball.x = x;
	ball.y = y;


	// Add ball to the collection
	App->physics->balls.emplace_back(ball);
}
