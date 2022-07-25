#include <SFML/Graphics.hpp>
#include <string>
#include <sstream>

#include "sfml-gui-text.hpp"
#include "sfml-gui-checkbox.hpp"
#include "sfml-gui-slider.hpp"
#include "sfml-gui-button.hpp"
#include "sfml-gui-listbox.hpp"

class gui
{
public:

	gui(std::string WINDOW_TITLE, sf::Vector2f GUI_SIZE, sf::Vector2f GUI_POSITION, sf::Color GUI_BACKGROUND_COLOR,
		sf::Color TOP_BAR_COLOR, sf::Color TEXT_COLOR)
	{
		GUI_BACKGROUND.setSize(GUI_SIZE);
		GUI_BACKGROUND.setFillColor(GUI_BACKGROUND_COLOR);
		GUI_BACKGROUND.setPosition(GUI_POSITION);
		GUI_BACKGROUND.setOrigin(GUI_BACKGROUND.getSize() / 2.0f);
		TOP_BAR.setPosition(sf::Vector2f(GUI_BACKGROUND.getGlobalBounds().left, GUI_BACKGROUND.getGlobalBounds().top));
		TOP_BAR.setOrigin(TOP_BAR.getSize() / 2.0f);
		TOP_BAR.setFillColor(TOP_BAR_COLOR);
		TOP_BAR.setSize(sf::Vector2f(GUI_BACKGROUND.getSize().x, 20.0f));

		//TEXT
		//WINDOW_TEXT.setColor(sf::Color(0, 0, 0));
		WINDOW_TEXT.setString(WINDOW_TITLE);
		font.loadFromFile("fonts/cour.ttf");
		WINDOW_TEXT.setFont(font);
		WINDOW_TEXT.setFillColor(TEXT_COLOR);
		WINDOW_TEXT.setCharacterSize(13);
		WINDOW_TEXT.setPosition(sf::Vector2f(GUI_BACKGROUND.getGlobalBounds().left + 8.0f, GUI_BACKGROUND.getGlobalBounds().top + 2.0f));



	}

	sf::RectangleShape getGUI()
	{
		return GUI_BACKGROUND;
	}
	sf::RectangleShape getGUIColor()
	{
		return TOP_BAR;
	}

	void DRAW_GUI(sf::RenderWindow& window)
	{
		window.draw(GUI_BACKGROUND);
		window.draw(TOP_BAR);
		window.draw(WINDOW_TEXT);
	}

	void UPDATE_GUI(sf::RenderWindow& window)
	{
		if(window.hasFocus()) // Checks if the window has focus to prevent moving the gui while not focused
		{
			// If gui isn't selected it checks for left clicks
			// If gui is selected it checks for when you let go of lmb
			switch(isSelected)
			{
				case false:
					if(sf::Mouse::isButtonPressed(sf::Mouse::Left))
					{
						if (sf::Mouse::getPosition(window).x >= TOP_BAR.getPosition().x &&
							sf::Mouse::getPosition(window).x <= TOP_BAR.getPosition().x + TOP_BAR.getSize().x &&
							sf::Mouse::getPosition(window).y >= TOP_BAR.getPosition().y &&
							sf::Mouse::getPosition(window).y <= TOP_BAR.getPosition().y + TOP_BAR.getSize().y)
						{
							isSelected = true;
							mouseOffSetX = sf::Mouse::getPosition(window).x - GUI_BACKGROUND.getPosition().x;
						}
					}
					break;
				case true:
					if(!sf::Mouse::isButtonPressed(sf::Mouse::Left))
					{
						isSelected = false;
					}
					break;
			}

			// If gui is selected it updates it's position
			switch(isSelected)
			{
				case true:
				GUI_BACKGROUND.setPosition((sf::Mouse::getPosition(window).x
											+ GUI_BACKGROUND.getSize().x
											/ sf::Mouse::getPosition(window).x) - mouseOffSetX,
											sf::Mouse::getPosition(window).y
											+ GUI_BACKGROUND.getSize().y
											/ 2.0f - 10.0f);
											
				TOP_BAR.setPosition(sf::Vector2f(GUI_BACKGROUND.getGlobalBounds().left, GUI_BACKGROUND.getGlobalBounds().top));
				WINDOW_TEXT.setPosition(sf::Vector2f(GUI_BACKGROUND.getGlobalBounds().left + 8.0f, GUI_BACKGROUND.getGlobalBounds().top + 2.0f));
					break;
				default:
					break;
			}
		}

	}


public:
	//void Text(std::string TEXT, sf::Color TEXT_COLOR, sf::RenderWindow& window, int slot)
	//{
	//	text guiTEXT(GUI_BACKGROUND, slot, TEXT, TEXT_COLOR, window);
	//}

	
private:
	
	sf::RectangleShape GUI_BACKGROUND;
	sf::RectangleShape TOP_BAR;
	sf::Text WINDOW_TEXT;
	sf::Font font;
	int ELEMENT_COUNT = 0;
	bool flag = true;
	
	bool isSelected = false; // Whether the gui is selected
	float mouseOffSetX = 0.0f; // X offset relative to the mouse
	//bool slots[5] = {false, false, false, false, false};

	struct GUI_IDS {
		sf::RectangleShape GUI_PID;
		sf::RectangleShape TOP_BAR;
	};


};
