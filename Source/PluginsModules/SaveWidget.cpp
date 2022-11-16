// Fill out your copyright notice in the Description page of Project Settings.


#include "SaveWidget.h"

#include "MyGameInstance.h"
#include "TestSaveGame.h"
#include "GameFramework/Character.h"
#include "Kismet/GameplayStatics.h"
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
		ACharacter* Character = UGameplayStatics::GetPlayerCharacter(GetWorld(),0);		
		UTestSaveGame* SaveGame  = MyGameInstance->SaveManager->GetCurrentGameObject();
		SaveGame->CharacterTransform = Character->GetActorTransform();
		MyGameInstance->SaveManager->SaveCurrentGame(EditableText->GetText().ToString());	
	}
	
}

void USaveWidget::OnLoadButtonPressed()
{
	if(!EditableText->GetText().ToString().IsEmpty())
	{
		MyGameInstance->SaveManager->LoadGame(EditableText->GetText().ToString());
		ACharacter* Character = UGameplayStatics::GetPlayerCharacter(GetWorld(),0);		
		UTestSaveGame* SaveGame  = MyGameInstance->SaveManager->GetCurrentGameObject();
		Character->SetActorTransform(SaveGame->CharacterTransform);
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
