/**
 * Jakub Drzewiecki
 * 268418
 * Bot client class.
 */

#include "BotClient.hpp"

namespace bot_client {

/**
 * Constructor. Validates given arguments and creates
 * connection with server on given ip and port.
 *
 * @param ip_address Ip address of the server.
 * @param port Port of the server.
 * @param player_number Player number, either 1 or 2.
 * @param depth Depth of the algorithm. Valid numbers are between 1 and 10.
 */
BotClient::BotClient(std::string & ip_address, int port, int player_number, int depth) {
  if(player_number < 1 || player_number > 2) {
    throw std::invalid_argument("Player number can equal either 1 or 2.");
  }
  player_number_ = player_number;
  if(depth < 1 || depth > 10) {
    throw std::invalid_argument("Depth has to be between 1 and 10.");
  }
  bot_ = std::make_shared<bot::Bot>(depth, player_number);
  connectToServer(ip_address, port);
}

/**
 * This method connects to the server on given ip address and port.
 *
 * @param ip_address Ip address of the server.
 * @param port Port of the server.
 */
void BotClient::connectToServer(std::string & ip_address, int port) {
  struct sockaddr_in serv_addr{};
  if ((server_file_descriptor_ = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
    throw std::runtime_error("\n Socket creation error/\n");
  }

  serv_addr.sin_family = AF_INET;
  serv_addr.sin_port = htons(port);

  if (inet_pton(AF_INET, ip_address.c_str(), &serv_addr.sin_addr)
      <= 0) {
    throw std::runtime_error("\nInvalid address/Address not supported.\n");
  }

  if(connect(server_file_descriptor_,
              (struct sockaddr*)&serv_addr,
              sizeof(serv_addr)) < 0) {
    throw std::runtime_error("\nConnection Failed.\n");
  }
  std::cout << "Connected to server.\n";

}

/**
 * Destructor. It ends the connection with the server.
 */
BotClient::~BotClient() {
  close(server_file_descriptor_);
}

/**
 * Communication loop. It reads data from server and acts accordingly
 * to the protocol.
 */
void BotClient::startCommunication() {
  while(true) {
    char buffer[1024] = {};
    read(server_file_descriptor_, buffer, 1024);
    std::cout << buffer << std::endl;
    int message = std::atoi(buffer);
    if(isFinalMessage(message)) {
      break;
    }
    std::string answer = createAnswer(message);
    std::cout << "Answer: " << answer << std::endl;
    send(server_file_descriptor_, answer.c_str(), answer.length(), 0);
  }
}

/**
 * This method checks if given message is a final message from the server
 * and no more data will be received.
 *
 * @param message Message received from server.
 * @return If no more messages will be received, true. False otherwise.
 */
bool BotClient::isFinalMessage(int message) {
  // TODO: Send last move to the game bot.
  int first_number = message / 100;
  int pos = message % 100;
  int enemy_player = player_number_ == 1 ? 2 : 1;
  switch(first_number) {
    case 1:
      std::cout << "You won" << std::endl;
      if(pos != 00) {
        bot_->makeMove(pos, enemy_player);
      }
      bot_->printBoard();
      return true;
    case 2:
      std::cout << "You lost" << std::endl;
      if(pos != 00) {
        bot_->makeMove(pos, enemy_player);
      }
      bot_->printBoard();
      return true;
    case 3:
      std::cout << "Draw" << std::endl;
      if(pos != 00) {
        bot_->makeMove(pos, enemy_player);
      }
      bot_->printBoard();
      return true;
    case 4:
      std::cout << "You won, enemy made a mistake" << std::endl;
      if(pos != 00) {
        bot_->makeMove(pos, enemy_player);
      }
      bot_->printBoard();
      return true;
    case 5:
      std::cout << "You lost, you made a mistake" << std::endl;
      if(pos != 00) {
        bot_->makeMove(pos, enemy_player);
      }
      bot_->printBoard();
      return true;
    default:
      return false;
  }
}

/**
 * This method creates an answer for the server.
 * If bot moves, it passes data to the bot.
 *
 * @param message Message received from server.
 * @return Response to server.
 */
std::string BotClient::createAnswer(int message) const {
  int first_number = message / 100;
  int position = message % 100;
  std::string answer;
  if(first_number == 7) {
    answer += (char)(player_number_ + '0');
    answer += "\n";
  }
  else if(first_number == 6 || first_number == 0) {
    int enemy_number = player_number_ == 1 ? 2 : 1;
    int move;
    if(position == 0) {
      move = bot_->findBestMove(player_number_);
      bot_->makeMove(move, player_number_);
    } else {
      bot_->makeMove(position, enemy_number);
      move = bot_->findBestMove(player_number_);
      bot_->makeMove(move, player_number_);
    }
    bot_->printBoard();
    answer += (char)(move / 10 + '0');
    answer += (char)(move % 10 + '0');
    answer += "\n";
  }
  return answer;
}

}  // namespace bot_client
