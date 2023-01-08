#include "Globals.h"
#include "ModulePlayer.h"
#include "Application.h"
#include "ModulePhysics.h"
#include "math.h"
#include <cmath>

// TODO 1: Include Box 2 header and library

ModulePhysics::ModulePhysics(Application* app, bool start_enabled) : Module(app, start_enabled)
{
	debug = true;
	for (int i = 0; i < 5; i++) {

		P1_idle.PushBack({ 48 * (0 + i), 0, 48, 39 });
	}
	P1_idle.loop = true;
	P1_idle.speed = 0.05f;

}

// Destructor
ModulePhysics::~ModulePhysics()
{
}

bool ModulePhysics::Start()
{
	LOG("Creating Physics 2D environment");

	// Create ground
	Ground ground = Ground();
	ground.x = PIXEL_TO_METERS(467); // [m]
	ground.y = PIXEL_TO_METERS(602); // [m]
	ground.w = PIXEL_TO_METERS(90); // [m]
	ground.h = PIXEL_TO_METERS(118); // [m]

	grounds.emplace_back(ground);

	ground.x = PIXEL_TO_METERS(0); // [m]
	ground.y = PIXEL_TO_METERS(566); // [m]
	ground.w = PIXEL_TO_METERS(132); // [m]
	ground.h = PIXEL_TO_METERS(23); // [m]

	grounds.emplace_back(ground);

	ground.x = PIXEL_TO_METERS(0); // [m]
	ground.y = PIXEL_TO_METERS(355); // [m]
	ground.w = PIXEL_TO_METERS(101); // [m]
	ground.h = PIXEL_TO_METERS(21); // [m]

	grounds.emplace_back(ground);

	ground.x = PIXEL_TO_METERS(0); // [m]
	ground.y = PIXEL_TO_METERS(0); // [m]
	ground.w = PIXEL_TO_METERS(203); // [m]
	ground.h = PIXEL_TO_METERS(153); // [m]

	grounds.emplace_back(ground);

	ground.x = PIXEL_TO_METERS(203); // [m]
	ground.y = PIXEL_TO_METERS(0); // [m]
	ground.w = PIXEL_TO_METERS(198); // [m]
	ground.h = PIXEL_TO_METERS(105); // [m]

	grounds.emplace_back(ground);

	ground.x = PIXEL_TO_METERS(425); // [m]
	ground.y = PIXEL_TO_METERS(169); // [m]
	ground.w = PIXEL_TO_METERS(171); // [m]
	ground.h = PIXEL_TO_METERS(22); // [m]

	grounds.emplace_back(ground);

	ground.x = PIXEL_TO_METERS(622); // [m]
	ground.y = PIXEL_TO_METERS(0); // [m]
	ground.w = PIXEL_TO_METERS(198); // [m]
	ground.h = PIXEL_TO_METERS(157); // [m]

	grounds.emplace_back(ground);

	ground.x = PIXEL_TO_METERS(820); // [m]
	ground.y = PIXEL_TO_METERS(0); // [m]
	ground.w = PIXEL_TO_METERS(204); // [m]
	ground.h = PIXEL_TO_METERS(206); // [m]

	grounds.emplace_back(ground);

	ground.x = PIXEL_TO_METERS(150); // [m]
	ground.y = PIXEL_TO_METERS(264); // [m]
	ground.w = PIXEL_TO_METERS(102); // [m]
	ground.h = PIXEL_TO_METERS(21); // [m]

	grounds.emplace_back(ground);

	ground.x = PIXEL_TO_METERS(174); // [m]
	ground.y = PIXEL_TO_METERS(441); // [m]
	ground.w = PIXEL_TO_METERS(102); // [m]
	ground.h = PIXEL_TO_METERS(21); // [m]

	grounds.emplace_back(ground);

	ground.x = PIXEL_TO_METERS(288); // [m]
	ground.y = PIXEL_TO_METERS(509); // [m]
	ground.w = PIXEL_TO_METERS(81); // [m]
	ground.h = PIXEL_TO_METERS(21); // [m]

	grounds.emplace_back(ground);

	ground.x = PIXEL_TO_METERS(369); // [m]
	ground.y = PIXEL_TO_METERS(509); // [m]
	ground.w = PIXEL_TO_METERS(21); // [m]
	ground.h = PIXEL_TO_METERS(33); // [m]

	grounds.emplace_back(ground);

	ground.x = PIXEL_TO_METERS(653); // [m]
	ground.y = PIXEL_TO_METERS(475); // [m]
	ground.w = PIXEL_TO_METERS(21); // [m]
	ground.h = PIXEL_TO_METERS(30); // [m]

	grounds.emplace_back(ground);

	ground.x = PIXEL_TO_METERS(674); // [m]
	ground.y = PIXEL_TO_METERS(475); // [m]
	ground.w = PIXEL_TO_METERS(81); // [m]
	ground.h = PIXEL_TO_METERS(21); // [m]

	grounds.emplace_back(ground);

	ground.x = PIXEL_TO_METERS(707); // [m]
	ground.y = PIXEL_TO_METERS(324); // [m]
	ground.w = PIXEL_TO_METERS(102); // [m]
	ground.h = PIXEL_TO_METERS(21); // [m]

	grounds.emplace_back(ground);

	ground.x = PIXEL_TO_METERS(831); // [m]
	ground.y = PIXEL_TO_METERS(438); // [m]
	ground.w = PIXEL_TO_METERS(194); // [m]
	ground.h = PIXEL_TO_METERS(23); // [m]

	grounds.emplace_back(ground);

	ground.x = PIXEL_TO_METERS(0); // [m]
	ground.y = PIXEL_TO_METERS(151); // [m]
	ground.w = PIXEL_TO_METERS(65); // [m]
	ground.h = PIXEL_TO_METERS(110); // [m]
	ground.ID = 1;

	grounds.emplace_back(ground);

	ground.x = PIXEL_TO_METERS(0); // [m]
	ground.y = PIXEL_TO_METERS(589); // [m]
	ground.w = PIXEL_TO_METERS(65); // [m]
	ground.h = PIXEL_TO_METERS(110); // [m]
	ground.ID = 1;

	grounds.emplace_back(ground);

	ground.x = PIXEL_TO_METERS(955); // [m]
	ground.y = PIXEL_TO_METERS(209); // [m]
	ground.w = PIXEL_TO_METERS(65); // [m]
	ground.h = PIXEL_TO_METERS(110); // [m]
	ground.ID = 2;

	grounds.emplace_back(ground);

	ground.x = PIXEL_TO_METERS(955); // [m]
	ground.y = PIXEL_TO_METERS(462); // [m]
	ground.w = PIXEL_TO_METERS(65); // [m]
	ground.h = PIXEL_TO_METERS(110); // [m]
	ground.ID = 2;

	grounds.emplace_back(ground);


	// Create player_1
	player_1 = Pplayer();
	player_1.x = PIXEL_TO_METERS(256); // [m]
	player_1.y = 10.0f; // [m]
	player_1.w = PIXEL_TO_METERS(18); // [m]
	player_1.h = PIXEL_TO_METERS(32); // [m]
	player_1.mass = 20.0f;


	// Create player_2
	player_2 = Pplayer();
	player_2.x = PIXEL_TO_METERS(788); // [m]
	player_2.y = 10.0f; // [m]
	player_2.w = PIXEL_TO_METERS(18); // [m]
	player_2.h = PIXEL_TO_METERS(32); // [m]
	player_2.mass = 20.0f;

	// Create atmosphere
	atmosphere = Atmosphere();
	atmosphere.windx = -10.0f; // [m/s]
	atmosphere.windy = 10.0f; // [m/s]
	atmosphere.density = 1.0f; // [kg/m^3]

	//Init water
	vy = 1.0f;
	vx = 0.0f;

	water = Water();
	water.x = PIXEL_TO_METERS(400); // Start where ground ends [m]
	water.y = PIXEL_TO_METERS(0); // [m]
	water.w = PIXEL_TO_METERS(222); // [m]
	water.h = PIXEL_TO_METERS(63); // [m]
	water.density = 50.0f; // [kg/m^3]
	water.vx = vx; // [m/s]
	water.vy = vy; // [m/s]

	App->physics->waters.emplace_back(water);

	//Textures
	bola = App->textures->Load("Assets/Bola.png");
	aire = App->textures->Load("Assets/Aire.png");
	agua = App->textures->Load("Assets/Agua.png");
	tierra = App->textures->Load("Assets/Tierra.png");
	green = App->textures->Load("Assets/Green.png");
	red = App->textures->Load("Assets/Red.png");


	return true;
}

