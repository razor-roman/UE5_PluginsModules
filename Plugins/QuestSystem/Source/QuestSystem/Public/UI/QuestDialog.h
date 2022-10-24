// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "QuestDialog.generated.h"

class UQuestDescription;
class UButton;
/**
 * 
 */
UCLASS()
class QUESTSYSTEM_API UQuestDialog : public UUserWidget
{
	GENERATED_BODY()
public:
	virtual void NativeConstruct() override;

	void Init(class AQuest * Quest);
	
	FSimpleDelegate OnQuestAccepted;
	
	FSimpleDelegate OnQuestQuited;
	
protected:
	UPROPERTY(meta = (BindWidget))
	UQuestDescription * Description;
	
	UPROPERTY(meta = (BindWidget))
	UButton * RejectButton;
	
	UPROPERTY(meta = (BindWidget))
	UButton * AcceptButton;
	
	UFUNCTION()
	void RejectQuest();
	
	UFUNCTION()
	void AcceptQuest();
	
	void HideDialog();
public:
	
	
    
};
