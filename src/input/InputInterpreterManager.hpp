#ifndef INPUT_INTERPRETER_MANAGER_HPP
#define INPUT_INTERPRETER_MANAGER_HPP

#include "InputInterpreter.hpp"
#include <vector>
#include <memory>

class InputInterpreterManager {
public:
    static InputInterpreterManager& getInstance();

    std::shared_ptr<InputInterpreter> getInterpreter(int playerIndex);
    const std::vector<std::shared_ptr<InputInterpreter>> getInterpreters() const;

private:
    InputInterpreterManager();
    ~InputInterpreterManager();
    InputInterpreterManager(const InputInterpreterManager&) = delete;
    InputInterpreterManager& operator=(const InputInterpreterManager&) = delete;
    
    std::vector<std::shared_ptr<InputInterpreter>> interpreters;
};

#endif // INPUT_INTERPRETER_MANAGER_HPP