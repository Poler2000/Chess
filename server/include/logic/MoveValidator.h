#ifndef CHESS_MOVEVALIDATOR_H
#define CHESS_MOVEVALIDATOR_H

#include "structure/Field.h"
#include "structure/Figure.h"
#include "structure/Move.h"
#include <vector>
#include <memory>

namespace logic {
    class MoveValidator {
    public:
        explicit MoveValidator(std::vector<std::shared_ptr<structure::Field>>& );
        bool isValid(structure::Move move) const;
    private:
        std::vector<std::shared_ptr<structure::Field>> fields;
    };
}

#endif //CHESS_MOVEVALIDATOR_H