update_status ModulePhysics::PreUpdate()
{
	//Delta Time
	dt = 1.0 / FPS;


	//// Create water
	//water = Water();
	//water.density = 50.0f; // [kg/m^3]
	//water.vx = vx; // [m/s]
	//water.vy = vy; // [m/s]


	// Process all balls in the scenario
	for (auto& ball : balls)
	{

		if (ball.vx == 0 && ball.vy == 0) { balls.clear(); }

		// Skip ball if physics not enabled
		if (!ball.physics_enabled)
		{
			continue;
		}

		// Step #0: Clear old values
		// ----------------------------------------------------------------------------------------

		// Reset total acceleration and total accumulated force of the ball
		ball.fx = ball.fy = 0.0f;
		ball.ax = ball.ay = 0.0f;

		// Step #1: Compute forces
		// ----------------------------------------------------------------------------------------

		// Gravity force
		float fgx = ball.mass * grx;
		float fgy = ball.mass * gry; // Let's assume gravity is constant and downwards
		ball.fx += fgx; ball.fy += fgy; // Add this force to ball's total force


		// Aerodynamic Drag force (only when not in water)
		if (App->scene_intro->vientesito == true)
		{
			float fdx = 0.0f; float fdy = 0.0f;
			compute_aerodynamic_drag(fdx, fdy, ball, atmosphere);
			ball.fx += fdx; ball.fy += fdy; // Add this force to ball's total force
		}

		for (auto& water : debug_water)
		{
			// Hydrodynamic forces (only when in water)
			if (is_colliding_with_water(ball, water))
			{

				// Hydrodynamic Drag force
				float fhdx = 0.0f; float fhdy = 0.0f;
				compute_hydrodynamic_drag(fhdx, fhdy, ball, water);
				ball.fx += fhdx; ball.fy += fhdy; // Add this force to ball's total force

				// Hydrodynamic Buoyancy force
				float fhbx = 0.0f; float fhby = 0.0f;
				compute_hydrodynamic_buoyancy(fhbx, fhby, ball, water);
				ball.fx += fhbx; ball.fy += fhby; // Add this force to ball's total force
			}
		}

		for (auto& water : waters)
		{
			// Hydrodynamic forces (only when in water)
			if (is_colliding_with_water(ball, water))
			{

				// Hydrodynamic Drag force
				float fhdx = 0.0f; float fhdy = 0.0f;
				compute_hydrodynamic_drag(fhdx, fhdy, ball, water);
				ball.fx += fhdx; ball.fy += fhdy; // Add this force to ball's total force

				// Hydrodynamic Buoyancy force
				float fhbx = 0.0f; float fhby = 0.0f;
				compute_hydrodynamic_buoyancy(fhbx, fhby, ball, water);
				ball.fx += fhbx; ball.fy += fhby; // Add this force to ball's total force
			}
		}

		for (auto& water : scene_waters)
		{
			// Hydrodynamic forces (only when in water)
			if (is_colliding_with_water(ball, water))
			{

				// Hydrodynamic Drag force
				float fhdx = 0.0f; float fhdy = 0.0f;
				compute_hydrodynamic_drag(fhdx, fhdy, ball, water);
				ball.fx += fhdx; ball.fy += fhdy; // Add this force to ball's total force

				// Hydrodynamic Buoyancy force
				float fhbx = 0.0f; float fhby = 0.0f;
				compute_hydrodynamic_buoyancy(fhbx, fhby, ball, water);
				ball.fx += fhbx; ball.fy += fhby; // Add this force to ball's total force
			}
		}

		for (auto& water : waters)
		{
			// Hydrodynamic forces (only when in water)
			if (is_colliding_with_water(ball, water))
			{

				// Hydrodynamic Drag force
				float fhdx = 0.0f; float fhdy = 0.0f;
				compute_hydrodynamic_drag(fhdx, fhdy, ball, water);
				ball.fx += fhdx; ball.fy += fhdy; // Add this force to ball's total force

				// Hydrodynamic Buoyancy force
				float fhbx = 0.0f; float fhby = 0.0f;
				compute_hydrodynamic_buoyancy(fhbx, fhby, ball, water);
				ball.fx += fhbx; ball.fy += fhby; // Add this force to ball's total force
			}
		}


		for (auto& air : airs)
		{
			if (is_colliding_with_air(ball, air))
			{
				float fdx = 0.0f; float fdy = 0.0f;
				compute_aerodynamic_drag(fdx, fdy, ball, atmosphere);
				ball.fx += fdx; ball.fy += fdy; // Add this force to ball's total force
			}
		}


		// Step #2: 2nd Newton's Law
		// ----------------------------------------------------------------------------------------

		// SUM_Forces = mass * accel --> accel = SUM_Forces / mass
		ball.ax = ball.fx / ball.mass;
		ball.ay = ball.fy / ball.mass;

		// Step #3: Integrate --> from accel to new velocity & new position
		// ----------------------------------------------------------------------------------------

		switch (integrator)
		{
			case 1:
				// We will use the 2nd order "Velocity Verlet" method for integration.
				integrator_velocity_verlet(ball, dt);
				break;
			case 2:
				// We will use the 2nd order "Velocity BackwardsEuler" method for integration.
				integrator_velocity_BackwardsEuler(ball, dt);
				break;
			case 3:
				// We will use the 2nd order "Velocity ForwardsEuler" method for integration.
				integrator_velocity_ForwardsEuler(ball, dt);
				break;
		}

		// Step #4: solve collisions
		// ----------------------------------------------------------------------------------------


		if ((is_colliding_with_player(ball, player_1) && ball.id == 1) || (is_colliding_with_player(ball, player_2) && ball.id == 0) || App->player->vida_1==0 || App->player->vida_2==0)
		{
			balls.clear();
			App->scene_intro->choose_material = false;
			if (ball.id == 1)
			{
				App->player->vida_1--;
				if (App->player->vida_1 <= 0)
				{
					App->scene_intro->pantallas = 4;
					App->renderer->camera.x = 4069;
					App->physics->airs.clear();
					App->physics->scene_grounds.clear();
					App->physics->scene_waters.clear();
					//Restart Vid
					App->player->vida_2 = 5;
					App->player->vida_1 = 5;
					//Restart Pos
					player_2.x = PIXEL_TO_METERS(788); // [m]
					player_2.y = 10.0f; // [m]
					player_1.x = PIXEL_TO_METERS(256); // [m]
					player_1.y = 10.0f; // [m]
				}
			}
			else
			{
				App->player->vida_2--;
				if (App->player->vida_2 <= 0)
				{
					App->scene_intro->pantallas = 3;
					App->renderer->camera.x = 3072;
					App->physics->airs.clear();
					App->physics->scene_grounds.clear();
					App->physics->scene_waters.clear();
					//Restart Vid
					App->player->vida_2 = 5;
					App->player->vida_1 = 5;
					//Restart Pos
					player_2.x = PIXEL_TO_METERS(788); // [m]
					player_2.y = 10.0f; // [m]
					player_1.x = PIXEL_TO_METERS(256); // [m]
					player_1.y = 10.0f; // [m]
				}
			}
		}

		for (auto& ball : bally)
		{
			for (auto& bal : balls)
			{
				if (is_colliding_with_ball(bal, ball))
				{

					// Elastic bounce with ground
					bal.vy = -bal.vy;
					bal.vx = -bal.vx;
					if (App->scene_intro->coef)
					{
						// FUYM non-elasticity
						bal.vx *= bal.coef_friction;
						bal.vy *= bal.coef_restitution;
					}
				}
			}
		}
		for (auto& ground : grounds)
		{
			if (is_colliding_with_ground(ball, ground))
			{

				if (ball.y > ground.y + ground.h)
				{
					// TP ball to ground surface
					ball.y = ground.y + ground.h + ball.radius;

					// Elastic bounce with ground
					ball.vy = -ball.vy;
					if (App->scene_intro->coef)
					{
						// FUYM non-elasticity
						ball.vx *= ball.coef_friction;
						ball.vy *= ball.coef_restitution;
					}
				}
				else if(ball.y < ground.y)
				{
					// TP ball to ground surface
					ball.y = ground.y - ball.radius;

					// Elastic bounce with ground
					ball.vy = -ball.vy;

					if (App->scene_intro->coef)
					{
						// FUYM non-elasticity
						ball.vx *= ball.coef_friction;
						ball.vy *= ball.coef_restitution;
					}

				}
				else
				{
					if (ball.x > ground.x)
					{
						// TP ball to ground right
						ball.x = ground.x + ground.w + ball.radius;
					}
					else
					{
						// TP ball to ground left
						ball.x = ground.x - ball.radius;
					}

					// Elastic bounce with ground
					ball.vx = -ball.vx;

					if (App->scene_intro->coef)
					{
						// FUYM non-elasticity
						ball.vx *= ball.coef_friction;
						ball.vy *= ball.coef_restitution;
					}
				}
			}

			
		}

		for (auto& ground : scene_grounds)
		{

			if (is_colliding_with_ground(ball, ground))
			{

				if (ball.y > ground.y + ground.h)
				{
					// TP ball to ground surface
					ball.y = ground.y + ground.h + ball.radius;

					// Elastic bounce with ground
					ball.vy = -ball.vy;
					if (App->scene_intro->coef)
					{
						// FUYM non-elasticity
						ball.vx *= ball.coef_friction;
						ball.vy *= ball.coef_restitution;
					}
				}
				else if (ball.y < ground.y)
				{
					// TP ball to ground surface
					ball.y = ground.y - ball.radius;

					// Elastic bounce with ground
					ball.vy = -ball.vy;

					if (App->scene_intro->coef)
					{
						// FUYM non-elasticity
						ball.vx *= ball.coef_friction;
						ball.vy *= ball.coef_restitution;
					}

				}
				else
				{
					if (ball.x > ground.x)
					{
						// TP ball to ground right
						ball.x = ground.x + ground.w + ball.radius;
					}
					else
					{
						// TP ball to ground left
						ball.x = ground.x - ball.radius;
					}

					// Elastic bounce with ground
					ball.vx = -ball.vx;

					if (App->scene_intro->coef)
					{
						// FUYM non-elasticity
						ball.vx *= ball.coef_friction;
						ball.vy *= ball.coef_restitution;
					}
				}
			}
		}
		if (ball.vx >= 30)
		{
			ball.vx = 30;
		}
		if (ball.vy >= 30)
		{
			ball.vy = 30;
		}
		if (ball.vx <= -30)
		{
			ball.vx = -30;
		}
		if (ball.vy <= -30)
		{
			ball.vy = -30;
		}

		bvx = ball.vx;
		bvy = ball.vy;
		bfx = ball.fx;
		bfy = ball.fy;
	}
	// Continue game
	return UPDATE_CONTINUE;
}

