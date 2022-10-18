// Fill out your copyright notice in the Description page of Project Settings.


#include "MyMediaPlayer.h"
#include "DesktopPlatformModule.h"
#include "FileMediaSource.h"
#include "IDesktopPlatform.h"

// Sets default values
AMyMediaPlayer::AMyMediaPlayer()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AMyMediaPlayer::BeginPlay()
{
	Super::BeginPlay();
	FString Path;	
	TArray<FString> OutFileNames;
	IDesktopPlatform* DesktopPlatform = FDesktopPlatformModule::Get();
	if (DesktopPlatform)
	{
		FString FileTypes = "All Files(*.PNG;*.JPG;*.MP4)|*.PNG;*.JPG;*.MP4|"
		"Image Files(*.PNG;*.JPG;)|*.PNG;*.JPG;|"
		"Video Files(*.MP4)|*.MP4";
		uint32 SelectionFlag = 0;
		auto* ParentHandle = FSlateApplication::Get().FindBestParentWindowHandleForDialogs(nullptr);
		DesktopPlatform->OpenFileDialog(ParentHandle,"Choose content", "", "", FileTypes, SelectionFlag, OutFileNames);
		if (OutFileNames.Num() > 0)
		{
			Path = OutFileNames[0];
		}
	}
	if(MediaPlayer)
	{
		UFileMediaSource * MediaSource = NewObject<UFileMediaSource>();
		MediaSource->FilePath = Path;
		MediaPlayer->OpenSource(MediaSource);
	}
	if(SoundComponent)
	{
		SoundComponent = NewObject<UMediaSoundComponent>(this);
		SoundComponent->SetMediaPlayer(MediaPlayer);
		SoundComponent->RegisterComponent();
	}
	MediaPlayer->Play();
}

// Called every frame
void AMyMediaPlayer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
}

