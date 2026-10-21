#include <string>
#include <iostream>
#include <map>
#include <limits>
#include <sstream>

/**
 * Checks that every character of s1 maps to a single character of s2, in that direction only.
 * Several characters of s1 may map to the same character of s2; isOneToOneMapping runs this
 * check both ways to rule that out. Returns false for strings of unequal length, empty strings,
 * and strings where either one contains a space character (other whitespace is accepted).
*/
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
 * Checks if two strings are one-to-one mapped, by requiring checkMapping to hold from s1 to s2
 * and from s2 back to s1. Inherits checkMapping's rejections, so strings of unequal length,
 * empty strings, and strings containing a space are never reported as mapped.
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
 * Returns true only when the first non-whitespace character is 'y', so leading spaces and
 * empty lines are skipped; reaching end of input counts as no.
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

void runTestSuccessSwappedCharacters() {
    std::string testName = "runTestSuccessSwappedCharacters()";
    // prepare
    // each character maps onto the other, so the mapping is its own inverse
    std::string s1 = "ab";
    std::string s2 = "ba";

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

void runTestSuccessLongString() {
    std::string testName = "runTestSuccessLongString()";
    // prepare
    std::string s1 = "abcdefghijklmnopqrstuvwxyz";
    std::string s2 = "zyxwvutsrqponmlkjihgfedcba";

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

void runTestFailureLongStringLastCharacter() {
    std::string testName = "runTestFailureLongStringLastCharacter()";
    // prepare
    // every character maps consistently until the last one, where 'a' would map to 'b' instead of 'z'
    std::string s1 = "abcdefghijklmnopqrstuvwxyza";
    std::string s2 = "zyxwvutsrqponmlkjihgfedcbab";

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

void runTestSuccessMultibyteCharacterComparedByByte() {
    std::string testName = "runTestSuccessMultibyteCharacterComparedByByte()";
    // prepare
    // "\xC3\xA9" is the single character 'é' in UTF-8, stored as two bytes; characters are
    // compared one byte at a time, so it is treated as two characters mapping onto "ab"
    std::string s1 = "\xC3\xA9";
    std::string s2 = "ab";

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

void runTestCheckMappingForwardConflict() {
    std::string testName = "runTestCheckMappingForwardConflict()";
    // prepare
    // 'o' would have to map to both 'a' and 'r', so the forward check alone rejects it
    std::string s1 = "foo";
    std::string s2 = "bar";

    // execute
    bool result = checkMapping(s1, s2);

    // assert
    if (!result) {
        std::cout << testName << " passed with strings: " << s1 << " and " << s2 << std::endl;
    }
    else {
        std::cout << testName << " failed with strings: " << s1 << " and " << s2 << std::endl;
    }
}

void runTestCheckMappingAllowsManyToOne() {
    std::string testName = "runTestCheckMappingAllowsManyToOne()";
    // prepare
    // 'a' and 'r' both map to 'o'; the one-directional helper accepts that, which is
    // why isOneToOneMapping also runs it in reverse
    std::string s1 = "bar";
    std::string s2 = "foo";

    // execute
    bool result = checkMapping(s1, s2);

    // assert
    if (result) {
        std::cout << testName << " passed with strings: " << s1 << " and " << s2 << std::endl;
    }
    else {
        std::cout << testName << " failed with strings: " << s1 << " and " << s2 << std::endl;
    }
}

void runTestCheckMappingSpaceInSecondString() {
    std::string testName = "runTestCheckMappingSpaceInSecondString()";
    // prepare
    // only the second string contains a space; without the space rule the forward mapping would hold
    std::string s1 = "abc";
    std::string s2 = "a c";

    // execute
    bool result = checkMapping(s1, s2);

    // assert
    if (!result) {
        std::cout << testName << " passed with strings: " << s1 << " and " << s2 << std::endl;
    }
    else {
        std::cout << testName << " failed with strings: " << s1 << " and " << s2 << std::endl;
    }
}

void runTestCheckMappingSpaceInFirstString() {
    std::string testName = "runTestCheckMappingSpaceInFirstString()";
    // prepare
    // only the first string contains a space; without the space rule the forward mapping would hold
    std::string s1 = "a c";
    std::string s2 = "abc";

    // execute
    bool result = checkMapping(s1, s2);

    // assert
    if (!result) {
        std::cout << testName << " passed with strings: " << s1 << " and " << s2 << std::endl;
    }
    else {
        std::cout << testName << " failed with strings: " << s1 << " and " << s2 << std::endl;
    }
}

void runTestCheckMappingRejectsEmptyStrings() {
    std::string testName = "runTestCheckMappingRejectsEmptyStrings()";
    // prepare
    // the one-directional helper itself rejects empty input, not only isOneToOneMapping
    std::string s1 = "";
    std::string s2 = "";

    // execute
    bool result = checkMapping(s1, s2);

    // assert
    if (!result) {
        std::cout << testName << " passed with empty strings" << std::endl;
    }
    else {
        std::cout << testName << " failed with empty strings" << std::endl;
    }
}

void runTestCheckMappingRejectsDifferentLength() {
    std::string testName = "runTestCheckMappingRejectsDifferentLength()";
    // prepare
    // every character of s1 maps consistently onto a prefix of s2, so only the length rule rejects it
    std::string s1 = "abc";
    std::string s2 = "abcd";

    // execute
    bool result = checkMapping(s1, s2);

    // assert
    if (!result) {
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

void runTestReadInputStringWithoutTrailingNewline() {
    std::string testName = "runTestReadInputStringWithoutTrailingNewline()";
    // prepare
    // the second string is the last thing in the input, with no closing newline
    std::istringstream input("abg\nbcd");

    // execute
    std::string s1 = readInputString(input);
    std::string s2 = readInputString(input);

    // assert
    if (s1 == "abg" && s2 == "bcd") {
        std::cout << testName << " passed with strings: " << s1 << " and " << s2 << std::endl;
    }
    else {
        std::cout << testName << " failed with strings: " << s1 << " and " << s2 << std::endl;
    }
}

void runTestReadInputStringAtEndOfInput() {
    std::string testName = "runTestReadInputStringAtEndOfInput()";
    // prepare
    // input ends after the first string, so the second read finds nothing
    std::istringstream input("abg\n");

    // execute
    std::string s1 = readInputString(input);
    std::string s2 = readInputString(input);
    bool result = isOneToOneMapping(s1, s2);

    // assert
    // the missing string reads as empty, so the round is reported as not one-to-one mapped
    if (s1 == "abg" && s2.empty() && !result) {
        std::cout << testName << " passed with strings: " << s1 << " and end of input" << std::endl;
    }
    else {
        std::cout << testName << " failed with strings: " << s1 << " and end of input" << std::endl;
    }
}

void runTestReadInputStringKeepsCarriageReturn() {
    std::string testName = "runTestReadInputStringKeepsCarriageReturn()";
    // prepare
    // both lines end in "\r\n"; std::getline stops at '\n' only, so each string keeps its '\r'
    std::istringstream input("abg\r\nbcd\r\n");

    // execute
    std::string s1 = readInputString(input);
    std::string s2 = readInputString(input);
    bool result = isOneToOneMapping(s1, s2);

    // assert
    // the '\r' sits at the same position in both strings and maps onto itself, so the result still holds
    if (s1 == "abg\r" && s2 == "bcd\r" && result) {
        std::cout << testName << " passed with strings: abg\\r and bcd\\r" << std::endl;
    }
    else {
        std::cout << testName << " failed with strings: abg\\r and bcd\\r" << std::endl;
    }
}

void runTestReadInputStringMixedLineEndings() {
    std::string testName = "runTestReadInputStringMixedLineEndings()";
    // prepare
    // only the first line ends in "\r\n", so only the first string keeps a trailing '\r'
    std::istringstream input("abg\r\nbcd\n");

    // execute
    std::string s1 = readInputString(input);
    std::string s2 = readInputString(input);
    bool result = isOneToOneMapping(s1, s2);

    // assert
    // the kept '\r' makes the strings unequal in length, so the round is reported as not one-to-one mapped
    if (s1 == "abg\r" && s2 == "bcd" && !result) {
        std::cout << testName << " passed with strings: abg\\r and bcd" << std::endl;
    }
    else {
        std::cout << testName << " failed with strings: abg\\r and bcd" << std::endl;
    }
}

void runTestReadInputStringBlankLines() {
    std::string testName = "runTestReadInputStringBlankLines()";
    // prepare
    // pressing Enter alone at both string prompts, before more input follows
    std::istringstream input("\n\nabg\n");

    // execute
    std::string s1 = readInputString(input);
    std::string s2 = readInputString(input);
    bool result = isOneToOneMapping(s1, s2);

    // assert
    // a blank line is read as an empty string rather than skipped, so the round is rejected by the empty-string rule
    if (s1.empty() && s2.empty() && !result) {
        std::cout << testName << " passed with two blank lines" << std::endl;
    }
    else {
        std::cout << testName << " failed with two blank lines" << std::endl;
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

void runTestReadRunAnotherAnswerDiscardsRestOfLine() {
    std::string testName = "runTestReadRunAnotherAnswerDiscardsRestOfLine()";
    // prepare
    // a "yes" answer followed by the first string, which must not start with the leftover "es"
    std::istringstream input("yes\nabg\n");

    // execute
    bool answer = readRunAnotherAnswer(input);
    std::string s1 = readInputString(input);

    // assert
    if (answer && s1 == "abg") {
        std::cout << testName << " passed with answer: yes and string: " << s1 << std::endl;
    }
    else {
        std::cout << testName << " failed with answer: yes and string: " << s1 << std::endl;
    }
}

void runTestReadRunAnotherAnswerUppercaseIsNo() {
    std::string testName = "runTestReadRunAnotherAnswerUppercaseIsNo()";
    // prepare
    // only a lowercase 'y' counts as yes
    std::istringstream input("Y\n");

    // execute
    bool answer = readRunAnotherAnswer(input);

    // assert
    if (!answer) {
        std::cout << testName << " passed with answer: Y" << std::endl;
    }
    else {
        std::cout << testName << " failed with answer: Y" << std::endl;
    }
}

void runTestReadRunAnotherAnswerSkipsBlankLines() {
    std::string testName = "runTestReadRunAnotherAnswerSkipsBlankLines()";
    // prepare
    // an empty line is not an answer; the read skips it and the leading spaces before the 'y'
    std::istringstream input("\n  y\nabg\n");

    // execute
    bool answer = readRunAnotherAnswer(input);
    std::string s1 = readInputString(input);

    // assert
    if (answer && s1 == "abg") {
        std::cout << testName << " passed with answer: blank line then y and string: " << s1 << std::endl;
    }
    else {
        std::cout << testName << " failed with answer: blank line then y and string: " << s1 << std::endl;
    }
}

void runTestReadRunAnotherAnswerNIsNo() {
    std::string testName = "runTestReadRunAnotherAnswerNIsNo()";
    // prepare
    std::istringstream input("n\n");

    // execute
    bool answer = readRunAnotherAnswer(input);

    // assert
    if (!answer) {
        std::cout << testName << " passed with answer: n" << std::endl;
    }
    else {
        std::cout << testName << " failed with answer: n" << std::endl;
    }
}

void runTestReadRunAnotherAnswerOnlyFirstCharacterCounts() {
    std::string testName = "runTestReadRunAnotherAnswerOnlyFirstCharacterCounts()";
    // prepare
    // the 'y' after the leading 'n' is discarded with the rest of the line, so it is not an answer
    std::istringstream input("ny\n");

    // execute
    bool answer = readRunAnotherAnswer(input);

    // assert
    if (!answer) {
        std::cout << testName << " passed with answer: ny" << std::endl;
    }
    else {
        std::cout << testName << " failed with answer: ny" << std::endl;
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
    runTestSuccessSwappedCharacters();
    runTestSuccessLongString();
    runTestFailureLongStringLastCharacter();
    runTestSuccessMultibyteCharacterComparedByByte();
    runTestCheckMappingForwardConflict();
    runTestCheckMappingAllowsManyToOne();
    runTestCheckMappingSpaceInSecondString();
    runTestCheckMappingSpaceInFirstString();
    runTestCheckMappingRejectsEmptyStrings();
    runTestCheckMappingRejectsDifferentLength();
    runTestReadInputStringKeepsSpaces();
    runTestReadInputStringWithoutTrailingNewline();
    runTestReadInputStringAtEndOfInput();
    runTestReadInputStringKeepsCarriageReturn();
    runTestReadInputStringMixedLineEndings();
    runTestReadInputStringBlankLines();
    runTestReadRunAnotherAnswerStopsAtEndOfInput();
    runTestReadRunAnotherAnswerDiscardsRestOfLine();
    runTestReadRunAnotherAnswerUppercaseIsNo();
    runTestReadRunAnotherAnswerSkipsBlankLines();
    runTestReadRunAnotherAnswerNIsNo();
    runTestReadRunAnotherAnswerOnlyFirstCharacterCounts();

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