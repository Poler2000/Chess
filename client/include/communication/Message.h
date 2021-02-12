#ifndef CHESS_MESSAGE_H
#define CHESS_MESSAGE_H

#include <string>
#include <vector>
#include <variant>
#include <utility>
#include <cereal/archives/json.hpp>
#include <cereal/types/vector.hpp>
#include <cereal/types/utility.hpp>
#include <cereal/types/variant.hpp>
#include <cereal/types/string.hpp>

namespace comm {
    struct Message {
        std::string type;
        std::vector<std::pair<std::string, std::variant<std::string, int>>> content;

        explicit Message(std::string type) : type(std::move(type)){}

        template<class T>
        void addField(std::string label, T arg) {
                    content.template emplace_back(std::make_pair(std::move(label), arg));
        }

        template <class Archive>
        void serialize(Archive& ar) {
            ar(type, content);
        }

        [[nodiscard]] std::string getType() const {
            return type;
        }

    };
}

#endif //CHESS_MESSAGE_H
