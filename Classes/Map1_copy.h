#pragma once


class Map1_copy
{
	ObRect* mapBox = new ObRect();
	Vector2		liftDir{ DOWN };

	ObRect* keyBox = new ObRect();

	bool		isButton{ false };
	bool		isPress{ false };
	bool		isOnce{ true };
	bool		isOpen{ false };


public:

	ObImage* blocks[8];




	ObImage* floorLF;


	ObImage* lift;
	ObImage* key = new ObImage(L"key.PNG");


	ObImage* door;
	ObImage* doorOP;

public:

	ObRect* button;

	Map1_copy();
	~Map1_copy();

	void Update();
	void Render();

	void Pressed();

	void openDoor();

	void stageOpen();
	void stageClose();

};