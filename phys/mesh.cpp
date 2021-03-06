#include "stdafx.h"
#include <phys/phys.h>
#include <phys/mesh.h>
#include <gfx/model.h>
#include <future>
#include <mutex>

using namespace phys;

//
// Based on Tomas M�ller's code
// http://web.stanford.edu/class/cs277/resources/papers/Moller1997b.pdf
//

#define FABS(x) (float(std::fabs(x)))

/* if USE_EPSILON_TEST is true then we do a check:
if |dv|<EPSILON then dv=0.0;
else no check is done (which is less robust)
*/
#define USE_EPSILON_TEST true

/* some macros */
#define CROSS(dest,v1,v2) dest = cross(v1, v2)

#define DOT(v1,v2) dot(v1, v2)

#define SUB(dest,v1,v2) dest = v1 - v2

#define EPSILON (0.000001f)

#define SORT(a,b)       \
             if(a>b)    \
             {          \
               float c; \
               c=a;     \
               a=b;     \
               b=c;     \
             }

/* this edge to edge test is based on Franlin Antonio's gem:
"Faster Line Segment Intersection", in Graphics Gems III,
pp. 199-202 */
#define EDGE_EDGE_TEST(V0,U0,U1)                      \
  Bx=U0[i0]-U1[i0];                                   \
  By=U0[i1]-U1[i1];                                   \
  Cx=V0[i0]-U0[i0];                                   \
  Cy=V0[i1]-U0[i1];                                   \
  f=Ay*Bx-Ax*By;                                      \
  d=By*Cx-Bx*Cy;                                      \
  if((f>0 && d>=0 && d<=f) || (f<0 && d<=0 && d>=f))  \
  {                                                   \
    e=Ax*Cy-Ay*Cx;                                    \
    if(f>0)                                           \
    {                                                 \
      if(e>=0 && e<=f) return 1;                      \
    }                                                 \
    else                                              \
    {                                                 \
      if(e<=0 && e>=f) return 1;                      \
    }                                                 \
  }

#define EDGE_AGAINST_TRI_EDGES(V0,V1,U0,U1,U2) \
{                                              \
  float Ax,Ay,Bx,By,Cx,Cy,e,d,f;               \
  Ax=V1[i0]-V0[i0];                            \
  Ay=V1[i1]-V0[i1];                            \
  /* test edge U0,U1 against V0,V1 */          \
  EDGE_EDGE_TEST(V0,U0,U1);                    \
  /* test edge U1,U2 against V0,V1 */          \
  EDGE_EDGE_TEST(V0,U1,U2);                    \
  /* test edge U2,U1 against V0,V1 */          \
  EDGE_EDGE_TEST(V0,U2,U0);                    \
}

#define POINT_IN_TRI(V0,U0,U1,U2)           \
{                                           \
  float a,b,c,d0,d1,d2;                     \
  /* is T1 completly inside T2? */          \
  /* check if V0 is inside tri(U0,U1,U2) */ \
  a=U1[i1]-U0[i1];                          \
  b=-(U1[i0]-U0[i0]);                       \
  c=-a*U0[i0]-b*U0[i1];                     \
  d0=a*V0[i0]+b*V0[i1]+c;                   \
                                            \
  a=U2[i1]-U1[i1];                          \
  b=-(U2[i0]-U1[i0]);                       \
  c=-a*U1[i0]-b*U1[i1];                     \
  d1=a*V0[i0]+b*V0[i1]+c;                   \
                                            \
  a=U0[i1]-U2[i1];                          \
  b=-(U0[i0]-U2[i0]);                       \
  c=-a*U2[i0]-b*U2[i1];                     \
  d2=a*V0[i0]+b*V0[i1]+c;                   \
  if(d0*d1>0.0)                             \
  {                                         \
    if(d0*d2>0.0) return 1;                 \
  }                                         \
}

