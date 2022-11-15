// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "InteractiveToolBuilder.h"
#include "BaseTools/SingleClickTool.h"
#include "EditorModeSimpleTool.generated.h"

/**
 * Builder for UEditorModeSimpleTool
 */
UCLASS()
class EDITORMODE_API UEditorModeSimpleToolBuilder : public UInteractiveToolBuilder
{
	GENERATED_BODY()

public:
	
	virtual bool CanBuildTool(const FToolBuilderState& SceneState) const override { return true; }
	virtual UInteractiveTool* BuildTool(const FToolBuilderState& SceneState) const override;
};



/**
 * Settings UObject for UEditorModeSimpleTool. This UClass inherits from UInteractiveToolPropertySet,
 * which provides an OnModified delegate that the Tool will listen to for changes in property values.
 */
UCLASS(Transient)
class EDITORMODE_API UEditorModeSimpleToolProperties : public UInteractiveToolPropertySet
{
	GENERATED_BODY()
public:
	UEditorModeSimpleToolProperties();
	
	/** If enabled, dialog should display extended information about the actor clicked on. Otherwise, only basic info will be shown. */
	UPROPERTY(EditAnywhere, Category = Options, meta = (DisplayName = "Show Extended Info"))
	bool ShowExtendedInfo;
};




/**
 * UEditorModeSimpleTool is an example Tool that opens a message box displaying info about an actor that the user
 * clicks left mouse button. All the action is in the ::OnClicked handler.
 */
UCLASS()
class EDITORMODE_API UEditorModeSimpleTool : public USingleClickTool
{
	GENERATED_BODY()

public:
	UEditorModeSimpleTool();

	virtual void SetWorld(UWorld* World);

	virtual void Setup() override;
	
	virtual void OnClicked(const FInputDeviceRay& ClickPos);
	virtual bool IsSelectedInEditor() const override;	
	virtual void Render(IToolsContextRenderAPI* RenderAPI) override;
	
protected:
	UPROPERTY()
	TObjectPtr<UEditorModeSimpleToolProperties> Properties;
	AActor* ClickedActor;

protected:
	/** target World we will raycast into to find actors */
	UWorld* TargetWorld;
};