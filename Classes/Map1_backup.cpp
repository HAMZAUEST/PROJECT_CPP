#include "stdafx.h"

Map1::Map1()
{
	mapBox->SetWorldPos(Vector2(0.0f, 240.0f));
	mapBox->scale = Vector2(app.GetWidth(), app.GetHeight());
	mapBox->isFilled = false;
	mapBox->colOnOff = false;

	keyBox->scale = Vector2(36.0f, 72.0f) * 0.5f;
	keyBox->SetWorldPos(Vector2(2100.0f, 240.0f));
	keyBox->isFilled = false;

	key->scale = Vector2(36.0f, 72.0f) * 0.5f;
	key->SetParentRT(*keyBox);
	key->collider = COLLIDER::RECT;

	for (int i = 0; i < 2; i++)
	{
		wall[i] = new ObImage(L"wall.png");
		wall[i]->SetParentRT(*mapBox);
		wall[i]->pivot = OFFSET_T;
		wall[i]->collider = COLLIDER::RECT;
		wall[i]->SetLocalPos(Vector2(-465.0f, app.GetHalfHeight()));
		wall[i]->scale = Vector2(30.0f, app.GetHeight());
	}

	for (int i = 0; i < 3; i++)
	{
		floor[i] = new ObImage(L"floor.png");
		floor[i]->SetParentRT(*mapBox);
		floor[i]->colOnOff = true;
		floor[i]->pivot = OFFSET_T;
		floor[i]->collider = COLLIDER::RECT;
		floor[i]->scale.y = 30.0f;
		floor[i]->SetLocalPosY(-app.GetHalfHeight() + 30.0f);


		stair[i] = new ObImage(L"wall.png");
		stair[i]->SetParentRT(*mapBox);
		stair[i]->pivot = OFFSET_T;
		stair[i]->collider = COLLIDER::RECT;
		stair[i]->scale.x = 50.0f;
		stair[i]->SetLocalPosX(1250.0f);
	}

	wall[1]->SetLocalPosX(2600.0f);
	wall[1]->SetLocalPosY(30.0f);
	wall[1]->scale = Vector2(400.0f, app.GetHalfHeight());

	floor[0]->scale.x = app.GetWidth();

	floor[1]->SetLocalPosX(1000.0f);
	floor[1]->scale.x = 500.0f;

	floor[2]->SetLocalPosX(2550.0f);
	floor[2]->scale.x = 1500.0f;

	stair[0]->SetLocalPosY(-app.GetHalfHeight() + 80.0f);
	stair[0]->scale.y = 180.0f;

	stair[1]->SetLocalPosX(1300.0f);
	stair[1]->SetLocalPosY(-app.GetHalfHeight() + 130.0f);
	stair[1]->scale.y = 180.0f;

	stair[2]->SetLocalPosX(1350.0f);
	stair[2]->SetLocalPosY(-app.GetHalfHeight() + 180.0f);
	stair[2]->scale.y = 180.0f;

	floorLF = new ObImage(L"floor.png");
	floorLF->SetParentRT(*floor[2]);
	floorLF->pivot = OFFSET_LT;
	floorLF->SetLocalPosX(-750.0f);
	floorLF->scale.y = 15.0f;
	floorLF->scale.x = 500.0f;
	floorLF->collider = COLLIDER::RECT;

	button = new ObRect();
	button->SetParentRT(*mapBox);
	button->scale = Vector2(15.0f, 10.0f);
	button->pivot = OFFSET_B;
	button->SetWorldPos(Vector2(1900.0f, -app.GetHalfHeight() + 30.0f));
	button->color = Color(1.0f, 0.0f, 0.0f, 1.0f);

	lift = new ObImage(L"floor.png");
	lift->SetParentRT(*mapBox);
	lift->collider = COLLIDER::RECT;
	lift->pivot = OFFSET_T;
	lift->SetLocalPos(Vector2(2300.0f, 0.0f));
	lift->color = Color(0.0f, 1.0f, 0.0f, 1.0f);
	lift->scale = Vector2(200.0f, 10.0f);

	door = new ObImage(L"door.png");
	door->collider = COLLIDER::RECT;
	door->pivot = OFFSET_B;
	door->SetParentRT(*wall[1]);
	door->scale = Vector2(95.0f, 93.0f) * 0.7f;



	doorOP = new ObImage(L"doorOpen.png");
	doorOP->collider = COLLIDER::RECT;
	doorOP->pivot = OFFSET_B;
	doorOP->SetParentRT(*wall[1]);
	doorOP->scale = Vector2(95.0f, 93.0f) * 0.7f;

	doorOP->visible = false;
	doorOP->colOnOff = false;

	SOUND->AddSound("button.mp3", "button", false);
}

Map1::~Map1()
{
	SafeDelete(mapBox);
}

void Map1::Update()
{

	if (isOpen)
	{
		door->visible = false;
		doorOP->visible = true;
		doorOP->colOnOff = true;
	}

	if (isPress && isOnce)
	{

		button->scale.y = 4.0f;

		floorLF->MoveWorldPos(LEFT * 100.0f * DELTA);

		if (floorLF->Intersect(stair[2]))
		{
			floorLF->SetWorldPosX(1375.0f);

			isOnce = false;
		}
	}

	//-------------------------
	mapBox->Update();
	for (int i = 0; i < 2; i++)
	{
		wall[i]->Update();
	}

	for (int i = 0; i < 3; i++)
	{
		floor[i]->Update();
		stair[i]->Update();
	}

	floorLF->Update();
	button->Update();
	door->Update();
	doorOP->Update();
	lift->Update();
	keyBox->Update();
	key->Update();
}

void Map1::Render()
{
	mapBox->Render();

	for (int i = 0; i < 2; i++)
	{
		wall[i]->Render();
	}

	for (int i = 0; i < 3; i++)
	{
		floor[i]->Render();
		stair[i]->Render();
	}




	floorLF->Render();
	button->Render();
	lift->Render();
	door->Render();
	doorOP->Render();
	key->Render();
	keyBox->Render();


}

void Map1::Pressed()
{
	isPress = true;
	if (!isButton)
	{
		SOUND->Play("button");
		isButton = true;
	}
}

void Map1::openDoor()
{
	door->colOnOff = false;
	isOpen = true;
}

void Map1::stageOpen()
{
	mapBox->colOnOff = false;

	for (int i = 0; i < 2; i++)
	{
		wall[i]->colOnOff = true;
	}

	for (int i = 0; i < 3; i++)
	{
		floor[i]->colOnOff = true;
		stair[i]->colOnOff = true;
	}

	floorLF->colOnOff = true;
	button->colOnOff = true;
	door->colOnOff = true;
	doorOP->colOnOff = false;
	lift->colOnOff = true;
}

void Map1::stageClose()
{
	mapBox->colOnOff = false;

	for (int i = 0; i < 2; i++)
	{
		wall[i]->colOnOff = false;
	}

	for (int i = 0; i < 3; i++)
	{
		floor[i]->colOnOff = false;
		stair[i]->colOnOff = false;
	}

	floorLF->colOnOff = false;
	button->colOnOff = false;
	door->colOnOff = false;
	doorOP->colOnOff = false;
	lift->colOnOff = false;

	door->visible = true;
	doorOP->visible = false;
	isOpen = false;

	key->SetParentRT(*keyBox);
	key->visible = true;

	floorLF->SetLocalPosX(-750.0f);

	button->scale.y = 10.0f;
	isPress = false;
	isOnce  = true;
}