#define NEWCOMPUTE_INTERVALS(VV0,VV1,VV2,D0,D1,D2,D0D1,D0D2,A,B,C,X0,X1) \
{ \
        if(D0D1>0.0f) \
        { \
                /* here we know that D0D2<=0.0 */ \
            /* that is D0, D1 are on the same side, D2 on the other or on the plane */ \
                A=VV2; B=(VV0-VV2)*D2; C=(VV1-VV2)*D2; X0=D2-D0; X1=D2-D1; \
        } \
        else if(D0D2>0.0f)\
        { \
                /* here we know that d0d1<=0.0 */ \
            A=VV1; B=(VV0-VV1)*D1; C=(VV2-VV1)*D1; X0=D1-D0; X1=D1-D2; \
        } \
        else if(D1*D2>0.0f || D0!=0.0f) \
        { \
                /* here we know that d0d1<=0.0 or that D0!=0.0 */ \
                A=VV0; B=(VV1-VV0)*D0; C=(VV2-VV0)*D0; X0=D0-D1; X1=D0-D2; \
        } \
        else if(D1!=0.0f) \
        { \
                A=VV1; B=(VV0-VV1)*D1; C=(VV2-VV1)*D1; X0=D1-D0; X1=D1-D2; \
        } \
        else if(D2!=0.0f) \
        { \
                A=VV2; B=(VV0-VV2)*D2; C=(VV1-VV2)*D2; X0=D2-D0; X1=D2-D1; \
        } \
        else \
        { \
                /* triangles are coplanar */ \
                return coplanar_tri_tri(N1,V0,V1,V2,U0,U1,U2); \
        } \
}

int coplanar_tri_tri(math::vector3<float>& N, math::vector3<float>& V0, math::vector3<float>& V1, math::vector3<float>& V2,
	math::vector3<float>& U0, math::vector3<float>& U1, math::vector3<float>& U2)
{
	float A[3];
	short i0, i1;
	/* first project onto an axis-aligned plane, that maximizes the area */
	/* of the triangles, compute indices: i0,i1. */
	A[0] = FABS(N[0]);
	A[1] = FABS(N[1]);
	A[2] = FABS(N[2]);
	if (A[0]>A[1])
	{
		if (A[0]>A[2])
		{
			i0 = 1;      /* A[0] is greatest */
			i1 = 2;
		}
		else
		{
			i0 = 0;      /* A[2] is greatest */
			i1 = 1;
		}
	}
	else   /* A[0]<=A[1] */
	{
		if (A[2]>A[1])
		{
			i0 = 0;      /* A[2] is greatest */
			i1 = 1;
		}
		else
		{
			i0 = 0;      /* A[1] is greatest */
			i1 = 2;
		}
	}

	/* test all edges of triangle 1 against the edges of triangle 2 */
	EDGE_AGAINST_TRI_EDGES(V0, V1, U0, U1, U2);
	EDGE_AGAINST_TRI_EDGES(V1, V2, U0, U1, U2);
	EDGE_AGAINST_TRI_EDGES(V2, V0, U0, U1, U2);

	/* finally, test if tri1 is totally contained in tri2 or vice versa */
	POINT_IN_TRI(V0, U0, U1, U2);
	POINT_IN_TRI(U0, V0, V1, V2);

	return 0;
}

