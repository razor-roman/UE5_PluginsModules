// Fill out your copyright notice in the Description page of Project Settings.


#include "QuestListComponent.h"
#include "UI/CurrentObjectives.h"
#include "Blueprint/UserWidget.h"
#include "Blueprint/WidgetBlueprintLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "UI/QuestList.h"

// Sets default values for this component's properties
UQuestListComponent::UQuestListComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

void UQuestListComponent::AddQuest(AQuest* Quest)
{
	if(ActiveQuest == nullptr || ActiveQuest->IsCompleted())
	{
		ActiveQuest=Quest;
		OnActiveQuestChanged.Broadcast(ActiveQuest);
	}
	if (Quest)
    {
	   AcceptedQuests.AddUnique(Quest);
	   Quest->TakeQuest(GetOwner());		
	   OnActiveQuestChanged.AddLambda([this](AQuest * Quest)
	   {
	    if (ActiveQuest == Quest)
	    {
		    if (OnActiveQuestChanged.IsBound())
		    {
			OnActiveQuestChanged.Broadcast(Quest);
			}
		}
		});
	}
}


void UQuestListComponent::SetActiveQuest(AQuest* Quest)
{
	if (AcceptedQuests.Contains(Quest))
	{
		ActiveQuest = Quest;
		if (OnActiveQuestChanged.IsBound())
		{
			OnActiveQuestChanged.Broadcast(ActiveQuest);
		}
	}
}


// Called when the game starts
void UQuestListComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	if (CurrentObjectivesWidgetClass)
	{
		UCurrentObjectives * CurrentObjectivesWidget = CreateWidget<UCurrentObjectives>(GetWorld(),
		CurrentObjectivesWidgetClass);
		
		OnActiveQuestChanged.AddUObject(CurrentObjectivesWidget,&UCurrentObjectives::SetCurrentObjectives);
		CurrentObjectivesWidget->AddToViewport();
	}
	
}

void UQuestListComponent::ToggleQuestListVisibility()
{
	APlayerController * PC = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	if (QuestList)
	{
		QuestList->RemoveFromParent();
		QuestList = nullptr;
		UWidgetBlueprintLibrary::SetInputMode_GameOnly(PC);
		PC->bShowMouseCursor = false;
	}
	else
	{
		if (QuestListClass)
		{
			QuestList = CreateWidget<UQuestList>(GetWorld(), QuestListClass);
			QuestList->Init(this);
			QuestList->AddToViewport();
			UWidgetBlueprintLibrary::SetInputMode_GameAndUIEx(PC);
			PC->bShowMouseCursor = true;
		}

	}
}



// Called every frame
void UQuestListComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	
}

