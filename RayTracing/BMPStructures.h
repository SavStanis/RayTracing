#pragma once
#include <stdint.h>

#pragma pack(2)
typedef struct BMPHEAD
{
	int8_t id[2] = {'B', 'M'};
	int32_t filesize = 0;      
	int16_t reserved[2] = { 0, 0 };
	int32_t headersize = 54L;      
	int32_t infoSize = 40L;        
	int32_t width = 0;           
	int32_t depth = 0;           
	int16_t biPlanes = 1;        
	int16_t bits = 24;            
	int32_t biCompression = 0L;   
	int32_t biSizeImage = 0L;     
	int32_t biXPelsPerMeter = 0L; 
	int32_t biYPelsPerMeter = 0L; 
	int32_t biClrUsed = 0L;       
	int32_t biClrImportant = 0L;  
};

typedef struct PIXELDATA 
{
	int8_t redComponent;
	int8_t greenComponent;
	int8_t blueComponent;
} ;