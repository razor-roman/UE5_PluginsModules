// Fill out your copyright notice in the Description page of Project Settings.


#include "SavingsManager.h"
#include "DesktopPlatformModule.h"
#include "IDesktopPlatform.h"
#include "JsonObjectConverter.h"
#include "TestSaveGame.h"
#include "Kismet/GameplayStatics.h"

#define LOCTEXT_NAMESPACE "SaveGameEditorUtilities"

void USavingsManager::Init()
{
	CurrentGameSave = Cast<UTestSaveGame>(UGameplayStatics::CreateSaveGameObject(UTestSaveGame::StaticClass()));
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

bool USavingsManager::ExportSaveGameToJsonFile(const FString& SlotName, int32 UserIndex)
{
	if (!UGameplayStatics::DoesSaveGameExist(SlotName, UserIndex))
	{
		FMessageLog("EditorErrors").Error(FText::Format(LOCTEXT("SaveGameDoesNotExit", "Save game '{0}' does not exist, cannot export save game"), FText::FromString(SlotName)));
		FMessageLog("EditorErrors").Notify(LOCTEXT("ExportFailNotification", "Failed to export save game"));
		return false;
	}

	OnGameSavedToSlotHandle(SlotName,0,true);	
	if (!CurrentGameSave)
	{
		FMessageLog("EditorErrors").Error(FText::Format(LOCTEXT("SaveGameFailedToLoad", "Save game '{0}' failed to load, cannot export save game"), FText::FromString(SlotName)));
		FMessageLog("EditorErrors").Notify(LOCTEXT("ExportFailNotification", "Failed to export save game"));
		return false;
	}	
	IDesktopPlatform* DesktopPlatform = FDesktopPlatformModule::Get();
	if (!DesktopPlatform)
	{
		FMessageLog("EditorErrors").Error(LOCTEXT("ExportBadDesktopPlatform", "Unable to retrieve IDesktopPlatform, cannot export save game"));
		FMessageLog("EditorErrors").Notify(LOCTEXT("ExportFailNotification", "Failed to export save game"));
		return false;
	}

	TSharedPtr<SWindow> ParentWindow = FSlateApplication::Get().GetActiveTopLevelWindow();
	void* ParentWindowHandle = (ParentWindow.IsValid() && ParentWindow->GetNativeWindow().IsValid())
		? ParentWindow->GetNativeWindow()->GetOSWindowHandle()
		: nullptr;

	TArray<FString> SelectedFiles;
	bool Result = DesktopPlatform->SaveFileDialog(
		ParentWindowHandle,
		TEXT("Export Save Game"),
		FPaths::ProjectDir(),
		FString::Printf(TEXT("%s.json"), *SlotName),
		TEXT("JSON Files|*.json"),
		EFileDialogFlags::None,
		SelectedFiles);

	if (!Result || SelectedFiles.Num() == 0)
	{
		return false;
	}

	FString JsonString;
	if (!ExportSaveGameToJson(CurrentGameSave, JsonString))
	{
		FMessageLog("EditorErrors").Error(LOCTEXT("ExportSaveFailedJson", "Failed to export save, json error"));
		FMessageLog("EditorErrors").Notify(LOCTEXT("ExportFailNotification", "Failed to export save game"));
	}

	if (!FFileHelper::SaveStringToFile(JsonString, *SelectedFiles[0]))
	{
		FMessageLog("EditorErrors").Error(FText::Format(LOCTEXT("ExportSaveFailed", "Failed to export save to '{0}'"), FText::FromString(SelectedFiles[0])));
		FMessageLog("EditorErrors").Notify(LOCTEXT("ExportFailNotification", "Failed to export save game"));
		return false;
	}

	return true;
}

bool USavingsManager::ImportSaveGameFromJsonFile(const FString& SlotName, int32 UserIndex)
{
	IDesktopPlatform* DesktopPlatform = FDesktopPlatformModule::Get();
	if (!DesktopPlatform)
	{
		FMessageLog("EditorErrors").Error(LOCTEXT("ImportBadDesktopPlatform", "Unable to retrieve IDesktopPlatform, cannot import save game"));
		FMessageLog("EditorErrors").Notify(LOCTEXT("ImportFailNotification", "Failed to import save game"));
		return false;
	}

	TSharedPtr<SWindow> ParentWindow = FSlateApplication::Get().GetActiveTopLevelWindow();
	void* ParentWindowHandle = (ParentWindow.IsValid() && ParentWindow->GetNativeWindow().IsValid())
        ? ParentWindow->GetNativeWindow()->GetOSWindowHandle()
        : nullptr;

	TArray<FString> SelectedFiles;
	bool Result = DesktopPlatform->OpenFileDialog(
        ParentWindowHandle,
        TEXT("Import Save Game"),
        FPaths::ProjectDir(),
        TEXT(""),
        TEXT("JSON Files|*.json"),
        EFileDialogFlags::None,
        SelectedFiles);

	if (!Result || SelectedFiles.Num() == 0)
	{
		return false;
	}

	FString JsonString;
	if (!FFileHelper::LoadFileToString(JsonString, *SelectedFiles[0]))
	{
		FMessageLog("EditorErrors").Error(FText::Format(LOCTEXT("ImportFileFailed", "Failed to import save from '{0}'"), FText::FromString(SelectedFiles[0])));
		FMessageLog("EditorErrors").Notify(LOCTEXT("ImportFailNotification", "Failed to import save game"));
		return false;
	}	
	if (!CurrentGameSave)
	{
		FMessageLog("EditorErrors").Error(FText::Format(LOCTEXT("ImportSaveFileFailed", "Failed to import save from '{0}', possible parse error"), FText::FromString(SelectedFiles[0])));
		FMessageLog("EditorErrors").Notify(LOCTEXT("ImportFailNotification", "Failed to import save game"));
		return false;
	}

	if (!UGameplayStatics::SaveGameToSlot(CurrentGameSave, SlotName, UserIndex))
	{
		FMessageLog("EditorErrors").Error(FText::Format(LOCTEXT("UnableToSaveImport", "Failed to save imported save game to slot '{0}'"), FText::FromString(SlotName)));
		FMessageLog("EditorErrors").Notify(LOCTEXT("ImportFailNotification", "Failed to import save game"));
		return false;
	}

	return true;
}

bool USavingsManager::ExportSaveGameToJson(UTestSaveGame* Save, FString& OutJsonString)
{
	if (!IsValid(Save))
	{
		return false;
	}
	FExportedSaveGame Export;
	Export.SaveGame = Save;
	return FJsonObjectConverter::UStructToJsonObjectString(Export, OutJsonString);
}

UTestSaveGame* USavingsManager::ImportSaveGameFromJson(const FString& JsonString)
{
	FExportedSaveGame Import;	
	if (!FJsonObjectConverter::JsonObjectStringToUStruct(JsonString, &Import, 0, 0,false))
	{
		return nullptr;
	}
	return Import.SaveGame;
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
	
	UGameplayStatics::AsyncSaveGameToSlot(CurrentGameSave,SlotName,0,
		FAsyncSaveGameToSlotDelegate::CreateUObject(this,&USavingsManager::OnGameSavedToSlotHandle));
}

void USavingsManager::OnGameLoadedFromSlotHandle(const FString& SlotName, const int32 UserIndex, USaveGame* SaveGame)
{
	CurrentGameSave = Cast<UTestSaveGame>(SaveGame);
	if(OnGameLoadedFromSlot.IsBound())
	{
		OnGameLoadedFromSlot.Broadcast(SlotName);
	}
	CurrentGameSave->OnFileLoad(GetWorld());
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
	CurrentGameSave->OnFileSave(GetWorld());
}
