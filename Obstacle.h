// Sumeed_Jawad_Kanwar_22i2651
// Maleek_Hussain_Ali_22i1526

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