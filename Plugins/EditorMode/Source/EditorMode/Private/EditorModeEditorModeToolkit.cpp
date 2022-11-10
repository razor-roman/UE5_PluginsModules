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
	GEditor->BeginTransaction(LOCTEXT("MoveActorsTransactionName","MoveActors"));
	
	for(FSelectionIterator Iter(*GEditor->GetSelectedActors());Iter;++Iter)
	{
		if(AActor* LevelActor = Cast<AActor>(*Iter))
		{
			LevelActor->Modify();
			LevelActor->TeleportTo(LevelActor->GetActorLocation()+InOffset,FRotator(0,0,0));
		}
	}
	GEditor->EndTransaction();
	// static TSharedRef<SWidget> MakeButton(FText InLabel, FVector InOffset)
	// {
	// 	return SNew(SButton)
	// 	.Text(InLabel)
	// 	.OnClicked_Static(&Locals::OnButtonClick,InOffset);
	// }
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
