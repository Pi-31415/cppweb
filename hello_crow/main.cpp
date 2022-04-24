#include "crow_all.h"
using namespace std;

int main(int argc, char *argv[]) {
  // Create a new crow app variable
  crow::SimpleApp app;

  // Create first route
  CROW_ROUTE(app, "/")
  ([]() { return "<div><h1>Hellow Crow</h1></div>"; });

  // Get the port from environment variable
  char *port = getenv("PORT");

  // Cast the port to int if not null, if not, return the default port of 18080
  uint16_t iPort = static_cast<uint16_t>(port != NULL ? stoi(port) : 18080);
  cout << "PORT = " << iPort << "\n";

  //   Create the app and get everything running
  //   Run in multithreaded mode
  app.port(iPort).multithreaded().run();
}