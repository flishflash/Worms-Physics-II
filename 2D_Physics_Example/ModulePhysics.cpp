#include "Globals.h"
#include "Application.h"
#include "ModulePhysics.h"
#include "math.h"
#include <cmath>

// TODO 1: Include Box 2 header and library

ModulePhysics::ModulePhysics(Application* app, bool start_enabled) : Module(app, start_enabled)
{
	debug = true;
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
	ground.x = 0.0f; // [m]
	ground.y = 0.0f; // [m]
	ground.w = PIXEL_TO_METERS(SCREEN_WIDTH); // [m]
	ground.h = 5.0f; // [m]

	grounds.emplace_back(ground);

	ground.x = PIXEL_TO_METERS(768); // [m]
	ground.y = 0.0f; // [m]
	ground.w = PIXEL_TO_METERS(256); // [m]
	ground.h = 10.0f; // [m]

	grounds.emplace_back(ground);

	ground.x = PIXEL_TO_METERS(768); // [m]
	ground.y = 10.0f; // [m]
	ground.w = 1.0f; // [m]
	ground.h = 3.0f; // [m]

	grounds.emplace_back(ground);

	ground.x = PIXEL_TO_METERS(768); // [m]
	ground.y = 13.0f; // [m]
	ground.w = 2.0f; // [m]
	ground.h = 1.0f; // [m]

	grounds.emplace_back(ground);

	ground.x = 0.0f; // [m]
	ground.y = 0.0f; // [m]
	ground.w = 1.0f; // [m]
	ground.h = PIXEL_TO_METERS(SCREEN_HEIGHT); // [m]

	grounds.emplace_back(ground);

	ground.x = PIXEL_TO_METERS(SCREEN_WIDTH)-1.0f; // [m]
	ground.y = 0.0f; // [m]
	ground.w = 1.0f; // [m]
	ground.h = PIXEL_TO_METERS(SCREEN_HEIGHT); // [m]

	grounds.emplace_back(ground);

	ground.x = 0.0f; // [m]
	ground.y = PIXEL_TO_METERS(SCREEN_HEIGHT)-1.0f; // [m]
	ground.w = PIXEL_TO_METERS(SCREEN_WIDTH); // [m]
	ground.h = 1.0f; // [m]

	grounds.emplace_back(ground);

	// Create player_1
	player_1 = Pplayer();
	player_1.x = PIXEL_TO_METERS(256); // [m]
	player_1.y = 5.0f; // [m]
	player_1.w = 1.0f; // [m]
	player_1.h = 2.0f; // [m]

	// Create player_2
	player_2 = Pplayer();
	player_2.x = PIXEL_TO_METERS(788); // [m]
	player_2.y = 10.0f; // [m]
	player_2.w = 1.0f; // [m]
	player_2.h = 2.0f; // [m]


	// Create Water
	//water = Water();
	//water.x = ground.x + ground.w; // Start where ground ends [m]
	//water.y = 0.0f; // [m]
	//water.w = 30.0f; // [m]
	//water.h = 5.0f; // [m]
	//water.density = 50.0f; // [kg/m^3]
	//water.vx = -1.0f; // [m/s]
	//water.vy = 0.0f; // [m/s]

	// Create atmosphere
	atmosphere = Atmosphere();
	atmosphere.windx = 10.0f; // [m/s]
	atmosphere.windy = 5.0f; // [m/s]
	atmosphere.density = 1.0f; // [kg/m^3]

	return true;
}

