// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "QuestList.generated.h"

class AQuest;
class UQuestListEntry;
class UQuestDescription;
class UScrollBox;
class UQuestListComponent;
/**
 * 
 */
UCLASS()
class QUESTSYSTEM_API UQuestList : public UUserWidget
{
	GENERATED_BODY()
public:
	void Init(UQuestListComponent * QuestList);
	void OnActiveQuestChanged(AQuest * ActiveQuest);
protected:
	UPROPERTY(meta = (BindWidget))
	UScrollBox * StoryQuestsList;
	UPROPERTY(meta = (BindWidget))
	UScrollBox * SideQuestsList;
	UPROPERTY(meta = (BindWidget))
	UQuestDescription * ActiveQuestDescription;
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UQuestListEntry> QuestEntryClass;
	UPROPERTY()
	TMap<AQuest*, UQuestListEntry*> QuestEntries;
	
};
