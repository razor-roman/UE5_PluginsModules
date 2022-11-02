// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/QuestList.h"

#include "UI/QuestDescription.h"
#include "QuestListComponent.h"
#include "UI/QuestListEntry.h"
#include "Components/ScrollBox.h"

void UQuestList::Init(UQuestListComponent* QuestList)
{
	if (QuestList && QuestEntryClass)
	{
		for (AQuest* Quest : QuestList->GetQuests())
		{
			UScrollBox * Scroll = Quest->IsStoryQuest() ? StoryQuestsList : SideQuestsList;
			if (Scroll)
			{
				UQuestListEntry * QuestEntry = CreateWidget<UQuestListEntry>(this, QuestEntryClass);
				QuestEntry->SetQuestText(Quest->GetName());
				QuestEntry->OnQuestChosen.BindUObject(QuestList,&UQuestListComponent::SetActiveQuest, Quest);
				QuestEntries.Add(Quest, QuestEntry);
				Scroll->AddChild(QuestEntry);
			}
		}
		OnActiveQuestChanged(QuestList->GetActiveQuest());
		QuestList->OnActiveQuestChanged.AddUObject(this, &UQuestList::OnActiveQuestChanged);
	}
}

void UQuestList::OnActiveQuestChanged(AQuest* ActiveQuest)
{
	for (const TPair<AQuest*, UQuestListEntry*>& Pair : QuestEntries)
	{
		Pair.Value->SetIsSelected(Pair.Key == ActiveQuest);
	}
	if (ActiveQuestDescription)
	{
		ActiveQuestDescription->Init(ActiveQuest);
		ActiveQuestDescription->SetVisibility(ActiveQuest ? ESlateVisibility::Visible : ESlateVisibility::Hidden);
	}
}
