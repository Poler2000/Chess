#ifndef CHESS_COMMEXCEPTION_H
#define CHESS_COMMEXCEPTION_H

#include <exception>
#include <string>
#include <utility>

namespace comm {
    class CommException : public std::exception {
    public:
        CommException(std::string msg) : m_msg(std::move(msg)) {}

        [[nodiscard]] const char* what() const noexcept override {
            return m_msg.c_str();
        }

        const std::string m_msg;
    };
}

#endif //CHESS_COMMEXCEPTION_H
