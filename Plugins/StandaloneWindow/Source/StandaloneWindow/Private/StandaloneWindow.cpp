// Copyright Epic Games, Inc. All Rights Reserved.

#include "StandaloneWindow.h"
#include "StandaloneWindowStyle.h"
#include "StandaloneWindowCommands.h"
#include "LevelEditor.h"
#include "Selection.h"
#include "Widgets/Docking/SDockTab.h"
#include "Widgets/Layout/SBox.h"
#include "Widgets/Text/STextBlock.h"
#include "ToolMenus.h"

static const FName StandaloneWindowTabName("StandaloneWindow");

#define LOCTEXT_NAMESPACE "FStandaloneWindowModule"

void FStandaloneWindowModule::StartupModule()
{
	
	FLevelEditorModule& LevelEditorModule = FModuleManager::LoadModuleChecked<FLevelEditorModule>("LevelEditor");
	{
		TSharedPtr<FExtender> MenuExtender = MakeShareable(new FExtender());
		MenuExtender->AddMenuExtension("WindowLayout", EExtensionHook::After,PluginCommands,
			FMenuExtensionDelegate::CreateRaw(this,&FStandaloneWindowModule::AddMenuExtension));

		LevelEditorModule.GetMenuExtensibilityManager()->AddExtender(MenuExtender);
		
	}

	{
		TSharedPtr<FExtender> ToolBarExtender = MakeShareable(new FExtender);
		ToolBarExtender->AddToolBarExtension("Settings",EExtensionHook::After,PluginCommands,
			FToolBarExtensionDelegate::CreateRaw(this,&FStandaloneWindowModule::AddToolbarExtension));

		LevelEditorModule.GetToolBarExtensibilityManager()->AddExtender(ToolBarExtender);
	}

	FGlobalTabmanager::Get()->RegisterNomadTabSpawner(StandaloneWindowTabName,
		FOnSpawnTab::CreateRaw(this,&FStandaloneWindowModule::OnSpawnPluginTab))
	.SetDisplayName(LOCTEXT("FStandaloneWindowModule","FStandaloneWindow"))
	.SetMenuType(ETabSpawnerMenuType::Hidden);
	
	// This code will execute after your module is loaded into memory; the exact timing is specified in the .uplugin file per-module
	
	FStandaloneWindowStyle::Initialize();
	FStandaloneWindowStyle::ReloadTextures();

	FStandaloneWindowCommands::Register();
	
	PluginCommands = MakeShareable(new FUICommandList);

	PluginCommands->MapAction(
		FStandaloneWindowCommands::Get().OpenPluginWindow,
		FExecuteAction::CreateRaw(this, &FStandaloneWindowModule::PluginButtonClicked),
		FCanExecuteAction());

	UToolMenus::RegisterStartupCallback(FSimpleMulticastDelegate::FDelegate::CreateRaw(this, &FStandaloneWindowModule::RegisterMenus));
	
	FGlobalTabmanager::Get()->RegisterNomadTabSpawner(StandaloneWindowTabName, FOnSpawnTab::CreateRaw(this, &FStandaloneWindowModule::OnSpawnPluginTab))
		.SetDisplayName(LOCTEXT("FStandaloneWindowTabTitle", "StandaloneWindow"))
		.SetMenuType(ETabSpawnerMenuType::Hidden);
}

void FStandaloneWindowModule::ShutdownModule()
{
	// This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
	// we call this function before unloading the module.

	UToolMenus::UnRegisterStartupCallback(this);

	UToolMenus::UnregisterOwner(this);

	FStandaloneWindowStyle::Shutdown();

	FStandaloneWindowCommands::Unregister();

	FGlobalTabmanager::Get()->UnregisterNomadTabSpawner(StandaloneWindowTabName);
}

TSharedRef<SDockTab> FStandaloneWindowModule::OnSpawnPluginTab(const FSpawnTabArgs& SpawnTabArgs)
{
	// FText WidgetText = FText::Format(
	// 	LOCTEXT("WindowWidgetText", "Add code to {0} in {1} to override this window's contents"),
	// 	FText::FromString(TEXT("FStandaloneWindowModule::OnSpawnPluginTab")),
	// 	FText::FromString(TEXT("StandaloneWindow.cpp"))
	// 	);
	FText WidgetText = FText::FromString("Move selected actors");
	return SNew(SDockTab)
		.TabRole(ETabRole::NomadTab)
		[
			// Put your tab content here!
			SNew(SBox)
			.HAlign(HAlign_Center)
			.VAlign(VAlign_Center)
			[
				// SNew(STextBlock)
				// .Text(WidgetText)
			
			SNew(SButton)
			.OnClicked_Lambda([]()
				{
					if (GEditor)
					{
						for (FSelectionIterator Iter((GEditor->GetSelectedActorIterator())); Iter; ++Iter)
						{
							AActor* Actor = Cast<AActor>(*Iter);if (Actor)
							if(Actor)
							{
								Actor->AddActorLocalOffset(FVector(50.f));
		                    }
	                    }
                    }
                    return FReply::Handled();
                })
            [
	            SNew(STextBlock)
	            .Text(WidgetText)
            ]
        ]
    ];
}


void FStandaloneWindowModule::PluginButtonClicked()
{
	FGlobalTabmanager::Get()->TryInvokeTab(StandaloneWindowTabName);
}

void FStandaloneWindowModule::RegisterMenus()
{
	// Owner will be used for cleanup in call to UToolMenus::UnregisterOwner
	FToolMenuOwnerScoped OwnerScoped(this);

	{
		UToolMenu* Menu = UToolMenus::Get()->ExtendMenu("LevelEditor.MainMenu.Window");
		{
			FToolMenuSection& Section = Menu->FindOrAddSection("WindowLayout");
			Section.AddMenuEntryWithCommandList(FStandaloneWindowCommands::Get().OpenPluginWindow, PluginCommands);
		}
	}

	{
		UToolMenu* ToolbarMenu = UToolMenus::Get()->ExtendMenu("LevelEditor.LevelEditorToolBar");
		{
			FToolMenuSection& Section = ToolbarMenu->FindOrAddSection("Settings");
			{
				FToolMenuEntry& Entry = Section.AddEntry(FToolMenuEntry::InitToolBarButton(FStandaloneWindowCommands::Get().OpenPluginWindow));
				Entry.SetCommandList(PluginCommands);
			}
		}
	}
}

void FStandaloneWindowModule::AddToolbarExtension(FToolBarBuilder& Builder)
{
	Builder.AddToolBarButton(FStandaloneWindowCommands::Get().OpenPluginWindow);
}

void FStandaloneWindowModule::AddMenuExtension(FMenuBuilder& Builder)
{
	Builder.AddMenuEntry(FStandaloneWindowCommands::Get().OpenPluginWindow);
}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FStandaloneWindowModule, StandaloneWindow)