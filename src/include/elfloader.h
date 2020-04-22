#ifndef __ELF_LOADER_H_
#define __ELF_LOADER_H_
#include <stdio.h>

typedef struct elfheader_s elfheader_t;
typedef struct lib_s lib_t;
typedef struct library_s library_t;
typedef struct kh_mapsymbols_s kh_mapsymbols_t;
typedef struct box86context_s box86context_t;
typedef struct x86emu_s x86emu_t;
#ifdef DYNAREC
typedef struct dynablocklist_s dynablocklist_t;
#endif

elfheader_t* LoadAndCheckElfHeader(FILE* f, const char* name, int exec); // exec : 0 = lib, 1 = exec
void FreeElfHeader(elfheader_t** head);
const char* ElfName(elfheader_t* head);

// return 0 if OK
int CalcLoadAddr(elfheader_t* head);
int AllocElfMemory(box86context_t* context, elfheader_t* head, int mainbin);
void FreeElfMemory(elfheader_t* head);
int LoadElfMemory(FILE* f, box86context_t* context, elfheader_t* head);
int ReloadElfMemory(FILE* f, box86context_t* context, elfheader_t* head);
int RelocateElf(lib_t *maplib, elfheader_t* head);
int RelocateElfPlt(box86context_t* context, lib_t *maplib, elfheader_t* head);
void CalcStack(elfheader_t* h, uint32_t* stacksz, int* stackalign);
uintptr_t GetEntryPoint(lib_t* maplib, elfheader_t* h);
uintptr_t GetLastByte(elfheader_t* h);
void AddSymbols(lib_t *maplib, kh_mapsymbols_t* mapsymbols, kh_mapsymbols_t* weaksymbols, kh_mapsymbols_t* localsymbols, elfheader_t* h);
int LoadNeededLibs(elfheader_t* h, lib_t *maplib, library_t* parent, box86context_t* box86, x86emu_t* emu);
int FinalizeNeededLibs(elfheader_t* h, lib_t *maplib, box86context_t *box86, x86emu_t* emu);
uintptr_t GetElfInit(elfheader_t* h);
uintptr_t GetElfFini(elfheader_t* h);
void RunElfInit(elfheader_t* h, x86emu_t *emu);
void RunElfFini(elfheader_t* h, x86emu_t *emu);
void RunDeferedElfInit(x86emu_t *emu);
void* GetBaseAddress(elfheader_t* h);
void* GetElfDelta(elfheader_t* h);
uint32_t GetBaseSize(elfheader_t* h);
int IsAddressInElfSpace(elfheader_t* h, uintptr_t addr);
elfheader_t* FindElfAddress(box86context_t *context, uintptr_t addr);
const char* FindNearestSymbolName(elfheader_t* h, void* p, uintptr_t* start, uint32_t* sz);
void* GetGSBase(box86context_t *context);
int32_t GetTLSBase(elfheader_t* h);
uint32_t GetTLSSize(elfheader_t* h);
void* GetTLSPointer(box86context_t* context, elfheader_t* h);
void* GetDTatOffset(box86context_t* context, int index, int offset);
#ifdef DYNAREC
dynablocklist_t* GetDynablocksFromAddress(box86context_t *context, uintptr_t addr);
#endif
void ResetSpecialCaseMainElf(elfheader_t* h);
void CreateMemorymapFile(box86context_t* context, int fd);


#endif //__ELF_LOADER_H_