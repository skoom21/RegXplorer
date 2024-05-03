
#include <string>
#include <vector>
#include <stack>
#include <iostream>

enum class TokenType
{
    LITERAL,
    DOT,
    CHARACTER_CLASS,
    NEGATED_CHARACTER_CLASS,
    CHARACTER_RANGE,
    STAR,
    PLUS,
    QUESTION_MARK,
    LEFT_BRACKET,
    RIGHT_BRACKET,
    ESCAPED_CHARACTER,
    START_ANCHOR,
    END_ANCHOR,
    WORD_BOUNDARY,
    NON_WORD_BOUNDARY,
    INVALID
};

// Add Token structure for additional constructs
struct Token
{
    TokenType type;
    std::string value; // For literals and character classes
};

// Implement lex function to handle additional constructs
bool allowInvalidEscapeSequences = false;

std::vector<Token> lex(const std::string &pattern)
{
    std::vector<Token> tokens;
    // Implement lexer logic to handle quantifiers, character sets, escaped characters, etc.
    // Iterate through the pattern string and tokenize it
    for (size_t i = 0; i < pattern.size(); i++)
    {
        char currentChar = pattern[i];
        TokenType tokenType;
        std::string tokenValue;

        // Implement logic to identify different token types based on currentChar
        if (currentChar == '.')
        {
            tokenType = TokenType::DOT;
            tokenValue = ".";
        }
        else if (currentChar == '*')
        {
            tokenType = TokenType::STAR;
            tokenValue = "*";
        }
        else if (currentChar == '+')
        {
            tokenType = TokenType::PLUS;
            tokenValue = "+";
        }
        else if (currentChar == '?')
        {
            tokenType = TokenType::QUESTION_MARK;
            tokenValue = "?";
        }
        else if (currentChar == '[')
        {
            // Handle character ranges
            if (i + 1 < pattern.size() && pattern[i + 1] == '-')
            {
                if (i + 2 < pattern.size() && pattern[i + 2] != ']')
                {
                    tokenType = TokenType::CHARACTER_RANGE;
                    tokenValue = "[" + std::string(1, currentChar) + "-" + std::string(1, pattern[i + 2]) + "]";
                    i = i+2; // Skip the next two characters since they have been processed
                }
                else
                {
                    // Handle invalid character range
                    // You can throw an exception or handle it in a way that suits your needs
                    throw std::runtime_error("Invalid character range in the pattern");
                }
            }
            else
            {
                tokenType = TokenType::LEFT_BRACKET;
                tokenValue = "[";
            }
        }
        else if (currentChar == ']')
        {
            tokenType = TokenType::RIGHT_BRACKET;
            tokenValue = "]";
        }
        else if (currentChar == '^')
        {
            tokenType = TokenType::START_ANCHOR;
            tokenValue = "^";
        }
        else if (currentChar == '$')
        {
            tokenType = TokenType::END_ANCHOR;
            tokenValue = "$";
        }
        else if (currentChar == '\\')
        {
            // Handle escaped characters
            if (i + 1 < pattern.size())
            {
                char nextChar = pattern[i + 1];
                switch (nextChar)
                {
                case 'd':
                    tokenType = TokenType::CHARACTER_CLASS;
                    tokenValue = "\\d";
                    break;
                case 'D':
                    tokenType = TokenType::NEGATED_CHARACTER_CLASS;
                    tokenValue = "\\D";
                    break;
                case 'w':
                    tokenType = TokenType::CHARACTER_CLASS;
                    tokenValue = "\\w";
                    break;
                case 'W':
                    tokenType = TokenType::NEGATED_CHARACTER_CLASS;
                    tokenValue = "\\W";
                    break;
                case 's':
                    tokenType = TokenType::CHARACTER_CLASS;
                    tokenValue = "\\s";
                    break;
                case 'S':
                    tokenType = TokenType::NEGATED_CHARACTER_CLASS;
                    tokenValue = "\\S";
                    break;
                default:
                    tokenType = TokenType::ESCAPED_CHARACTER;
                    tokenValue = "\\" + std::string(1, nextChar);
                    break;
                }
                i++; // Skip the next character since it has been processed
            }
            else
            {
                // Handle invalid escape sequence
                // You can throw an exception or handle it in a way that suits your needs
                if (!allowInvalidEscapeSequences)
                {
                    throw std::runtime_error("Invalid escape sequence at the end of the pattern");
                }

                tokenType = TokenType::INVALID;
                tokenValue.clear();
            }
        }
        else
        {
            tokenType = TokenType::LITERAL;
            tokenValue = std::string(1, currentChar);
        }

        // Add the token to the tokens vector
        tokens.push_back({tokenType, tokenValue});
    }

    // Print the tokens
    for (const Token &token : tokens)
    {
        std::cout << token.value << " ";
    }

    return tokens;
}

