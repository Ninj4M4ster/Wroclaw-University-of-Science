#include <iostream>
#include <future>
#include <memory>

class Fork {
    bool is_clean_ = false;
public:
    bool IsClean();
    void ChangeState(bool clean);
};