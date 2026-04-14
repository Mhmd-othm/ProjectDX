#include "Game.h"
#include "Graphics.h"
#include "Mesh.h"
#include "Object.h"


Game::Game(std::shared_ptr<Graphics>& gfx) : gfx(gfx)
{
}

Game::~Game()
{
	gfx.reset();
}

void Game::BeginPlay()
{

	Mesh* triangleMesh = new Mesh({
			{ 0.0f, 0.5f, 0.0f },
			{ 0.45f, -0.5f, 0.0f },
			{ -0.45f, -0.5f, 0.0f }
		});

	gfx->RegisterObject(std::make_shared<Object>("Triangle", triangleMesh));
}

void Game::Update(float dt)
{
}
