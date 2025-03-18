// Fill out your copyright notice in the Description page of Project Settings.


#include "GCPlayerController.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputActionValue.h"
#include "InputMappingContext.h"
#include "interface/InterfacePlayer.h"

AGCPlayerController::AGCPlayerController()
{
	static ConstructorHelpers::FObjectFinder<UInputMappingContext>mapping_context(TEXT("/Game/Input/IMC_Input"));
	static ConstructorHelpers::FObjectFinder<UInputAction> cursor_action(TEXT("/Game/Input/InputAction/IA_Cursor"));
	static ConstructorHelpers::FObjectFinder<UInputAction> shoot_action(TEXT("/Game/Input/InputAction/IA_Shoot"));
	static ConstructorHelpers::FObjectFinder<UInputAction> move_action(TEXT("/Game/Input/InputAction/IA_Move"));

	InputMappingContext = mapping_context.Object;
	CursorAction = cursor_action.Object;
	ShootAction = shoot_action.Object;
	MoveAction = move_action.Object;

	fSensitivity = 5.0f;
}

void AGCPlayerController::BeginPlay()
{
	Super::BeginPlay();

	if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer()))
		Subsystem->AddMappingContext(InputMappingContext, 0);

	InterfacePlayer = Cast<IInterfacePlayer>(UGameplayStatics::GetPlayerController(GetWorld(), 0)->GetPawn());
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
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AGCPlayerController::Move);
		EnhancedInputComponent->BindAction(CursorAction, ETriggerEvent::Triggered, this, &AGCPlayerController::Cursor);
		EnhancedInputComponent->BindAction(CursorAction, ETriggerEvent::Completed, this, &AGCPlayerController::CursorIdle);
		EnhancedInputComponent->BindAction(ShootAction, ETriggerEvent::Triggered, this, &AGCPlayerController::Shoot);
		EnhancedInputComponent->BindAction(ShootAction, ETriggerEvent::Completed, this, &AGCPlayerController::EndShoot);
	}
}

void AGCPlayerController::Move(const FInputActionValue& Value)
{
	float input_move = Value.Get<float>();
	UE_LOG(LogTemp, Warning, TEXT("%f"), input_move);
	InterfacePlayer->IMove(input_move);
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

	if (bIsShoot) return;
	CurrentMouseCursor = EMouseCursor::Hand;
}

void AGCPlayerController::CursorIdle(const FInputActionValue& value)
{
	if (bIsShoot) return;
	CurrentMouseCursor = EMouseCursor::Default;
}

void AGCPlayerController::Shoot()
{
	UE_LOG(LogTemp, Error, TEXT("Shoot"));
	bIsShoot = true;
	CurrentMouseCursor = EMouseCursor::GrabHand;
}

void AGCPlayerController::EndShoot()
{
	bIsShoot = false;
	CurrentMouseCursor = EMouseCursor::Default;
}
