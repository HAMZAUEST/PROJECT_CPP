#include "stdafx.h"

Title::Title()
{

	mapBox->SetWorldPos(Vector2(0.0f, 240.0f));
	mapBox->scale = Vector2(app.GetWidth(), app.GetHeight());
	mapBox->isFilled = false;
	mapBox->colOnOff = false;
	mapBox->visible = false;


	name = new ObImage(L"title.png");
	name->SetParentRT(*mapBox);
	name->scale = Vector2(990.0f, 222.0f) * 0.6f;
	name->SetLocalPosY(50.0f);
	name->colOnOff = false;


	floor = new ObImage(L"floor.png");
	floor->pivot = OFFSET_T;
	floor->collider = COLLIDER::RECT;
	floor->SetParentRT(*mapBox);
	floor->scale = Vector2(app.GetWidth(), 30.0f);
	floor->SetLocalPosY(-app.GetHalfHeight() + 30.0f);


	door = new ObImage(L"door.png");
	door->collider = COLLIDER::RECT;
	door->pivot = OFFSET_B;
	door->SetParentRT(*mapBox);
	door->scale = Vector2(95.0f, 93.0f) * 0.7f;
	door->SetLocalPosY(-app.GetHalfHeight() + 30.0f);


	doorOP = new ObImage(L"doorOpen.png");
	doorOP->collider = COLLIDER::RECT;
	doorOP->pivot = OFFSET_B;
	doorOP->SetParentRT(*mapBox);
	doorOP->scale = Vector2(95.0f, 93.0f) * 0.7f;
	doorOP->SetLocalPosY(-app.GetHalfHeight() + 30.0f);
	doorOP->visible = false;
	doorOP->colOnOff = false;
}

Title::~Title()
{
	SafeDelete(mapBox);
	SafeDelete(name);
	SafeDelete(floor);
	SafeDelete(door);
	SafeDelete(doorOP);

}

void Title::Update()
{

	//if (isOpen)
	//{
	//	door->visible = false;
	//	doorOP->visible = true;
	//	doorOP->colOnOff = true;
	//}


	mapBox->Update();
	name->Update();
	floor->Update();
	door->Update();
	doorOP->Update();
}

void Title::Render()
{
	mapBox->Render();
	name->Render();
	floor->Render();
	door->Render();
	doorOP->Render();
}

void Title::openDoor()
{
	door->visible = false;
	door->colOnOff = false;
	//isOpen = true;

	doorOP->visible = true;
	doorOP->colOnOff = true;

}

void Title::stageOpen()
{
	mapBox->colOnOff = false;
	name->colOnOff = true;
	floor->colOnOff = true;
	door->colOnOff = true;
	doorOP->colOnOff = false;
}

void Title::stageClose()
{
	mapBox->colOnOff = false;
	name->colOnOff = false;
	floor->colOnOff = false;
	door->colOnOff = false;
	doorOP->colOnOff = false;

	door->visible = true;
	doorOP->visible = false;
	isOpen  = false;
}