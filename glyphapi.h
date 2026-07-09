#include <Windows.h>

typedef struct {
    void* address;
} sexportAddr;

typedef struct {
    char name[128];
    int timesCalled;
    int currentAddressCount;
    sexportAddr addr[300];
} sexportData;

typedef struct {
    char name[150];
    void* address;
} HookedFunctions;

typedef struct {
    char name[128];
    FARPROC address;
} Imports;

typedef struct {
    char name[100];
    void* address;
    int timesCalled;
} exports;

typedef struct {
    wchar_t modName[MAX_PATH];
    FARPROC modAddress;
    exports* export;
    unsigned long exportCount;
} Dlls;

typedef struct GlyphHandle {
    void* hproc;
    void* base;
    unsigned char engineName[0x20];
} GlyphHandle;

int readExports(void* hProcess, void* exportList);
int readHooked(void* hProcess, void* hookedList);
int readModules(void* hProcess, void* moduleStruct);
int readImports(void* hProcess, void* ImportStruct);
void* GlyphGetHandle(GlyphHandle* in, char* name);
int GetGlyph(GlyphHandle* out, char* procName);
int wideToChar(wchar_t* word, char* out, int size);
int wideLen(wchar_t* word);
unsigned long long GlyphConnect(GlyphHandle* out, char* GlyphEXEName, char* sessionName);
int GlyphSendCommandA(GlyphHandle* out, void* apiInAddress, unsigned char* command);
int GlyphCloseHandle(GlyphHandle* out);
int GlyphDump(GlyphHandle* out, void* commandBuff, unsigned char* address);

// Memory Allocator
#define MAXSIZE 100000

typedef struct {
    unsigned char name[8];
    unsigned long long address;
    unsigned long dataRVA;
    struct Entry* next;
} Entry;

//int startingrva = 10000;

Entry* GlyphMakeChunks(Entry* ent, int num);

int GlyphAlloc(Entry* ent, char* name, unsigned char* data, int len);

void* GlyphReadAlloc(Entry* ent, char* name);

// Hash Map 
typedef struct{
unsigned char name[16];
void* address;
int len;
} Entrymap;

typedef struct {
Entrymap entry[20];
} hashmap;

hashmap map[50];

int hash(char* key);

int GlyphHashmapStore(char* key, void* address, int len);

Entrymap* GlyphHashmapGet(char* key);

// Helpers
int mystrcmp(char* one, char* two);

int mystrstr(char* buff, char* string, int size);

int mystrlen(char* buff);

int myisAlpha(unsigned char byte);

int myisprint(unsigned char byte);

int toUpper(unsigned char byte);

char* zero(char* buff, char* delimiter);

void* mystdhandleIN(int num);

int writeCon(char* buff);
int charToWide(char* string, wchar_t* out);
int mygetlasterror();

// Nt typedefs

// typedef NTSTATUS (NTAPI* pNtTerminateProcess)(HANDLE, NTSTATUS);
// typedef NTSTATUS(NTAPI* pNtQueryInformationProcess)(HANDLE, PROCESSINFOCLASS, PVOID, ULONG, PULONG);
// typedef NTSTATUS(NTAPI* pNtQuerySystemInformation)(SYSTEM_INFORMATION_CLASS, PVOID, ULONG, PULONG);
