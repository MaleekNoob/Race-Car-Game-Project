#pragma once

class Obstacle
{
    private:
        string type;

    public:
        Obstacle()
        {
            type = "Obstacle";
        }

        Obstacle(string t)
        {
            type = t;
        }

        void setType(string t)
        {
            type = t;
        }

        string getType()
        {
            return type;
        }
};