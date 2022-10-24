// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/QuestDescription.h"

#include "Quest.h"
#include "Components/ScrollBox.h"
#include "Components/TextBlock.h"
#include "UI/ObjectiveWidget.h"


class UObjectiveWidget;
class UObjective;

void UQuestDescription::Init(AQuest* Quest)
{
	if (Quest)
	{
		if (NameText)
		{
			NameText->SetText(Quest->GetName());
		}
		if (DescriptionText)
		{
			DescriptionText->SetText(Quest->GetDescription());
		}
		if (ObjectiveWidgetClass && ObjectivesList)
		{
			ObjectivesList->ClearChildren();
			for (UObjective* Objective : Quest->GetObjectives())
			{
				UObjectiveWidget * ObjectiveWidget =CreateWidget<UObjectiveWidget>(this, ObjectiveWidgetClass);
				ObjectiveWidget->Init(Objective);
				ObjectivesList->AddChild(ObjectiveWidget);
			}
		}
	}
}
