// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Quest.h"
#include "Components/ActorComponent.h"
#include "QuestListComponent.generated.h"

DECLARE_MULTICAST_DELEGATE_OneParam(FOnQuestAction, AQuest*);

class UQuestList;
class UCurrentObjectives;
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class QUESTSYSTEM_API UQuestListComponent : public UActorComponent
{
	GENERATED_BODY()
	
public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

public:	
	// Sets default values for this component's properties
	UQuestListComponent();
	UFUNCTION()
	void AddQuest(AQuest* Quest);
	const TArray<AQuest*>& GetQuests() const {return AcceptedQuests;};

	AQuest* GetActiveQuest() const {return ActiveQuest;}
	void SetActiveQuest(AQuest* Quest);
	
	
	FOnQuestAction OnActiveQuestChanged;
private:
	// Called when the game starts
	virtual void BeginPlay() override;

	UPROPERTY()
	TArray<AQuest*> AcceptedQuests;
	UPROPERTY()
	AQuest* ActiveQuest;
	UPROPERTY(EditAnywhere)
	TSubclassOf<UCurrentObjectives> CurrentObjectivesWidgetClass;
	
	UFUNCTION(BlueprintCallable)
	void ToggleQuestListVisibility();
	
	UPROPERTY()
	UQuestList * QuestList;
	
	UPROPERTY(EditAnywhere)
	TSubclassOf<UQuestList> QuestListClass;
};
