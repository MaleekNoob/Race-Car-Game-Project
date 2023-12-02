#pragma once

class Coin
{
private:
    int value;

public:
    Coin(int value) : value(value) {}
    void setValue(int value) { this->value = value; }
    int getValue() const { return value; }
};

class Trophy
{
private:
    int value;

public:
    Trophy(int value) : value(value) {}
    void setValue(int value) { this->value = value; }
    int getValue() const { return value; }
};