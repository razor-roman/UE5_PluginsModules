// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MyGameInstance.h"
#include "Blueprint/UserWidget.h"
#include "Components/Button.h"
#include "Components/EditableText.h"
#include "SaveWidget.generated.h"

class USavingsManager;
/**
 * 
 */
UCLASS()
class PLUGINSMODULES_API USaveWidget : public UUserWidget
{
	GENERATED_BODY()
	UPROPERTY(meta=(BindWidget))
	UButton* SaveButton;
	UPROPERTY(meta=(BindWidget))
	UButton* LoadButton;
	UPROPERTY(meta=(BindWidget))
	UButton* RandomButton;
	UPROPERTY(meta=(BindWidget))
	UButton* PrintSavesListButton;
	UPROPERTY(meta=(BindWidget))
	UEditableText* EditableText;
	virtual void NativeConstruct() override;
	virtual void NativeDestruct() override;
	UFUNCTION()
	void OnSaveButtonPressed();
	UFUNCTION()
	void OnLoadButtonPressed();
	UFUNCTION()
	void OnRandomButtonPressed();
	UFUNCTION()
	void OnRPrintSavesListButtonPressed();
	UPROPERTY()
	UMyGameInstance* MyGameInstance;
	FOnGameFromSlotAction OnGameFromSlotAction;
};