update_status ModulePhysics::PostUpdate()
{
	if (App->scene_intro->debug)
	{
		// Colors
		int color_r, color_g, color_b;
		for (auto& ground : grounds)
		{
			// Draw ground
			if (ground.ID == 0)
			{
				color_r = 0; color_g = 255; color_b = 0;
				App->renderer->DrawQuad(ground.pixels(), color_r, color_g, color_b, 80);
			}
			else
			{
				color_r = 115; color_g = 61; color_b = 86;
				App->renderer->DrawQuad(ground.pixels(), color_r, color_g, color_b, 80);
			}
		}
		for (auto& ground : scene_grounds)
		{
			// Draw scene_ground
			color_r = 0; color_g = 255; color_b = 0;
			App->renderer->DrawQuad(ground.pixels(), color_r, color_g, color_b, 80);
		}
		for (auto& ball : bally)
		{
			// Draw scene_ground
			color_r = 0; color_g = 255; color_b = 0;
			// Convert from physical magnitudes to geometrical pixels
			int pos_x = METERS_TO_PIXELS(ball.x);
			int pos_y = SCREEN_HEIGHT - METERS_TO_PIXELS(ball.y);
			int size_r = METERS_TO_PIXELS(ball.radius);
			// Draw ball
			App->renderer->DrawCircle(pos_x, pos_y, size_r, color_r, color_g, color_b, 80);
		}

		// Draw player_1
		color_r = 255; color_g = 0; color_b = 0;
		App->renderer->DrawQuad(player_1.pixels(), color_r, color_g, color_b, 80);
		currentAnimation = &P1_idle;

		// Draw player_2
		color_r = 200; color_g = 70; color_b = 150;
		App->renderer->DrawQuad(player_2.pixels(), color_r, color_g, color_b, 80);

		for (auto& water : waters)
		{
			// Draw water
			color_r = 0; color_g = 0; color_b = 255;
			App->renderer->DrawQuad(water.pixels(), color_r, color_g, color_b, 80);
		}
		for (auto& water : scene_waters)
		{
			// Draw scene_water
			color_r = 0; color_g = 0; color_b = 255;
			App->renderer->DrawQuad(water.pixels(), color_r, color_g, color_b, 80);
		}

		for (auto& water : debug_water)
		{
			// Draw water
			color_r = 0; color_g = 0; color_b = 255;
			App->renderer->DrawQuad(water.pixels(), color_r, color_g, color_b, 90);
		}

		for (auto& air : airs)
		{
			// Draw water
			color_r = 0; color_g = 120; color_b = 200;
			App->renderer->DrawQuad(air.pixels(), color_r, color_g, color_b, 80);
		}

		// Draw all balls in the scenario
		for (auto& ball : balls)
		{
			// Convert from physical magnitudes to geometrical pixels
			int pos_x = METERS_TO_PIXELS(ball.x);
			int pos_y = SCREEN_HEIGHT - METERS_TO_PIXELS(ball.y);
			int size_r = METERS_TO_PIXELS(ball.radius);

			// Select color
			if (ball.physics_enabled)
			{
				if (ball.id == 0)
				{
					color_r = 150; color_g = 255; color_b = 150;
				}
				else {
					color_r = 200; color_g = 70; color_b = 150;
				}
			}
			else
			{
				color_r = 255; color_g = 0; color_b = 0;
			}

			// Draw ball
			App->renderer->DrawCircle(pos_x, pos_y, size_r, color_r, color_g, color_b);
		}
	}
		for (auto& ball : balls)
		{
			// Convert from physical magnitudes to geometrical pixels
			int pos_x = METERS_TO_PIXELS((ball.x - ball.radius));
			int pos_y = SCREEN_HEIGHT - METERS_TO_PIXELS((ball.y + ball.radius));

			// Draw ball
			App->renderer->Blit(bola, pos_x, pos_y);
		}
		for (auto& air : airs)
		{
			int pos_x = METERS_TO_PIXELS(air.x);
			int pos_y = SCREEN_HEIGHT - METERS_TO_PIXELS((air.y + air.h));
			// Draw water
			App->renderer->Blit(aire, pos_x, pos_y);
		}
		for (auto& water : scene_waters)
		{
			int pos_x = METERS_TO_PIXELS(water.x);
			int pos_y = SCREEN_HEIGHT - METERS_TO_PIXELS((water.y + water.h));
			// Draw water
			App->renderer->Blit(agua, pos_x, pos_y);
		}
		for (auto& ground : scene_grounds)
		{
			int pos_x = METERS_TO_PIXELS(ground.x);
			int pos_y = SCREEN_HEIGHT - METERS_TO_PIXELS((ground.y + ground.h));
			// Draw water
			App->renderer->Blit(tierra, pos_x, pos_y);
		}

		//Draw Player_1
		int pos_x_1 = METERS_TO_PIXELS(player_1.x);
		int pos_y_1 = SCREEN_HEIGHT - METERS_TO_PIXELS((player_1.y + player_1.h));
		App->renderer->Blit(green, pos_x_1, pos_y_1, NULL, 1.0f, NULL, NULL, NULL, App->scene_intro->flip_1);

		//Draw Player_2
		int pos_x_2 = METERS_TO_PIXELS(player_2.x);
		int pos_y_2 = SCREEN_HEIGHT - METERS_TO_PIXELS((player_2.y + player_2.h));
		App->renderer->Blit(red, pos_x_2, pos_y_2, NULL, 1.0f, NULL, NULL, NULL, App->scene_intro->flip_2);

	return UPDATE_CONTINUE;
}

