#include <string>
#include <iostream>
#include <map>
#include <limits>
#include <sstream>

bool checkMapping(const std::string& s1, const std::string& s2) {
    if (s1.length() != s2.length()) {
        return false;
    }
    if (s1.length() == 0) {
        return false;
    }
    if (s1.find(' ') != std::string::npos || s2.find(' ') != std::string::npos) {
        return false;
    }

    std::map<char, char> map;

    for (std::string::size_type i = 0; i < s1.length(); i++) {
        std::map<char, char>::iterator entry = map.find(s1[i]);
        // if the character is not in the map, add it
        if (entry == map.end()) {
            map[s1[i]] = s2[i];
        }
        // if the character is in the map, check if it maps to the same character
        else {
            if (entry->second != s2[i]) {
                return false;
            }
        }
    }
    return true;
}

/**
 * Checks if two strings are one-to-one mapped.
*/
bool isOneToOneMapping(const std::string& s1, const std::string& s2) {
    bool forwardResult = checkMapping(s1, s2);
    if (!forwardResult) {
        return false;
    }

    bool reverseResult = checkMapping(s2, s1);
    if (!reverseResult) {
        return false;
    }
    return true;
}

/**
 * Reads one whole line of input, so that strings containing spaces reach isOneToOneMapping.
*/
std::string readInputString(std::istream& input) {
    std::string line;
    std::getline(input, line);
    return line;
}

/**
 * Reads the answer to the "Run another test?" prompt and discards the rest of its line.
 * Returns true only when the answer starts with 'y'; reaching end of input counts as no.
*/
bool readRunAnotherAnswer(std::istream& input) {
    char c = 'n';
    input >> c;
    // discard the rest of the answer line so the next std::getline starts fresh
    input.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    return c == 'y';
}

void runTestSuccess() {
    std::string testName = "runTestSuccess()";
    // prepare
    std::string s1 = "abg";
    std::string s2 = "bcd";

    // execute
    bool result = isOneToOneMapping(s1, s2);

    // assert
    if (result) {
        std::cout << testName << " passed with strings: " << s1 << " and " << s2 << std::endl;
    }
    else {
        std::cout << testName << " failed with strings: " << s1 << " and " << s2 << std::endl;
    }
}

void runTestFailureFooBar() {
    std::string testName = "runTestFailureFooBar()";
    // prepare
    std::string s1 = "foo";
    std::string s2 = "bar";

    // execute
    bool result = isOneToOneMapping(s1, s2);

    // assert
    if (!result) {
        std::cout << testName << " passed with strings: " << s1 << " and " << s2 << std::endl;
    }
    else {
        std::cout << testName << " failed with strings: " << s1 << " and " << s2 << std::endl;
    }
}

void runTestFailureBarFoo() {
    std::string testName = "runTestFailureBarFoo()";
    // prepare
    std::string s1 = "bar";
    std::string s2 = "foo";

    // execute
    bool result = isOneToOneMapping(s1, s2);

    // assert
    if (!result) {
        std::cout << testName << " passed with strings: " << s1 << " and " << s2 << std::endl;
    }
    else {
        std::cout << testName << " failed with strings: " << s1 << " and " << s2 << std::endl;
    }
}

void runTestFailureEmptyString() {
    std::string testName = "runTestFailureEmptyString()";
    // prepare
    std::string s1 = "";
    std::string s2 = "";

    // execute
    bool result = isOneToOneMapping(s1, s2);

    // assert
    if (!result) {
        std::cout << testName << " passed with empty strings" << std::endl;
    }
    else {
        std::cout << testName << " failed with empty strings" << std::endl;
    }
}

void runTestFailureSpaces() {
    std::string testName = "runTestFailureSpaces()";
    // prepare
    std::string s1 = "a b";
    std::string s2 = "b c";

    // execute
    bool result = isOneToOneMapping(s1, s2);

    // assert
    if (!result) {
        std::cout << testName << " passed with strings: " << s1 << " and " << s2 << std::endl;
    }
    else {
        std::cout << testName << " failed with strings: " << s1 << " and " << s2 << std::endl;
    }
}

void runTestFailureDifferentLength() {
    std::string testName = "runTestFailureDifferentLength()";
    // prepare
    std::string s1 = "abc";
    std::string s2 = "abcd";

    // execute
    bool result = isOneToOneMapping(s1, s2);

    // assert
    if (!result) {
        std::cout << testName << " passed with strings: " << s1 << " and " << s2 << std::endl;
    }
    else {
        std::cout << testName << " failed with strings: " << s1 << " and " << s2 << std::endl;
    }
}

void runTestSuccessSingleCharacter() {
    std::string testName = "runTestSuccessSingleCharacter()";
    // prepare
    std::string s1 = "a";
    std::string s2 = "b";

    // execute
    bool result = isOneToOneMapping(s1, s2);

    // assert
    if (result) {
        std::cout << testName << " passed with strings: " << s1 << " and " << s2 << std::endl;
    }
    else {
        std::cout << testName << " failed with strings: " << s1 << " and " << s2 << std::endl;
    }
}

