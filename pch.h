// pch.h: это предварительно скомпилированный заголовочный файл.
// Перечисленные ниже файлы компилируются только один раз, что ускоряет последующие сборки.
// Это также влияет на работу IntelliSense, включая многие функции просмотра и завершения кода.
// Однако изменение любого из приведенных здесь файлов между операциями сборки приведет к повторной компиляции всех(!) этих файлов.
// Не добавляйте сюда файлы, которые планируете часто изменять, так как в этом случае выигрыша в производительности не будет.

#ifndef PCH_H
#define PCH_H

// Добавьте сюда заголовочные файлы для предварительной компиляции
#include "framework.h"

#include"D:\Program Files\ASCON\KOMPAS-3D v24 Study\SDK\Include\ksConstants.h"
#include"D:\Program Files\ASCON\KOMPAS-3D v24 Study\SDK\Include\ksConstants3D.h"
#include"D:\Program Files\ASCON\KOMPAS-3D v24 Study\SDK\Include\kAPI7.h"

#import"D:\Program Files\ASCON\KOMPAS-3D v24 Study\SDK\lib\kAPI5.tlb" \
	rename("min", "kAPI5_min") \
	rename("max", "kAPI5_max") \
	rename("GetObject", "kAPI5_GetObject")
#import"D:\Program Files\ASCON\KOMPAS-3D v24 Study\SDK\lib\kAPI7.tlb" \
	rename("DeleteFile", "kAPI7_DeleteFile") \
	rename("PostMessage", "kAPI7_PostMessage") \
	rename("GetObject", "kAPI7_GetObject") \
	rename("FindText", "kAPI7_FindText") \
	rename("MessageBoxEx", "kAPI7_MessageBoxEx") \
	rename("DrawText", "kAPI7_DrawText")

#endif //PCH_H
