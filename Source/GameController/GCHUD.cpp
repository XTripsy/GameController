// Fill out your copyright notice in the Description page of Project Settings.


#include "GCHUD.h"
#include "Blueprint/UserWidget.h"
#include "interface/InterfaceWidget.h"
#include <Components/ProgressBar.h>
#include <Components/CanvasPanel.h>
#include <Kismet/GameplayStatics.h>

void AGCHUD::BeginPlay()
{
    WidgetClass = StaticLoadClass(UUserWidget::StaticClass(), nullptr, TEXT("/Game/UI/WBP_Player.WBP_Player_C"));
    MyWidget = CreateWidget<UUserWidget>(GetWorld(), WidgetClass);
    MyWidget->AddToViewport();

    GameOverClass = StaticLoadClass(UUserWidget::StaticClass(), nullptr, TEXT("/Game/UI/WBP_GameOver.WBP_GameOver_C"));
}

void AGCHUD::UpdateHealth(float current)
{
    if (current <= 0)
    {
        UGameplayStatics::SetGamePaused(GetWorld(), true);
        GameOverWidget = CreateWidget<UUserWidget>(GetWorld(), GameOverClass);
        GameOverWidget->AddToViewport();
        MyWidget->RemoveFromParent();
    }

    UProgressBar* HealthBar = Cast<UProgressBar>(MyWidget->GetWidgetFromName(TEXT("health")));
    if (HealthBar)
    {
        HealthBar->SetPercent(current);
        UE_LOG(LogTemp, Warning, TEXT("Health Updated: %f"), current);
    }
}
