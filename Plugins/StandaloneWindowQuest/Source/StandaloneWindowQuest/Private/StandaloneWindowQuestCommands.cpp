// Copyright Epic Games, Inc. All Rights Reserved.

#include "StandaloneWindowQuestCommands.h"

#define LOCTEXT_NAMESPACE "FStandaloneWindowQuestModule"

void FStandaloneWindowQuestCommands::RegisterCommands()
{
	UI_COMMAND(OpenPluginWindow, "StandaloneWindowQuest", "Bring up StandaloneWindowQuest window", EUserInterfaceActionType::Button, FInputChord());
}

#undef LOCTEXT_NAMESPACE
