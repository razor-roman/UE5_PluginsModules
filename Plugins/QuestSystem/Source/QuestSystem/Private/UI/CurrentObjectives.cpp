// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/CurrentObjectives.h"
#include "UI/ObjectiveWidget.h"
#include "Quest.h"
#include "Components/VerticalBox.h"

class UObjective;

void UCurrentObjectives::SetCurrentObjectives(AQuest* Quest)
{
	if (ObjectivesList && ObjectiveWidgetClass)
	{
		ObjectivesList->ClearChildren();
		for (UObjective* Objective : Quest->GetObjectives())
		{
			UObjectiveWidget * ObjectiveWidget =
			CreateWidget<UObjectiveWidget>(this, ObjectiveWidgetClass);
			ObjectiveWidget->Init(Objective);
			ObjectivesList->AddChildToVerticalBox(ObjectiveWidget);
		}
	}
}
