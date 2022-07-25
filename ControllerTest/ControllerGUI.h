#pragma once
#include <SFML/Graphics.hpp>
#include <Windows.h>
#include <Xinput.h>
#include "XBOXController.h"
#include <iostream>

class Bumpers
{
public:
	Bumpers(float x, float y, bool isRB = false)
	{
		Controller = new XBOXController(1);
		isRight = isRB;
		Button.setOutlineColor(sf::Color(217, 126, 95));
		Button.setFillColor(sf::Color(32, 32, 32));
		Button.setOutlineThickness(5);
		Button.setPosition(x, y);
		Button.setSize(sf::Vector2f(80, 25));
	}
	void Update()
	{
		if (Controller->IsConnected())
		{
			if (isRight)
				if (Controller->GetState().Gamepad.wButtons & XINPUT_GAMEPAD_RIGHT_SHOULDER)
					Button.setFillColor(sf::Color(217, 126, 95));
				else
					Button.setFillColor(sf::Color(32, 32, 32));
			else
				if (Controller->GetState().Gamepad.wButtons & XINPUT_GAMEPAD_LEFT_SHOULDER)
					Button.setFillColor(sf::Color(217, 126, 95));
				else
					Button.setFillColor(sf::Color(32, 32, 32));

		}
	}
	void Draw(sf::RenderWindow& window)
	{
		window.draw(Button);
	}
private:
	sf::RectangleShape Button;
	XBOXController* Controller;
	bool isRight;
};

class OptionButtons
{
public:
	OptionButtons(float x, float y, bool isBack = false)
	{
		backButton = isBack;
		Controller = new XBOXController(1);

		Button.setOutlineColor(sf::Color(217, 126, 95));
		Button.setFillColor(sf::Color(32, 32, 32));
		Button.setOutlineThickness(5);
		Button.setRadius(15);
		Button.setPosition(x, y);
	}

	void Update()
	{
		if (Controller->IsConnected())
		{
			if (backButton) {
				if (Controller->GetState().Gamepad.wButtons & XINPUT_GAMEPAD_BACK)
					Button.setFillColor(sf::Color(216, 126, 92));
				else
					Button.setFillColor(sf::Color(32, 32, 32));
			}
			else
			{
				if (Controller->GetState().Gamepad.wButtons & XINPUT_GAMEPAD_START)
					Button.setFillColor(sf::Color(216, 126, 92));
				else
					Button.setFillColor(sf::Color(32, 32, 32));
			}
		}
	}

	void Draw(sf::RenderWindow& window)
	{
		window.draw(Button);
	}

private:
	sf::CircleShape Button;
	XBOXController* Controller;
	bool backButton = false;
};

class Dpad
{
public:
	Dpad(float x, float y)
	{
		Controller = new XBOXController(1);

		Up.setSize(sf::Vector2f(20, -47));
		Up.setFillColor(sf::Color(32, 32, 32));
		Up.setOutlineColor(sf::Color(217, 126, 95));
		Up.setOutlineThickness(5);
		Up.setPosition(x, y-5);

		Down.setSize(sf::Vector2f(20, -47));
		Down.setFillColor(sf::Color(32, 32, 32));
		Down.setOutlineColor(sf::Color(217, 126, 95));
		Down.setOutlineThickness(5);
		Down.setPosition(x, y+47+20+5+5+5);

		Right.setSize(sf::Vector2f(20, -47));
		Right.setFillColor(sf::Color(32, 32, 32));
		Right.setOutlineColor(sf::Color(217, 126, 95));
		Right.setOutlineThickness(5);
		Right.rotate(90);
		Right.setPosition(x+20+5+5,y+5);

		Left.setSize(sf::Vector2f(20, -47));
		Left.setFillColor(sf::Color(32, 32, 32));
		Left.setOutlineColor(sf::Color(217, 126, 95));
		Left.setOutlineThickness(5);
		Left.rotate(90);
		Left.setPosition(x-47-5-5, y+5);


	}
	void Update()
	{
		if (Controller->GetState().Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_UP)
			Up.setFillColor(sf::Color(217, 126, 95));
		else
			Up.setFillColor(sf::Color(32, 32, 32));

		if (Controller->GetState().Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_DOWN)
			Down.setFillColor(sf::Color(217, 126, 95));
		else
			Down.setFillColor(sf::Color(32, 32, 32));

		if (Controller->GetState().Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_LEFT)
			Left.setFillColor(sf::Color(217, 126, 95));
		else
			Left.setFillColor(sf::Color(32, 32, 32));

		if (Controller->GetState().Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_RIGHT)
			Right.setFillColor(sf::Color(217, 126, 95));
		else
			Right.setFillColor(sf::Color(32, 32, 32));
	}

