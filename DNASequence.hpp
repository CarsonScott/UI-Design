#ifndef DNASEQUENCE_HPP_INCLUDED
#define DNASEQUENCE_HPP_INCLUDED

struct Box
{
    sf::Vector2f size;
    sf::Vector2f position;
    sf::Color color;
    int saved_values;
    Box()
    {
        size = sf::Vector2f(0, 0);
        position = sf::Vector2f(0, 0);
        color = sf::Color(0, 0, 0);
        saved_values = 8;
    }
};

struct Interface
{
    std::vector<Box> boxes;
};

class DNASequence
{
public:
    std::string get_sequence(std::vector<std::string> strings)
    {
        std::string sequence = "";
        for(int i = 0; i < strings.size(); i++)
        {
            sequence += strings[i];
            sequence += " ";
        }

        sequence += "\n";
        return sequence;
    }

    std::vector<std::string> to_strings(Box box)
    {
        std::vector<std::string> values;

        values.push_back(to_string(box.size.x));
        values.push_back(to_string(box.size.y));

        values.push_back(to_string(box.position.x));
        values.push_back(to_string(box.position.y));

        values.push_back(to_string(box.color.r));
        values.push_back(to_string(box.color.g));
        values.push_back(to_string(box.color.b));
        values.push_back(to_string(box.color.a));

        return values;
    }

    std::string to_string(float number)
    {
        std::stringstream ss(std::stringstream::in | std::stringstream::out);
        ss << number;
        return ss.str();
    }

    std::string create(Interface interface)
    {
        std::string sequence = "";
        for(int i = 0; i < interface.boxes.size(); i++)
        {
            std::string box_sequence = get_sequence(to_strings(interface.boxes[i]));
            sequence += box_sequence;
        }
        return sequence;
    }

    void save(std::ofstream& file, std::string sequence)
    {
        file << sequence;
    }

    std::string load(std::ifstream& file)
    {
        std::string sequence;
        std::getline(file, sequence);
        return sequence;
    }
};

#endif // DNASEQUENCE_HPP_INCLUDED
