// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SavingsManager.generated.h"

class USaveGame;
class UTestSaveGame;
/**
 * 
 */
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnGameFromSlotAction, const FString&,SotName);
UCLASS()
class PLUGINSMODULES_API USavingsManager : public UObject
{
	GENERATED_BODY()
	
	UFUNCTION(BlueprintCallable)
	bool DoesSaveGameExist(const FString& SlotName);
	UFUNCTION(BlueprintCallable)
	void LoadGame(const FString& SlotName);
	UFUNCTION(BlueprintCallable)
	void SaveCurrentGame(const FString& SlotName);
public:
	UPROPERTY(BlueprintReadWrite, BlueprintAssignable)
	FOnGameFromSlotAction OnGameLoadedFromSlot;
	UPROPERTY(BlueprintReadWrite, BlueprintAssignable)
	FOnGameFromSlotAction OnGameSavedToSlot;
protected:
	UPROPERTY(BlueprintReadWrite)
	UTestSaveGame * CurrentGameObject;
	void OnGameLoadedFromSlotHandle(const FString& SlotName, const int32 UserIndex,USaveGame* SaveGame);
	void OnGameSavedToSlotHandle(const FString& SlotName, const int32 UserIndex,bool bSuccess);
public:
	void Init();
};
