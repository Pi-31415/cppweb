#include "crow_all.h"
using namespace std;
using namespace crow;

// This function returns any file as response based on url
void sendFile(response &res, string filename, string contentType) {
  ifstream in("../public/" + filename, ifstream::in);
  if (in) {
    ostringstream contents;
    contents << in.rdbuf();
    in.close(); // Close the file
    res.set_header("Content-Type", contentType);
    // Take the contents of the html file and send them out
    // res.write(contents.str());
    res.write("<h1>Successful</h1>");
  } else {
    res.code = 404;
    res.write("Not found");
  }
  res.end();
}

// Helper files for server response
void sendHTML(response &res, string filename) {
  sendFile(res, filename + ".html", "text/html");
}

void sendImage(response &res, string filename) {
  sendFile(res, "images/" + filename, "image/jpeg");
}

void sendScript(response &res, string filename) {
  sendFile(res, "scripts/" + filename, "text/javascript");
}

void sendStyle(response &res, string filename) {
  sendFile(res, "styles/" + filename, "text/css");
}

// Main server code
int main(int argc, char *argv[]) {
  // Create a new crow app variable
  crow::SimpleApp app;

  // App Routing here

  // Other routes for other filetypes
  CROW_ROUTE(app, "/styles/<string>")
  ([](const request &req, response &res, string filename) {
    // Read an external web page, and if successful, display it on "/" path
    sendStyle(res, filename);
  });

  CROW_ROUTE(app, "/scripts/<string>")
  ([](const request &req, response &res, string filename) {
    // Read an external web page, and if successful, display it on "/" path
    sendScript(res, filename);
  });

  CROW_ROUTE(app, "/images/<string>")
  ([](const request &req, response &res, string filename) {
    // Read an external web page, and if successful, display it on "/" path
    sendImage(res, filename);
  });

  // Create main route
  CROW_ROUTE(app, "/")
  ([](const request &req, response &res) {
    // Read an external web page, and if successful, display it on "/" path
    sendHTML(res, "index");
  });

  // Get the port from environment variable
  char *port = getenv("PORT");

  // Cast the port to int if not null, if not, return the default port of 18080
  uint16_t iPort = static_cast<uint16_t>(port != NULL ? stoi(port) : 18080);
  cout << "PORT = " << iPort << "\n";

  //   Create the app and get everything running
  //   Run in multithreaded mode
  app.port(iPort).multithreaded().run();
}