// Fill out your copyright notice in the Description page of Project Settings.


#include "TestSaveGame.h"

#include "MyGameInstance.h"
#include "GameFramework/Character.h"
#include "Kismet/GameplayStatics.h"


void UTestSaveGame::OnFileLoad(UWorld* ThisWorld)
{
	ACharacter* Character = UGameplayStatics::GetPlayerCharacter(ThisWorld,0);		
	Character->SetActorTransform(CharacterTransform);
}

void UTestSaveGame::OnFileSave(UWorld* ThisWorld)
{
	ACharacter* Character = UGameplayStatics::GetPlayerCharacter(ThisWorld,0);		
	CharacterTransform = Character->GetActorTransform();	
}