	void Draw(sf::RenderWindow& window)
	{
		window.draw(Up);
		window.draw(Down);
		window.draw(Right);
		window.draw(Left);
	}

private:
	sf::RectangleShape Up;
	sf::RectangleShape Down;
	sf::RectangleShape Left;
	sf::RectangleShape Right;
	XBOXController* Controller;
};

class JoyStickButton
{
public:
	JoyStickButton(float x, float y, bool isRightJoystick)
	{
		origX = x;
		origY = y;
		RightJoystick = isRightJoystick;
		Controller = new XBOXController(1);
		JoyStickCircle.setFillColor(sf::Color(217, 126, 95));
		JoyStickCircle.setRadius(30);
		JoyStickCircle.setOrigin(sf::Vector2f(JoyStickCircle.getRadius() / 2, JoyStickCircle.getRadius() / 2));
		JoyStickCircle.setPosition(x, y);

		Outline.setFillColor(sf::Color(32, 32, 32));
		Outline.setRadius(84);
		Outline.setOutlineColor(sf::Color(217, 126, 95));
		Outline.setOutlineThickness(5);
		//Outline.setOrigin(sf::Vector2f(Outline.getRadius() / 2, Outline.getRadius() / 2));
		Outline.setPosition(x-70,y-70);
		
	}

	sf::Vector2f getPos()
	{
		return JoyStickCircle.getPosition();
	}

	void Update()
	{
		if (RightJoystick) {
			if (Controller->GetState().Gamepad.wButtons & XINPUT_GAMEPAD_RIGHT_THUMB)
				JoyStickCircle.setRadius(25);
			else
				JoyStickCircle.setRadius(30);

			if (JoyStickCircle.getPosition().x <= origX + 54 && JoyStickCircle.getPosition().x >= origX - 54)
				JoyStickCircle.setPosition(sf::Vector2f(origX + (Controller->GetState().Gamepad.sThumbRX / 600), JoyStickCircle.getPosition().y));

			if (JoyStickCircle.getPosition().y <= origY + 54 && JoyStickCircle.getPosition().y >= origY - 54)
				JoyStickCircle.setPosition(sf::Vector2f(JoyStickCircle.getPosition().x, origY - (Controller->GetState().Gamepad.sThumbRY / 600)));

			if (JoyStickCircle.getPosition().x > origX + 54)
				JoyStickCircle.setPosition(sf::Vector2f(origX + 53, JoyStickCircle.getPosition().y));
			if (JoyStickCircle.getPosition().x < origX - 54)
				JoyStickCircle.setPosition(sf::Vector2f(origX - 53, JoyStickCircle.getPosition().y));

			if (JoyStickCircle.getPosition().y > origY + 54)
				JoyStickCircle.setPosition(sf::Vector2f(JoyStickCircle.getPosition().x, origY + 53));
			if (JoyStickCircle.getPosition().y < origY - 54)
				JoyStickCircle.setPosition(sf::Vector2f(JoyStickCircle.getPosition().x, origY - 53));
		}
		if (!RightJoystick) {
			if (Controller->GetState().Gamepad.wButtons & XINPUT_GAMEPAD_LEFT_THUMB)
				JoyStickCircle.setRadius(25);
			else
				JoyStickCircle.setRadius(30);
			if (JoyStickCircle.getPosition().x <= origX + 54 && JoyStickCircle.getPosition().x >= origX - 54)
				JoyStickCircle.setPosition(sf::Vector2f(origX + (Controller->GetState().Gamepad.sThumbLX / 600), JoyStickCircle.getPosition().y));

			if (JoyStickCircle.getPosition().y <= origY + 54 && JoyStickCircle.getPosition().y >= origY - 54)
				JoyStickCircle.setPosition(sf::Vector2f(JoyStickCircle.getPosition().x, origY - (Controller->GetState().Gamepad.sThumbLY / 600)));

			if (JoyStickCircle.getPosition().x > origX + 54)
				JoyStickCircle.setPosition(sf::Vector2f(origX + 53, JoyStickCircle.getPosition().y));
			if (JoyStickCircle.getPosition().x < origX - 54)
				JoyStickCircle.setPosition(sf::Vector2f(origX - 53, JoyStickCircle.getPosition().y));

			if (JoyStickCircle.getPosition().y > origY + 54)
				JoyStickCircle.setPosition(sf::Vector2f(JoyStickCircle.getPosition().x, origY + 53));
			if (JoyStickCircle.getPosition().y < origY - 54)
				JoyStickCircle.setPosition(sf::Vector2f(JoyStickCircle.getPosition().x, origY - 53));

		}

	}

