// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "interface/InterfaceHUD.h"
#include "GCHUD.generated.h"

class IInterfaceWidget;

UCLASS()
class GAMECONTROLLER_API AGCHUD : public AHUD, public IInterfaceHUD
{
	GENERATED_BODY()
	
public:
	AGCHUD() = default;

	virtual void BeginPlay() override;

protected:
	UPROPERTY(EditAnywhere, Category = "UI")
	TSubclassOf<class UUserWidget> WidgetClass;

	UPROPERTY(EditAnywhere, Category = "UI")
	TSubclassOf<class UUserWidget> GameOverClass;

	UPROPERTY()
	class UUserWidget* MyWidget;

	UPROPERTY()
	class UUserWidget* GameOverWidget;

private:
	IInterfaceWidget* iInterfaceWidget;

private:
	virtual void UpdateHealth(float current) override;
};
