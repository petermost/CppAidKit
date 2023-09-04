#include "crtdebug_heap.hpp"

#include <crtdbg.h>

using namespace std;

unordered_map<long /* request number */, CRTDebugHeap::AllocationInfo> CRTDebugHeap::s_allocations;

CRTDebugHeap::CRTDebugHeap()
{
	_CrtSetAllocHook(AllocHook);
}

CRTDebugHeap::~CRTDebugHeap()
{
	_CrtSetAllocHook(nullptr);
}

void CRTDebugHeap::forEachAllocation(const function<void (long, const AllocationInfo &)> &consumer)
{
	for (const auto &entry : s_allocations)
		consumer(entry.first, entry.second);
}

#ifdef _DEBUG
int CRTDebugHeap::AllocHook(int allocType, void *userData, size_t userDataSize,
	int blockType, long requestNumber,
	const unsigned char *fileName, int lineNumber)
{
	// Ignore and therefore prevent infinite recursion for CRT allocated memory!
	if (blockType == _CRT_BLOCK)
		return true;

	switch (allocType) {
		case _HOOK_ALLOC: {
			// We only store the allocation info if we have a filename, otherwise it is not much use to us.
			if (fileName != nullptr)
				s_allocations.insert({ requestNumber, { userDataSize, reinterpret_cast<const char *>(fileName), lineNumber }});

			break;
		}
		case _HOOK_REALLOC: {
			long previousRequestNumber;
			char *previousFileName;
			int previousLineNumber;
			size_t previousSize = _msize_dbg(userData, blockType);

			if (_CrtIsMemoryBlock(userData, previousSize, &previousRequestNumber, &previousFileName, &previousLineNumber)) {
				// Again, we only store the allocation info if we have a filename:
				if (fileName != nullptr)
					s_allocations.insert({ requestNumber, { userDataSize, reinterpret_cast<const char *>(fileName), lineNumber }});
				else if (previousFileName != nullptr)
					s_allocations.insert({ requestNumber, { userDataSize, previousFileName, previousLineNumber }});

				s_allocations.erase(previousRequestNumber);
			}
			break;
		}
		case _HOOK_FREE: {
			long previousRequestNumber;
			char *previousFileName;
			int previousLineNumber;
			size_t previousSize = _msize_dbg(userData, blockType);

			if (_CrtIsMemoryBlock(userData, previousSize, &previousRequestNumber, &previousFileName, &previousLineNumber)) {
				if (previousFileName != nullptr)
					s_allocations.erase(previousRequestNumber);
			}
			break;
		}
	}
	return true;
}
#endif
