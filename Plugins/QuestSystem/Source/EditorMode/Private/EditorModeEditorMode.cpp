// Copyright Epic Games, Inc. All Rights Reserved.

#include "EditorModeEditorMode.h"
#include "EditorModeEditorModeToolkit.h"
#include "EdModeInteractiveToolsContext.h"
#include "InteractiveToolManager.h"
#include "EditorModeEditorModeCommands.h"


//////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////// 
// AddYourTool Step 1 - include the header file for your Tools here
//////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////// 
#include "EditorModeManager.h"
#include "LandscapeRender.h"
#include "Selection.h"
#include "Toolkits/ToolkitManager.h"
#include "Tools/EditorModeSimpleTool.h"
#include "Tools/EditorModeInteractiveTool.h"

// step 2: register a ToolBuilder in FEditorModeEditorMode::Enter() below


#define LOCTEXT_NAMESPACE "EditorModeEditorMode"

const FEditorModeID UEditorModeEditorMode::EM_EditorModeEditorModeId = TEXT("EM_EditorModeEditorMode");

FString UEditorModeEditorMode::SimpleToolName = TEXT("EditorMode_ActorInfoTool");
FString UEditorModeEditorMode::InteractiveToolName = TEXT("EditorMode_MeasureDistanceTool");


UEditorModeEditorMode::UEditorModeEditorMode()
{
	FModuleManager::Get().LoadModule("EditorStyle");

	// appearance and icon in the editing mode ribbon can be customized here
	Info = FEditorModeInfo(UEditorModeEditorMode::EM_EditorModeEditorModeId,
		LOCTEXT("ModeName", "EditorMode"),
		FSlateIcon(),
		true);
}


UEditorModeEditorMode::~UEditorModeEditorMode()
{
	
}


void UEditorModeEditorMode::ActorSelectionChangeNotify()
{	
	UpdateSelectedActors();
}

void UEditorModeEditorMode::Enter()
{
	UEdMode::Enter(); 
	//////////////////////////////////////////////////////////////////////////
	//////////////////////////////////////////////////////////////////////////
	// AddYourTool Step 2 - register the ToolBuilders for your Tools here.
	// The string name you pass to the ToolManager is used to select/activate your ToolBuilder later.
	//////////////////////////////////////////////////////////////////////////
	////////////////////////////////////////////////////////////////////////// 
	const FEditorModeEditorModeCommands& SampleToolCommands = FEditorModeEditorModeCommands::Get();

	RegisterTool(SampleToolCommands.SimpleTool, SimpleToolName, NewObject<UEditorModeSimpleToolBuilder>(this));
	RegisterTool(SampleToolCommands.InteractiveTool, InteractiveToolName, NewObject<UEditorModeInteractiveToolBuilder>(this));

	// active tool type is not relevant here, we just set to default
	GetToolManager()->SelectActiveToolType(EToolSide::Left, SimpleToolName);
	if(!Toolkit.IsValid() && UsesToolkits())
	{
		Toolkit = MakeShareable(new FEditorModeEditorModeToolkit);
		Toolkit->Init(Owner->GetToolkitHost());
	}
	UpdateSelectedActors();
}

void UEditorModeEditorMode::Exit()
{	
	if(Toolkit.IsValid())
	{
		FToolkitManager::Get().CloseToolkit(Toolkit.ToSharedRef());
		Toolkit.Reset();
	}
	Super::Exit();
}

void UEditorModeEditorMode::CreateToolkit()
{
	Toolkit = MakeShareable(new FEditorModeEditorModeToolkit);
}

bool UEditorModeEditorMode::UsesToolkits() const
{
	//return Super::UsesToolkits();
	return true;
}

TMap<FName, TArray<TSharedPtr<FUICommandInfo>>> UEditorModeEditorMode::GetModeCommands() const
{
	return FEditorModeEditorModeCommands::Get().GetCommands();
}

void UEditorModeEditorMode::UpdateSelectedActors()
{
	SelectedActors.Empty();
	USelection* Selection = GEditor->GetSelectedActors();
	for(FSelectionIterator Iter(*Selection);Iter;++Iter)
	{
		if(AActor* SelectedActor = Cast<AActor>(*Iter))
		{
			SelectedActors.AddUnique(SelectedActor);
		}
	}
}

#undef LOCTEXT_NAMESPACE
