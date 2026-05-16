
#pragma once

using namespace RC;
using namespace RC::Unreal;


namespace BPSharing {
	void ManageHook([[maybe_unused]] Unreal::UObject* Context, Unreal::FFrame& Stack, [[maybe_unused]] void* RESULT_DECL);
	void SetBPFunctions();
}