static int NoDivTriTriIsect(const triangle& v, const triangle& u)
{
	math::vector3<float> E1, E2;
	math::vector3<float> N1, N2;
	float d1, d2;
	//float E1[3], E2[3];
	//float N1[3], N2[3], d1, d2;
	float du0, du1, du2, dv0, dv1, dv2;
	math::vector3<float> D;
	float isect1[2], isect2[2];
	float du0du1, du0du2, dv0dv1, dv0dv2;
	short index;
	float vp0, vp1, vp2;
	float up0, up1, up2;
	float bb, cc, max;

	math::vector3<float> V0 = v[0];
	math::vector3<float> V1 = v[1];
	math::vector3<float> V2 = v[2];
	math::vector3<float> U0 = u[0];
	math::vector3<float> U1 = u[1];
	math::vector3<float> U2 = u[2];
	/* compute plane equation of triangle(V0,V1,V2) */
	SUB(E1, V1, V0);
	SUB(E2, V2, V0);
	CROSS(N1, E1, E2);
	d1 = -DOT(N1, V0);
	/* plane equation 1: N1.X+d1=0 */

	/* put U0,U1,U2 into plane equation 1 to compute signed distances to the plane*/
	du0 = DOT(N1, U0) + d1;
	du1 = DOT(N1, U1) + d1;
	du2 = DOT(N1, U2) + d1;

	/* coplanarity robustness check */
#if USE_EPSILON_TEST==TRUE
	if (FABS(du0)<EPSILON) du0 = 0.0;
	if (FABS(du1)<EPSILON) du1 = 0.0;
	if (FABS(du2)<EPSILON) du2 = 0.0;
#endif
	du0du1 = du0 * du1;
	du0du2 = du0 * du2;

	if (du0du1>0.0f && du0du2>0.0f) /* same sign on all of them + not equal 0 ? */
		return 0;                    /* no intersection occurs */

									 /* compute plane of triangle (U0,U1,U2) */
	SUB(E1, U1, U0);
	SUB(E2, U2, U0);
	CROSS(N2, E1, E2);
	d2 = -DOT(N2, U0);
	/* plane equation 2: N2.X+d2=0 */

	/* put V0,V1,V2 into plane equation 2 */
	dv0 = DOT(N2, V0) + d2;
	dv1 = DOT(N2, V1) + d2;
	dv2 = DOT(N2, V2) + d2;

#if USE_EPSILON_TEST==TRUE
	if (FABS(dv0)<EPSILON) dv0 = 0.0;
	if (FABS(dv1)<EPSILON) dv1 = 0.0;
	if (FABS(dv2)<EPSILON) dv2 = 0.0;
#endif

	dv0dv1 = dv0 * dv1;
	dv0dv2 = dv0 * dv2;

	if (dv0dv1>0.0f && dv0dv2>0.0f) /* same sign on all of them + not equal 0 ? */
		return 0;                    /* no intersection occurs */

									 /* compute direction of intersection line */
	CROSS(D, N1, N2);

	/* compute and index to the largest component of D */
	max = (float)FABS(D[0]);
	index = 0;
	bb = (float)FABS(D[1]);
	cc = (float)FABS(D[2]);
	if (bb>max) max = bb, index = 1;
	if (cc>max) max = cc, index = 2;

	/* this is the simplified projection onto L*/
	vp0 = V0[index];
	vp1 = V1[index];
	vp2 = V2[index];

	up0 = U0[index];
	up1 = U1[index];
	up2 = U2[index];

	/* compute interval for triangle 1 */
	float a, b, c, x0, x1;
	NEWCOMPUTE_INTERVALS(vp0, vp1, vp2, dv0, dv1, dv2, dv0dv1, dv0dv2, a, b, c, x0, x1);

	/* compute interval for triangle 2 */
	float d, e, f, y0, y1;
	NEWCOMPUTE_INTERVALS(up0, up1, up2, du0, du1, du2, du0du1, du0du2, d, e, f, y0, y1);

	float xx, yy, xxyy, tmp;
	xx = x0 * x1;
	yy = y0 * y1;
	xxyy = xx * yy;

	tmp = a * xxyy;
	isect1[0] = tmp + b * x1*yy;
	isect1[1] = tmp + c * x0*yy;

	tmp = d * xxyy;
	isect2[0] = tmp + e * xx*y1;
	isect2[1] = tmp + f * xx*y0;

	SORT(isect1[0], isect1[1]);
	SORT(isect2[0], isect2[1]);

	if (isect1[1]<isect2[0] || isect2[1]<isect1[0]) return 0;
	return 1;
}

intersect_result phys::intersect_triangles(const triangle& lhs, const triangle& rhs) {
	intersect_result ret;
	ret.hit = NoDivTriTriIsect(lhs, rhs) == 1;
	return ret;
}

phys::triangle mt2pt(const gfx::triangle& t) {
	phys::triangle ret;
	for (const auto& v : t) {
		ret.vertices.push_back(math::vector3<float>(v.pos[0], v.pos[1], v.pos[2]));
	}
	ASSERT(ret.vertices.size() >= 3);
	return ret;
}

// egy batch m�rete
static const size_t BATCH_SIZE = 8;

