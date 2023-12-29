#include <iostream>
#include <string>
#include <stdexcept>

class SyntaxAnalyzer {
private:
    std::string input_string;
    char current_token;
    int current_position;

    char getNextToken() {
        if (current_position < input_string.length()) {
            current_token = input_string[current_position];
            current_position++;
            return current_token;
        }
        else {
            return '\0';
        }
    }

    int parseExpression() {
        getNextToken();  // Initialize the current_token
        int result = parseTerm();
        while (current_token == '+' || current_token == '-') {
            char op = current_token;
            getNextToken();
            int term = parseTerm();
            if (op == '+') {
                result += term;
            }
            else if (op == '-') {
                result -= term;
            }
        }
        return result;
    }

    int parseTerm() {
        int result = parseFactor();
        while (current_token == '*' || current_token == '/') {
            char op = current_token;
            getNextToken();
            int factor = parseFactor();
            if (op == '*') {
                result *= factor;
            }
            else {
                result /= factor;
            }
        }
        return result;
    }

    int parseFactor() {
        if (isdigit(current_token)) {
            int value = current_token - '0';
            getNextToken();
            return value;
        }
        else {
            throw std::invalid_argument("Unexpected token: " + std::string(1, current_token));
        }
    }

public:
    SyntaxAnalyzer(const std::string& input_string) : input_string(input_string), current_token('\0'), current_position(0) {}

    void parse() {
        try {
            int result = parseExpression();
            std::cout << "Parsing successful. Result: " << result << std::endl;
        }
        catch (const std::exception& e) {
            std::cout << "Syntax Error: " << e.what() << std::endl;
        }
    }
};

int main() {
    std::string input_string = "1+3";
    SyntaxAnalyzer syntax_analyzer(input_string);
    syntax_analyzer.parse();

    return 0;
}
