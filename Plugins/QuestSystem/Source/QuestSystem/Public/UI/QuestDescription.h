// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "QuestDescription.generated.h"

class UObjectiveWidget;
class UScrollBox;
class UTextBlock;
/**
 * 
 */
UCLASS()
class QUESTSYSTEM_API UQuestDescription : public UUserWidget
{
	GENERATED_BODY()
public:
	void Init(class AQuest * Quest);
protected:
	UPROPERTY(meta = (BindWidget))
	UTextBlock * NameText;
	
	UPROPERTY(meta = (BindWidget))
	UScrollBox * ObjectivesList;
	
	UPROPERTY(meta = (BindWidget))
	UTextBlock * DescriptionText;
	
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UObjectiveWidget> ObjectiveWidgetClass;
};