bool hasHigherPrecedence(Token &op1, const Token &op2)
{
    // Implement the logic to compare the precedence of two tokens
    // Return true if op1 has higher precedence than op2, false otherwise
    if (op1.type == TokenType::STAR || op1.type == TokenType::PLUS || op1.type == TokenType::QUESTION_MARK)
    {
        return true;
    }
    else if (op1.type == TokenType::LEFT_BRACKET && (op2.type == TokenType::STAR || op2.type == TokenType::PLUS || op2.type == TokenType::QUESTION_MARK))
    {
        return true;
    }
    else if ((op1.type == TokenType::START_ANCHOR || op1.type == TokenType::END_ANCHOR) && (op2.type != TokenType::START_ANCHOR && op2.type != TokenType::END_ANCHOR))
    {
        return true;
    }
    else
    {
        return false;
    }
}
// Implement parse function to handle additional constructs
std::vector<Token> parse(const std::vector<Token> &tokens)
{
    std::vector<Token> output;
    std::stack<Token> operatorStack;

    for (const Token &token : tokens)
    {
        switch (token.type)
        {
        case TokenType::LITERAL:
        case TokenType::DOT:
        case TokenType::CHARACTER_CLASS:
        case TokenType::NEGATED_CHARACTER_CLASS:
        case TokenType::CHARACTER_RANGE:
            output.push_back(token);
            break;
        case TokenType::STAR:
        case TokenType::PLUS:
        case TokenType::QUESTION_MARK:
        case TokenType::LEFT_BRACKET:
        case TokenType::RIGHT_BRACKET:
        case TokenType::START_ANCHOR:
        case TokenType::END_ANCHOR:
        case TokenType::WORD_BOUNDARY:
        case TokenType::NON_WORD_BOUNDARY:
            while (!operatorStack.empty() && hasHigherPrecedence(operatorStack.top(), token))
            {
                output.push_back(operatorStack.top());
                operatorStack.pop();
            }
            operatorStack.push(token);
            break;
        default:
            // Handle invalid token type
            break;
        }
    }

    while (!operatorStack.empty())
    {
        output.push_back(operatorStack.top());
        operatorStack.pop();
    }
    // print the output
    for (const Token &token : output)
    {
        std::cout << token.value << " ";
    }

    return output;
}

bool isCharacterInClass(char c, const std::string &characterClass)
{
    return characterClass.find(c) != std::string::npos;
}
bool isWordCharacter(char c)
{
    // Word characters include alphabets (lowercase and uppercase), digits, and underscore
    // Check if the character is an alphabet (lowercase or uppercase)
    if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
    {
        return true;
    }

    // Check if the character is a digit
    if (c >= '0' && c <= '9')
    {
        return true;
    }

    // Check if the character is an underscore
    if (c == '_')
    {
        return true;
    }

    // If none of the above conditions are met, it's not a word character
    return false;
}

void storeMatch(std::vector<std::string> &matches, const std::string &text)
{
    // Store the matched text
    matches.push_back(text);
}

