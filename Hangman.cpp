#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <random>
#include <regex>
using namespace std;


bool fetchGuess(std::istream& kB, const std::string& specWord, std::vector<char>& pG) {
    std::cout << "Please enter a letter of your choice:" << std::endl;
    std::string guess;
    std::getline(kB, guess);
    pG.push_back(guess[0]);

    return (specWord.find(guess) != std::string::npos);
}



bool WordStatus(const std::string& specWord, const std::vector<char>& pG) {
    int validCnt = 0;
    for (size_t i = 0; i < specWord.length(); i++) {
        if (std::find(pG.begin(), pG.end(), specWord[i]) != pG.end()) {
            std::cout << specWord[i];
            validCnt++;
        } else {
            std::cout << "_";
        }
    }
    std::cout << std::endl;

    return (specWord.length() == validCnt);
}



void HangedMan(int wrongCnT) {
    std::cout << " -------" << std::endl;
    std::cout << " |     |" << std::endl;

    if (wrongCnT >= 1) {
        std::cout << " O" << std::endl;
    }

    if (wrongCnT >= 2) {
        std::cout << "\\ ";
        if (wrongCnT >= 3) {
            std::cout << "/" << std::endl;
        }
        else {
            std::cout << " " << std::endl;
        }
    }

    if (wrongCnT >= 4) {
        std::cout << " |" << std::endl;
    }

    if (wrongCnT >= 5) {
        std::cout << "/ ";
        if (wrongCnT >= 6) {
            std::cout << "\\" << std::endl;
        }
        else {
            std::cout << " " << std::endl;
        }
    }

    std::cout << std::endl;
    std::cout << std::endl;
}



int main() {
    std::ifstream fetch("/Users/display/CLionProjects/HangerMan/words_alpha.txt");
    std::istream& kB = std::cin;

    std::vector<std::string> words;
    std::string line;
    while (std::getline(fetch, line)) {
        line = std::regex_replace(line, std::regex("^\\s+|\\s+$"), "");
        if (!line.empty()) {
            words.push_back(line);
        }
    }

    fetch.close();


    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(0, words.size() - 1);
    std::string specWord = words[dis(gen)];

    std::cout << specWord << std::endl;

    std::vector<char> pG;

    int wrongCnT = 0;
    while (true) {
        HangedMan(wrongCnT);

        if (wrongCnT >= 6) {
            std::cout << "You suck bud! Try Again! :P" << std::endl;
            break;
        }

        WordStatus(specWord, pG);

        if (!fetchGuess(kB, specWord, pG)) {
            wrongCnT++;
        }

        if (WordStatus(specWord, pG)) {
            std::cout << "You win!" << std::endl;
            break;
        }

        std::cout << "Please enter guess for the entire word:" << std::endl;
        std::string input;
        std::getline(kB, input);

        if (input == specWord) {
            std::cout << "You win!" << std::endl;
            break;
        } else {
            std::cout << "User Error! Try again!" << std::endl;
        }
    }
    return 0;
}

