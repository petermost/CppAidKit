#pragma once

#include <functional>
#include <unordered_map>

class CRTDebugHeap {
	public:
		struct AllocationInfo {
			std::size_t size;
			const char *fileName;
			int lineNumber;
		};

		CRTDebugHeap();
		~CRTDebugHeap();

		static void forEachAllocation(const std::function<void (long /* request number */, const AllocationInfo &)> &consumer);

	private:
		static int AllocHook(int allocType, void *userData, size_t size, int blockType, long requestNumber,
			const unsigned char *fileName, int lineNumber);

		static std::unordered_map<long /* request number */, AllocationInfo> s_allocations;
};
