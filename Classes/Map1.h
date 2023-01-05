#pragma once


class Map1
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

	ObRect* button;
	ObImage* floorLF;

	ObRect* liftBox = new ObRect();

	ObImage* lift;
	ObImage* key = new ObImage(L"key.PNG");

	ObImage* door;
	ObImage* doorOP;

public:

	Map1();
	~Map1();

	void Update();
	void Render();

	void Pressed();

	void openDoor();

	void stageOpen();
	void stageClose();

};