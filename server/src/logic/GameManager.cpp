#include "logic/GameManager.h"
#include "communication/CommException.h"
#include <iostream>
#include <communication/Message.h>
#include <map>

namespace logic {
    constexpr uint64_t mix(char m, uint64_t s) {
        return ((s<<7) + ~(s>>3)) + ~m;
    }

    constexpr uint64_t hash(const char * m) {
        return (*m) ? mix(*m,hash(m+1)) : 0;
    }
    
    
    GameManager::GameManager()
        : m_communicationCentre(new comm::CommunicationCentre(this)) {}

    GameManager::~GameManager() = default;

    void GameManager::init() {
        try {
            m_communicationCentre->init();
            std::thread t(&GameManager::monitorMessages, this);
            t.detach();
            m_communicationCentre->startListening(s_maxClients);
        }
        catch (comm::CommException& ex) {
            std::cout << ex.what() << '\n';
        }

    }

    void GameManager::createNewGame(const int clientFd) {
        gmMutex.lock();
        m_games.emplace_back(Game());
        m_games.back().init();

        comm::Message msg("ReconnectMsg");
        msg.addField("port", m_games.back().getPort());
        m_communicationCentre->send(msg, clientFd);
        m_communicationCentre->closeConnection(clientFd);
        gmMutex.unlock();
    }

    void GameManager::run() {
        while(true) {


        }
    }

    void GameManager::processMessage(const comm::Message& msg, const int clientFd) {
        switch(hash(msg.getType().c_str())) {
            case hash("RegisterMsg"):
                prepareAndSendListOfGames(clientFd);
                break;
            case hash("CreateGameMsg"):
                createNewGame(clientFd);
                break;
            case hash("JoinGameMsg"):
                if(msg.hasField("gameId")){
                    addClientToGame(msg.getInt("gameId"), clientFd);
                }
                break;
            case hash("SpectateGameMsg"):
                if(msg.hasField("gameId")){
                    addAsSpectator(msg.getInt("gameId"), clientFd);
                }
                break;
            default:
                std::cout << "Incorrect message type\n";
                break;
        }
    }

    void GameManager::addClientToGame(const int gameId, const int clientFd) {
        gmMutex.lock();
        auto g = getGameById(gameId);
        if(g.canAddClient()) {
            comm::Message msg("reconnectMsg");
            msg.addField("port", g.getPort());
            m_communicationCentre->send(msg, clientFd);
        }
        gmMutex.unlock();
    }


    void GameManager::addAsSpectator(const int gameId, const int clientFd) {
        auto g = getGameById(gameId);
        comm::Message msg("reconnectMsg");
        msg.addField("port", g.getPort());
        m_communicationCentre->send(msg, clientFd);
    }

    // TODO what if no game matches?
    Game& GameManager::getGameById(const uint32_t id) {
        auto k = std::find_if(m_games.begin(), m_games.end(),
                              [=](const Game & g) -> bool { return g.getId() == id; });
        return *k;
    }

    void GameManager::prepareAndSendListOfGames(const int fd) {
        comm::Message msg("GameListMsg");
        std::for_each(m_games.begin(), m_games.end(), [&](const Game& game){
            msg.addField("id", game.getId());
        });
        m_communicationCentre->send(msg, fd);
    }

    void GameManager::monitorMessages() {
        while (true) {
            if (!m_msgQueue.empty()) {
                std::cout << "MessageToprocess: " << m_msgQueue.front().first.getType() << '\n';
                processMessage(m_msgQueue.front().first, m_msgQueue.front().second);
                m_msgQueue.pop();
            }
        }
    }

    void GameManager::addMessageToQueue(const comm::Message &msg, const int clientFd) {
        m_msgQueue.push(std::make_pair(msg, clientFd));
    }


}