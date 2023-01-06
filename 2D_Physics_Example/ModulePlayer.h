#pragma once
#include "Module.h"
#include "Globals.h"
#include "p2Point.h"

class PhysBody;

class ModulePlayer : public Module
{
public:
	ModulePlayer(Application* app, bool start_enabled = true);
	virtual ~ModulePlayer();

	bool Start();
	update_status Update();
	bool CleanUp();
	int x;
	int y;
	int w;
	int h;

	int vida_1;
	int vida_2;

public:

};