// Called before quitting
bool ModulePhysics::CleanUp()
{
	return true;
}

// Compute modulus of a vector
float modulus(float vx, float vy)
{
	return std::sqrt(vx * vx + vy * vy);
}

// Compute Aerodynamic Drag force
void compute_aerodynamic_drag(float &fx, float& fy, const PhysBall &ball, const Atmosphere &atmosphere)
{
	float rel_vel[2] = { ball.vx - atmosphere.windx, ball.vy - atmosphere.windy }; // Relative velocity
	float speed = modulus(rel_vel[0], rel_vel[1]); // Modulus of the relative velocity
	float rel_vel_unitary[2] = { rel_vel[0] / speed, rel_vel[1] / speed }; // Unitary vector of relative velocity
	float fdrag_modulus = 0.5f * atmosphere.density * speed * speed * ball.surface * ball.cd; // Drag force (modulus)
	fx = -rel_vel_unitary[0] * fdrag_modulus; // Drag is antiparallel to relative velocity
	fy = -rel_vel_unitary[1] * fdrag_modulus; // Drag is antiparallel to relative velocity
}

// Compute Aerodynamic Lift force
void compute_aerodynamic_lift(float& fx, float& fy, const PhysBall& ball, const Atmosphere& atmosphere)
{
	float rel_vel[2] = { ball.vx - atmosphere.windx, ball.vy - atmosphere.windy }; // Relative velocity
	float speed = modulus(rel_vel[0], rel_vel[1]); // Modulus of the relative velocity
	float rel_vel_unitary[2] = { rel_vel[0] / speed, rel_vel[1] / speed }; // Unitary vector of relative velocity
	float flift_modulus = 0.5f * atmosphere.density * speed * speed * ball.surface * ball.cl; // Drag force (modulus)
	fx = -rel_vel_unitary[0] * flift_modulus; // Drag is antiparallel to relative velocity
	fy = -rel_vel_unitary[1] * flift_modulus; // Drag is antiparallel to relative velocity
}

