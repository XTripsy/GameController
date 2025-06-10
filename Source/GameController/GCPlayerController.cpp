// GCPlayerController.cpp (Final Version)

#include "GCPlayerController.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputActionValue.h"
#include "InputMappingContext.h"
#include "interface/InterfacePlayer.h"
#include "library/LibraryFunction.h"
#include "interface/InterfaceGameMode.h"
#include "GameFramework/GameModeBase.h"
#include "SerialCom.h"

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

	fSensitivity = 1000.0f;
	PortID = 4; // Ganti dengan nomor Port COM Arduino Anda
	BaudRate = 9600;

	SerialPort = NewObject<USerialCom>();
}

void AGCPlayerController::BeginPlay()
{
	Super::BeginPlay();

	if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer()))
		Subsystem->AddMappingContext(InputMappingContext, 0);

	InterfacePlayer = Cast<IInterfacePlayer>(UGameplayStatics::GetPlayerController(GetWorld(), 0)->GetPawn());
	InterfaceGameMode = Cast<IInterfaceGameMode>(GetWorld()->GetAuthGameMode());
	CloseSerialPort();
	
	OpenSerialPort(PortID, BaudRate);

	bShowMouseCursor = true;
	bEnableClickEvents = true;
	bEnableMouseOverEvents = true;
}

void AGCPlayerController::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);
	CloseSerialPort();
}

void AGCPlayerController::Tick(float deltaTime)
{
	Super::Tick(deltaTime);
	ProcessSerialData(deltaTime);
}

void AGCPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(InputComponent))
	{
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AGCPlayerController::Move);
		EnhancedInputComponent->BindAction(CursorAction, ETriggerEvent::Triggered, this, &AGCPlayerController::Cursor);
		EnhancedInputComponent->BindAction(CursorAction, ETriggerEvent::Completed, this, &AGCPlayerController::CursorIdle);
		EnhancedInputComponent->BindAction(ShootAction, ETriggerEvent::Started, this, &AGCPlayerController::Shoot);
		EnhancedInputComponent->BindAction(ShootAction, ETriggerEvent::Completed, this, &AGCPlayerController::EndShoot);
	}
}

void AGCPlayerController::Move(const FInputActionValue& Value)
{
	float input_move = Value.Get<float>();
	UE_LOG(LogTemp, Warning, TEXT("%f"), input_move);
	//InterfacePlayer->IMove(input_move);
}

void AGCPlayerController::ProcessSerialData(float DeltaTime)
{
	if (!SerialPort || !SerialPort->IsOpened()) return;

	bool bIsReadSuccessful = false;
	const FString DataFromSerial = SerialPort->ReadString(bIsReadSuccessful);

	// PENANDA 1: Cek apakah ada data mentah yang masuk
	if (bIsReadSuccessful && !DataFromSerial.IsEmpty())
	{
		UE_LOG(LogTemp, Warning, TEXT("Data Mentah Diterima: %s"), *DataFromSerial); // Tambahkan ini
		SerialBuffer.Append(DataFromSerial);
	}

	FString Line;
	FString RemainingBuffer;
	if (SerialBuffer.Split(TEXT("\n"), &Line, &RemainingBuffer, ESearchCase::IgnoreCase))
	{
		SerialBuffer = RemainingBuffer;

		// PENANDA 2: Cek apakah baris data berhasil dipisahkan
		UE_LOG(LogTemp, Warning, TEXT("Baris Diproses: %s"), *Line); // Tambahkan ini

		FString GyroX_Str, GyroY_Str;
		FString TempStr;

		if (Line.Split(TEXT("Y"), &TempStr, &GyroY_Str))
		{
			if (TempStr.Split(TEXT("X"), nullptr, &GyroX_Str))
			{
				const float GyroX = FCString::Atof(*GyroX_Str);
				const float GyroY = FCString::Atof(*GyroY_Str);

				// PENANDA 3: Cek apakah angka berhasil di-parse
				UE_LOG(LogTemp, Warning, TEXT("Nilai Final: X=%.2f, Y=%.2f"), GyroX, GyroY); // Tambahkan ini

				FVector2D CurrentMousePosition;
				GetMousePosition(CurrentMousePosition.X, CurrentMousePosition.Y);

				const float NewX = CurrentMousePosition.X + (GyroX * fSensitivity * DeltaTime);
				const float NewY = CurrentMousePosition.Y + (GyroY * fSensitivity * DeltaTime);

				SetMouseLocation(NewX, NewY);
			}
		}
	}
}

void AGCPlayerController::Cursor(const FInputActionValue& Value)
{
	// Dibiarkan kosong
}

void AGCPlayerController::CursorIdle(const FInputActionValue& value)
{
	// Anda mungkin perlu mendeklarasikan bIsShoot di file .h jika belum ada
	if (bIsShoot) return;
	CurrentMouseCursor = EMouseCursor::Default;
}

void AGCPlayerController::Shoot()
{
	// Variabel-variabel ini harus dideklarasikan di file .h Anda
	// atau sebagai variabel lokal di sini jika hanya digunakan di sini.
	//FVector2D vMousePosition;
	//FVector vMouseWorldLocation;
	FVector world_location;

	GetMousePosition(vMousePosition.X, vMousePosition.Y);
	DeprojectScreenPositionToWorld(vMousePosition.X, vMousePosition.Y, world_location, vMouseWorldLocation);

	AActor* player_actor = GetPawn();
	if (!player_actor) return;

	FVector player_start = player_actor->GetActorLocation();
	FVector player_end = vMouseWorldLocation.GetSafeNormal() * 10000 + player_start;
	player_end.Y = 0;

	if (InterfaceGameMode)
	{
		LibraryFunction::LibraryLineTraceByChannel(GetWorld(), player_start, player_end, ECC_Visibility, player_actor, false,
			[&](FHitResult hit)
			{
				InterfaceGameMode->ISpawnProjectile(player_start, hit.ImpactPoint);
			},
			[&]()
			{
				InterfaceGameMode->ISpawnProjectile(player_start, player_end);
			}
		);
	}

	// Anda mungkin perlu mendeklarasikan bIsShoot di file .h jika belum ada
	bIsShoot = true;
	CurrentMouseCursor = EMouseCursor::GrabHand;
}

void AGCPlayerController::EndShoot()
{
	// Anda mungkin perlu mendeklarasikan bIsShoot di file .h jika belum ada
	bIsShoot = false;
	CurrentMouseCursor = EMouseCursor::Default;
}

void AGCPlayerController::OpenSerialPort(int32 InPortID, int32 InBaudRate)
{
	if (!SerialPort) return;

	bool bOpened = false;
	SerialPort->OpenComPort(bOpened, InPortID, InBaudRate);

	if (bOpened)
	{
		UE_LOG(LogTemp, Warning, TEXT("Serial Port COM%d terbuka dengan sukses!"), InPortID);
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("Gagal membuka Serial Port COM%d!"), InPortID);
	}
}

void AGCPlayerController::CloseSerialPort()
{
	if (!SerialPort || !SerialPort->IsOpened()) return;

	SerialPort->Close();
	UE_LOG(LogTemp, Warning, TEXT("Serial Port ditutup."));
}