#ifndef INPUT_INTERPRETER_MANAGER_HPP
#define INPUT_INTERPRETER_MANAGER_HPP

#include "InputInterpreter.hpp"
#include <vector>
#include <memory>

class InputInterpreterManager {
public:
    static InputInterpreterManager& getInstance();
    
    InputInterpreter* getInterpreter(int playerIndex);
    std::vector<const InputInterpreter*> getInterpreters() const;

private:
    InputInterpreterManager();
    ~InputInterpreterManager();
    InputInterpreterManager(const InputInterpreterManager&) = delete;
    InputInterpreterManager& operator=(const InputInterpreterManager&) = delete;
    
    std::vector<std::unique_ptr<InputInterpreter>> interpreters;
};

#endif // INPUT_INTERPRETER_MANAGER_HPP