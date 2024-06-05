#include "fork.hpp"

bool Fork::IsClean() {
    return is_clean_;
}

void Fork::ChangeState(bool clean) {
    is_clean_ = clean;
}