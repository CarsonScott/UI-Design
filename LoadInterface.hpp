#ifndef LOADINTERFACE_HPP_INCLUDED
#define LOADINTERFACE_HPP_INCLUDED

class LoadInterface
{
public:
    std::vector<std::string>* seperate_values(std::string sequence)
    {
        std::vector<std::string>* values = new std::vector<std::string>;
        std::string value;
        for(int i = 0; i < sequence.size(); i++)
        {
            if(sequence[i] != ' ')
            {
                value += sequence[i];
            }
            else
            {
                values->push_back(value);
                value = "";
            }
        }
        return values;
    }

    Interface* load(std::ifstream& file)
    {
        std::vector<std::string> lines;
        std::string line;

        while(std::getline(file, line))
        {
            lines.push_back(line);
        }

        Interface* interface = new Interface();
        for(int i = 0; i < lines.size(); i++)
        {
            std::vector<std::string>* values = seperate_values(lines[i]);

            Box box;
            bool done = false;
            for(int j = 0; j < values->size(); j++)
            {
                double d_val = strtod(values->at(j).c_str(), NULL);
                float val = float(d_val);

                switch(j)
                {
                case 0:
                    box.size.x = val;
                    break;
                case 1:
                    box.size.y = val;
                    break;
                case 2:
                    box.position.x = val;
                case 3:
                    box.position.y = val;
                    break;
                case 4:
                    box.color.r = val;
                    break;
                case 5:
                    box.color.g = val;
                    break;
                case 6:
                    box.color.b = val;
                    break;
                case 7:
                    box.color.a = val;
                    interface->boxes.push_back(box);
                    break;
                }
            }
        }
        return interface;
    }

    Interface* load(std::vector<std::string> lines)
    {
        Interface* interface = new Interface();
        for(int i = 0; i < lines.size(); i++)
        {
            std::vector<std::string>* values = seperate_values(lines[i]);

            Box box;
            bool done = false;
            for(int j = 0; j < values->size(); j++)
            {
                double d_val = strtod(values->at(j).c_str(), NULL);
                float val = float(d_val);

                switch(j)
                {
                case 0:
                    box.size.x = val;
                    break;
                case 1:
                    box.size.y = val;
                    break;
                case 2:
                    box.position.x = val;
                case 3:
                    box.position.y = val;
                    break;
                case 4:
                    box.color.r = val;
                    break;
                case 5:
                    box.color.g = val;
                    break;
                case 6:
                    box.color.b = val;
                    break;
                case 7:
                    box.color.a = val;
                    interface->boxes.push_back(box);
                    break;
                }
            }
        }
        return interface;
    }
};

#endif // LOADINTERFACE_HPP_INCLUDED
