#include "stdafx.h"

PicoCat::PicoCat()
{

	col->isFilled = false;
	col->collider = COLLIDER::RECT;
	col->pivot = OFFSET_B;
	col->SetWorldPos(Vector2(0.0f, 0.0f));
	col->scale = Vector2(25.0f, 40.0f);
	col->color = Color(1.0f, 0.0f, 0.0f, 1.0f);

	col->visible = false;
	headCol->visible = false;

	headCol->isFilled = false;
	headCol->collider = COLLIDER::RECT;
	headCol->SetParentRT(*col);
	headCol->pivot = OFFSET_B;
	headCol->SetLocalPos(Vector2(0.0f, 15.0f));
	headCol->scale = Vector2(48.0f, 32.0f);
	headCol->color = Color(1.0f, 0.0f, 0.0f, 1.0f);

	stand->SetParentRT(*col);
	stand->visible = true;
	stand->pivot = OFFSET_B;
	stand->scale = Vector2(50.0f, 50.0f);

	walk->SetParentRT(*col);
	walk->visible = false;
	walk->pivot = OFFSET_B;
	walk->scale = Vector2(50.0f, 50.0f);
	walk->maxFrame.x = 8;
	walk->ChangeAnim(ANIMSTATE::LOOP, 0.1f);

	jump->SetParentRT(*col);
	jump->visible = false;
	jump->pivot = OFFSET_B;
	jump->scale = Vector2(50.0f, 50.0f);

	push->SetParentRT(*col);
	push->visible = false;
	push->pivot = OFFSET_B;
	push->scale = Vector2(50.0f, 50.0f);
	push->maxFrame.x = 8;
	push->ChangeAnim(ANIMSTATE::LOOP, 0.1f);

	scalar = 100.0f;
	gravity = 0.0f;
	gravityPlus = 0.0f;

	stat = CATSTAT::STAND;

	//SOUND->AddSound("jumSFX.mp3", "jump", false);

}

PicoCat::~PicoCat()
{
	SafeDelete(col);
	SafeDelete(stand);
	SafeDelete(walk);
	SafeDelete(jump);
	SafeDelete(push);
}

