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

	Mesh* RectangleMesh = new Mesh(
		{
			{ -0.5f, 0.5f, 0.0f },
			{ 0.5f, 0.5f, 0.0f },
			{ 0.5f, -0.5f, 0.0f },
			{ -0.5f, -0.5f, 0.0f }

		},
		{
			0,1,2,
			0,2,3

		});

	gfx->RegisterObject(std::make_shared<Object>("Triangle", RectangleMesh));
}

void Game::Update(float dt)
{
}
