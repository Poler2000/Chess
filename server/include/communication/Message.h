#ifndef CHESS_MESSAGE_H
#define CHESS_MESSAGE_H

#include <string>
#include <vector>
#include <variant>
#include <utility>

namespace comm {
    struct Message {
        const std::string type;
        std::vector<std::pair<std::string, std::variant<std::string, int>>> content;

        template<class T>
        void addField(std::string label, T arg) {
            content.template emplace_back(std::make_pair(std::move(label), arg));
        }
    };
}

#endif //CHESS_MESSAGE_H
