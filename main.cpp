#include "jump.h"
#include <SFML/Graphics.hpp>

int main() {

    constexpr float window_height = 100.f;
    constexpr float window_width = 450.f;
    constexpr float ground_height = window_height / 6;
    constexpr float ground_pos = window_height - ground_height;
    constexpr float text_size = 20.f;

    // window
    sf::RenderWindow window(sf::VideoMode(window_width, window_height), "Jumping Game");
    sf::RectangleShape GroundShape(sf::Vector2f(window_width, ground_height));

    // ground
    GroundShape.setFillColor(sf::Color::White);
    GroundShape.setPosition(0, ground_pos);

    std::srand(time(NULL));

    sf::Font f;
    if (!f.loadFromFile("sansation.ttf")) {//upload the font of the text
        throw std::runtime_error("loading failed");
    }

    sf::Text status(" ", f, text_size);

    sf::Text msg;
    msg.setFont(f);//set the font for the text
    msg.setFillColor(sf::Color::White);
    msg.setCharacterSize(20.f);//set the size of the text
    msg.setString("Press any key to begin. \n Press Up to jump. \n Get hit 3 times and lose.");

    character c;
    game g(&c);

    sf::SoundBuffer buff;
    if (!buff.loadFromFile("jump.wav")) {
        throw std::runtime_error("sound Loading Failed");
    }//load sound file for jump sound
    sf::Sound sound = sf::Sound(buff);//edited by Chloe

    sf::SoundBuffer hit_buff;
    if (!hit_buff.loadFromFile("hit.wav")) {
        throw std::runtime_error("sound Loading Failed");
    }//load sound file for hit sound
    sf::Sound hit_sound(hit_buff);//edited by Chloe

    bool game_start = false;
    bool game_over = false;

    while (window.isOpen()) {//while the window is open
        sf::Event event;

        while (window.pollEvent(event)) {//while poll event
            if (event.type == sf::Event::Closed) {//if the type ic close
                window.close();//close the window
            }

            if (((event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Up) && game_start) && !game_over) {//when up key is pressed
                if (!c.moving()) {// character is not jumping
                    c.jump();
                    c.restart_timer();//restart timer
                    sound.play();//jump sound play
                }
            }
            if (event.type == sf::Event::KeyPressed) {//if any key is pressed. game starts
                game_start = true;
            }
        }

        if (c.moving()) {//check if c is moving
            c.update_position(); //jump
        }

        window.clear(sf::Color::Black);//backgroud is black
        c.display(window);//display
        window.draw(GroundShape);//display the ground

        if (game_start)
        {   //if game started
            if (!game_over)
            {   //if game is not over
                g.make_enemies(std::rand() % 2);
                g.move_enemies();
                if (g.check_hits()) {//if is enemy hit
                    hit_sound.play();//hitsound will play
                }
            }
            game_over = !g.manage_events(window);//return false if anything happend
            status.setString(g.scoreDisplay() + ((game_over) ? "\tGame Over" : ""));
            window.draw(status);//display the status of the player

        }
        else
        {
            window.draw(msg);//draw the text
        }

        window.display();//display
    }
    return 0;
}
