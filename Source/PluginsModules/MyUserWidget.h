// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MediaPlayer.h"
#include "Blueprint/UserWidget.h"
#include "Components/Button.h"
#include "Components/Image.h"
#include "MyUserWidget.generated.h"

/**
 * 
 */
UCLASS(Abstract)
class PLUGINSMODULES_API UMyUserWidget : public UUserWidget
{
	GENERATED_BODY()
protected:
	UPROPERTY(meta=(BindWidget))
	UButton* OpenWindowButton;
	UPROPERTY(meta=(BindWidget))
	UImage* Image;
	UPROPERTY(meta=(BindWidget))
	UImage* Video;
	UPROPERTY(meta=(BindWidget))
	UButton* PlayButton;
	UPROPERTY(EditAnywhere)
	UMediaPlayer* MediaPlayer;
public:
	virtual void NativeConstruct() override;
	virtual void NativeDestruct() override;
	UFUNCTION()
	void OnOpenWindowButtonClicked();
	UFUNCTION()
	void OnPlayButtonClicked();
	FString Path;
};