// Compute Hydrodynamic Drag force
void compute_hydrodynamic_drag(float& fx, float& fy, const PhysBall& ball, const Water& water)
{
	float rel_vel[2] = { ball.vx - water.vx, ball.vy - water.vy }; // Relative velocity
	float speed = modulus(rel_vel[0], rel_vel[1]); // Modulus of the relative velocity
	float rel_vel_unitary[2] = { rel_vel[0] / speed, rel_vel[1] / speed }; // Unitary vector of relative velocity
	float fdrag_modulus = ball.b * speed; // Drag force (modulus)
	fx = -rel_vel_unitary[0] * fdrag_modulus; // Drag is antiparallel to relative velocity
	fy = -rel_vel_unitary[1] * fdrag_modulus; // Drag is antiparallel to relative velocity
}

// Compute Hydrodynamic Buoyancy force
void compute_hydrodynamic_buoyancy(float& fx, float& fy, const PhysBall& ball, const Water& water)
{
	// Compute submerged area (assume ball is a rectangle, for simplicity)
	float water_top_level = water.y + water.h; // Water top level y
	float h = 2.0f * ball.radius; // Ball "hitbox" height
	float surf = h * (water_top_level - ball.y); // Submerged surface
	if ((ball.y + ball.radius) < water_top_level) surf = 1.0f; // If ball completely submerged, use just all ball area
	surf *= 0.4; // FUYM to adjust values (should compute the area of circle segment correctly instead; I'm too lazy for that)

	// Compute Buoyancy force
	double fbuoyancy_modulus = water.density * 10.0 * surf; // Buoyancy force (modulus)
	fx = 0.0; // Buoyancy is parallel to pressure gradient
	fy = fbuoyancy_modulus; // Buoyancy is parallel to pressure gradient
}

