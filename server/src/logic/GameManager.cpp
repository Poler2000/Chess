#include "logic/GameManager.h"
#include "communication/CommException.h"
#include <iostream>
#include <communication/Message.h>
#include <fstream>
#include <map>

namespace logic {
    constexpr uint64_t mix(char m, uint64_t s)
    {
        return ((s<<7) + ~(s>>3)) + ~m;
    }

    constexpr uint64_t hash(const char * m)
    {
        return (*m) ? mix(*m,hash(m+1)) : 0;
    }
    
    
    GameManager::GameManager()
        : m_communicationCentre(new comm::CommunicationCentre(this)) {}

    GameManager::~GameManager() = default;

    void GameManager::init() {
        try {
            m_communicationCentre->init();
            m_communicationCentre->startListening(s_maxClients);
        }
        catch (comm::CommException& ex) {
            std::cout << ex.what() << '\n';
        }
    }

    void GameManager::createNewGame(const int clientFd) {
        gmMutex.lock();
        m_games.emplace_back(Game());
        comm::Message msg("ReconnectMsg");
        msg.addField("port", m_games.back().getPort());
        gmMutex.unlock();
        m_communicationCentre->send(msg, clientFd);
    }

    void GameManager::run() {
        while(true) {


        }
    }

    void GameManager::processMessage(const std::string& msg, const int clientFd) {
        gmMutex.lock();

        gmMutex.unlock();
    }

    void GameManager::processMessage(const comm::Message& msg, const int clientFd) {
        switch(hash(msg.getType().c_str())) {
            case hash("RegisterMsg"):
                break;
            case hash("CreateGameMsg"):
                break;
            case hash("JoinGameMsg"):
                break;
            case hash("SpectateGameMsg"):
                break;
            case hash("StartGameMsg"):
                break;
            case hash("PieceSelectedMsg"):
                break;
            case hash("MoveMsg"):
                break;
        }
        std::cout << "Received\n";
    }

    void GameManager::addClientToGame(const int gameId, const int clientFd) {
        auto g = getGameById(gameId);
        if(g.canAddClient()) {
            m_communicationCentre->sendPortInfo(g.getPort(), clientFd);
        }
    }


    void GameManager::addAsSpectator(const int gameId, const int clientFd) {
        auto g = getGameById(gameId);
        m_communicationCentre->sendPortInfo(g.getPort(), clientFd);
    }

    // TODO what if no game matches?
    Game& GameManager::getGameById(const uint32_t id) {
        auto k = std::find_if(m_games.begin(), m_games.end(),
                              [=](const Game & g) -> bool { return g.getId() == id; });
        return *k;
    }


}