// Fill out your copyright notice in the Description page of Project Settings.


#include "GCPlayerController.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputActionValue.h"
#include "InputMappingContext.h"

AGCPlayerController::AGCPlayerController()
{
	static ConstructorHelpers::FObjectFinder<UInputMappingContext>mapping_context(TEXT("/Game/Input/IMC_Input"));
	static ConstructorHelpers::FObjectFinder<UInputAction> cursor_action(TEXT("/Game/Input/InputAction/IA_Cursor"));
	static ConstructorHelpers::FObjectFinder<UInputAction> shoot_action(TEXT("/Game/Input/InputAction/IA_Shoot"));

	InputMappingContext = mapping_context.Object;
	CursorAction = cursor_action.Object;
	ShootAction = shoot_action.Object;

	fSensitivity = 5.0f;
}

void AGCPlayerController::BeginPlay()
{
	Super::BeginPlay();

	if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer()))
		Subsystem->AddMappingContext(InputMappingContext, 0);
}

void AGCPlayerController::Tick(float deltaTime)
{
	Super::Tick(deltaTime);
}

void AGCPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(InputComponent))
	{
		EnhancedInputComponent->BindAction(CursorAction, ETriggerEvent::Triggered, this, &AGCPlayerController::Cursor);
		EnhancedInputComponent->BindAction(CursorAction, ETriggerEvent::Completed, this, &AGCPlayerController::CursorIdle);
		EnhancedInputComponent->BindAction(ShootAction, ETriggerEvent::Triggered, this, &AGCPlayerController::Shoot);
		EnhancedInputComponent->BindAction(ShootAction, ETriggerEvent::Completed, this, &AGCPlayerController::EndShoot);
	}
}

void AGCPlayerController::Cursor(const FInputActionValue& Value)
{
	FVector2D crosshair_vector = Value.Get<FVector2D>();
	FVector world_location, world_direction;

	bShowMouseCursor = true;
	bEnableClickEvents = true;
	bEnableMouseOverEvents = true;

	GetMousePosition(vMousePosition.X, vMousePosition.Y);
	SetMouseLocation(vMousePosition.X + crosshair_vector.X * fSensitivity, vMousePosition.Y - crosshair_vector.Y * fSensitivity);
	DeprojectScreenPositionToWorld(vMousePosition.X, vMousePosition.Y, world_location, world_direction);

	CurrentMouseCursor = EMouseCursor::Hand;
}

void AGCPlayerController::CursorIdle(const FInputActionValue& value)
{
	CurrentMouseCursor = EMouseCursor::Default;
}

void AGCPlayerController::Shoot()
{
	UE_LOG(LogTemp, Error, TEXT("Shoot"));
	CurrentMouseCursor = EMouseCursor::GrabHand;
}

void AGCPlayerController::EndShoot()
{
	CurrentMouseCursor = EMouseCursor::Default;
}