// Compute Hydrodynamic Drag force
void compute_hydrodynamic_drag_player(float& fx, float& fy, const Pplayer& player, const Water& water)
{
	float rel_vel[2] = { 0, player.vy - water.vy }; // Relative velocity
	float speed = modulus(rel_vel[0], rel_vel[1]); // Modulus of the relative velocity
	float rel_vel_unitary[2] = { rel_vel[0] / speed, rel_vel[1] / speed }; // Unitary vector of relative velocity
	float fdrag_modulus = 50.0f * speed; // Drag force (modulus)
	fx = -rel_vel_unitary[0] * fdrag_modulus; // Drag is antiparallel to relative velocity
	fy = -rel_vel_unitary[1] * fdrag_modulus; // Drag is antiparallel to relative velocity
}

// Compute Hydrodynamic Buoyancy force
void compute_hydrodynamic_buoyancy_player(float& fx, float& fy, const Pplayer& player, const Water& water)
{
	// Compute submerged area (assume ball is a rectangle, for simplicity)
	float water_top_level = water.y + water.h; // Water top level y
	float h = player.h; // Ball "hitbox" height
	float surf = h * (water_top_level - player.y); // Submerged surface
	if ((player.y + player.h) < water_top_level) surf = h * h; // If ball completely submerged, use just all ball area
	surf *= 0.4; // FUYM to adjust values (should compute the area of circle segment correctly instead; I'm too lazy for that)

	// Compute Buoyancy force
	double fbuoyancy_modulus = water.density * 10.0 * surf; // Buoyancy force (modulus)
	fx = 0.0; // Buoyancy is parallel to pressure gradient
	fy = fbuoyancy_modulus; // Buoyancy is parallel to pressure gradient
}

