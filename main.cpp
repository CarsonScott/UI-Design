#include <iostream>
#include <ctime>
#include <cmath>
#include <cstdlib>
#include <sstream>
#include <cstdio>
#include <fstream>
#include <SFML/Graphics.hpp>

#include "DNASequence.hpp"
#include "CreateChild.hpp"
#include "LoadInterface.hpp"

class RandomInterface
{
public:
    Interface* create(sf::Vector2i screen_size)
    {
        Interface* interface = new Interface();
        int box_limit = rand()% 300 + 10;
        int box_count = rand()% box_limit + 50;

        sf::Vector2i size_limit;
        size_limit.x = rand()% screen_size.x + 10;
        size_limit.y = rand()% screen_size.y + 10;

        sf::Color color_limit(rand()%255+5, rand()%255+5, rand()%255+5, rand()%255+5);

        for(int i = 0; i < box_count; i++)
        {
            Box* box = new Box();
            box->size.x = rand()% size_limit.x*0.25 + 10;
            box->size.y = rand()% size_limit.y*0.25 + 10;

            box->position.x = rand()% screen_size.x - 25;
            box->position.y = rand()% screen_size.y - 25;

            box->color = sf::Color(rand()%color_limit.r+5, rand()%color_limit.g+5, rand()%color_limit.b+5, rand()%color_limit.a+5);
            interface->boxes.push_back(*box);
        }

        return interface;
    }
};

class Game
{
    sf::RectangleShape* get_rect(Box box)
    {
        sf::RectangleShape* rect = new sf::RectangleShape();
        rect->setSize(box.size);
        rect->setFillColor(box.color);
        rect->setPosition(box.position);

        return rect;
    }

    std::string to_string(float number)
    {
        std::stringstream ss(std::stringstream::in | std::stringstream::out);
        ss << number;
        return ss.str();
    }
public:
    void main(sf::RenderWindow& window)
    {
        Interface* interface = NULL;
        bool random_interface = true;
        if(random_interface)
        {
            RandomInterface randInterface;
            interface = randInterface.create(sf::Vector2i(window.getSize()));
        }
        else
        {
            LoadInterface loadInterface;

            std::ifstream file;
            file.open("log3.txt");
            interface = loadInterface.load(file);
            file.close();
        }

        std::vector<sf::RectangleShape> rects;
        for(int i = 0; i < interface->boxes.size(); i++)
        {
            sf::RectangleShape* rect = get_rect(interface->boxes[i]);

            int ot = rand()% int(int(rect->getFillColor().a + 5)/5);
            rect->setOutlineThickness(ot);

            sf::Color oc(rand()%rect->getFillColor().r+5, rand()%rect->getFillColor().g+5, rand()%rect->getFillColor().b+5, rand()%rect->getFillColor().a+5);
            rect->setOutlineColor(oc);
            rects.push_back(*rect);
        }

        float time_limit = 1;
        float time = 0;

        sf::Clock clock;
        bool done = false;
        bool take_screenshot = true;

        sf::Color bg = sf::Color(0, 0, 0);

        while (window.isOpen())
        {
            float dt = clock.restart().asSeconds();
            time += dt;
            if(time >= time_limit)
            {
                done = true;
            }

            sf::Event event;
            while (window.pollEvent(event))
            {
                if (event.type == sf::Event::Closed)
                {
                    done = true;
                }
            }

            if(done)
            {
                std::string random_file = to_string(rects.size()) + "_" + to_string(rand()%100) + to_string(rand()%100) + to_string(rand()%100);

                std::string log_file = "DNA/" + random_file + ".txt";
                std::ofstream log;
                log.open(log_file.c_str());

                DNASequence dna;
                std::string sequence = dna.create(*interface);
                dna.save(log, sequence);

                log.close();

                std::ofstream ids;
                ids.open("ids.txt", std::ios::app);
                ids << random_file << "\n";
                ids.close();

                if(take_screenshot)
                {
                    sf::Image image = window.capture();
                    image.saveToFile("images/" + random_file + ".png");
                }

                window.close();
            }

            window.clear(bg);
            for(int i = 0; i < rects.size(); i++)
            {
                window.draw(rects[i]);
            }
            window.display();
        }
    }
};

int main()
{
    srand(time(NULL));
    for(int i = 0; i < 75; i++)
    {
        if(rand()% 10 < 5)
        {
            srand(time(NULL));
        }
        sf::RenderWindow window(sf::VideoMode::getDesktopMode(), "UI Design");
        Game().main(window);
    }
    return 0;
}
