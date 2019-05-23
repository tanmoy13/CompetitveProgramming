/**
	The lattitude and longitude are given with respect to the earth radius.
	Which is R = 6378. radius of earth.
	Find the minimum distance between the two points.
	UVa : 10075
**/


double gc_distance(double pLat, double pLong, double qLat, double qLong, double r)
{
    /// Angels must be converted into radian.
    pLat *= pi / 180;
    pLong *= pi / 180;
    qLat *= pi / 180;
    qLong *= pi / 180;
    return r * acos(cos(pLat) * cos(qLat) * cos(pLong - qLong) + sin(pLat) * sin(qLat));
}

