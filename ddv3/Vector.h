#pragma once
#include <cmath>

struct Vec2{
	   float x = 0;
	   float y = 0;
	   Vec2 operator* (float d) {
		    return { x*d,y*d }; 
	   }
	   Vec2 operator- (Vec2 d) {
		    return { x - d.x, y - d.y};
	   }
	   Vec2 operator+ (Vec2 d) {
		    return { x + d.x, y + d.y};
	   }

};

struct Vec3 {
	   float x = 0;
	   float y = 0;
	   float z = 0;
	   Vec3 operator- (Vec3 d) {
		    return { x - d.x, y - d.y, z - d.z };
	   }
	   Vec3 operator+ (Vec3 d) {
		   return { x + d.x, y + d.y, z + d.z };
	   }
	   Vec3 operator* (float d) {
		   return { x * d, y * d, z * d };
	   }
	   Vec3 operator/ (float d) {
		   return { x / d, y / d, z / d };
	   }
	   Vec3 ToAngle() {
		   float pi = 3.141592f;
		   float dx = atan2(-z, hypot(x, y)) * (180.0f / pi);
		   float dy = atan2(y, x) * (180.0f / pi);
		   return { dx, dy, 0 };
	   }
	   bool isZero() {
		   return (x == 0 && y == 0 && z == 0);
	   }
	   Vec2 ToVec2() {
		    return { x, y };
	   }
};
Vec3 CalculateAngle(Vec3 localPosition, Vec3 enemyPosition, Vec3 viewAngles) {
	 return ((enemyPosition - localPosition).ToAngle() - viewAngles);
}