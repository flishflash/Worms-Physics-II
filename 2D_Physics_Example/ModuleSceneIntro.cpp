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
	if (App->input->GetKey(SDL_SCANCODE_M) == KEY_UP)
	{
		App->physics->balls.clear();
	}
	if (App->input->GetMouseButtonDown(SDL_BUTTON_LEFT) == KEY_UP)
	{
		AddBall(App->physics->player_1.x, App->physics->player_1.y + App->physics->player_1.h / 2.0f, App->input->GetMouseX(), App->input->GetMouseY());
	}
	if (App->input->GetKey(SDL_SCANCODE_R) == KEY_UP)
	{
		AddBall(1, 20, 0, 0);
	}

	return UPDATE_CONTINUE;
}

void ModuleSceneIntro::AddBall(float x, float y, float X, float Y)
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

	// Set initial position and velocity of the ball
	ball.x = x;
	ball.y = y;
	ball.vx = 20.0f;
	ball.vy = 10.0f;

	// Add ball to the collection
	App->physics->balls.emplace_back(ball);
}