// Integration scheme: Velocity Verlet
void integrator_velocity_verlet(PhysBall& ball, float dt)
{
	ball.x += ball.vx * dt + 0.5f * ball.ax * dt * dt;
	ball.y += ball.vy * dt + 0.5f * ball.ay * dt * dt;
	ball.vx += ball.ax * dt;
	ball.vy += ball.ay * dt;
}

// Integration scheme: Velocity Verlet
void integrator_velocity_verlet_player(Pplayer& player, float dt)
{
	player.x += player.vx * dt + 0.5f * player.ax * dt * dt;
	player.y += player.vy * dt + 0.5f * player.ay * dt * dt;
	player.vx += player.ax * dt;
	player.vy += player.ay * dt;
}

// Integration scheme: Velocity Backwards Euler
void integrator_velocity_BackwardsEuler(PhysBall& ball, float dt)
{
	ball.x += ball.vx * dt;
	ball.y += ball.vy * dt;
	ball.vx += ball.ax * dt;
	ball.vy += ball.ay * dt;
}

// Integration scheme: Velocity Backwards Euler
void integrator_velocity_BackwardsEuler_player(Pplayer& player, float dt)
{
	player.x += player.vx * dt;
	player.y += player.vy * dt;
	player.vx += player.ax * dt;
	player.vy += player.ay * dt;
}

// Integration scheme: Velocity Forwards Euler
void integrator_velocity_ForwardsEuler(PhysBall& ball, float dt)
{
	ball.vx += ball.ax * dt;
	ball.vy += ball.ay * dt;
	ball.x += ball.vx * dt;
	ball.y += ball.vy * dt;
}

