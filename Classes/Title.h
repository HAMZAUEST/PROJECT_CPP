#pragma once
class Title
{
private:

	ObRect*		mapBox = new ObRect();
	
	ObImage*	name;

	bool		isOpen{ false };

public:

	ObImage*	floor;
	ObImage*	door;
	ObImage*	doorOP;


public:

	Title();
	~Title();

	void Update();
	void Render();

	void openDoor();

	void stageOpen();
	void stageClose();

};