void PicoCat::Update()
{
	//cout << col->GetWorldPivot().y << endl;

	//gravity = Utility::Saturate(gravity, 0.0f, 500.0f);


	col->MoveWorldPos(direction * scalar * DELTA + DOWN * gravity * DELTA);
	//col->MoveWorldPos(DOWN * gravity * DELTA);


	if (col->GetWorldPos().y < -app.GetHalfHeight())
	{
		col->SetWorldPosX(col->GetWorldPos().x - 400.0f);
		col->SetWorldPosY(app.GetHalfHeight() + 240.0f);
	}


	if (isOn)
	{
		jump->visible = false;
		stand->visible = true;

		gravity = 0.0f;
		//scalar = 0.0f;

		isJump = false;

		col->SetWorldPosY(blockOn);
		//col->SetLocalPosY(blockOn);
	}
	else
	{
		gravity += 100.0f * DELTA;
		if (gravity > 300.0f) gravity = 300.0f;
	}


	if (isWall)
	{
		col->SetWorldPosX(wallOn);
	}

	if (isEnd)
	{
		Endgame();
	}
	else
	{

		if (stat == CATSTAT::RIGHTPRESS)
		{
			direction = RIGHT;
			//col->MoveWorldPos(RIGHT * 100.0f * DELTA);

			stand->visible = false;
			jump->visible = false;

			walk->visible = true;

			stand->reverseLR = false;
			walk->reverseLR = false;
		}

		else if (stat == CATSTAT::LEFTPRESS)
		{
			direction = LEFT;
			//col->MoveWorldPos(LEFT * 100.0f * DELTA);

			stand->visible = false;
			jump->visible = false;

			walk->visible = true;

			stand->reverseLR = true;
			walk->reverseLR = true;
		}
		//else if (stat == CATSTAT::RIGHTPUSH)
		//{
		//	direction = RIGHT;
		//	//col->MoveWorldPos(RIGHT * 100.0f * DELTA);

		//	stand->visible = false;
		//	jump->visible = false;
		//	walk->visible = false;

		//	push->visible = true;

		//	push->reverseLR = false;
		//	stand->reverseLR = false;
		//	walk->reverseLR = false;
		//}
		////¿ÞÂÊÀ¸·Î
		//else if (stat == CATSTAT::LEFTPUSH)
		//{
		//	direction = LEFT;
		//	//col->MoveWorldPos(LEFT * 100.0f * DELTA);

		//	stand->visible = false;
		//	jump->visible = false;
		//	walk->visible = false;

		//	push->visible = true;

		//	push->reverseLR = true;
		//	stand->reverseLR = true;
		//	walk->reverseLR = true;
		//}
		else if (stat == CATSTAT::STAND)
		{
			direction = Vector2(0.0f, 0.0f);

			//push->visible = false;
			//jump->visible = false;
			//walk->visible = false;

			//stand->visible = true;
		}


		if (stat == CATSTAT::RIGHTUP)
		{
			stand->visible = false;
			walk->visible = false;

			jump->visible = true;

			jump->reverseLR = false;
			stand->reverseLR = false;
			walk->reverseLR = false;
		}
		else if (stat == CATSTAT::LEFTUP)
		{
			stand->visible = false;
			walk->visible = false;

			jump->visible = true;

			jump->reverseLR = true;
			stand->reverseLR = true;
			walk->reverseLR = true;
		}


		if (INPUT->KeyPress(VK_UP) || INPUT->KeyPress('W'))
		{
		}

		if (stat == CATSTAT::JUMPDOWN)
		{
			if (!isJump && !underLift)
			{
				SOUND->Stop("jump");
				SOUND->Play("jump");


				isOn = false;

				gravity = -150.0f;

				stand->visible = false;
				walk->visible = false;

				jump->visible = true;
			}

		}

		if (stat == CATSTAT::JUMPUP)
		{
			isJump = true;
		}
	}


#if 0   

	if (INPUT->KeyPress(VK_RIGHT) || INPUT->KeyPress('D'))
	{
		direction = RIGHT;
		//col->MoveWorldPos(RIGHT * 100.0f * DELTA);

		stand->visible = false;
		jump->visible = false;

		walk->visible = true;

		stand->reverseLR = false;
		walk->reverseLR = false;
	}

	else if (INPUT->KeyPress(VK_LEFT) || INPUT->KeyPress('S'))
	{
		direction = LEFT;
		//col->MoveWorldPos(LEFT * 100.0f * DELTA);

		stand->visible = false;
		jump->visible = false;

		walk->visible = true;

		stand->reverseLR = true;
		walk->reverseLR = true;
	}
	else direction = Vector2(0.0f, 0.0f);


	if (INPUT->KeyUp(VK_RIGHT) || INPUT->KeyUp('D'))
	{
		stand->visible = false;
		walk->visible = false;

		jump->visible = true;

		jump->reverseLR = false;
		stand->reverseLR = false;
		walk->reverseLR = false;
	}

	else if (INPUT->KeyUp(VK_LEFT) || INPUT->KeyUp('S'))
	{
		stand->visible = false;
		walk->visible = false;

		jump->visible = true;

		jump->reverseLR = true;
		stand->reverseLR = true;
		walk->reverseLR = true;
	}


	if (INPUT->KeyPress(VK_UP) || INPUT->KeyPress('W'))
	{

		//if (gravityPlus <= 5.0f)
		//{
		//	if (TIMER->GetTick(jumpTime, 5.0f))
		//	{
		//		gravityPlus += 1.0f * DELTA;
		//	}
		//}
		//else
		//{
		//	gravityPlus = 5.0f * DELTA;
		//}

		//scalar += 1.0f;
		//scalar = Utility::Saturate(scalar,0.0f,50.0f);
	}


	if (INPUT->KeyDown(VK_UP) || INPUT->KeyDown('W'))
	{

		if (!isJump)
		{

			isOn = false;

			gravity = -150.0f;


			//if (jump->reverseLR != stand->reverseLR) jump->reverseLR = stand->reverseLR;

			stand->visible = false;
			walk->visible = false;

			jump->visible = true;
		}

	}


	if (INPUT->KeyUp(VK_UP) || INPUT->KeyUp('W'))
	{
		//isJump = true;
	}

#endif


#if 0 

	if (stat == CATSTAT::STAND)
	{

		if (INPUT->KeyDown(VK_RIGHT) || INPUT->KeyDown('D'))
		{
			stat = CATSTAT::WALK;
			stand->visible = false;
			stand->reverseLR = false;

			walk->visible = true;
			walk->reverseLR = false;
		}

		else if (INPUT->KeyDown(VK_LEFT) || INPUT->KeyDown('S'))
		{
			stat = CATSTAT::WALK;

			stand->visible = false;
			stand->reverseLR = true;

			walk->visible = true;
			walk->reverseLR = true;
		}


		if (INPUT->KeyDown(VK_UP) || INPUT->KeyDown('W'))
		{
			stat = CATSTAT::JUMP;


			if (jump->reverseLR != stand->reverseLR) jump->reverseLR = stand->reverseLR;

			stand->visible = false;
			jump->visible = true;
		}



		if (INPUT->KeyDown(VK_DOWN) || INPUT->KeyDown('S'))
		{

		}

	}

	else if (stat == CATSTAT::WALK)
	{

		if (INPUT->KeyPress(VK_RIGHT) || INPUT->KeyPress('D'))
		{
			col->MoveWorldPos(RIGHT * scalar * DELTA);
		}

		if (INPUT->KeyPress(VK_LEFT) || INPUT->KeyPress('S'))
		{
			col->MoveWorldPos(LEFT * scalar * DELTA);
		}





		if (INPUT->KeyUp(VK_RIGHT) || INPUT->KeyUp(VK_LEFT))
		{
			stat = CATSTAT::STAND;

			walk->visible = false;
			stand->visible = true;
		}


		if (INPUT->KeyUp(VK_RIGHT) || INPUT->KeyUp(VK_LEFT))
		{
			stat = CATSTAT::STAND;

			walk->visible = false;
			stand->visible = true;
		}


		if (INPUT->KeyDown(VK_UP) || INPUT->KeyDown('W'))
		{
			stat = CATSTAT::JUMP;


			if (jump->reverseLR != walk->reverseLR) jump->reverseLR = walk->reverseLR;

			walk->visible = false;
			jump->visible = true;
		}



	}

	else if (stat == CATSTAT::JUMP)
	{
		//gravity = -700.0f;

		if (INPUT->KeyPress(VK_RIGHT) || INPUT->KeyPress('D'))
		{
			jump->reverseLR = false;
			col->MoveWorldPos(RIGHT * scalar * DELTA);
		}

		if (INPUT->KeyPress(VK_LEFT) || INPUT->KeyPress('S'))
		{
			jump->reverseLR = true;
			col->MoveWorldPos(LEFT * scalar * DELTA);
		}




		if (INPUT->KeyUp(VK_UP) || INPUT->KeyUp('W'))
		{
			stat = CATSTAT::STAND;

			jump->visible = false;
			stand->visible = true;
		}



	}


	else if (stat == CATSTAT::PUSH)
	{



	}

#endif

	//-------------------------------------
	col->Update();
	headCol->Update();
	stand->Update();
	walk->Update();
	jump->Update();
	push->Update();

}

