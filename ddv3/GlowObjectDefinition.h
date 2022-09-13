#pragma once

struct ColorRGBA {
	   float r = 0; // [0, 255]
	   float g = 0; // [0, 255]
	   float b = 0; // [0, 255]
	   float a = 0; // [0, 255]
};
struct ColorRGB {
	uint8_t r{}; // [0, 255]
	uint8_t g{}; // [0, 255]
	uint8_t b{}; // [0, 255]
};

struct GlowObjectDefinition {
	   int				nextFreeSlot;			//0x0000
	   unsigned int	    baseEntity;				//0x0004
	   float			color[4];				//0x0008
	   unsigned long	_pad0x0018;				//0x0018 
	   float			_pad0x001C;				//0x001C 
	   float			bloomAmount;			//0x0020
	   float			noise;					//0x0024
	   bool			    renderWhenOccluded;		//0x0028
       bool			    renderWhenUnoccluded;	//0x0029
	   bool			    fullBloomRender;		//0x002A
	   unsigned char	_pad0x002B[0x1];		//0x002B
	   int				_pad0x002C;				//0x002C
	   int				style;					//0x0030
	   int				splitScreenSlot;		//0x0034

	   void SetColor(float r, float g, float b, float a) {
		    color[0] = r / 255.f;
		    color[1] = g / 255.f;
		    color[2] = b / 255.f;
		    color[3] = a / 255.f;
	   }

	   void SetColor(ColorRGBA value) {
		    color[0] = value.r / 255.f;
		    color[1] = value.g / 255.f;
		    color[2] = value.b / 255.f;
		    color[3] = value.a / 255.f;
	   } 
};