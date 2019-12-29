#include <cstring>

#include "gamefactory.h"
#include "iostream"

void usage() {
  std::cout << R"(Usage: ctetris -c -d <display> -i <input>
Where:
    -c: colored flag for console display (false by default)
    -d:
        console (default)
    -i:
        keyboard (default))"
            << std::endl;
}

int main(int argc, char *argv[]) {
  GameFactory::Settings settings;

  for (int i = 1; i != argc; ++i) {
    if (std::strcmp(argv[i], "-d") == 0) {
      settings.display = argv[++i];
    } else if (std::strcmp(argv[i], "-i") == 0) {
      settings.input = argv[++i];
    } else if (std::strcmp(argv[i], "-c") == 0) {
      settings.console_colored = true;
    } else {
      std::cout << "Wrong arguments\n";
      usage();
      return 1;
    }
  }

  auto game = GameFactory::makeGame(settings);
  game.loop();

  return 0;
}
