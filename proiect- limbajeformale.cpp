#include <iostream>
#include <fstream>
#include <set>
#include <string>

std::string GetInput();
void BuildLB(std::string input);
void Rezultat(std::set<char> set, std::string type);

int main() {
    std::cout << "Selecteaza optiunea : " << std::endl;
    std::cout << "1. De la tastatura" << std::endl;
    std::cout << "2. De la un fisier" << std::endl;
    std::string input = GetInput();
    BuildLB(input);
}

std::string GetInput() {
    std::string choice;
    std::getline(std::cin, choice);

    while (choice != "1" && choice != "2") {
        std::cout << "Trebuie una dintr-e optiuni !" << std::endl;
        std::getline(std::cin, choice);
    }

    if (choice == "1") {
        std::cout << "inputul : ";
        std::string input;
        std::getline(std::cin, input);
        return input;
    }
    else if (choice == "2") {
        std::ifstream file("Text.txt");
        if (!file) {
            std::cerr << "Nu s-a putut deschide fisierul :)" << std::endl;
            return "";
        }
        std::string fileInput((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
        std::cout << "input :" << fileInput << std::endl;
        return fileInput;
    }
}

void BuildLB(std::string input) {
    std::set<char> terminal;
    std::set<char> nonTerminal;

    if (isupper(input[0])) {
        nonTerminal.insert(input[0]);
    }

    std::cout << input[0] << " -> ";
    for (int i = 1; i < input.length(); i++) {
        if (isupper(input[i])) {
            nonTerminal.insert(input[i]);
            std::cout << input[i];
            continue;
        }

        if (islower(input[i])) {
            terminal.insert(input[i]);
            std::cout << input[i];
            continue;
        }

        switch (input[i]) {
        case '$':
            std::cout << "; " << input[++i] << " -> ";
            nonTerminal.insert(input[i]);
            continue;
        case '@':
            terminal.insert('λ');
            std::cout << "λ";
            continue;
        case '&':
            std::cout << std::endl;
            break;
        default:
            std::cout << input[i];
            break;
        }
    }

    Rezultat(nonTerminal, "VN");
    Rezultat(terminal, "VT");
}

void Rezultat(std::set<char> set, std::string type) {
    std::cout << type << " = {";
    for (auto entry : set)
        std::cout << entry << ", ";
    std::cout << "\b\b}" << std::endl;
}