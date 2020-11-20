#include "Runtime/BuildFramework/Public/Ghost/Ghost.h"

#include "Runtime/BuildFramework/Public/BuildInfo/BuildInfo.h"
#include "Runtime/BuildFramework/Public/Footprint/BuildFootprint.h"
#include "Runtime/BuildFramework/Public/Footprint/BuildPoint.h"

#include <Runtime/Engine/Classes/Components/SceneComponent.h>
#include <Runtime/Engine/Classes/Components/HierarchicalInstancedStaticMeshComponent.h>
#include <Runtime/Engine/Classes/Engine/StaticMesh.h>

DEFINE_LOG_CATEGORY_STATIC(GhostLog, Log, Log)

namespace GhostPrivate
{
	const FName RootComponentName = TEXT("GhostRoot");
}

AGhost::AGhost(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
	, GhostRoot(ObjectInitializer.CreateDefaultSubobject<USceneComponent>(this, GhostPrivate::RootComponentName))
{
	SetRootComponent(GhostRoot);
}

void AGhost::UpdateFootprint(const FBuildFootprint& InFootprint)
{
	Reset();
	Rebuild(InFootprint);
}

void AGhost::Reset()
{
	for (UHierarchicalInstancedStaticMeshComponent* PreviewMesh : PreviewMeshes)
	{
		PreviewMesh->ClearInstances();
	}
}

void AGhost::Rebuild(const FBuildFootprint& InFootprint)
{
	for (const FBuildPoint& Point : InFootprint.Points)
	{
		if(UStaticMesh* Mesh = const_cast<UStaticMesh*>(InFootprint.SourceBuildInfo->GetMeshForPoint(Point.GetType())))
		{
			UHierarchicalInstancedStaticMeshComponent& HIMesh = GetComponentForMesh(*Mesh);
			HIMesh.AddInstance(Point.GetTransform());
		}
	}
}

UHierarchicalInstancedStaticMeshComponent& AGhost::GetComponentForMesh(UStaticMesh& InMesh)
{
	const uint32 IndexOfExistingMesh = PreviewMeshes.IndexOfByPredicate([&InMesh](const UHierarchicalInstancedStaticMeshComponent* Comp)
	{
		return Comp->GetStaticMesh() == &InMesh;
	});

	return IndexOfExistingMesh != INDEX_NONE ? *PreviewMeshes[IndexOfExistingMesh] : CreateInstanceForMesh(InMesh);
}

UHierarchicalInstancedStaticMeshComponent& AGhost::CreateInstanceForMesh(UStaticMesh& InMesh)
{
	UE_LOG(GhostLog, Log, TEXT("Creating HIMesh for %s"), *InMesh.GetName());

	UHierarchicalInstancedStaticMeshComponent* NewMesh = NewObject<UHierarchicalInstancedStaticMeshComponent>
		(
			this,
			UHierarchicalInstancedStaticMeshComponent::StaticClass(),
			*InMesh.GetName()
		);

	NewMesh->RegisterComponent();

	NewMesh->AttachToComponent(GhostRoot, FAttachmentTransformRules::SnapToTargetIncludingScale);
	NewMesh->SetStaticMesh(&InMesh);

	PreviewMeshes.AddUnique(NewMesh);

	return *NewMesh;
}