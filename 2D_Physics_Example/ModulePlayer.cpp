#include "Globals.h"
#include "Application.h"
#include "ModulePlayer.h"
#include "PhysBody.h"
#include "ModulePlayer.h"
#include "Animation.h"

ModulePlayer::ModulePlayer(Application* app, bool start_enabled) : Module(app, start_enabled)
{
	
}

ModulePlayer::~ModulePlayer()
{}

// Load assets
bool ModulePlayer::Start()
{
	LOG("Loading player");
	
	vida_1 = 5;
	vida_2 = 5;

	return true;
}

// Unload assets
bool ModulePlayer::CleanUp()
{
	LOG("Unloading player");

	return true;
}

// Update: draw background
update_status ModulePlayer::Update()
{
	int x = (App->physics->player_1.x*20);
	int h = ((36-(App->physics->player_1.y + App->physics->player_1.h)) * 20);
	int x_2 = (App->physics->player_2.x * 20);
	int h_2 = ((36 - (App->physics->player_2.y + App->physics->player_2.h)) * 20);
	//Print Vidas
	for(int i=0; i<vida_1; i++)
	{
		App->renderer->DrawQuad({(x-2)+(5*i),(h-20), 5,5}, 255, 0, 0);
	}
	for (int i = 0; i < vida_2; i++)
	{
		App->renderer->DrawQuad({ (x_2 - 2) + (5 * i),(h_2 - 20), 5,5}, 255, 0, 0);
	}



	//Reset total acceleration and total accumulated force of the players
	App->physics->player_1.fx = App->physics->player_1.fy = 0.0f;
	App->physics->player_1.ax = App->physics->player_1.ay = 0.0f;
	App->physics->player_2.fx = App->physics->player_2.fy = 0.0f;
	App->physics->player_2.ax = App->physics->player_2.ay = 0.0f;

	float fgx_1 = App->physics->player_1.mass * 0.0f;
	float fgy_1 = App->physics->player_1.mass * -20.0f; // Let's assume gravity is constant and downwards
	App->physics->player_1.fx += fgx_1; App->physics->player_1.fy += fgy_1; // Add this force to ball's total force

	float fgx_2 = App->physics->player_2.mass * 0.0f;
	float fgy_2 = App->physics->player_2.mass * -20.0f; // Let's assume gravity is constant and downwards
	App->physics->player_2.fx += fgx_2; App->physics->player_2.fy += fgy_2; // Add this force to ball's total force

	// SUM_Forces = mass * accel --> accel = SUM_Forces / mass
	App->physics->player_1.ax = App->physics->player_1.fx / App->physics->player_1.mass;
	App->physics->player_1.ay = App->physics->player_1.fy / App->physics->player_1.mass;

	// SUM_Forces = mass * accel --> accel = SUM_Forces / mass
	App->physics->player_2.ax = App->physics->player_2.fx / App->physics->player_2.mass;
	App->physics->player_2.ay = App->physics->player_2.fy / App->physics->player_2.mass;

	// We will use the 2nd order "Velocity Verlet" method for integration.
	integrator_velocity_verlet_player(App->physics->player_1, App->physics->dt);
	integrator_velocity_verlet_player(App->physics->player_2, App->physics->dt);

	for (auto& ground : App->physics->grounds)
	{
		if (is_colliding_ground_with_player(App->physics->player_1, ground))
		{
			//r2y < r1y + r1h
			if (App->physics->player_1.y + App->physics->player_1.h > ground.y + ground.h)
			{
				// TP ball to ground surface
				App->physics->player_1.y = ground.y + ground.h;
				App->physics->player_1.vy = 0;
			}
			else if (App->physics->player_1.y < ground.y)
			{
				// TP ball to ground surface
				App->physics->player_1.y = ground.y - App->physics->player_1.h;
			}
			else
			{
				if (App->physics->player_1.x > ground.x)
				{
					// TP ball to ground right
					App->physics->player_1.x = ground.x + ground.w;
				}
				else
				{
					// TP ball to ground left
					App->physics->player_1.x = ground.x - App->physics->player_1.w;
				}
			}
		}

		if (is_colliding_ground_with_player(App->physics->player_2, ground))
		{
			//r2y < r1y + r1h
			if (App->physics->player_2.y + App->physics->player_2.h > ground.y + ground.h)
			{
				// TP ball to ground surface
				App->physics->player_2.y = ground.y + ground.h;
				App->physics->player_2.vy = 0;
			}
			else if (App->physics->player_2.y < ground.y)
			{
				// TP ball to ground surface
				App->physics->player_2.y = ground.y - App->physics->player_2.h;
			}
			else
			{
				if (App->physics->player_2.x > ground.x)
				{
					// TP ball to ground right
					App->physics->player_2.x = ground.x + ground.w;
				}
				else
				{
					// TP ball to ground left
					App->physics->player_2.x = ground.x - App->physics->player_2.w;
				}
			}
		}
	}


	return UPDATE_CONTINUE;
}



