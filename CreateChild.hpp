#ifndef CREATECHILD_HPP_INCLUDED
#define CREATECHILD_HPP_INCLUDED

class CreateChild
{
public:
    Interface* create(Interface& a, Interface& b)
    {
        Interface* interface = new Interface();
        int midpoint = floor(a.boxes.size()/2);
        for(int i = 0; i < midpoint; i++)
        {
            interface->boxes.push_back(a.boxes[i]);
        }

        midpoint = floor(b.boxes.size()/2);
        for(int i = 0; i < midpoint; i++)
        {
            interface->boxes.push_back(b.boxes[i]);
        }

        return interface;
    }
};

#endif // CREATECHILD_HPP_INCLUDED
