#include <iostream>
#include <string>

#include "../header/olcConsoleGameEngine.h"

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



	virtual bool OnUserCreate(){
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

		Fill(0, 0, ScreenWidth(), ScreenHeight(), L' ');

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
	Flappy_Bird game;
	game.ConstructConsole(60, 40, 16, 16);
	game.Start();





	return 0;
}
