// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/ObjectiveWidget.h"

#include "Objective.h"
#include "Components/CheckBox.h"
#include "Components/TextBlock.h"

void UObjectiveWidget::Init(UObjective* Objective)
{
	if (Objective)
	{
		if (CompletedCheck)
		{
			CompletedCheck->SetIsChecked(Objective->bIsCompleted);
		}
		if (DescriptionText)
		{
			DescriptionText->SetText(Objective->Description);
		}
	}
}
