#include "logic/MoveValidator.h"

namespace logic {
    MoveValidator::MoveValidator(std::vector<std::shared_ptr<structure::Field>>& fields)
        : fields(fields) {}

    std::vector<int> MoveValidator::getPossibleFieldIds(const structure::Figure &figure) {
        std::vector<int> results;
        
        return results;
    }

}

