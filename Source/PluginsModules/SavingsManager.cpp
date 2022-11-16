// Fill out your copyright notice in the Description page of Project Settings.


#include "SavingsManager.h"
#include "TestSaveGame.h"
#include "Kismet/GameplayStatics.h"

void USavingsManager::Init()
{
	CurrentGameObject = Cast<UTestSaveGame>(UGameplayStatics::CreateSaveGameObject(UTestSaveGame::StaticClass()));
	IPlatformFile& PlatformFile = FPlatformFileManager::Get().GetPlatformFile();
	FString FilePath = FPaths::Combine(FPaths::ProjectContentDir(),ExistingSavedSlotsFilePath);
	if (PlatformFile.FileExists(*FilePath))
    {
		FString ExistingSavingsArray;
	    if (FFileHelper::LoadFileToString(ExistingSavingsArray, *FilePath))
	    {
			ExistingSavingsArray.ParseIntoArray(ExistingSavedSlots, TEXT(","));
	    }
    }
	ExistingSavedSlots.Empty();	
}

const TArray<FString>& USavingsManager::GetExistingSavedSlots() const
{
	return ExistingSavedSlots;
}

void USavingsManager::CacheExistingSavedSlotsInfo()
{
	FString FilePath = FPaths::Combine(FPaths::ProjectContentDir(), ExistingSavedSlotsFilePath);
	FString ExistingSavingsArray = "";	
	for (const FString& Slot : ExistingSavedSlots)
	{
		ExistingSavingsArray += Slot + ",";
	}
	FFileHelper::SaveStringToFile(ExistingSavingsArray, *FilePath,
	FFileHelper::EEncodingOptions::ForceUnicode, &IFileManager::Get(),
FILEWRITE_EvenIfReadOnly);
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
	if (!ExistingSavedSlots.Contains(SlotName))
	{
		ExistingSavedSlots.Add(SlotName);
		CacheExistingSavedSlotsInfo();
	}
}
