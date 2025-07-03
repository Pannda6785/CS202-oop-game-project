#ifndef PRIESTESS_HPP
#define PRIESTESS_HPP

#include "../Character.hpp"

#include <string>
#include <array>

class Priestess : public Character {
public:
    Priestess();

    void init() override;
    void update(float dt, InputBufferer* input) override;

};

#endif // PRIESTESS_HPP
