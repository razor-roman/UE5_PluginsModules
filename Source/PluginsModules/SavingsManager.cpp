// Fill out your copyright notice in the Description page of Project Settings.


#include "SavingsManager.h"
#include "TestSaveGame.h"
#include "Kismet/GameplayStatics.h"

void USavingsManager::Init()
{
	CurrentGameObject = Cast<UTestSaveGame>(UGameplayStatics::CreateSaveGameObject(UTestSaveGame::StaticClass()));
}

bool USavingsManager::DoesSaveGameExist(const FString& SlotName)
{
	return UGameplayStatics::DoesSaveGameExist(SlotName,0);
}

void USavingsManager::LoadGame(const FString& SlotName)
{
	UGameplayStatics::AsyncLoadGameFromSlot(SlotName,0,
		FAsyncLoadGameFromSlotDelegate::CreateUObject(this,&USavingsManager::OnGameLoadedFromSlotHandle));
}

void USavingsManager::SaveCurrentGame(const FString& SlotName)
{
	UGameplayStatics::AsyncSaveGameToSlot(CurrentGameObject,SlotName,0,
		FAsyncSaveGameToSlotDelegate::CreateUObject(this,&USavingsManager::OnGameSavedToSlotHandle));
}

void USavingsManager::OnGameLoadedFromSlotHandle(const FString& SlotName, const int32 UserIndex, USaveGame* SaveGame)
{
	CurrentGameObject = Cast<UTestSaveGame>(SaveGame);
	if(OnGameLoadedFromSlot.IsBound())
	{
		OnGameLoadedFromSlot.Broadcast(SlotName);
	} 
}

void USavingsManager::OnGameSavedToSlotHandle(const FString& SlotName, const int32 UserIndex, bool bSuccess)
{
	if(OnGameLoadedFromSlot.IsBound())
	{
		OnGameLoadedFromSlot.Broadcast(SlotName);
	}
}
