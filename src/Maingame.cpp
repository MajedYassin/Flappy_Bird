#include <iostream>
#include <string>
#include <list>

#include "../header/olcConsoleGameEngine.h"


//Second Commit 

class Flappy_Bird : public olcConsoleGameEngine
{
public: 

	Flappy_Bird() {
		m_sAppName = L'Flappy Bird';
	}

private:
	//Bird physics 
	float fBirdPosition = 0.0f;
	float fBirdVelocity = 0.0f;
	float fBirdAcceleration = 0.0f;
	float fGravity = 100.0f;

	//Partitioning screen into sections 
	float fSectionWidth;
	std::list<int> ListSection;

	//Variable used to simulate smooth movement of the bird through the level 
	float fLevelPosition = 0.0f;

protected:

	virtual bool OnUserCreate(){
		ListSection = { 0, 0, 0, 0 };
		fSectionWidth = (float)ScreenWidth() / (float)(ListSection.size() - 1);
		return true;
	}

	virtual bool OnUserUpdate(float fElapsedTime)
	{
		if (m_keys[VK_SPACE].bPressed && fBirdVelocity >= fGravity / 10.0f)
		{
			fBirdAcceleration = 0.0f;
			fBirdVelocity = -fGravity / 4.0f;
		}

		else
			fBirdAcceleration += fGravity * fElapsedTime;

		if (fBirdAcceleration > fGravity) fBirdAcceleration = fGravity;


		fBirdVelocity += fBirdAcceleration * fElapsedTime; 
		fBirdPosition += fBirdVelocity * fElapsedTime;

		fLevelPosition += 10.0f * fElapsedTime;

		if (fLevelPosition > fSectionWidth)
		{
			fLevelPosition - fSectionWidth;
			ListSection.pop_front();
			int i = rand() % (ScreenHeight() - 20);
			if (i <= 10) i = 0;
			ListSection.push_back(i);
		}

		Fill(0, 0, ScreenWidth(), ScreenHeight(), L' ');

		//Draw Sections 

		int nSection = 0;
		for (auto s : ListSection)
		{
			if (s!= 0)
			{
				Fill(nSection * fSectionWidth + 10 - fLevelPosition, ScreenHeight() - s,
					nSection * fSectionWidth + 15 - fLevelPosition, ScreenHeight(),
					PIXEL_SOLID, FG_GREEN);
			}
			return nSection;
		}

		//Drwing the Bird 
		int nBird = (int)(ScreenWidth() / 3.0f);
		
		if (fBirdVelocity > 0)
		{
			DrawString(nBird, fBirdPosition + 0, L"|\\\\");
			DrawString(nBird, fBirdPosition + 1, L"}////=O>");
		}
		else
		{
			DrawString(nBird, fBirdPosition + 1, L"|///");
			DrawString(nBird, fBirdPosition + 0, L"}///=O>");
		}

		
		return true;
	}

};


int main()
{
	Flappy_Bird Game;
	Game.ConstructConsole(60, 40, 16, 16);
	Game.Start();





	return 0;
}