	void setPos(float x, float y)
	{
		JoyStickCircle.setPosition(x, y);
	}

	void Draw(sf::RenderWindow& window)
	{
		window.draw(Outline);
		window.draw(JoyStickCircle);
	}

private:
	sf::CircleShape JoyStickCircle;
	sf::CircleShape Outline;
	XBOXController* Controller;
	bool RightJoystick;

	float origX;
	float origY;
};


class TriggerButton
{
public:
	TriggerButton(float x, float y)
	{
		TriggerRect.setFillColor(sf::Color(217, 126, 95));
		TriggerRect.setSize(sf::Vector2f(30, 30));
		TriggerRect.setPosition(x, y);

		TriggerOutline.setOutlineColor(sf::Color(217, 126, 95));
		TriggerOutline.setOutlineThickness(10);
		TriggerOutline.setFillColor(sf::Color(32, 32, 32));
		TriggerOutline.setPosition(x, y);
		TriggerOutline.setSize(sf::Vector2f(30, -84));
	}

	void setSize(sf::Vector2f size)
	{
		TriggerRect.setSize(size);
	}

	void setPos(float x, float y)
	{
		TriggerRect.setPosition(x, y);
	}

	void Draw(sf::RenderWindow& window)
	{
		window.draw(TriggerOutline);
		window.draw(TriggerRect);
	
	}

private:
	sf::RectangleShape TriggerRect;
	sf::RectangleShape TriggerOutline;
};

class InputButton
{
public:
	InputButton(float x, float y, std::string text)
	{
		ButtonShape.setOutlineColor(sf::Color(217, 126, 95));
		ButtonShape.setOutlineThickness(10);
		ButtonShape.setFillColor(sf::Color(33, 32, 32));
		ButtonShape.setRadius(30);
		ButtonShape.setOrigin(sf::Vector2f(ButtonShape.getRadius() / 2, ButtonShape.getRadius() / 2));
		ButtonShape.setPosition(x, y);

		if (!ButtonFont.loadFromFile("fonts/ARCADECLASSIC.TTF"))
			std::cout << "Failed to Load Font" << std::endl;
		ButtonText.setFont(ButtonFont);
		ButtonText.setCharacterSize(50);
		ButtonText.setFillColor(sf::Color::White);
		ButtonText.setString(text);
		ButtonText.setOrigin(ButtonText.getLocalBounds().left / 2.0f, ButtonText.getLocalBounds().top / 2.0f);
		ButtonText.setPosition(x+1, y-8);
		//ButtonText.setStyle(sf::Text::Bold);
	}

