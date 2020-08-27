
#include "BullCowCartridge.h"
#include "HiddenWordList.h"

// When the game is first played
void UBullCowCartridge::BeginPlay()
{
    Super::BeginPlay();
    isograms = getValidWords(words);
    setupGame();
}

// When the player hits enter
void UBullCowCartridge::OnInput(const FString& playerInput)
{
    ClearScreen();

    if (bGameOver) {
        setupGame();
    }
    else {
        processGuess(playerInput);
    }
}

// Setting up the game (Welcome screen)
void UBullCowCartridge::setupGame()
{
    ClearScreen();

    PrintLine(TEXT("Welcome to Bull Cows!"));

    hiddenWord = isograms[FMath::RandRange(0, isograms.Num() - 1)];
    lives = hiddenWord.Len();
    bGameOver = false;

    PrintLine(TEXT("Guess the %i letter word!"), hiddenWord.Len());
    PrintLine(TEXT("You have %i lives."), lives);
    PrintLine(TEXT("Type in your guess. Press enter to go on."));
}

// Game over
void UBullCowCartridge::endGame() {
    bGameOver = true;
    ClearScreen();
    PrintLine("You won Bulls and Cows!");
    PrintLine(TEXT("The hidden words was: %s"), *hiddenWord);
    PrintLine(TEXT("\nPress enter to play again."));
}

// Checks if guess is correct and loses a life or ends the game
void UBullCowCartridge::processGuess(const FString& guess) {

    if (!isIsogram(guess)) {
        PrintLine(TEXT("No repeating letters, guess again!"));
        PrintLine(TEXT("The hidden word has %i letters."), hiddenWord.Len());
        return;
    }

    if (guess == hiddenWord) {
        endGame();
        return;
    }
    else {
        lives -= 1;
        
        if (lives <= 0) {
            ClearScreen();
            PrintLine("You have no lives left!");
            PrintLine(TEXT("The hidden words was: %s"), *hiddenWord);
            bGameOver = true;
            PrintLine(TEXT("\nPress enter to play again."));
            return;
        } 
        else if (guess.Len() != hiddenWord.Len()) {
            PrintLine(TEXT("The hidden word is %i letters long."), hiddenWord.Len());
            lives += 1;
            PrintLine(TEXT("Try guessing again! You have %i lives left."), lives);
            return;
        }
    }

    PrintLine(TEXT("You lost a life!"));
    int32 bulls, cows;
    getBullCows(guess, bulls, cows);
    PrintLine(TEXT("You have %i Bulls and %i Cows"), bulls, cows);
    PrintLine(TEXT("Guess again, you have %i lives left"), lives);
}

// Checks if any of the letters are the same
bool UBullCowCartridge::isIsogram(const FString& word) const
{
    for (int32 index = 0; index < word.Len(); index++) {
        for (int32 comparison = index + 1; comparison < word.Len(); comparison++) {
            if (word[index] == word[comparison]) {
                return false;
            }
        }
    }

    return true;
}

TArray<FString> UBullCowCartridge::getValidWords(const TArray<FString>& wordList) const {

    TArray<FString> validWords;

    for (FString word : wordList) {
        if (word.Len() >= 4 && isIsogram(word)) {
                validWords.Emplace(word);
        }
    }

    return validWords;
}

void UBullCowCartridge::getBullCows(const FString& guess, int32& bullCount, int32& cowCount) const {
    bullCount = 0;
    cowCount = 0;

    for (int32 guessIndex = 0; guessIndex < guess.Len(); guessIndex++) {
        if (guess[guessIndex] == hiddenWord[guessIndex]) {
            bullCount++;
            continue;
        }

        for (int32 hiddenIndex = 0; hiddenIndex < hiddenWord.Len(); hiddenIndex++) {
            if (guess[guessIndex] == hiddenWord[hiddenIndex]) {
                cowCount++;
                break;
            }
        }
    }
}