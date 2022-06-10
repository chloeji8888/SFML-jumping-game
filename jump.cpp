#include"jump.h"
#include"time.h"

enemy::enemy() noexcept : RectangleShape(sf::Vector2f(size, size)), x_min(window_width), timer()
{
    // set properties of enemy
    setFillColor(sf::Color::Yellow);
    setPosition(x_min, y_min);
    timer.restart();
}

//constexpr float enemy::get_x_min() const { return x_min; }

void enemy::update_position()
{
    if (timer.getElapsedTime().asMilliseconds() >= time_between_moves)
    {	//time to move
        move(sf::Vector2f(-step_length, 0));
        x_min -= step_length;
        timer.restart();
    }
}

character::character() noexcept :position(window_height), top(sf::Vector2f(size, size)), bottom(sf::Vector2f(3 * size, size)) {
    // set color, origin, position
    top.setFillColor(sf::Color::Red);
    bottom.setFillColor(sf::Color::Red);
    top.setOrigin(0, size);
    bottom.setOrigin(0, size);
    top.setPosition(size, window_height - size * 2);
    bottom.setPosition(0, window_height - size);

}

bool character::moving() const {
    return jumping;
}

void character::jump() {
    jumping = true;
}

void character::display(sf::RenderWindow& const w) const {
    // draws character to the window
    w.draw(top);
    w.draw(bottom);
}

float character::path() const {
    float t = timer.getElapsedTime().asSeconds();
    float h = 0.f;
    if (t <= T) {// height positive
        h = 8 * size * t * (T - t) / (T * T);
    }
    return h;

}void character::update_position() {
    float top_pos = 0.f;
    if (timer.getElapsedTime().asSeconds() < T_star) {//moving
        top_pos = window_height - size * 2 - this->path();
        // set position
        top.setPosition(size, top_pos);
        bottom.setPosition(0, top_pos + size);
    }
    else {
        jumping = false; //not jumping
    }
}
void character::restart_timer() {
    timer.restart();
}

void game::do_removal() {
    for (size_t j = 0; j < enemyList.size(); ++j) {//check for each enemy
        sf::FloatRect en_bound = enemyList[j].getGlobalBounds(); 

        //enemy collides with character
        if (check_hits()) {//when enemy hits character, delete it
            enemyList.erase(enemyList.begin() + j);//delete enemy
            --life;
        }
        //enemy's right bound pass the window's left frame
        if ((en_bound.left + en_bound.width) < 0) {//when enemy passes the left boundary, delete it 
            enemyList.erase(enemyList.begin() + j);//delete enemy
            ++score;//score boost
        }
    }
}

bool game::check_hits() const {
    bool hit = false;
    for (size_t j = 0; j < enemyList.size(); ++j) {//check for each enemy
        if (c->bottom.getGlobalBounds().intersects(enemyList[j].getGlobalBounds())) {//a enemy hits
            hit = true;
        }
    }
    return hit;
}

void game::move_enemies() {
    for (enemy& e : enemyList) {//move each enemy
        e.update_position();
    }
}



void game::make_enemies(int make) {
    float second = enemy_clock.getElapsedTime().asMilliseconds();
    if (second >= time_between_enemy) {//time to make enemy
        if (make)
        {   //50% to make enemy
            enemyList.push_back(enemy{});
        }
        enemy_clock.restart();
    }

}

bool game::manage_events(sf::RenderWindow& window)
{
    for (auto& e : enemyList)
    {   //draw each enemy
        window.draw(e);
    }
    if (life > 0)
    {   //the game is not over
        do_removal();
        return true;
    }
    return false;

}

game::game(character* c) noexcept : c(c)
{
    enemy_clock.restart();
}

std::string game::scoreDisplay() const {
    return "Score: " + std::to_string(score);
}
