#include "Globals.h"
#include "Animation.h"
#include "Application.h"
#include "ModulePlayer.h"
#include "PhysBody.h"

ModulePlayer::ModulePlayer(Application* app, bool start_enabled) : Module(app, start_enabled)
{
	for (int i = 0; i < 5; i++) {

		PlayerIdleRight.PushBack({ 48 * (0 + i), 0, 48, 39 });
	}
	PlayerIdleRight.loop = true;
	PlayerIdleRight.speed = 0.05f;
}

ModulePlayer::~ModulePlayer()
{}

// Load assets
bool ModulePlayer::Start()
{
	LOG("Loading player");

	texture = App->textures->Load("Assets/Gunner_Green_Idle.png");

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
	currentAnimation = &PlayerIdleRight;

	return UPDATE_CONTINUE;
}



