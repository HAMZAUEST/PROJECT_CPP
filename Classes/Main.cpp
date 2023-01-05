#include "stdafx.h"
#include "Main.h"

void Main::Init()
{
	titleMap = new Title();
	firstMap = new Map1();

	pNum = 2;

	camScalar = 0.0f;

	
	for (int i = 0; i < pNum; i++)
	{
		player[i] = new PicoCat();
	
	}
	player[0]->col->SetWorldPosX(100.0f);

	player[1]->col->SetWorldPosX(-100.0f);
	player[1]->ColorChange(0.5f, 0.5f, 0.8f);


	
	SOUND->AddSound("01Spring.mp3", "title", true);
	SOUND->SetVolume("title", 0.1f);


	SOUND->AddSound("jumSFX.mp3", "jump", false);
	SOUND->AddSound("lockDoor.mp3", "doorSound", false);
	SOUND->AddSound("keyGet.mp3", "key", false);

	SOUND->AddSound("03Doremi.mp3", "Stage1", true);

}

void Main::Release()
{
	SafeDelete(titleMap);
	SafeDelete(firstMap);

}

void Main::Update()
{


	float velo = (player[0]->col->GetWorldPos().x + player[pNum - 1]->col->GetWorldPos().x) * 0.5f - CAM->position.x;
	Vector2 velocity;
	velocity.x = velo;

	CAM->position += velocity * camScalar * DELTA;

	if (INPUT->KeyPress('L'))
	{
		CAM->position.x += 200.0f * DELTA;
	}


#if 1
	///1P
	if (INPUT->KeyPress(VK_RIGHT)/* || INPUT->KeyPress('D')*/)
	{
		player[0]->stat = CATSTAT::RIGHTPRESS;
		//player->stat = CATSTAT::RIGHTPRESS;
	}
	else if (INPUT->KeyPress(VK_LEFT)/* || INPUT->KeyPress('S')*/)
	{
		player[0]->stat = CATSTAT::LEFTPRESS;
		//player->stat = CATSTAT::LEFTPRESS;
	}
	else
	{
		player[0]->stat = CATSTAT::STAND;
		//player->stat = CATSTAT::STAND;
	}
	if (INPUT->KeyUp(VK_RIGHT))
	{
		player[0]->stat = CATSTAT::RIGHTUP;
	}
	else if (INPUT->KeyUp(VK_LEFT))
	{
		player[0]->stat = CATSTAT::LEFTUP;
	}

	if (INPUT->KeyDown(VK_UP))
	{
		player[0]->stat = CATSTAT::JUMPDOWN;
	}

	if (INPUT->KeyUp(VK_UP))
	{
		player[0]->stat = CATSTAT::JUMPUP;
	}

	///2P
	if (INPUT->KeyPress('D'))
	{
		player[1]->stat = CATSTAT::RIGHTPRESS;
	}
	else if (INPUT->KeyPress('A'))
	{
		player[1]->stat = CATSTAT::LEFTPRESS;
	}
	else
	{
		player[1]->stat = CATSTAT::STAND;
	}

	if (INPUT->KeyUp('D'))
	{
		player[1]->stat = CATSTAT::RIGHTUP;
	}
	
	else if (INPUT->KeyUp('A'))
	{
		player[1]->stat = CATSTAT::LEFTUP;
	}
	
	if (INPUT->KeyDown('W'))
	{
		player[1]->stat = CATSTAT::JUMPDOWN;
	}
	
	if (INPUT->KeyUp('W'))
	{
		player[1]->stat = CATSTAT::JUMPUP;
	}
#endif

	if (stage == STAGE::TITLE)
	{
		camScalar = 0.0f;

		for (int i = 0; i < pNum; i++)
		{
			player[i]->scalar = 150.0f;
		}

		SOUND->Stop("Stage1");
		SOUND->Play("title");


		if (player[0]->col->Intersect(titleMap->door))
		{

			if (INPUT->KeyDown(VK_DOWN))
			{

				SOUND->Stop("doorSound");
				SOUND->Play("doorSound");

				titleMap->openDoor();
			}
		}
		else if (player[0]->col->Intersect(titleMap->doorOP)) 
		{
		
			if (INPUT->KeyDown(VK_DOWN))
			{
				player[0]->isEnd = true;
			}
		}

		
		if (player[1]->col->Intersect(titleMap->door))
		{
			if (INPUT->KeyDown('S'))
			{
			
				SOUND->Stop("doorSound");
				SOUND->Play("doorSound");

				titleMap->openDoor();
			}
		}
		else if (player[1]->col->Intersect(titleMap->doorOP))
		{
		
			if (INPUT->KeyDown('S'))
			{
				player[1]->isEnd = true;
			}
		}

		
		if (player[0]->isEnd && player[1]->isEnd)
		{
			for (int j = 0; j < pNum; j++)
			{
				player[j]->isEnd = false;
				player[j]->StartGame();
				//player[j]->col->SetWorldPosX(100.0f - 200.0f * j);
			}
			player[0]->col->SetWorldPos(Vector2(100.0f, 0.0f));
			player[1]->col->SetWorldPos(Vector2(-100.0f, 0.0f));

			titleMap->stageClose();
			firstMap->stageOpen();

			stage = STAGE::ST_1;
		}
	}

	if (stage == STAGE::ST_1)
	{                                                                                           
		camScalar = 100.0f;

		for (int i = 0; i < pNum; i++)
		{
			player[i]->scalar = 100.0f;
		}

		SOUND->Stop("title");
		SOUND->Play("Stage1");


		if (player[0]->isLift && player[1]->isLift)
		{
			isFull = true;
		}
		else isFull = false;
	
		if (isFull)
		{
			if (firstMap->lift->GetWorldPos().y >= 260.0f)
			{
				firstMap->lift->SetWorldPosY(260.0f);
			}
			else
			{
				liftDir = UP;
				firstMap->lift->MoveWorldPos(liftDir * 100.0f * DELTA);
			}
		}
		else
		{
			liftDir = DOWN;
			firstMap->lift->MoveWorldPos(liftDir * 100.0f * DELTA);

			if (firstMap->lift->GetWorldPos().y <= 20.0f)
			{
				firstMap->lift->SetWorldPosY(20.0f);
			}
		}

		if (player[0]->col->Intersect(firstMap->door))
		{

			if (INPUT->KeyDown(VK_DOWN))
			{

				if (player[0]->isHave)
				{
	
					SOUND->Stop("doorSound");
					SOUND->Play("doorSound");
					firstMap->key->visible = false;
					firstMap->openDoor();
				}
			}
		}
		else if (player[0]->col->Intersect(firstMap->doorOP)) 
		{

			if (INPUT->KeyDown(VK_DOWN))
			{
				player[0]->isEnd = true;
			}
		}


		if (player[1]->col->Intersect(firstMap->door))
		{
			if (INPUT->KeyDown('S'))
			{

				if (player[1]->isHave)
				{
	
					SOUND->Stop("doorSound");
					SOUND->Play("doorSound");
					firstMap->key->visible = false;
					firstMap->openDoor();
				}
			}
		}
		else if (player[1]->col->Intersect(firstMap->doorOP))
		{

			if (INPUT->KeyDown('S'))
			{
				player[1]->isEnd = true;
			}
		}


		if (player[0]->isEnd && player[1]->isEnd)
		{
			for (int j = 0; j < pNum; j++)
			{
				player[j]->isHave = false;
				player[j]->isEnd = false;
				player[j]->StartGame();
				//player[j]->col->SetWorldPosX(100.0f - 200.0f * j);
			}
			player[0]->col->SetWorldPos(Vector2(100.0f, 0.0f));
			player[1]->col->SetWorldPos(Vector2(-100.0f, 0.0f));

			firstMap->stageClose();
			isKey = false;

			titleMap->stageOpen();

			stage = STAGE::TITLE;
		}


		if (isKey)
		{
			for (int j = 0; j < pNum; j++)
			{
	
				if (player[j]->isHave)
				{
					Vector2 dir = player[j]->headCol->GetWorldPos() + keyPos - firstMap->key->GetWorldPos();
					firstMap->key->MoveWorldPos(dir * 10.0f * DELTA);

					if (j == 0 && INPUT->KeyPress(VK_RIGHT))
					{
						keyPos.x = -50.0f;
					}
					else if (j == 0 && INPUT->KeyPress(VK_LEFT))
					{
						keyPos.x = 50.0f;
					}

					if (j == 1 && INPUT->KeyPress('D'))
					{
						keyPos.x = -50.0f;
					}
					else if (j == 1 && INPUT->KeyPress('A'))
					{
						keyPos.x = 50.0f;
					}
				}
			}
		}


		for (int j = 0; j < pNum; j++)
		{
			if (player[j]->col->Intersect(firstMap->floorLF))
			{
				player[j]->onBlock(firstMap->floorLF->GetWorldPos().y);
			}
			else
			{
				player[j]->offBlock();
			}
		}
	}

	for (int i = 0; i < pNum; i++)
	{
		player[i]->Update();
	}

	titleMap->Update();
	firstMap->Update();
}

