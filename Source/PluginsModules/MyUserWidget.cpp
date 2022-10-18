// Fill out your copyright notice in the Description page of Project Settings.


#include "MyUserWidget.h"

#include "DesktopPlatformModule.h"
#include "FileMediaSource.h"
#include "IDesktopPlatform.h"
#include "Kismet/KismetRenderingLibrary.h"
#include "Kismet/KismetSystemLibrary.h"


void UMyUserWidget::NativeConstruct()
{
	Super::NativeConstruct();
	if(OpenWindowButton)
		OpenWindowButton->OnClicked.AddDynamic(this,&UMyUserWidget::OnOpenWindowButtonClicked);
	else UKismetSystemLibrary::PrintString(GetWorld(),"No OpenWinBut",true);	
	if(PlayButton)
		PlayButton->OnClicked.AddDynamic(this,&UMyUserWidget::OnPlayButtonClicked);
	else UKismetSystemLibrary::PrintString(GetWorld(),"No Play Button",true);	
	
}

void UMyUserWidget::NativeDestruct()
{
	
	Super::NativeDestruct();
}

void UMyUserWidget::OnPlayButtonClicked()
{
	UFileMediaSource * MediaSource = NewObject<UFileMediaSource>();
	MediaSource->FilePath = Path;
	MediaPlayer->OpenSource(MediaSource);
	
	if(MediaPlayer && Path.EndsWith("jpg"))
	{
		Video->SetVisibility(ESlateVisibility::Hidden);
		Image->SetVisibility(ESlateVisibility::Visible);
		UTexture2D * Texture = UKismetRenderingLibrary::ImportFileAsTexture2D(this,Path);		
		Image->SetBrushFromTexture(Texture,true);
		// FVector2D Size;
		// Size.X=100;
		// Size.Y=100;
		// FVector2D ViewportSize = FVector2D(GEngine->GameViewport->Viewport->GetSizeXY());
		// FVector2D Resolution = FVector2D(GSystemResolution.ResX, GSystemResolution.ResY);
		// FVector2D newSize(Resolution.X * DesignTimeSize.X / ViewportSize.X, Resolution.Y * DesignTimeSize.Y / ViewportSize.Y);Image->Brush.SetImageSize(Size);
		// Image->SetBrushSize(newSize);
		MediaPlayer->Play();
		
	}		
	if(MediaPlayer && Path.EndsWith("mp4"))
	{
		Video->SetVisibility(ESlateVisibility::Visible);
		Image->SetVisibility(ESlateVisibility::Hidden);
		UKismetSystemLibrary::PrintString(GetWorld(),"mp4",true);
		if(MediaSource) MediaPlayer->Play();
		else UKismetSystemLibrary::PrintString(GetWorld(),"Nothing to Play",true);	
	}
	
	
}

void UMyUserWidget::OnOpenWindowButtonClicked()
{	
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
			Path=OutFileNames[0];
		}
	}
}
