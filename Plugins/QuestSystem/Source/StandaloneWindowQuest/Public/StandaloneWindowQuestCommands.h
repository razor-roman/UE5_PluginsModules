// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Framework/Commands/Commands.h"
#include "StandaloneWindowQuestStyle.h"

class FStandaloneWindowQuestCommands : public TCommands<FStandaloneWindowQuestCommands>
{
public:

	FStandaloneWindowQuestCommands()
		: TCommands<FStandaloneWindowQuestCommands>(TEXT("StandaloneWindowQuest"), NSLOCTEXT("Contexts", "StandaloneWindowQuest", "StandaloneWindowQuest Plugin"), NAME_None, FStandaloneWindowQuestStyle::GetStyleSetName())
	{
	}

	// TCommands<> interface
	virtual void RegisterCommands() override;

public:
	TSharedPtr< FUICommandInfo > OpenPluginWindow;
};