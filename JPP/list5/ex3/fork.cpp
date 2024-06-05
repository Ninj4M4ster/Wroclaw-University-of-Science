#include "fork.hpp"

Fork::IsClean() {
    return is_clean_;
}

Fork::ChangeState(bool clean) {
    is_clean_ = clean;
}