	void Draw(sf::RenderWindow& window)
	{
		window.draw(ButtonShape);
		window.draw(ButtonText);
	}

	void Enable()
	{
		ButtonShape.setFillColor(sf::Color(217, 126, 95));
	}

	void Disable()
	{
		ButtonShape.setFillColor(sf::Color(32, 32, 32));
	}

	sf::CircleShape getButton()
	{
		return ButtonShape;
	}

private:
	sf::CircleShape ButtonShape;
	sf::Text ButtonText;
	sf::Font ButtonFont;
};


class ControllerGUI
{
public:
	ControllerGUI()
	{
		RB = new Bumpers(975, 280, true);
		LB = new Bumpers(300, 280);

		Start_Button = new OptionButtons(700, 360);
		Back_Button = new OptionButtons(580, 360, true);
		DPAD = new Dpad(500, 600);

		R_Joystick = new JoyStickButton(800, 600, true);
		L_Joystick = new JoyStickButton(320, 430, false);

		R_Trigger = new TriggerButton(1000, 220);
		L_Trigger = new TriggerButton(320, 220);

		A_Button = new InputButton(1000, 500, "A");
		B_Button = new InputButton(1070, 430, "B");
		Y_Button = new InputButton(1000, 360, "Y");
		X_Button = new InputButton(930, 430, "X");
		Controller = new XBOXController(1);
	}

	void UpdateButton()
	{
		if (Controller->IsConnected())
		{
			if (Controller->GetState().Gamepad.wButtons & XINPUT_GAMEPAD_A)
				A_Button->Enable();
			else
				A_Button->Disable();
			
			if (Controller->GetState().Gamepad.wButtons & XINPUT_GAMEPAD_B)
				B_Button->Enable();
			else
				B_Button->Disable();

			if (Controller->GetState().Gamepad.wButtons & XINPUT_GAMEPAD_Y)
				Y_Button->Enable();
			else
				Y_Button->Disable();

			if (Controller->GetState().Gamepad.wButtons & XINPUT_GAMEPAD_X)
				X_Button->Enable();
			else
				X_Button->Disable();

			R_Trigger->setSize(sf::Vector2f(30,float((-Controller->GetState().Gamepad.bRightTrigger) + 2)/3));
			L_Trigger->setSize(sf::Vector2f(30, float((-Controller->GetState().Gamepad.bLeftTrigger) + 2) / 3));

			R_Joystick->Update();
			L_Joystick->Update();

			DPAD->Update();
			Back_Button->Update();
			Start_Button->Update();
			RB->Update();
			LB->Update();

			//std::cout << R_Joystick.getPosition().x + (Controller->GetState().Gamepad.sThumbRX / 600) << std::endl;

		}
	}

	void Draw(sf::RenderWindow& window)
	{
		R_Joystick->Draw(window);
		L_Joystick->Draw(window);
		L_Trigger->Draw(window);
		R_Trigger->Draw(window);
		A_Button->Draw(window);
		B_Button->Draw(window);
		Y_Button->Draw(window);
		X_Button->Draw(window);
		DPAD->Draw(window);
		Back_Button->Draw(window);
		Start_Button->Draw(window);
		RB->Draw(window);
		LB->Draw(window);
	}
private:
	Bumpers* RB;
	Bumpers* LB;

	OptionButtons* Start_Button;
	OptionButtons* Back_Button;
	Dpad* DPAD;
	JoyStickButton* R_Joystick;
	JoyStickButton* L_Joystick;
	TriggerButton* R_Trigger;
	TriggerButton* L_Trigger;
	InputButton* A_Button;
	InputButton* B_Button;
	InputButton* Y_Button;
	InputButton* X_Button;
	XBOXController* Controller;
};

