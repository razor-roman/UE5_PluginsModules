// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SavingsManager.generated.h"

class USaveGame;
class UTestSaveGame;
/**
 * 
 */
USTRUCT()
struct FExportedSaveGame
{
	GENERATED_BODY()
	UPROPERTY()
	int32 Level;
	FExportedSaveGame() : Level(-1)
	{
		SaveGame=nullptr;
	}
	UPROPERTY()
	UTestSaveGame* SaveGame;
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnGameFromSlotAction, const FString&,SotName);
UCLASS()
class PLUGINSMODULES_API USavingsManager : public UObject
{
	GENERATED_BODY()
public:	
	UFUNCTION(BlueprintCallable)
	bool DoesSaveGameExist(const FString& SlotName);
	UFUNCTION(BlueprintCallable)
	void LoadGame(const FString& SlotName);
	UFUNCTION(BlueprintCallable)
	void SaveCurrentGame(const FString& SlotName);
	UTestSaveGame* GetCurrentGameObject() const {return CurrentGameSave;}
	UPROPERTY(BlueprintReadWrite, BlueprintAssignable)
	FOnGameFromSlotAction OnGameLoadedFromSlot;
	UPROPERTY(BlueprintReadWrite, BlueprintAssignable)
	FOnGameFromSlotAction OnGameSavedToSlot;
protected:
	UPROPERTY(BlueprintReadWrite)
	UTestSaveGame * CurrentGameSave;
	void OnGameLoadedFromSlotHandle(const FString& SlotName, const int32 UserIndex,USaveGame* SaveGame);
	void OnGameSavedToSlotHandle(const FString& SlotName, const int32 UserIndex,bool bSuccess);
public:
	void Init();
	
public:
	UFUNCTION(BlueprintCallable)
	const TArray<FString>& GetExistingSavedSlots() const;
protected:
	TArray<FString> ExistingSavedSlots;
	const FString ExistingSavedSlotsFilePath = "existing_slots.txt";
	void CacheExistingSavedSlotsInfo();
	
public:
	UFUNCTION()
	bool ExportSaveGameToJsonFile(const FString& SlotName, int32 UserIndex);
	UFUNCTION()
	bool ImportSaveGameFromJsonFile(const FString& SlotName, int32 UserIndex);

	static bool ExportSaveGameToJson(UTestSaveGame* Save, FString& OutJsonString);

	static UTestSaveGame* ImportSaveGameFromJson(const FString& JsonString);
};
