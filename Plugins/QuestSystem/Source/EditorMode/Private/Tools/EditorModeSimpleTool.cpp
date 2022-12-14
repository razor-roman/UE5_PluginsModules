// Copyright Epic Games, Inc. All Rights Reserved.

 #include "EditorModeSimpleTool.h"
#include "InteractiveToolManager.h"
#include "ToolBuilderUtil.h"
#include "CollisionQueryParams.h"
#include "Quest.h"
#include "QuestSystemCharacter.h"
#include "Engine/World.h"

// localization namespace
#define LOCTEXT_NAMESPACE "EditorModeSimpleTool"

/*
 * ToolBuilder implementation
 */

class AQuest;

UInteractiveTool* UEditorModeSimpleToolBuilder::BuildTool(const FToolBuilderState& SceneState) const
{
	UEditorModeSimpleTool* NewTool = NewObject<UEditorModeSimpleTool>(SceneState.ToolManager);
	NewTool->SetWorld(SceneState.World);
	return NewTool;
}



/*
 * ToolProperties implementation
 */

UEditorModeSimpleToolProperties::UEditorModeSimpleToolProperties()
{
	ShowExtendedInfo = true;
}


/*
 * Tool implementation
 */

UEditorModeSimpleTool::UEditorModeSimpleTool()
{
}


void UEditorModeSimpleTool::SetWorld(UWorld* World)
{
	this->TargetWorld = World;
}


void UEditorModeSimpleTool::Setup()
{
	USingleClickTool::Setup();

	Properties = NewObject<UEditorModeSimpleToolProperties>(this);
	AddToolPropertySource(Properties);
}


void UEditorModeSimpleTool::OnClicked(const FInputDeviceRay& ClickPos)
{
	// we will create actor at this position
	FVector NewActorPos = FVector::ZeroVector;

	// cast ray into world to find hit position
	FVector RayStart = ClickPos.WorldRay.Origin;
	FVector RayEnd = ClickPos.WorldRay.PointAt(99999999.f);
	FCollisionObjectQueryParams QueryParams(FCollisionObjectQueryParams::AllObjects);
	FHitResult Result;
	if (TargetWorld->LineTraceSingleByObjectType(Result, RayStart, RayEnd, QueryParams))
	{
		ClickedActor = Result.GetActor();
		// if (AActor* ClickedActor = Result.GetActor())
		// {
		// 	FText ActorInfoMsg;
		//
		// 	if (Properties->ShowExtendedInfo)
		// 	{
		// 		ActorInfoMsg = FText::Format(LOCTEXT("ExtendedActorInfo", "Name: {0}\nClass: {1}"), 
		// 			FText::FromString(ClickedActor->GetName()), 
		// 			FText::FromString(ClickedActor->GetClass()->GetName())
		// 		);
		// 	}
		// 	else
		// 	{
		// 		ActorInfoMsg = FText::Format(LOCTEXT("BasicActorInfo", "Name: {0}"), FText::FromString(Result.GetActor()->GetName()));
		// 	}
		//
		// 	FText Title = LOCTEXT("ActorInfoDialogTitle", "Actor Info");
		// 	// JAH TODO: consider if we can highlight the actor prior to opening the dialog box or make it non-modal
		// 	FMessageDialog::Open(EAppMsgType::Ok, ActorInfoMsg, &Title);
		// }
	}
}

bool UEditorModeSimpleTool::IsSelectedInEditor() const
{
	return Super::IsSelectedInEditor();
}

void UEditorModeSimpleTool::Render(IToolsContextRenderAPI* RenderAPI)
{
	Super::Render(RenderAPI);
	FPrimitiveDrawInterface* PDI = RenderAPI->GetPrimitiveDrawInterface();
	Super::Render(RenderAPI);
	USelection* ActorsSelection = GEditor->GetSelectedActors();
	
   	if(ClickedActor)
	{
		DrawWireBox(PDI,ClickedActor->GetComponentsBoundingBox(true),FColor::Yellow,1);
	}
	if(AQuestSystemCharacter* QuestSystemCharacter = Cast<AQuestSystemCharacter>(ClickedActor))
	{
		TArray<AActor*> AttachedActors;
		QuestSystemCharacter->GetAttachedActors(AttachedActors);
		for(auto AttachedActor : AttachedActors)
		{
			if(AQuest* QuestActor = Cast<AQuest>(AttachedActor))
			{
				TArray<UObjective*> Objectives = QuestActor->GetObjectives();
				if(Objectives.Num()==0) return;
				for(auto Objective : Objectives)
				{
					if(!Objective) continue;
					if(Objective->GetActor() && Objective)
					{
						DrawWireBox(PDI,Objective->GetActor()->GetComponentsBoundingBox(true),FColor::Red,1);
					}
				}
			}
		}
		
	}
}


#undef LOCTEXT_NAMESPACE
