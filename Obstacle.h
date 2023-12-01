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

        void setType(string t)
        {
            type = t;
        }

        string getType()
        {
            return type;
        }
};