update_status ModulePhysics::PreUpdate()
{
	// Process all balls in the scenario

	for (auto& ball : balls)
	{

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
		float fgx = ball.mass * 0.0f;
		float fgy = ball.mass * -10.0f; // Let's assume gravity is constant and downwards
		ball.fx += fgx; ball.fy += fgy; // Add this force to ball's total force

		for (auto& water : waters)
		{

			// Aerodynamic Drag force (only when not in water)
			if (!is_colliding_with_water(ball, water))
			{
				float fdx = 0.0f; float fdy = 0.0f;
				//compute_aerodynamic_drag(fdx, fdy, ball, atmosphere);
				//ball.fx += fdx; ball.fy += fdy; // Add this force to ball's total force
			}

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
		// Other forces
		// ...

		// Step #2: 2nd Newton's Law
		// ----------------------------------------------------------------------------------------

		// SUM_Forces = mass * accel --> accel = SUM_Forces / mass
		ball.ax = ball.fx / ball.mass;
		ball.ay = ball.fy / ball.mass;

		// Step #3: Integrate --> from accel to new velocity & new position
		// ----------------------------------------------------------------------------------------

		// We will use the 2nd order "Velocity Verlet" method for integration.
		integrator_velocity_verlet(ball, dt);

		// Step #4: solve collisions
		// ----------------------------------------------------------------------------------------


		if ((is_colliding_with_player(ball, player_1) && App->scene_intro->turns == false) || (is_colliding_with_player(ball, player_2) && App->scene_intro->turns == true))
		{
			balls.clear();
			App->scene_intro->turns = !App->scene_intro->turns;
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

					// FUYM non-elasticity
					ball.vx *= ball.coef_friction;
					ball.vy *= ball.coef_restitution;
				}
				else if(ball.y < ground.y)
				{
					// TP ball to ground surface
					ball.y = ground.y - ball.radius;

					// Elastic bounce with ground
					ball.vy = -ball.vy;

					// FUYM non-elasticity
					ball.vx *= ball.coef_friction;
					ball.vy *= ball.coef_restitution;

				}else{
					if (ball.x > ground.x)
					{
						// TP ball to ground surface
						ball.x = ground.w + ball.radius;
					}
					else
					{
						// TP ball to ground surface
						ball.x = ground.x - ball.radius;
					}

					// Elastic bounce with ground
					ball.vx = -ball.vx;

					// FUYM non-elasticity
					ball.vx *= ball.coef_friction;
					ball.vy *= ball.coef_restitution;
				}
			}
		}

	}
		
	
	// Continue game
	return UPDATE_CONTINUE;
}

update_status ModulePhysics::PostUpdate()
{
	// Colors
	int color_r, color_g, color_b;
	for (auto& ground : grounds)
	{
		// Draw ground
		color_r = 0; color_g = 255; color_b = 0;
		App->renderer->DrawQuad(ground.pixels(), color_r, color_g, color_b);
	}
	
	// Draw player
	color_r = 255; color_g = 0; color_b = 0;
	App->renderer->DrawQuad(player_1.pixels(), color_r, color_g, color_b);

	// Draw player
	color_r = 255; color_g = 0; color_b = 0;
	App->renderer->DrawQuad(player_2.pixels(), color_r, color_g, color_b);

	for (auto& water : waters)
	{
		// Draw water
		color_r = 0; color_g = 0; color_b = 255;
		App->renderer->DrawQuad(water.pixels(), color_r, color_g, color_b);
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
			color_r = 255; color_g = 255; color_b = 255;
		}
		else
		{
			color_r = 255; color_g = 0; color_b = 0;
		}

		// Draw ball
		App->renderer->DrawCircle(pos_x, pos_y, size_r, color_r, color_g, color_b);
	}

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
	if ((ball.y + ball.radius) < water_top_level) surf = h * h; // If ball completely submerged, use just all ball area
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

// Detect collision with ground
bool is_colliding_with_ground(const PhysBall& ball, const Ground& ground)
{
	float rect_x = (ground.x + ground.w / 2.0f); // Center of rectangle
	float rect_y = (ground.y + ground.h / 2.0f); // Center of rectangle
	return check_collision_circle_rectangle(ball.x, ball.y, ball.radius, rect_x, rect_y, ground.w, ground.h);
}

// Detect collision with ground
bool is_colliding_with_ball(const PhysBall& ball, const PhysBall& ball_)
{
	return check_collision_circle_circle(ball.x, ball.y, ball.radius, ball_.x, ball_.y, ball_.radius);
}

// Detect collision with ground
bool is_colliding_with_player(const PhysBall& ball, const Pplayer& player)
{
	float rect_x = (player.x + player.w / 2.0f); // Center of rectangle
	float rect_y = (player.y + player.h / 2.0f); // Center of rectangle

	return check_collision_circle_rectangle(ball.x, ball.y, ball.radius, rect_x, rect_y, player.w, player.h);
}

// Detect collision with water
bool is_colliding_with_water(const PhysBall& ball, const Water& water)
{
	float rect_x = (water.x + water.w / 2.0f); // Center of rectangle
	float rect_y = (water.y + water.h / 2.0f); // Center of rectangle
	return check_collision_circle_rectangle(ball.x, ball.y, ball.radius, rect_x, rect_y, water.w, water.h);
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

bool check_collision_circle_circle(float c1x, float c1y, float c1r, float c2x, float c2y, float c2r)
{
	// Distance from center of circle to center of rectangle
	float dist_x = std::abs(c1x - c2x);
	float dist_y = std::abs(c1y - c2y);

	// If circle is further than half-rectangle, not intersecting
	if ((sqrt(dist_x * dist_x + dist_y * dist_y)) > (c1r + c2r)) { return false; }

	if ((sqrt(dist_x * dist_x + dist_y * dist_y)) <= (c1r + c2r)) { return false; }
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


