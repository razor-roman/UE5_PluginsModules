// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Objective.generated.h"

UENUM()
enum class EObjectiveType : uint8
	{
	Location,
	Interact,
	Collect,
	Kill
	};
/**
 * 
 */
DECLARE_MULTICAST_DELEGATE_OneParam(FOnObjectiveCompleted, UObjective*/*Objective*/);

UCLASS(Abstract)
class QUESTSYSTEM_API UObjective : public UObject
{
	GENERATED_BODY()
public:
	virtual void ActivateObjective(AActor * Character) {}
	UPROPERTY(EditAnywhere)
	FText Description;
	UPROPERTY(VisibleAnywhere)
	EObjectiveType Type;
	FOnObjectiveCompleted OnObjectiveCompleted;
	UPROPERTY(VisibleAnywhere)
	bool bIsCompleted;
	UPROPERTY(VisibleAnywhere)
	bool bCanBeCompleted;
	virtual AActor* GetActor() {return nullptr;}
};

UCLASS()
class QUESTSYSTEM_API UInteractionObjective : public UObjective
{
	GENERATED_BODY()
	public:
	UInteractionObjective();
	virtual void ActivateObjective(AActor * Character) override;
	UPROPERTY(EditAnywhere, meta = (AllowedClasses = "InteractableObject"))
	AActor* Target;
	virtual AActor* GetActor() override{return Target;}
};

UCLASS()
class QUESTSYSTEM_API ULocationObjective : public UObjective
{
	GENERATED_BODY()
public:
	ULocationObjective();
	virtual void ActivateObjective(AActor * Character) override;
	UPROPERTY(EditAnywhere, meta = (AllowedClasses = "LocationMarker"))
    AActor* Marker;
	virtual AActor* GetActor() override {return  Marker;}
};