void PicoCat::Render()
{

	stand->Render();
	walk->Render();
	jump->Render();
	push->Render();

	col->Render();
	headCol->Render();

}


void PicoCat::onBlock(float obPosY)
{
	blockOn = obPosY;
	isOn = true;
}

void PicoCat::offBlock()
{
	isOn = false;
}



void PicoCat::onWall(float obPosX, float obScaleX)
{

	if (col->GetWorldPivot().x < obPosX)
	{

		wallOn = obPosX - obScaleX * 0.5f - 24.0f;
	}

	else if (col->GetWorldPivot().x > obPosX)
	{
		wallOn = obPosX + obScaleX * 0.5f + 24.0f;
	}

	isWall = true;
}

void PicoCat::offWall()
{
	isWall = false;
}

void PicoCat::StartGame()
{
	col->colOnOff = true;
	headCol->colOnOff = true;
}

void PicoCat::Endgame()
{
	col->SetWorldPos(Vector2(2600.0f, 270.0f));

	col->colOnOff = false;
	headCol->colOnOff = false;

	stand->visible = false;
	walk->visible = false;
	push->visible = false;
	jump->visible = false;
}

void PicoCat::ColorChange(float r, float g, float b)
{
	stand->color = Color(r, g, b, 0.5f);
	walk->color = Color(r, g, b, 0.5f);
	push->color = Color(r, g, b, 0.5f);
	jump->color = Color(r, g, b, 0.5f);

	//stand = new ObImage(L"1_stand1.png");
	//walk = new ObImage(L"1_walkSprite.png");
	//push = new ObImage(L"1_pushSprite.png");
	//jump = new ObImage(L"1_jump1.png");
}