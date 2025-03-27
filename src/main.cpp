// dxlAPRS_encrypt - dxlAPRS extension for RS41-SGM report

// Copyright (C) Jean-Michael Grobel (DO2JMG) <do2jmg@wettersonde.net>

// Released under GNU GPL v3 or later

#include <iostream>
#include <fstream>
#include <cstring>
#include <unistd.h>
#include <sstream>
#include <vector>
#include <curl/curl.h>

using namespace std;

struct app_config {
  string filename;
  string callsign;
};

app_config config;

bool fileExists(const string& filename) {
    std::ifstream file(filename.c_str());
    return file.good();
};

bool fileRemove(const string& filename) {
  if (remove(config.filename.c_str()) == 0) {
    return true;
  } else {
    return false;
  }
};

bool sendHttp(string url) {
      // Initialize libcurl
    CURL* curl = curl_easy_init();
    
    if (curl) {
        curl_easy_setopt(curl, CURLOPT_URL, url.c_str());

        CURLcode res = curl_easy_perform(curl);

        if (res != CURLE_OK) {
            cerr << "Error: " << curl_easy_strerror(res) << endl;
            return false;
        } else {
            cout << "HTTP GET request successful." << endl;
            return true;
        }

        curl_easy_cleanup(curl);
    } else {
        cerr << "Failed to initialize libcurl." << endl;
        return false;
    }
}

int main(int argc, char** argv) {

  for (int i = 0; i<argc; i++) {
    if (strcmp(argv[i],"-f") == 0) { // encrypt file
      if(i+1 < argc) {
        config.filename = argv[i+1];
      } else {
        cout << "Error : Filename" << endl;
      }
    } 
    if (strcmp(argv[i],"-c") == 0) { // callsign
      if(i+1 < argc) {
        config.callsign = argv[i+1];
      } else {
        cout << "Error : Callsign" << endl;
      }
    } 
  }

  if (config.filename.length() == 0) return 0;
  if (config.callsign.length() == 0) return 0;

  if (fileExists(config.filename)) {
    ifstream inputFile(config.filename);

    if (inputFile.is_open()) {
      string line;
      while (getline(inputFile, line)) {
        istringstream iss(line);
        vector<string> tokens;

        string token;
        while (iss >> token) {
            tokens.push_back(token);
        }

        cout << "Serial : " << tokens[0] << endl;
        cout << "Frequency : " << tokens[1] << endl;

        string out = "http://api.wettersonde.net/encrypt.php?serial=" + tokens[0] + "&frequency=" + tokens[1] + "&callsign=" + config.callsign;

        if (sendHttp(out)) {
          cout << "Send true " << endl;
        }
      }
      inputFile.close();  // Close the file when done.
      fileRemove(config.filename);
    } else {
      cout << "Unable to open the file." << endl;
    }
  }


  return 0;
         
}
