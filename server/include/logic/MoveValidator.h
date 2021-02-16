#ifndef CHESS_MOVEVALIDATOR_H
#define CHESS_MOVEVALIDATOR_H

#include "structure/Field.h"
#include "structure/Figure.h"
#include <vector>
#include <memory>

namespace logic {
    class MoveValidator {
    public:
        explicit MoveValidator(std::vector<std::shared_ptr<structure::Field>>& );
        std::vector<int> getPossibleFieldIds(const structure::Figure& figure);
    private:
        std::vector<std::shared_ptr<structure::Field>> fields;
    };
}

#endif //CHESS_MOVEVALIDATOR_H
