// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SavingsManager.h"
#include "Engine/GameInstance.h"
#include "MyGameInstance.generated.h"

/**
 * 
 */
UCLASS()
class PLUGINSMODULES_API UMyGameInstance : public UGameInstance
{
	GENERATED_BODY()
public:
	virtual void Init() override;

	UPROPERTY(BlueprintReadWrite)
	USavingsManager* SaveManager;
};
