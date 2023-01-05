#include "stdafx.h"

Map1_copy::Map1_copy()
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



	for (int i = 0; i < 3; i++)
	{
		blocks[i] = new ObImage(L"floor.png");
		blocks[i]->SetParentRT(*mapBox);
		blocks[i]->colOnOff = true;
		blocks[i]->pivot = OFFSET_T;
		blocks[i]->collider = COLLIDER::RECT;
		blocks[i]->scale.y = 30.0f;
		blocks[i]->SetLocalPosY(-app.GetHalfHeight() + 30.0f);
	}

	blocks[0]->scale.x = app.GetWidth();

	blocks[1]->SetLocalPosX(1000.0f);
	blocks[1]->scale.x = 500.0f;

	blocks[2]->scale.x = 1500.0f;


	for (int i = 3; i < 6; i++)
	{
		blocks[i] = new ObImage(L"wall.png");
		blocks[i]->SetParentRT(*mapBox);
		blocks[i]->pivot = OFFSET_T;
		blocks[i]->collider = COLLIDER::RECT;
		blocks[i]->scale.x = 50.0f;
		blocks[i]->SetLocalPosX(1250.0f);

	}

	blocks[3]->SetLocalPosY(-app.GetHalfHeight() + 80.0f);
	blocks[3]->scale.y = 180.0f;

	blocks[4]->SetLocalPosX(1300.0f);
	blocks[4]->SetLocalPosY(-app.GetHalfHeight() + 130.0f);
	blocks[4]->scale.y = 180.0f;

	blocks[5]->SetLocalPosX(1350.0f);
	blocks[5]->SetLocalPosY(-app.GetHalfHeight() + 180.0f);
	blocks[5]->scale.y = 180.0f;


	for (int i = 6; i < 8; i++)
	{
		blocks[i] = new ObImage(L"wall.png");
		blocks[i]->SetParentRT(*mapBox);
		blocks[i]->pivot = OFFSET_T;
		blocks[i]->collider = COLLIDER::RECT;

		blocks[i]->SetLocalPos(Vector2(-465.0f, app.GetHalfHeight()));
		blocks[i]->scale = Vector2(30.0f, app.GetHeight());
	}

	blocks[7]->SetLocalPosX(2600.0f);
	blocks[7]->SetLocalPosY(30.0f);
	blocks[7]->scale = Vector2(400.0f, app.GetHalfHeight());

	//-----------------------------------------------------------------------------------
	floorLF = new ObImage(L"floor.png");
	floorLF->SetParentRT(*blocks[2]);
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
	door->SetParentRT(*blocks[7]);
	door->scale = Vector2(95.0f, 93.0f) * 0.7f;

	doorOP = new ObImage(L"doorOpen.png");
	doorOP->collider = COLLIDER::RECT;
	doorOP->pivot = OFFSET_B;
	doorOP->SetParentRT(*blocks[7]);
	doorOP->scale = Vector2(95.0f, 93.0f) * 0.7f;
	doorOP->visible = false;
	doorOP->colOnOff = false;

	SOUND->AddSound("button.mp3", "button", false);
}

Map1_copy::~Map1_copy()
{
	SafeDelete(mapBox);
}

void Map1_copy::Update()
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

		if (floorLF->Intersect(blocks[5]))
		{
			floorLF->SetWorldPosX(1375.0f);

			isOnce = false;
		}
	}

	//-------------------------
	mapBox->Update();

	for (int i = 0; i < BMAX; i++)
	{
		blocks[i]->Update();
	}

	floorLF->Update();
	button->Update();
	door->Update();
	doorOP->Update();
	lift->Update();
	keyBox->Update();
	key->Update();
}

void Map1_copy::Render()
{
	mapBox->Render();

	for (int i = 0; i < BMAX; i++)
	{
		blocks[i]->Render();
	}

	floorLF->Render();
	button->Render();
	lift->Render();
	door->Render();
	doorOP->Render();
	key->Render();
	keyBox->Render();


}

void Map1_copy::Pressed()
{
	isPress = true;
	if (!isButton)
	{
		SOUND->Play("button");
		isButton = true;
	}
}

void Map1_copy::openDoor()
{
	door->colOnOff = false;
	isOpen = true;
}

void Map1_copy::stageOpen()
{
	mapBox->colOnOff = false;

	for (int i = 0; i < BMAX; i++)
	{
		blocks[i]->colOnOff = true;
	}

	floorLF->colOnOff = true;
	button->colOnOff = true;
	door->colOnOff = true;
	doorOP->colOnOff = false;
	lift->colOnOff = true;
}

void Map1_copy::stageClose()
{
	mapBox->colOnOff = false;

	for (int i = 0; i < BMAX; i++)
	{
		blocks[i]->colOnOff = false;
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