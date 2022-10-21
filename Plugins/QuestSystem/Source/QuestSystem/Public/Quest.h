// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Quest.generated.h"

class UObjective;
UCLASS()
class QUESTSYSTEM_API AQuest : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AQuest();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
	UPROPERTY(EditAnywhere)
	FText Name;
	UPROPERTY(EditAnywhere)
	FText Descrition;
	UPROPERTY(EditAnywhere)
	TArray<UObjective*> Objectives;
	UPROPERTY(EditAnywhere)
	bool bIsStoryQuest = true;
	UPROPERTY(EditAnywhere)
	bool bKeepObjectivesOrder = true;
	UPROPERTY(EditAnywhere)
	AQuest* PrerquisedQuest;
	UPROPERTY(VisibleAnywhere)
	bool bIsTaken;
public:	
	// Called every frame	
	UFUNCTION(BlueprintCallable, CallInEditor)
    void UpdateLocation();
	
	void TakeQuest(AActor * Character);
	//FOnQuestStatusUpdated OnQuestStatusUpdated;
	void OnObjectiveCompleted(UObjective* Objective);
#if WITH_EDITOR
	UFUNCTION(BlueprintCallable, CallInEditor)
	void AddLocationObjective();
	UFUNCTION(BlueprintCallable, CallInEditor)
	void AddInteractObjective();
#endif
	
};
