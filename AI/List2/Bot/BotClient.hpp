/**
 * Jakub Drzewiecki
 * 268418
 * Bot client class.
 */

#ifndef AI_LIST2_BOT_BOTCLIENT_HPP_
#define AI_LIST2_BOT_BOTCLIENT_HPP_

#include <arpa/inet.h>
#include <iostream>
#include <netinet/in.h>
#include <sys/socket.h>
#include <unistd.h>
#include <memory>
#include "Bot.cpp"

namespace bot_client {

class BotClient {
 private:
  int player_number_;
  int server_file_descriptor_{};

  std::shared_ptr<bot::Bot> bot_;

  void connectToServer(std::string & ip_address, int port);
  bool isFinalMessage(int message);
  std::string createAnswer(int message) const;
 public:
  explicit BotClient(std::string & ip_address, int port, int player_number, int depth);
  ~BotClient();

  void startCommunication();
};

}  // namespace bot_client

#endif  // AI_LIST2_BOT_BOTCLIENT_HPP_
