// Fill out your copyright notice in the Description page of Project Settings.

#include "../Library/LibraryFunction.h"

void LibraryFunction::LibraryCapsuleTraceByChannel(UWorld* World, FVector Start, FVector End, float Radius, float HalfHeight,
	ECollisionChannel TraceChannel, const AActor* ignore, bool isDebug, std::function<void(FHitResult)> onHit, std::function<void()> unHit)
{
	FHitResult hit_result;
	FCollisionQueryParams query_params;
	query_params.bTraceComplex = true;
	query_params.AddIgnoredActor(ignore);

	bool bHit = World->SweepSingleByChannel(
		hit_result,
		Start,
		End,
		FQuat::Identity,
		TraceChannel,
		FCollisionShape::MakeCapsule(Radius, HalfHeight),
		query_params
	);

	if (bHit)
		onHit(hit_result);
	else
		unHit();

	if (!isDebug)
		return;

	FColor TraceColor = bHit ? FColor::Green : FColor::Red;
	DrawDebugCapsule(
		World,
		End,
		HalfHeight,
		Radius,
		FQuat::Identity,
		TraceColor,
		false,
		1.5f
	);
}

void LibraryFunction::LibrarySphereTraceByChannel(UWorld* World, FVector Start, FVector End, float Radius,
	ECollisionChannel TraceChannel, const AActor* ignore, bool isDebug, std::function<void(FHitResult)> onHit, std::function<void()> unHit)
{
	FHitResult hit_result;
	FCollisionQueryParams query_params;
	query_params.bTraceComplex = true;
	query_params.AddIgnoredActor(ignore);

	bool bHit = World->SweepSingleByChannel(
		hit_result,
		Start,
		End,
		FQuat::Identity,
		TraceChannel,
		FCollisionShape::MakeSphere(Radius),
		query_params
	);

	if (bHit)
		onHit(hit_result);
	else
		unHit();

	if (!isDebug)
		return;

	FColor TraceColor = bHit ? FColor::Green : FColor::Red;
	DrawDebugSphere(
		World,
		(Start + End) / 2,
		Radius,
		12,
		TraceColor,
		false,
		1.5f
	);
}

void LibraryFunction::LibraryMultiSphereTraceByChannel(UWorld* World, FVector Start, FVector End, float Radius,
	ECollisionChannel TraceChannel, const AActor* ignore, bool isDebug, std::function<void(TArray<FHitResult>&)> onHit, std::function<void()> unHit)
{
	if (!World) return;

	TArray<FHitResult> HitResults;
	FCollisionQueryParams query_params;
	query_params.bTraceComplex = true;
	query_params.AddIgnoredActor(ignore);

	bool bHit = World->SweepMultiByChannel(
		HitResults,
		Start,
		End,
		FQuat::Identity,
		TraceChannel,
		FCollisionShape::MakeSphere(Radius),
		query_params
	);

	if (bHit)
		onHit(HitResults);
	else
		unHit();

	if (!isDebug)
		return;

	FColor TraceColor = bHit ? FColor::Green : FColor::Red;
	DrawDebugSphere(
		World,
		(Start + End) / 2,
		Radius,
		12,
		TraceColor,
		false,
		1.5f
	);
}


void LibraryFunction::LibraryLineTraceByChannel(UWorld* World, FVector Start, FVector End, 
	ECollisionChannel TraceChannel, const AActor* ignore, bool isDebug, std::function<void(FHitResult)> onHit, std::function<void()> unHit)
{
	FHitResult HitResult;
	FCollisionQueryParams QueryParams;
	QueryParams.bTraceComplex = true;
	QueryParams.AddIgnoredActor(ignore);

	bool bHit = World->LineTraceSingleByChannel(
		HitResult,
		Start,
		End,
		TraceChannel,
		QueryParams
	);

	if (bHit)
		onHit(HitResult);
	else
		unHit();

	if (!isDebug)
		return;

	FColor TraceColor = bHit ? FColor::Green : FColor::Red;
	DrawDebugLine(
		World,
		Start,
		End,
		TraceColor,
		false,
		1.5f,
		0,
		1
	);
}

void LibraryFunction::LibraryMultiLineTraceByChannel(UWorld* World, FVector Start, FVector End, 
	ECollisionChannel TraceChannel, const AActor* ignore, bool isDebug, std::function<void(TArray<FHitResult>&)> onHit, std::function<void()> unHit)
{
	TArray<FHitResult> HitResults;
	FCollisionQueryParams QueryParams;
	QueryParams.bTraceComplex = true;
	QueryParams.AddIgnoredActor(ignore);

	bool bHit = World->LineTraceMultiByChannel(
		HitResults,
		Start,
		End,
		TraceChannel,
		QueryParams
	);

	if (bHit)
		onHit(HitResults);
	else
		unHit();

	if (!isDebug)
		return;

	FColor TraceColor = bHit ? FColor::Green : FColor::Red;
	DrawDebugLine(
		World,
		Start,
		End,
		TraceColor,
		false,
		1.5f,
		0,
		1
	);
}

void LibraryFunction::LibraryBoxTraceByChannel(UWorld* World, FVector Start, FVector End, FVector BoxExtent,
	ECollisionChannel TraceChannel, const AActor* ignore, bool isDebug, std::function<void(FHitResult)> onHit, std::function<void()> unHit)
{
	FHitResult hit_result;
	FCollisionQueryParams query_params;
	query_params.bTraceComplex = true;
	query_params.AddIgnoredActor(ignore);

	bool bHit = World->SweepSingleByChannel(
		hit_result,
		Start,
		End,
		FQuat::Identity,
		TraceChannel,
		FCollisionShape::MakeBox(BoxExtent),
		query_params
	);

	if (bHit)
		onHit(hit_result);
	else
		unHit();

	if (!isDebug)
		return;

	FColor TraceColor = bHit ? FColor::Green : FColor::Red;
	DrawDebugBox(
		World,
		(Start + End) / 2,
		BoxExtent,
		TraceColor,
		false,
		1.5f
	);
}
