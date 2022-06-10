
#include<SFML/Graphics.hpp>

int main()
{
	constexpr float window_width = 400.f, window_height = 400.f;// width and height of the window
	constexpr float rad = 150.f; // radius of circle
	constexpr float msg_x = 110.f, msg_y = 165.f; // coordinates of text message 
	constexpr float shape_pos= 200.f; // coordinate of circle

	// window object with given size and name
	sf::RenderWindow window(sf::VideoMode(window_width,window_height), "Hello World");
	
	// circle with given radius
	sf::CircleShape shape(rad);

	shape.setFillColor(sf::Color{ 255, 209, 0 , 255 }); // set fill color of circle 
	shape.setOrigin(rad, rad); // set origin of circle
	shape.setPosition(shape_pos,shape_pos); //set position of circle

	// font object sans
	sf::Font sans;
	if (!sans.loadFromFile("comic.ttf")) { // load the font
		throw std::runtime_error("Font Loading Failed"); // throw error
	}

	// text message object
	sf::Text msg;

	msg.setFont(sans); // set font of message to be the uploaded font
	msg.setFillColor(sf::Color{ 39, 116, 174, 255 }); // set fill color of message
	msg.setCharacterSize(50); // set character size of message 
	msg.setString("PIC 10C"); // set content of message 
	msg.setPosition(msg_x, msg_y); // set coordinates to be given coordinates

	// window is open
	while (window.isOpen())
	{
		sf::Event event; // event object

		// poll event on window
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed) // close the window
				window.close();
		}
		
		window.clear(sf::Color{ 39, 116, 174, 255 }); // clear window with background color
		window.draw(shape); // draw the circle
		window.draw(msg); // draw the message 
		window.display(); // display circle and message
		
	}

	return 0;
}
