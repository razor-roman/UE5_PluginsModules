// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Objective.h"
#include "GameFramework/Actor.h"
#include "Quest.generated.h"

DECLARE_MULTICAST_DELEGATE_OneParam(FOnQuestStatusUpdated, AQuest*/*Quest*/);
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
	FText Description;
	
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
	
	UPROPERTY(VisibleAnywhere)
	bool bIsCompleted;
	
public:	
	// Called every frame	
	UFUNCTION(BlueprintCallable, CallInEditor)
    void UpdateLocation();
	FText GetName() {return Name;}
	FText GetDescription() {return Description;}
	void SetDescription(FText Text) {Description=Text;}
	void SetName(FText Text) {Name=Text;}
	TArray<UObjective*> GetObjectives() {return Objectives;}
	void TakeQuest(AActor * Character);
	//TODO fix delegate
	FOnQuestStatusUpdated OnQuestStatusUpdated;
	void OnObjectiveCompleted(UObjective* Objective);
	bool IsAlreadyTaken() const {return bIsTaken;}
	AQuest* GetPrerquisedQuest(){return PrerquisedQuest;}
	bool IsCompleted(){return bIsCompleted;}
	bool IsStoryQuest() {return bIsStoryQuest;}

#if WITH_EDITOR
	UFUNCTION(BlueprintCallable, CallInEditor)
	void AddLocationObjective();
	UFUNCTION(BlueprintCallable, CallInEditor)
	void AddInteractObjective();
#endif
	
};
