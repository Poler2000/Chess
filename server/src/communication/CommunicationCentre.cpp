#include "communication/CommunicationCentre.h"
#include "communication/CommException.h"

namespace comm {

    CommunicationCentre::CommunicationCentre() {

    }

    void CommunicationCentre::init() noexcept(false) {
        if ((serverFd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
            throw new CommException("Unable to create file descriptor");
        }

        if (setsockopt(serverFd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT,
                       &m_option, sizeof(m_option))) {
            throw new CommException("Unable to set socket options");
        }
        m_address.sin_family = AF_INET;
        m_address.sin_addr.s_addr = INADDR_ANY;
        m_address.sin_port = htons(m_port);

        if (bind(serverFd, (struct sockaddr *)&m_address,
                 sizeof(m_address))<0) {
            throw new CommException("Unable to bind socket to port");
        }

    }
}
