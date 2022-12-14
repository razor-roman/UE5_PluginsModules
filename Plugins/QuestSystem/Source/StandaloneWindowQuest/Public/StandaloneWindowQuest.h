// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"

class AQuest;
class FToolBarBuilder;
class FMenuBuilder;

class FStandaloneWindowQuestModule : public IModuleInterface
{
public:
	
	/** IModuleInterface implementation */
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;
	
	/** This function will be bound to Command (by default it will bring up plugin window) */
	void PluginButtonClicked();
	
private:
	void RegisterMenus();
	TSharedRef<class SDockTab> OnSpawnPluginTab(const class FSpawnTabArgs& SpawnTabArgs);
	TSharedPtr<SVerticalBox> Container = SNew(SVerticalBox);
	TArray<AQuest*> QuestActors;
private:
	TSharedPtr<class FUICommandList> PluginCommands;
};
