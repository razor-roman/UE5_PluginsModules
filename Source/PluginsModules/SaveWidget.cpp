// Fill out your copyright notice in the Description page of Project Settings.


#include "SaveWidget.h"

#include "MyGameInstance.h"
#include "Kismet/KismetMathLibrary.h"

void USaveWidget::NativeConstruct()
{
	Super::NativeConstruct();
	SaveButton->OnPressed.AddDynamic(this,&USaveWidget::OnSaveButtonPressed);
	LoadButton->OnPressed.AddDynamic(this,&USaveWidget::OnLoadButtonPressed);
	RandomButton->OnPressed.AddDynamic(this,&USaveWidget::OnRandomButtonPressed);
	PrintSavesListButton->OnPressed.AddDynamic(this,&USaveWidget::OnRPrintSavesListButtonPressed);
	MyGameInstance = Cast<UMyGameInstance>(GetGameInstance());
	
}

void USaveWidget::NativeDestruct()
{
	Super::NativeDestruct();
	
}

void USaveWidget::OnSaveButtonPressed()
{
	if(!EditableText->GetText().ToString().IsEmpty())
	{		
		MyGameInstance->SaveManager->SaveCurrentGame(EditableText->GetText().ToString());
		MyGameInstance->SaveManager->ExportSaveGameToJsonFile(EditableText->GetText().ToString(),0);
	}
	
}

void USaveWidget::OnLoadButtonPressed()
{
	if(!EditableText->GetText().ToString().IsEmpty())
	{
		MyGameInstance->SaveManager->ImportSaveGameFromJsonFile(EditableText->GetText().ToString(),0);
		MyGameInstance->SaveManager->LoadGame(EditableText->GetText().ToString());
	}
	
}

void USaveWidget::OnRandomButtonPressed()
{
	EditableText->SetText(FText::AsNumber(UKismetMathLibrary::RandomFloat()));
}

void USaveWidget::OnRPrintSavesListButtonPressed()
{
	TArray<FString> ExistingSavedSlots = MyGameInstance->SaveManager->GetExistingSavedSlots();
	for(FString ExistingSavedSlot : ExistingSavedSlots)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red,ExistingSavedSlot);
	}
	
}