void runTestSuccessIdenticalStrings() {
    std::string testName = "runTestSuccessIdenticalStrings()";
    // prepare
    std::string s1 = "abc";
    std::string s2 = "abc";

    // execute
    bool result = isOneToOneMapping(s1, s2);

    // assert
    if (result) {
        std::cout << testName << " passed with strings: " << s1 << " and " << s2 << std::endl;
    }
    else {
        std::cout << testName << " failed with strings: " << s1 << " and " << s2 << std::endl;
    }
}

void runTestSuccessRepeatedCharacters() {
    std::string testName = "runTestSuccessRepeatedCharacters()";
    // prepare
    std::string s1 = "aa";
    std::string s2 = "bb";

    // execute
    bool result = isOneToOneMapping(s1, s2);

    // assert
    if (result) {
        std::cout << testName << " passed with strings: " << s1 << " and " << s2 << std::endl;
    }
    else {
        std::cout << testName << " failed with strings: " << s1 << " and " << s2 << std::endl;
    }
}

void runTestSuccessMixedCase() {
    std::string testName = "runTestSuccessMixedCase()";
    // prepare
    // 'a' and 'A' are distinct characters, so they may map to different targets
    std::string s1 = "aA";
    std::string s2 = "bc";

    // execute
    bool result = isOneToOneMapping(s1, s2);

    // assert
    if (result) {
        std::cout << testName << " passed with strings: " << s1 << " and " << s2 << std::endl;
    }
    else {
        std::cout << testName << " failed with strings: " << s1 << " and " << s2 << std::endl;
    }
}

void runTestSuccessTab() {
    std::string testName = "runTestSuccessTab()";
    // prepare
    // only the space character is rejected, so a tab is accepted and mapped like any other character
    std::string s1 = "a\tb";
    std::string s2 = "b\tc";

    // execute
    bool result = isOneToOneMapping(s1, s2);

    // assert
    if (result) {
        std::cout << testName << " passed with strings: " << s1 << " and " << s2 << std::endl;
    }
    else {
        std::cout << testName << " failed with strings: " << s1 << " and " << s2 << std::endl;
    }
}

void runTestReadInputStringKeepsSpaces() {
    std::string testName = "runTestReadInputStringKeepsSpaces()";
    // prepare
    std::istringstream input("a b\nb c\n");

    // execute
    std::string s1 = readInputString(input);
    std::string s2 = readInputString(input);

    // assert
    if (s1 == "a b" && s2 == "b c") {
        std::cout << testName << " passed with strings: " << s1 << " and " << s2 << std::endl;
    }
    else {
        std::cout << testName << " failed with strings: " << s1 << " and " << s2 << std::endl;
    }
}

void runTestReadRunAnotherAnswerStopsAtEndOfInput() {
    std::string testName = "runTestReadRunAnotherAnswerStopsAtEndOfInput()";
    // prepare
    // a "y" answer followed by end of input, with no closing "n"
    std::istringstream input("y\n");

    // execute
    bool first = readRunAnotherAnswer(input);
    bool second = readRunAnotherAnswer(input);

    // assert
    if (first && !second) {
        std::cout << testName << " passed with answers: y and end of input" << std::endl;
    }
    else {
        std::cout << testName << " failed with answers: y and end of input" << std::endl;
    }
}

void runInteractiveTest() {
    // prepare
    std::string s1;
    std::string s2;

    std::cout << "Enter the first string: ";
    s1 = readInputString(std::cin);

    std::cout << "Enter the second string: ";
    s2 = readInputString(std::cin);

    // execute
    bool result = isOneToOneMapping(s1, s2);

    // verify
    if (result) {
        std::cout << "True. The strings are one-to-one mapped." << std::endl;
    }
    else {
        std::cout << "False. The strings are not one-to-one mapped." << std::endl;
    }
}

int main() {
    std::cout << " == One-to-One Mapping Tests == " << std::endl;
    runTestSuccess();
    runTestFailureFooBar();
    runTestFailureBarFoo();
    runTestFailureEmptyString();
    runTestFailureSpaces();
    runTestFailureDifferentLength();
    runTestSuccessSingleCharacter();
    runTestSuccessIdenticalStrings();
    runTestSuccessRepeatedCharacters();
    runTestSuccessMixedCase();
    runTestSuccessTab();
    runTestReadInputStringKeepsSpaces();
    runTestReadRunAnotherAnswerStopsAtEndOfInput();

    std::cout << "\n == Interactive Testing == " << std::endl;
    while (true) {
        std::cout << "Run another test? (y/n): ";
        if (readRunAnotherAnswer(std::cin)) {
            std::cout << std::endl;
            runInteractiveTest();
        }
        else {
            break;
        }
    }
    return 0;
}