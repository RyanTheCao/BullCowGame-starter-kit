
#pragma once

#include "CoreMinimal.h"
#include "Console/Cartridge.h"
#include "BullCowCartridge.generated.h"

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))

class BULLCOWGAME_API UBullCowCartridge : public UCartridge
{
	GENERATED_BODY()

	public:
	virtual void BeginPlay() override;
	virtual void OnInput(const FString& input) override;
	void setupGame();
	void processGuess(const FString& guess);
	void endGame();
	bool isIsogram(const FString& word) const;
	TArray<FString> getValidWords(const TArray<FString>& wordList) const;
	void getBullCows(const FString& guess, int32& bullCount, int32& cowCount) const;
	
	private:
	FString hiddenWord;
	int32 lives;
	bool bGameOver;
	TArray<FString> isograms;
};