intersect_result phys::intersect(const mesh& lhs, const mesh& rhs)
{
	intersect_result ret;
	
	for (size_t i = 0; i < lhs.size(); i++) {
		for (size_t j = 0; j < rhs.size(); j++) {
			phys::triangle l = mt2pt(lhs[i]);
			phys::triangle r = mt2pt(lhs[j]);
			ret = phys::intersect_triangles(l, r);
			if (ret.hit) {
				return ret;
			}
		}
	}

	ret.hit = false;
	return ret;
	//
	// MT
	//
	//std::list<std::future<intersect_result>> futures;

	//// �sszehasonl�tjuk az LHS �sszes h�romsz�g�t az RHS
	//// �sszes h�romsz�g�vel
	//for (size_t i = 0; i < lhs.size(); i++) {
	//	for (size_t j = 0; j < rhs.size(); j += BATCH_SIZE) {
	//		const model_triangle& l = lhs[i];
	//		const model_triangle& r = rhs[i];

	//		// Aszinkron azonnal elindul a thread
	//		// �tadjuk a kezd�indexeket
	//		// Egy task �sszehasonl�t egy h�romsz�get m�sik BATCH_SIZE darab h�romsz�ggel
	//		std::future<intersect_result> result = std::async(std::launch::async, 
	//			[&lhs, &rhs](size_t l, size_t r) {
	//				intersect_result ret;

	//				// Lek�rj�k az `l`-ik h�romsz�get �s �talak�tjuk phys::triangle-�
	//				phys::triangle tri_l = mt2pt(lhs[l]);
	//				// 
	//				for (size_t i = 0; i < BATCH_SIZE; i++) {
	//					if (r + i == rhs.size())
	//						break;
	//					phys::triangle tri_r = mt2pt(lhs[r + i]);
	//					// Intersection test
	//					intersect_result ret = phys::intersect_triangles(tri_l, tri_r);
	//					// Ha valamely h�romsz�gek metszik egym�st, early return
	//					if (ret.hit) {
	//						return ret;
	//					}
	//				}
	//				// Ha nincs metsz�s
	//				ret.hit = false;
	//				return ret;
	//			},
	//		i, j);
	//		// a future-t elt�roljuk
	//		futures.push_back(std::move(result));
	//	}
	//}

	//// 
	//while(true) {
	//	for (size_t i = 0; i < futures.size(); i++) {

	//	}
	//}

	//// 
	//intersect_result ret;
	//ret.hit = false;
	//return ret;
}

intersect_result phys::intersect_triangle_ray(const ray& r, const triangle& tri)
{
	intersect_result ret;
	ret.hit = false;
	math::vector3<float> v1 = tri.vertices[0];
	math::vector3<float> v2 = tri.vertices[1];
	math::vector3<float> v3 = tri.vertices[2];
	math::vector3<float> orig = r.origin;
	math::vector3<float> dir = r.dir;
	math::vector3<float> e1, e2, pvec, qvec, tvec;

	e1 = v2 - v1;
	e2 = v3 - v1;

	pvec = cross(dir, e2);

	dir.normalize();
	//pvec.normalize();
	float det = dot(pvec, e1);
#ifdef TEST_CULL
	if (det <EPSILON)
	{

		ret.hit = false;
		return ret;
	}
	tvec = orig - v1;
	float u = dot(tvec, pvec);
	if (u < 0.0 || u > det)
	{

		ret.hit = false;
		return ret;
	}
	qvec = cross(tvec, e1);
	float v = dot(dir, qvec);
	if (v < 0.0f || v + u > det)
	{

		ret.hit = false;
		return ret;
	}
#else
	if (det < EPSILON && det > -EPSILON)
	{

		ret.hit = false;
		return ret;
	}

	float invDet = 1.0f / det;
	tvec = orig - v1;
	//tvec.normalize();
	float u = invDet * dot(tvec, pvec);
	if (u <0.0f || u > 1.0f)
	{

		ret.hit = false;
		return ret;
	}
	qvec = cross(tvec, e1);
	//qvec.normalize();
	float v = invDet * dot(qvec, dir);
	if (v < 0.0f || u + v > 1.0f)
	{

		ret.hit = false;
		return ret;
	}
#endif
	ret.hit = true;
	return ret;
}
