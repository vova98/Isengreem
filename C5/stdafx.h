// stdafx.h: включаемый файл дл€ стандартных системных включаемых файлов
// или включаемых файлов дл€ конкретного проекта, которые часто используютс€, но
// не часто измен€ютс€
//

#pragma once

#include "targetver.h"

#include <stdio.h>
#include <tchar.h>


#include <cerrno>
struct StudAndMark
{
	char surname[29];
	int mark;
	int surnlength;
};

StudAndMark* InputData(int count);
