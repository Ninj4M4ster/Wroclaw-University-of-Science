/**
 * Jakub Drzewiecki
 * 268418
 * Main.
 */

#include "BotClient.cpp"
#include <vector>
#include <memory>

int main(int argc, char* argv[]) {
  std::vector<std::string> arguments(argc - 1);
  if(argc - 1 != 4) {
    std::cout << "Inputted wrong number of arguments";
    return -1;
  }
  for(int i = 1; i < argc; i++) {
    arguments.at(i - 1) = std::string(argv[i]);
  }
  for(std::string & data : arguments) {
    std::cout << data << std::endl;
  }

  std::string ip_address = arguments.at(0);
  int port = std::stoi(arguments.at(1));
  int player_number = std::stoi(arguments.at(2));
  int depth = std::stoi(arguments.at(3));

  std::shared_ptr<bot_client::BotClient> bot_client =
      std::make_shared<bot_client::BotClient>(ip_address, port, player_number, depth);
  bot_client->startCommunication();
}