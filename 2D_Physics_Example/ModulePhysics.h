#pragma once
#include "Module.h"
#include "Globals.h"
#include "Animation.h"
#include <vector>


#define PIXELS_PER_METER (20.0f) // if touched change METER_PER_PIXEL too
#define METER_PER_PIXEL (1.0f / PIXELS_PER_METER) // this is 1 / PIXELS_PER_METER !

#define METERS_TO_PIXELS(m) ((int) std::floor(PIXELS_PER_METER * m))
#define PIXEL_TO_METERS(p)  ((float) METER_PER_PIXEL * p)


// Class: Ball object (a simple stoopid physics object)
class PhysBall
{
public:
	// Position
	// You could also use an array/vector
	float x;
	float y;

	// Velocity
	float vx;
	float vy;

	// Acceleration
	float ax;
	float ay;

	// Force (total) applied to the ball
	float fx;
	float fy;

	// Mass
	float mass;

	// Aerodynamics stuff
	float surface; // Effective wet surface
	float cl; // Aerodynamic Lift coefficient
	float cd; // Aerodynamic Drag coefficient
	float b; // Hydrodynamic Drag coefficient

	// Coefficients of friction & restitution (for bounces)
	float coef_friction;
	float coef_restitution;

	// Shape
	float radius;

	// Has physics enabled?
	bool physics_enabled = true;

	//ID
	int id = 0;
};

// Class: Ground
class Ground : public SDL_Rect
{
public:
	float x,y,w,h; // Geometry (x,y,w,h)
	SDL_Rect pixels(); // Convert geometry to pixels to draw w/ SDL
};


// Class: Water
class Water : public Ground
{
public:
	float density; // Density of fluid
	float vx; // Velocity x
	float vy; // Velocity y
};

// Class: Air
class Air : public Ground
{
public:

};

// Class: Player
class Pplayer : public Ground
{
public:

	// Velocity
	float vx;
	float vy;

	// Acceleration
	float ax;
	float ay;

	// Force (total) applied to the ball
	float fx;
	float fy;

	// Mass
	float mass;
};

// Class: Atmosphere
class Atmosphere
{
public:
	float density; // Density of air
	float windx; // Wind x
	float windy; // Wind y
};

class ModulePhysics : public Module
{
public:
	ModulePhysics(Application* app, bool start_enabled = true);
	~ModulePhysics();

	bool Start();
	update_status PreUpdate();
	update_status PostUpdate();
	bool CleanUp();

	// Physics objects
	std::vector<PhysBall> balls{};
	Atmosphere atmosphere{};
	Water water{};
	Pplayer player_1{};
	Pplayer player_2{};
	std::vector<Ground> grounds{};
	std::vector<Ground> scene_grounds{};
	std::vector<Water> waters{};
	std::vector<Water> scene_waters{};
	std::vector<Water> debug_water{};
	std::vector<Air> airs{};

	//Gravity
	float grx = 0.0f;
	float gry = -10.0f;

	// Misc
	float dt = 1.0 / 60.0;

	//Water
	float vy, vx;

	//Animations
	SDL_Texture* texture;
	Animation* currentAnimation = nullptr;
	Animation P1_idle;
	const char* path_p1 = "Assets/player1.png";
	const char* path_p2 = NULL;
private:

	bool debug;
};

// Compute modulus of a vector
float modulus(float vx, float vy);

// Compute Aerodynamic Drag force
void compute_aerodynamic_drag(float& fx, float& fy, const PhysBall& ball, const Atmosphere& atmosphere);

// Compute Hydrodynamic Drag force
void compute_hydrodynamic_drag(float& fx, float& fy, const PhysBall& ball, const Water& water);

// Compute Hydrodynamic Buoyancy force
void compute_hydrodynamic_buoyancy(float& fx, float& fy, const PhysBall& ball, const Water& water);

// Compute Hydrodynamic Drag force
void compute_hydrodynamic_drag_player(float& fx, float& fy, const Pplayer& player, const Water& water);

// Compute Hydrodynamic Buoyancy force
void compute_hydrodynamic_buoyancy_player(float& fx, float& fy, const Pplayer& player, const Water& water);

// Integration scheme: Velocity Verlet
void integrator_velocity_verlet(PhysBall& ball, float dt);

void integrator_velocity_verlet_player(Pplayer& player, float dt);

// Detect collision with ground
bool is_colliding_with_ground(const PhysBall& ball, const Ground& ground);

bool is_colliding_with_air(const PhysBall& ball, const Air& air);

// Detect collision with player
bool is_colliding_with_player(const PhysBall& ball, const Pplayer& player);

// Detect collision with player
bool is_colliding_ground_with_player(const Pplayer& player, const Ground& ground);

bool is_colliding_water_with_player(const Pplayer& player, const Water& water);

// Detect collision with water
bool is_colliding_with_water(const PhysBall& ball, const Water& water);

bool is_colliding_with_ball(const PhysBall& ball, const PhysBall& ball_);

// Detect collision between circle and rectange
bool check_collision_circle_rectangle(float cx, float cy, float cr, float rx, float ry, float rw, float rh);

// Detect collision between circle and circle
bool check_collision_rectangle_rectangle(float r1x, float r1y, float r1w, float r1h, float r2x, float r2y, float r2w, float r2h);


