#ifndef _JUMP_
#define _JUMP_

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <vector>
#include"stdlib.h"


class game;

/*
@class representing the character
*/
class character
{
    friend game;

private:
    static constexpr float window_height = 100.f;
    static constexpr float window_width = 450.f;
    static constexpr float size = window_height / 6;
    static constexpr float T = 1.f;
    static constexpr float T_star = 1.1;
    static constexpr float start_position = window_height;
    bool jumping = false;
    float position;
    sf::Clock timer;
    sf::RectangleShape bottom;
    sf::RectangleShape top;


public:
    /**
    default constructor
    */
    character()noexcept;

    /*
    draw character
    @param window to draw
    */
    void display(sf::RenderWindow& const) const;

    /*
    describe h(t)
    @return float height of character
    */
    float path() const;

    /*
    called by Game to update position
    */
    void update_position();

    /*
    restart the timer when UP pressed
    */
    void restart_timer();

    /*
    change moving state
    */
    void jump();

    /*
    check if moving
    @return bool, true if moving, false otherwise
    */
    bool moving() const;


};
/**
@class representing an enemy
*/
class enemy : public sf::RectangleShape {

public:
    /**
    default constructor
    */
    enemy() noexcept;

    /**
    function to update the position of the enemy
    */
    void update_position();


private:
    static constexpr float window_height = 100.f;
    static constexpr float window_width = 450.f;
    static constexpr float size = window_height / 6;
    constexpr static float step_length = 2;
    float x_min = window_width;
    constexpr static float y_min = window_height * 2 / 3;
    constexpr static int time_between_moves = 10;

    sf::Clock timer;
};


/**
@class to run the game
*/
class game
{
private:
    static constexpr int time_between_enemy = 1500;
    std::vector<enemy> enemyList;
    size_t score = 0;
    size_t life = 3;
    sf::Clock enemy_clock;
    character* c;

public:

    /**
    @Default constructor of game class
    @param c: the player
    */
    game(character* c) noexcept;

    /**
    @remove any enemies that are out of the window
    */
    void do_removal();

    /**
    Check if the player has been hit by an enemy and remove the enemy if they were hit
    @return if the player has been hit
    */
    bool check_hits() const;

    /**
    @Function to move the enemy
    */
    void move_enemies();

    /**
    @Function to possibly add more enemies
    */
    void make_enemies(int make);

    /**
    functions to check if the user has pressed anything worth nothing
    @param window: the window of the game
    @return bool game is not over
    */
    bool manage_events(sf::RenderWindow& window);

    /**
    @Function print out the status of the character
    @return a string of status
    */
    std::string scoreDisplay() const;

};


#endif // !_JUMP_
