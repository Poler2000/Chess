#include "logic/MoveValidator.h"

namespace logic {
    MoveValidator::MoveValidator(std::vector<std::shared_ptr<structure::Field>>& fields)
        : fields(fields) {}

    bool MoveValidator::isValid(structure::Move move) const {
        return true;
    }
}