// Integration scheme: Velocity Forwards Euler
void integrator_velocity_ForwardsEuler_player(Pplayer& player, float dt)
{
	player.vx += player.ax * dt;
	player.vy += player.ay * dt;
	player.x += player.vx * dt;
	player.y += player.vy * dt;
}

// Detect collision with ground
bool is_colliding_with_ground(const PhysBall& ball, const Ground& ground)
{
	float rect_x = (ground.x + ground.w / 2.0f); // Center of rectangle
	float rect_y = (ground.y + ground.h / 2.0f); // Center of rectangle
	return check_collision_circle_rectangle(ball.x, ball.y, ball.radius, rect_x, rect_y, ground.w, ground.h);
}

// Detect collision with air
bool is_colliding_with_air(const PhysBall& ball, const Air& air)
{
	float rect_x = (air.x + air.w / 2.0f); // Center of rectangle
	float rect_y = (air.y + air.h / 2.0f); // Center of rectangle
	return check_collision_circle_rectangle(ball.x, ball.y, ball.radius, rect_x, rect_y, air.w, air.h);
}

// Detect collision with player
bool is_colliding_with_player(const PhysBall& ball, const Pplayer& player)
{
	float rect_x = (player.x + player.w / 2.0f); // Center of rectangle
	float rect_y = (player.y + player.h / 2.0f); // Center of rectangle
	return check_collision_circle_rectangle(ball.x, ball.y, ball.radius, rect_x, rect_y, player.w, player.h);
}

// Detect collision with ball
bool is_colliding_with_ball(const PhysBall& ball, const PhysBall& ball_)
{
	return check_collision_circle_circle(ball.x, ball.y, ball.radius, ball_.x, ball_.y, ball_.radius);
}

// Detect collision with water
bool is_colliding_with_water(const PhysBall& ball, const Water& water)
{
	float rect_x = (water.x + water.w / 2.0f); // Center of rectangle
	float rect_y = (water.y + water.h / 2.0f); // Center of rectangle
	return check_collision_circle_rectangle(ball.x, ball.y, ball.radius, rect_x, rect_y, water.w, water.h);
}

// Detect collision with player
bool is_colliding_ground_with_player(const Pplayer& player, const Ground& ground)
{
	return check_collision_rectangle_rectangle(ground.x, ground.y, ground.w, ground.h, player.x, player.y, player.w, player.h);
}
// Detect collision with player
bool is_colliding_water_with_player(const Pplayer& player, const Water& water)
{
	return check_collision_rectangle_rectangle(water.x, water.y, water.w, water.h, player.x, player.y, player.w, player.h);
}

// Detect collision between circle and rectange
bool check_collision_circle_rectangle(float cx, float cy, float cr, float rx, float ry, float rw, float rh)
{
	// Algorithm taken from https://stackoverflow.com/a/402010

	// Distance from center of circle to center of rectangle
	float dist_x = std::abs(cx - rx);
	float dist_y = std::abs(cy - ry);

	// If circle is further than half-rectangle, not intersecting
	if (dist_x > (rw / 2.0f + cr)) { return false; }
	if (dist_y > (rh / 2.0f + cr)) { return false; }

	// If circle is closer than half-rectangle, is intersecting
	if (dist_x <= (rw / 2.0f)) { return true; }
	if (dist_y <= (rh / 2.0f)) { return true; }

	// If all of above fails, check corners
	float a = dist_x - rw / 2.0f;
	float b = dist_y - rh / 2.0f;
	float cornerDistance_sq = a * a + b * b;
	return (cornerDistance_sq <= (cr * cr));
}

bool check_collision_rectangle_rectangle(float r1x, float r1y, float r1w, float r1h, float r2x, float r2y, float r2w, float r2h)
{
	return (r2x < r1x + r1w && r2x + r2w > r1x && 
			r2y < r1y + r1h && r2y + r2h > r1y);
}

bool check_collision_circle_circle(float cx, float cy, float cr, float cx_, float cy_, float cr_)
{
	float xd = cx - cx_;
	float yd = cy - cy_;

	float sumRadius = cr + cr_;
	float sqrRadius = sumRadius * sumRadius;

	float distSqr = (xd * xd) + (yd * yd);

	if (distSqr <= sqrRadius)
	{
		return true;
	}

	return false;
}

// Convert from meters to pixels (for SDL drawing)
SDL_Rect Ground::pixels()
{
	SDL_Rect pos_px{};
	pos_px.x = METERS_TO_PIXELS(x);
	pos_px.y = SCREEN_HEIGHT - METERS_TO_PIXELS(y);
	pos_px.w = METERS_TO_PIXELS(w);
	pos_px.h = METERS_TO_PIXELS(-h); // Can I do this? LOL
	return pos_px;
}