bool match(const std::string &text, const std::vector<Token> &tokens, std::vector<std::string> &matches, size_t textIndex = 0, size_t tokenIndex = 0)
{
    // Debug statement for current text index and token index
    std::cout << "Processing text index: " << textIndex << ", token index: " << tokenIndex << std::endl;

    // Base case: if text is exhausted, return true if all tokens are matched
    if (textIndex == text.size())
    {
        std::cout << "Text is exhausted." << std::endl;
        return tokenIndex == tokens.size();
    }

    // Base case: if tokens are exhausted but text is not, return false
    if (tokenIndex == tokens.size())
    {
        std::cout << "Tokens are exhausted." << std::endl;
        return false;
    }

    // Get the current token
    const Token &token = tokens[tokenIndex];

    // Debug statement for current token type and value
    std::cout << "Processing token: " << token.value << std::endl;

    // Match the current token based on its type
    switch (token.type)
    {
    // Handle literal characters
    case TokenType::LITERAL:   
        if (text.substr(textIndex, token.value.size()) == token.value)
        {
            std::cout << "Matched literal: " << token.value << std::endl;
            storeMatch(matches, token.value);
            return match(text, tokens, matches, textIndex + token.value.size(), tokenIndex + 1);
        }
        std::cout << "Literal mismatch." << std::endl;
        return match(text, tokens, matches, textIndex, tokenIndex + 1);

    // Handle dot wildcard character
    case TokenType::DOT:
        std::cout << "Matched dot." << std::endl;
        storeMatch(matches, text.substr(textIndex, 1));
        return match(text, tokens, matches, textIndex + 1, tokenIndex + 1);

    // Handle character classes
    case TokenType::CHARACTER_CLASS:
        if (isCharacterInClass(text[textIndex], token.value))
        {
            std::cout << "Matched character class." << std::endl;
            storeMatch(matches, text.substr(textIndex, 1));
            return match(text, tokens, matches, textIndex + 1, tokenIndex + 1);
        }
        std::cout << "Character class mismatch." << std::endl;
        return false;

    // Handle negated character classes
    case TokenType::NEGATED_CHARACTER_CLASS:
        if (!isCharacterInClass(text[textIndex], token.value))
        {
            std::cout << "Matched negated character class." << std::endl;
            storeMatch(matches, text.substr(textIndex, 1));
            return match(text, tokens, matches, textIndex + 1, tokenIndex + 1);
        }
        std::cout << "Negated character class mismatch." << std::endl;
        return false;

    // Handle character ranges
    case TokenType::CHARACTER_RANGE:
        if (text[textIndex] >= token.value[0] && text[textIndex] <= token.value[2])
        {
            std::cout << "Matched character range." << std::endl;
            storeMatch(matches, text.substr(textIndex, 1));
            return match(text, tokens, matches, textIndex + 1, tokenIndex + 1);
        }
        std::cout << "Character range mismatch." << std::endl;
        return false;

    // Handle zero or more quantifier (*)
    case TokenType::STAR:
    {
        std::cout << "Processing zero or more quantifier (*)." << std::endl;
        // Match zero occurrences of the current token
        if (match(text, tokens, matches, textIndex, tokenIndex + 1))
        {
            return true;
        }
        // Match one or more occurrences of the current token
        while (textIndex < text.size() && (token.value.empty() || text.substr(textIndex, token.value.size()) == token.value))
        {
            std::cout << "Matched zero or more occurrences of the current token." << std::endl;
            storeMatch(matches, text.substr(textIndex, 1));
            if (match(text, tokens, matches, textIndex + 1, tokenIndex + 1))
            {
                ++textIndex;
            }
            else
            {
                break;
            }
        }
        return false;
    }

    // Handle one or more quantifier (+)
    case TokenType::PLUS:
    {
        std::cout << "Processing one or more quantifier (+)." << std::endl;
        if (match(text, tokens, matches, textIndex, tokenIndex + 1))
        {
            return true;
        }
        if (text.substr(textIndex, token.value.size()) == token.value)
        {
            std::cout << "Matched one or more occurrences of the current token." << std::endl;
            storeMatch(matches, text.substr(textIndex, 1));
            return match(text, tokens, matches, textIndex + 1, tokenIndex);
        }
        return false;
    }

    // Handle zero or one quantifier (?)
    case TokenType::QUESTION_MARK:
    {
        std::cout << "Processing zero or one quantifier (?)." << std::endl;
        if (match(text, tokens, matches, textIndex, tokenIndex + 1))
        {
            return true;
        }
        if (text.substr(textIndex, token.value.size()) == token.value)
        {
            std::cout << "Matched zero or one occurrence of the current token." << std::endl;
            storeMatch(matches, text.substr(textIndex, 1));
            return match(text, tokens, matches, textIndex + 1, tokenIndex + 1);
        }
        return false;
    }

    // Handle left bracket for grouping
    case TokenType::LEFT_BRACKET:
    {
        std::cout << "Processing left bracket for grouping." << std::endl;
        bool result = match(text, tokens, matches, textIndex, tokenIndex + 1);
        if (result && textIndex < text.size())
        {
            storeMatch(matches, text.substr(textIndex, 1));
            return match(text, tokens, matches, textIndex + 1, tokenIndex + 1);
        }
        return result;
    }

    // Handle right bracket for grouping
    case TokenType::RIGHT_BRACKET:
        std::cout << "Processing right bracket for grouping." << std::endl;
        storeMatch(matches, text.substr(textIndex, 1));
        return match(text, tokens, matches, textIndex, tokenIndex + 1);

    // Handle start anchor (^)
    case TokenType::START_ANCHOR:
        if (textIndex == 0)
        {
            std::cout << "Processing start anchor (^)." << std::endl;
            storeMatch(matches, text.substr(textIndex, 1));
            return match(text, tokens, matches, textIndex, tokenIndex + 1);
        }
        return false;

    // Handle end anchor ($)
    case TokenType::END_ANCHOR:
        std::cout << "Processing end anchor ($)." << std::endl;
        if (textIndex == text.size())
        {
            return match(text, tokens, matches, textIndex, tokenIndex + 1);
        }
        return false;

    // Handle word boundary (\b)
    case TokenType::WORD_BOUNDARY:
        std::cout << "Processing word boundary (\\b)." << std::endl;
        if ((textIndex == 0 || !isWordCharacter(text[textIndex - 1])) && (textIndex == text.size() || !isWordCharacter(text[textIndex])))
        {
            storeMatch(matches, text.substr(textIndex, 1));
            return match(text, tokens, matches, textIndex, tokenIndex + 1);
        }
        return false;

    // Handle non-word boundary (\B)
    case TokenType::NON_WORD_BOUNDARY:
        std::cout << "Processing non-word boundary (\\B)." << std::endl;
        if ((textIndex > 0 && isWordCharacter(text[textIndex - 1])) || (textIndex < text.size() && isWordCharacter(text[textIndex])))
        {
            storeMatch(matches, text.substr(textIndex, 1));
            return match(text, tokens, matches, textIndex, tokenIndex + 1);
        }
        return false;

    // Handle escaped characters
    case TokenType::ESCAPED_CHARACTER:
        std::cout << "Processing escaped character." << std::endl;
        if (textIndex < text.size() && text[textIndex] == token.value[1])
        {
            storeMatch(matches, text.substr(textIndex, 1));
            return match(text, tokens, matches, textIndex + 1, tokenIndex + 1);
        }
        return false;

    // Handle invalid token types
    case TokenType::INVALID:
        // Implement logic for invalid token type if needed
        std::cout << "Invalid token type." << std::endl;
        return false;
    }

    // Default case: return false
    return match(text, tokens, matches, textIndex + 1, tokenIndex);
}

// Extend RegexSearchEngine class to handle additional constructs
class RegexSearchEngine
{
public:
    RegexSearchEngine(const std::string &pattern) : tokens(parse(lex(pattern))) {}
    bool search(std::string &text)
    {
        match(text, tokens, matches);
        if (matches.empty())
        {
            std::cout << "No matches found" << std::endl;
            return false;
        }
        else
        {
            std::cout << "Matches found:" << std::endl;
            for (const std::string &match : matches)
            {
                std::cout << match << std::endl;
            }
            std::cout << "exit" << std::endl;
            return true;
        }
    }

    std::vector<Token> tokens;
    // Vector to store matches generated by the match func
    std::vector<std::string> matches;
};


int main()
{
    std::string pattern = "R[a-z]*";
    std::string text = "RegExr ";
    RegexSearchEngine engine(pattern);
    engine.search(text);
    return 0;
}