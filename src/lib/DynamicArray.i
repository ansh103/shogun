%{
 #include "lib/DynamicArray.h" 
 #include "structure/PlifBase.h"
%}

%include "lib/DynamicArray.h"
%include "structure/PlifBase.i"

%template(DynamicCharArray) CDynamicArray<char>;
%template(DynamicByteArray) CDynamicArray<uint8_t>;
%template(DynamicShortArray) CDynamicArray<SHORT>;
%template(DynamicWordArray) CDynamicArray<uint16_t>;
%template(DynamicIntArray) CDynamicArray<int32_t>;
%template(DynamicUIntArray) CDynamicArray<uint32_t>;
%template(DynamicLongArray) CDynamicArray<LONG>;
%template(DynamicULongArray) CDynamicArray<ULONG>;
%template(DynamicShortRealArray) CDynamicArray<SHORTREAL>;
%template(DynamicRealArray) CDynamicArray<DREAL>;
%template(DynamicPlifArray) CDynamicArray<CPlifBase*>;
