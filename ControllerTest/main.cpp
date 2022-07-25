#include <SFML/Graphics.hpp>
#include "XBOXController.h"
#include "ControllerGUI.h"
#include "sfml-gui.hpp"

XBOXController* Controller;
ControllerGUI* ControlGUI;
int main(int argc, char* argv[])
{
    //GUI Init
    Controller = new XBOXController(1);
    sf::RenderWindow window(sf::VideoMode(1280, 720), "Controller Vibration Tester");
    gui NewGui("Controller Vibration Tester", sf::Vector2f(530, 100), sf::Vector2f(670, 200), sf::Color(41, 39, 39, 128), sf::Color(217, 126, 95), sf::Color(46, 45, 46));
    CheckBox checkBox(NewGui.getGUIColor(), "Enable Vibration", sf::Color(255, 255, 255));
    text Text(NewGui.getGUI(), "Welcome to the Vibration Tester!", sf::Color(255, 255, 255), window);
    SliderInt RightMotorSlider(NewGui.getGUIColor(), sf::Color(255, 255, 255), 400, "Right Motor");
    SliderInt LeftMotorSlider(NewGui.getGUIColor(), sf::Color(255, 255, 255), 400, "Left Motor");
    bool checkBoxFlag = false;
    bool testBoolean;
    int RightValue;
    int LeftValue;

    //Controller GUI init
    ControlGUI = new ControllerGUI();

    

    while (window.isOpen())
    {
        
        if (checkBox.isChecked()) {      
            if (Controller->IsConnected())
                Controller->Vibrate(RightValue, LeftValue);
        }
        else
            Controller->Vibrate(0, 0);  

        ControlGUI->UpdateButton();

        sf::Event event;
        while (window.pollEvent(event))
            if (event.type == sf::Event::Closed)
                window.close();
        window.clear(sf::Color(33, 32, 32));
        ControlGUI->Draw(window);
        NewGui.UPDATE_GUI(window);
        NewGui.DRAW_GUI(window);
        Text.Draw(window, 1, NewGui.getGUI());
        checkBox.Draw(window, 2, NewGui.getGUI(), testBoolean);
        RightMotorSlider.Draw(window, 3, NewGui.getGUI(), RightValue, 0, 65535);
        LeftMotorSlider.Draw(window, 4, NewGui.getGUI(), LeftValue, 0, 65535);
        

        window.display();
    }
    return 0;
}