// Copyright Epic Games, Inc. All Rights Reserved.

#include "EditorModeModule.h"
#include "EditorModeEditorMode.h"
#include "EditorModeEditorModeCommands.h"
#include "EditorModeEditorModeToolkit.h"
#include "EditorModeRegistry.h"

#define LOCTEXT_NAMESPACE "EditorModeModule"

void FEditorModeModule::StartupModule()
{
	// This code will execute after your module is loaded into memory; the exact timing is specified in the .uplugin file per-module
	// FEditorModeRegistry::Get().RegisterMode<UEditorModeEditorMode>
	// (UEditorModeEditorMode::EM_EditorModeEditorModeId
	// 	);
	FEditorModeEditorModeCommands::Register();
	
}

void FEditorModeModule::ShutdownModule()
{
	// This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
	// we call this function before unloading the module.

	FEditorModeRegistry::Get().UnregisterMode(UEditorModeEditorMode::EM_EditorModeEditorModeId);
	FEditorModeEditorModeCommands::Unregister();
	
}

#undef LOCTEXT_NAMESPACE

IMPLEMENT_MODULE(FEditorModeModule, EditorModeEditorMode)