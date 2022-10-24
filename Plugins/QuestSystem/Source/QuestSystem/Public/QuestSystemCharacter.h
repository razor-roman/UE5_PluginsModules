// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InteractableObject.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/Character.h"
#include "GameFramework/SpringArmComponent.h"
#include "QuestSystemCharacter.generated.h"

class UQuestList;
class UQuestDialog;
UCLASS()
class QUESTSYSTEM_API AQuestSystemCharacter : public ACharacter, public  IInteractableObject
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AQuestSystemCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	UPROPERTY(EditAnywhere)
	USpringArmComponent* SpringArmComponent;
	UPROPERTY(EditAnywhere)
	UCameraComponent* CameraComponent;
	

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	void Interact_Implementation(AActor* ActorInteractedWithObject) override;
	
	UPROPERTY(EditAnywhere)
	TSubclassOf<UQuestDialog> QuestDialogClass;
		
};
