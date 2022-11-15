// Copyright Epic Games, Inc. All Rights Reserved.

#include "EditorModeEditorModeToolkit.h"
#include "Engine/Selection.h"
#include "EditorModeManager.h"

#define LOCTEXT_NAMESPACE "EditorModeEditorModeToolkit"

FEditorModeEditorModeToolkit::FEditorModeEditorModeToolkit()
{
}

void FEditorModeEditorModeToolkit::Init(const TSharedPtr<IToolkitHost>& InitToolkitHost, TWeakObjectPtr<UEdMode> InOwningMode)
{
	FModeToolkit::Init(InitToolkitHost, InOwningMode);

}

void FEditorModeEditorModeToolkit::GetToolPaletteNames(TArray<FName>& PaletteNames) const
{
	PaletteNames.Add(NAME_Default);
}


FName FEditorModeEditorModeToolkit::GetToolkitFName() const
{
	return FName("EditorModeEditorMode");
}

FText FEditorModeEditorModeToolkit::GetBaseToolkitName() const
{
	return LOCTEXT("DisplayName", "EditorModeEditorMode Toolkit");
}

FEdMode* FEditorModeEditorModeToolkit::GetEditorMode() const
{
	return FModeToolkit::GetEditorMode();
}

#undef LOCTEXT_NAMESPACE
