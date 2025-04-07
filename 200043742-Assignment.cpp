//Mohamed-200043742
#include <iostream>
using namespace std;

enum class TokenType {
    COMMAND, LETTERS, NUM_LITERAL, DECIMAL_LITERAL, 
    PLUS_OP, MINUS_OP, TIMES_OP, DIV_OP, POWER_OP, MOD_OP, ASSIGN_OP,
    INC_OP, DEC_OP, LE_COMPARISON, RE_COMPARISON, 
    L_SQUARE, R_SQUARE, L_CIRCLE, R_CIRCLE, L_CURLY, R_CURLY, SEMICOLON, 
    INVALID
};

struct Token {
    TokenType type;
    string value;
};

bool isCommand(const string& word) {
    return (word == "int" || word == "float" || word == "if" || word == "else" || 
            word == "return" || word == "while" || word == "for" || word == "cin" || 
            word == "cout" || word == "string");
}

const int MAX_TOKENS = 100;

int tokenize(const string& input, Token tokens[], int maxTokens) {
    int count = 0;
    size_t i = 0;

    while (i < input.length() && count < maxTokens) {
        char c = input[i];

        if (isspace(c)) {
            i++;
            continue;
        } else if (isalpha(c)) { 
            string word;
            while (i < input.length() && (isalnum(input[i]) || input[i] == '_')) {
                word += input[i];
                i++;
            }
            tokens[count++] = {isCommand(word) ? TokenType::COMMAND : TokenType::LETTERS, word};
        } else if (isdigit(c)) { 
            string number;
            bool hasDecimal = false;
            while (i < input.length() && (isdigit(input[i]) || (input[i] == '.' && !hasDecimal))) {
                if (input[i] == '.') hasDecimal = true;
                number += input[i];
                i++;
            }
            tokens[count++] = {hasDecimal ? TokenType::DECIMAL_LITERAL : TokenType::NUM_LITERAL, number};
        } else if (c == '+') {
            if (i + 1 < input.length() && input[i + 1] == '+') {
                tokens[count++] = {TokenType::INC_OP, "++"};
                i += 2;
            } else {
                tokens[count++] = {TokenType::PLUS_OP, "+"};
                i++;
            }
        } else if (c == '-') {
            if (i + 1 < input.length() && input[i + 1] == '-') {
                tokens[count++] = {TokenType::DEC_OP, "--"};
                i += 2;
            } else {
                tokens[count++] = {TokenType::MINUS_OP, "-"};
                i++;
            }
        } else if (c == '*') {
            tokens[count++] = {TokenType::TIMES_OP, "*"};
            i++;
        } else if (c == '/') {
            tokens[count++] = {TokenType::DIV_OP, "/"};
            i++;
        } else if (c == '^') {
            tokens[count++] = {TokenType::POWER_OP, "^"};
            i++;
        } else if (c == '%') {
            tokens[count++] = {TokenType::MOD_OP, "%"};
            i++;
        } else if (c == '=') {
            tokens[count++] = {TokenType::ASSIGN_OP, "="};
            i++;
        } else if (c == '<') {
            tokens[count++] = {TokenType::LE_COMPARISON, "<"};
            i++;
        } else if (c == '>') {
            tokens[count++] = {TokenType::RE_COMPARISON, ">"};
            i++;
        } else if (c == '(') {
            tokens[count++] = {TokenType::L_CIRCLE, "("};
            i++;
        } else if (c == ')') {
            tokens[count++] = {TokenType::R_CIRCLE, ")"};
            i++;
        } else if (c == '[') {
            tokens[count++] = {TokenType::L_SQUARE, "["};
            i++;
        } else if (c == ']') {
            tokens[count++] = {TokenType::R_SQUARE, "]"};
            i++;
        } else if (c == '{') {
            tokens[count++] = {TokenType::L_CURLY, "{"};
            i++;
        } else if (c == '}') {
            tokens[count++] = {TokenType::R_CURLY, "}"};
            i++;
        } else if (c == ';') {
            tokens[count++] = {TokenType::SEMICOLON, ";"};
            i++;
        } else {
            tokens[count++] = {TokenType::INVALID, string(1, c)};
            i++;
        }
    }
    return count;
}

void printTokens(const Token tokens[], int count) {
    for (int i = 0; i < count; i++) {
        const Token& token = tokens[i];
        cout << "[ " << token.value << " : ";
        switch (token.type) {
            case TokenType::COMMAND: cout << "COMMAND"; break;
            case TokenType::LETTERS: cout << "LETTERS"; break;
            case TokenType::NUM_LITERAL: cout << "NUM_LITERAL"; break;
            case TokenType::DECIMAL_LITERAL: cout << "DECIMAL_LITERAL"; break;
            case TokenType::PLUS_OP: cout << "PLUS_OP"; break;
            case TokenType::MINUS_OP: cout << "MINUS_OP"; break;
            case TokenType::TIMES_OP: cout << "TIMES_OP"; break;
            case TokenType::DIV_OP: cout << "DIV_OP"; break;
            case TokenType::POWER_OP: cout << "POWER_OP"; break;
            case TokenType::MOD_OP: cout << "MOD_OP"; break;
            case TokenType::ASSIGN_OP: cout << "ASSIGN_OP"; break;
            case TokenType::INC_OP: cout << "INC_OP"; break;
            case TokenType::DEC_OP: cout << "DEC_OP"; break;
            case TokenType::LE_COMPARISON: cout << "LE_COMPARISON"; break;
            case TokenType::RE_COMPARISON: cout << "RE_COMPARISON"; break;
            case TokenType::L_SQUARE: cout << "L_SQUARE"; break;
            case TokenType::R_SQUARE: cout << "R_SQUARE"; break;
            case TokenType::L_CIRCLE: cout << "L_CIRCLE"; break;
            case TokenType::R_CIRCLE: cout << "R_CIRCLE"; break;
            case TokenType::L_CURLY: cout << "L_CURLY"; break;
            case TokenType::R_CURLY: cout << "R_CURLY"; break;
            case TokenType::SEMICOLON: cout << "SEMICOLON"; break;
            case TokenType::INVALID: cout << "INVALID"; break;
        }
        cout << " ]\n";
    }
}

int main() {
    string input;
    while (true) {
        cout << "Enter source code (type 'exit' to quit): ";
        getline(cin, input);
        if (input == "exit") break;
        Token tokens[MAX_TOKENS];
        int count = tokenize(input, tokens, MAX_TOKENS);
        cout << "\nTokens:\n";
        printTokens(tokens, count);
    }
    return 0;
}