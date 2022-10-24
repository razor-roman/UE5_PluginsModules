// Fill out your copyright notice in the Description page of Project Settings.


#include "QuestSystemCharacter.h"

#include "UI/QuestDialog.h"
#include "QuestListComponent.h"
#include "Blueprint/UserWidget.h"
#include "Blueprint/WidgetBlueprintLibrary.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AQuestSystemCharacter::AQuestSystemCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>("SpringArm");
	CameraComponent = CreateDefaultSubobject<UCameraComponent>("Camera");
	SpringArmComponent->SetupAttachment(GetMesh());
	CameraComponent->SetupAttachment(GetMesh());
}

// Called when the game starts or when spawned
void AQuestSystemCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AQuestSystemCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AQuestSystemCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void AQuestSystemCharacter::Interact_Implementation(AActor* ActorInteractedWithObject)
{	
	IInteractableObject::Interact_Implementation(ActorInteractedWithObject);
	if (ActorInteractedWithObject)
	{
		// check if actor has QuestList and can accept quests
		UActorComponent * ActorQuestListComp = ActorInteractedWithObject->GetComponentByClass(
		UQuestListComponent::StaticClass());
		if (ActorQuestListComp)
		{
			UQuestListComponent * ActorQuestList = Cast<UQuestListComponent>(ActorQuestListComp);
			// past any limitations and quest choosing logic
			TArray<AActor*> AttachedActors;
			GetAttachedActors(AttachedActors);
			bool HadQuestsAvailable = false;
			for (AActor * Actor : AttachedActors)
			{
				if (AQuest * Quest = Cast<AQuest>(Actor))
				{
					if (Quest->IsAlreadyTaken() || (Quest->GetPrerquisedQuest() &&
					!Quest->GetPrerquisedQuest()->IsCompleted()))
					{
						continue;
					}
					if (QuestDialogClass)
					{
						UQuestDialog * QuestDialog =CreateWidget<UQuestDialog>(GetWorld(),QuestDialogClass);
						QuestDialog->Init(Quest);
						QuestDialog->OnQuestAccepted.BindUObject(ActorQuestList,
						&UQuestListComponent::AddQuest, Quest);
						QuestDialog->OnQuestQuited.BindLambda(
						[this, ActorInteractedWithObject]()
						{
							NotifyInteractionFinished(this,
							ActorInteractedWithObject);
						});
						QuestDialog->AddToViewport();
						return;
					}
					HadQuestsAvailable = true;
				}
			}
			if (!HadQuestsAvailable)
			{
				NotifyInteractionFinished(this, ActorInteractedWithObject);
			}
		}
	}
}

