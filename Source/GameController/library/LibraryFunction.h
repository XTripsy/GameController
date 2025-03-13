// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include <functional>

#define Timeline_Play 0
#define Timeline_PlayStart 1
#define Timeline_Reverse 2
#define Timeline_ReverseEnd 3

#define CameraShakeAttack 0
#define CameraShakeDamaged 1
#define CameraShakeDeflect 2

class GAMECONTROLLER_API LibraryFunction
{
public:
	static void LibraryCapsuleTraceByChannel(UWorld* World, FVector Start, FVector End, float Radius, float HalfHeight,
		ECollisionChannel TraceChannel, const AActor* ignore, bool isDebug, std::function<void(FHitResult)> onHit, std::function<void()> unHit);
	static void LibrarySphereTraceByChannel(UWorld* World, FVector Start, FVector End, float Radius,
		ECollisionChannel TraceChannel, const AActor* ignore, bool isDebug, std::function<void(FHitResult)> onHit, std::function<void()> unHit);
	static void LibraryMultiSphereTraceByChannel(UWorld* World, FVector Start, FVector End, float Radius,
		ECollisionChannel TraceChannel, const AActor* ignore, bool isDebug, std::function<void(TArray<FHitResult>&)> onHit, std::function<void()> unHit);
	static void LibraryLineTraceByChannel(UWorld* World, FVector Start, FVector End,
		ECollisionChannel TraceChannel, const AActor* ignore, bool isDebug, std::function<void(FHitResult)> onHit, std::function<void()> unHit);
	static void LibraryMultiLineTraceByChannel(UWorld* World, FVector Start, FVector End,
		ECollisionChannel TraceChannel, const AActor* ignore, bool isDebug, std::function<void(TArray<FHitResult>&)> onHit, std::function<void()> unHit);
	static void LibraryBoxTraceByChannel(UWorld* World, FVector Start, FVector End, FVector BoxExtent,
		ECollisionChannel TraceChannel, const AActor* ignore, bool isDebug, std::function<void(FHitResult)> onHit, std::function<void()> unHit);
	static void LibraryCameraShake(APlayerCameraManager* camera_manager, int shake_type);
};
