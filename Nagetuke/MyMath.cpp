#include "MyMath.h"

const float MyMath::PI = 3.141593f;

//オブジェクト同士の衝突判定用関数
//衝突していればtrue

/// <summary>
/// 矩形同士が当たっているかどうかを判定する。
/// 辺同士がちょうど重なっている場合は、当たっていないと判定する
/// </summary>
/// <returns>当たっていればtrue, 当たっていなければfalse</returns>
bool MyMath::RectRectIntersect(
	float aLeft, float aRight, float aTop, float aBottom,
	float bLeft, float bRight, float bTop, float bBottom)
{
	return
		aLeft   < bRight  &&
		aRight  > bLeft   &&
		aTop    < bBottom &&
		aBottom > bTop;

}