void Main::LateUpdate()
{

#if 1

	if (player[0]->col->Intersect(player[1]->headCol))
	{
	
		float headP = player[1]->headCol->GetWorldPos().y + player[1]->headCol->scale.y;
		player[0]->onBlock(headP);
	}

	else if (player[0]->headCol->Intersect(player[1]->headCol))
	{

		if (INPUT->KeyPress(VK_LEFT) || INPUT->KeyPress(VK_RIGHT))
		{
		
			if (player[0]->col->GetWorldPos().x < player[1]->headCol->GetWorldPos().x)
			{
				//player[0]->stat = CATSTAT::RIGHTPUSH;
				
				int wallOn = player[1]->headCol->GetWorldPos().x - player[1]->headCol->scale.x * 0.5f - 23.0f;

				
				float Ipos = player[1]->col->GetWorldPos().x;

				//player[i]->col->SetWorldPosX(Ipos);
				player[0]->col->SetWorldPosX(wallOn);
				//break;
			}
		
			else if (player[0]->col->GetWorldPos().x > player[1]->headCol->GetWorldPos().x)
			{
				//player[0]->stat = CATSTAT::LEFTPUSH;

				int wallOn = player[1]->headCol->GetWorldPos().x + player[1]->headCol->scale.x * 0.5f + 23.0f;
			
				float Ipos = player[1]->col->GetWorldPos().x;

				//player[i]->col->SetWorldPosX(Ipos);
				player[0]->col->SetWorldPosX(wallOn);
				//break;
			}
		}
	}

	if (player[1]->col->Intersect(player[0]->headCol))
	{
	�
		float headP = player[0]->headCol->GetWorldPos().y + player[0]->headCol->scale.y;
		player[1]->onBlock(headP);
	}
	
	else if (player[1]->headCol->Intersect(player[0]->headCol))
	{
		 
		if (INPUT->KeyPress('A') || INPUT->KeyPress('D'))
		{
			
			if (player[1]->col->GetWorldPos().x < player[0]->headCol->GetWorldPos().x)
			{
				
				int wallOn = player[0]->headCol->GetWorldPos().x - player[0]->headCol->scale.x * 0.5f - 23.0f;

				float Ipos = player[0]->col->GetWorldPos().x;

				//player[i]->col->SetWorldPosX(Ipos);
				player[1]->col->SetWorldPosX(wallOn);
				//break;
			}
	
			else if (player[1]->col->GetWorldPos().x > player[0]->headCol->GetWorldPos().x)
			{
				int wallOn = player[0]->headCol->GetWorldPos().x + player[0]->headCol->scale.x * 0.5f + 23.0f;
				
				float Ipos = player[0]->col->GetWorldPos().x;

				//player[i]->col->SetWorldPosX(Ipos);
				player[1]->col->SetWorldPosX(wallOn);
				//break;
			}
		}
	}
	for (int i = 0; i < pNum; i++)
	{
		player[i]->Update();
	}
#endif
		
	///타이틀
	if (stage == STAGE::TITLE)
	{
		CAM->position.y = 240.0f;
		CAM->position.x = 0.0f;
		// 960*0.5  = -480 + 30 + 내scale*0.5
		for (int i = 0; i < pNum; i++)
		{
			player[i]->col->SetWorldPosX(Utility::Saturate(player[i]->col->GetWorldPos().x, -455.0f, 455.0f));
		}

		for (int i = 0; i < pNum; i++)
		{
			
			if (player[i]->col->Intersect(titleMap->floor))
			{
				player[i]->onBlock(titleMap->floor->GetWorldPos().y);
			}
			else player[i]->offBlock();

			player[i]->Update();
		}
	}

	else if (stage == STAGE::ST_1)
	{
		CAM->position.y = 240.0f;
		CAM->position.x = Utility::Saturate(CAM->position.x, 0.0f, 2320.0f);
		//CAM->position.x = Utility::Saturate(CAM->position.x, 0.0f, 2000.0f);

	// 960*0.5  = -480 + 30 + 내scale*0.5
		for (int i = 0; i < pNum; i++)
		{
			player[i]->col->SetWorldPosX(Utility::Saturate(player[i]->col->GetWorldPos().x, -480.0f, 2775.0f));
		}

		for (int j = 0; j < pNum; j++)
		{
			if (player[j]->col->Intersect(firstMap->key))
			{
				if (!isKey)
				{
					player[j]->isHave = true;
					SOUND->Play("key");
					firstMap->key->SetParentT(*player[j]->col);
					firstMap->key->SetLocalPos(Vector2(0.0f, 0.0f));
					//firstMap->key->SetLocalPos(Vector2(-50.0f, 50.0f));
					isKey = true;
				}
			}
		}
		firstMap->key->Update();

		for (int j = 0; j < pNum; j++)
		{
			
			if (player[j]->col->Intersect(firstMap->button))
			{
				firstMap->Pressed();

				player[j]->onBlock(firstMap->button->GetWorldPos().y + firstMap->button->scale.y);
				player[j]->Update();
			}
			else
			{
				player[j]->offBlock();
				player[j]->Update();
			}
			firstMap->button->Update();
		}


		for (int j = 0; j < pNum; j++)
		{
		
			if (player[j]->col->Intersect(firstMap->liftBox))
			{
		
				if (firstMap->lift->GetWorldPos().y + 5.0f > player[j]->col->GetWorldPos().y
					&& firstMap->lift->GetWorldPos().y - firstMap->lift->scale.y < player[j]->col->GetWorldPos().y)
				{
					player[j]->onBlock(firstMap->lift->GetWorldPos().y);
					player[j]->isLift = true;

					if (INPUT->KeyPress(VK_UP) || INPUT->KeyPress('W'))
					{
						if (INPUT->KeyPress(VK_UP))
						{
							player[0]->offBlock();
							player[0]->isLift = false;
						}
						if (INPUT->KeyPress('W'))
						{
							player[1]->offBlock();
							player[1]->isLift = false;
						}
					}
					player[j]->underLift = false;
				}
				else
				{
					player[j]->underLift = false;
					player[j]->isLift = false;
					//player[j]->offBlock();
					//player[j]->Update();
				}
			}
			else
			{
				player[j]->underLift = false;
				player[j]->isLift = false;
				//player[j]->offBlock();
				//player[j]->Update();
			}
			if (player[j]->headCol->Intersect(firstMap->lift))
			{
				float liftOn = player[j]->headCol->GetWorldPos().y + player[j]->headCol->scale.y;

				if (player[j]->col->GetWorldPos().x < firstMap->lift->GetWorldPos().x - firstMap->lift->scale.x * 0.5f)
				{
					if (INPUT->KeyPress(VK_RIGHT) || INPUT->KeyPress('D'))
					{
						int wallOn = firstMap->lift->GetWorldPos().x - firstMap->lift->scale.x * 0.5f - 22.0f;

						player[j]->col->SetWorldPosX(wallOn);
						player[j]->isLift = false; 
					}
				}
				
				else if (player[j]->col->Intersect(firstMap->liftBox) &&
					liftOn < firstMap->lift->GetWorldPos().y - 5.0f)
				{
		
					float liftOn2 = liftOn + 10.0f;

					firstMap->lift->SetWorldPosY(liftOn2);
					player[j]->isLift = false;
					player[j]->underLift = true;

					if (INPUT->KeyPress(VK_UP) || INPUT->KeyPress('W'))
					{
						player[j]->stat = CATSTAT::STAND;
					}
				}
			}
			player[j]->Update();

			firstMap->lift->Update();
		}
	
		for (int j = 0; j < pNum; j++)
		{
			for (int i = 0; i < BMAX; i++)
			{
				if (player[j]->col->Intersect(firstMap->blocks[i]))
				{
					player[j]->onBlock(firstMap->blocks[i]->GetWorldPos().y);
				}
				
				else if (player[j]->headCol->Intersect(firstMap->blocks[i]))
				{
					
					if (player[j]->col->GetWorldPos().x < firstMap->blocks[i]->GetWorldPos().x)
					{
						int wallOn = firstMap->blocks[i]->GetWorldPos().x - firstMap->blocks[i]->scale.x * 0.5f - 22.0f;

						player[j]->col->SetWorldPosX(wallOn);
					}
					
					else if (player[j]->col->GetWorldPos().x > firstMap->blocks[i]->GetWorldPos().x)
					{
						int wallOn = firstMap->blocks[i]->GetWorldPos().x + firstMap->blocks[i]->scale.x * 0.5f + 22.0f;

						player[j]->col->SetWorldPosX(wallOn);
					}
				}
			}
			player[j]->Update();
		}
	}

}

void Main::Render()
{
	if (stage == STAGE::TITLE)
	{
		titleMap->Render();
	}
	else if(stage == STAGE::ST_1)
	{
		firstMap->Render();
	}

	for (int i = 0; i < pNum; i++)
	{
		player[i]->Render();
	}
}

void Main::ResizeScreen()
{

}

int WINAPI wWinMain(HINSTANCE instance, HINSTANCE prevInstance, LPWSTR param, int command)
{
    app.SetAppName(L"Game1");
    app.SetInstance(instance);
	app.InitWidthHeight(960.0f,540.0f);
	Main* main = new Main();
	int wParam = (int)WIN->Run(main);
	WIN->DeleteSingleton();
	SafeDelete(main);
	return wParam;
}