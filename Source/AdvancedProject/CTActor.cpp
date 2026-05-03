#include "CTActor.h"

#include "MyTestDamageType.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetSystemLibrary.h"

ACTActor::ACTActor()
{
	PrimaryActorTick.bCanEverTick = true;
}

void ACTActor::BeginPlay()
{
	Super::BeginPlay();
}

void ACTActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	//StartSingleTrace();
}

/*void ACTActor::StartSingleTrace()
{
	TArray<FHitResult> HitResult;
	TArray<AActor*> ActorsToIgnore;
	ActorsToIgnore.Add(this);

	UKismetSystemLibrary::LineTraceMulti(
		GetWorld(),
		GetActorLocation(),
		GetActorForwardVector() * 1000.0f + GetActorLocation(),
		UEngineTypes::ConvertToTraceType(ECC_Visibility),
		false,
		ActorsToIgnore,
		EDrawDebugTrace::ForOneFrame,
		HitResult,
		true,
		FLinearColor::Red,
		FLinearColor::Green
	);
}*/

void ACTActor::StartAsyncTrace()
{
	FTraceDelegate TraceDelegate;
	TraceDelegate.BindUObject(this, &ACTActor::OnAsyncTraceCompleted);

	FCollisionResponseParams ResponseParams;
	ResponseParams.CollisionResponse.WorldDynamic = ECR_Block; // 부딪히는 걸 강제로 타입 변환

	FCollisionQueryParams QueryParams;
	QueryParams.AddIgnoredActor(this);
	QueryParams.bTraceComplex = false;

	GetWorld()->AsyncLineTraceByChannel(
		EAsyncTraceType::Multi,
		GetActorLocation(),
		GetActorForwardVector() * 1000.0f + GetActorLocation(),
		ECC_Visibility,
		QueryParams,
		ResponseParams,
		&TraceDelegate
	);
}

void ACTActor::OnAsyncTraceCompleted(const FTraceHandle& Handle, FTraceDatum& Data)
{
	for (const FHitResult& Hit : Data.OutHits)
	{
		AActor* HitActor = Hit.GetActor();

		GEngine->AddOnScreenDebugMessage(-1, 0.0f, FColor::Green,
		                                 FString::Printf(TEXT("Mult Hit Actor %s"), *HitActor->GetName()));

		DrawDebugSphere(GetWorld(), Hit.ImpactPoint, 20.f, 12, FColor::Green, false, 2.f);

		UGameplayStatics::ApplyPointDamage(
			HitActor,
			50.f,
			GetActorForwardVector(),
			Hit,
			GetInstigatorController(),
			this,
			UMyTestDamageType::StaticClass()
		);
	}
}
