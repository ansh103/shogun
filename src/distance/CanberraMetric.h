/*
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3 of the License, or
 * (at your option) any later version.
 *
 * Written (W) 2006 Christian Gehl
 * Copyright (C) 1999-2008 Fraunhofer Institute FIRST
 */

#ifndef _CANBERRAMETRIC_H__
#define _CANBERRAMETRIC_H___

#include "lib/common.h"
#include "distance/SimpleDistance.h"
#include "features/RealFeatures.h"

/** class CanberraMetric 
 *
 * The Canberra distance sums up the dissimilarity (ratios) between feature 
 * dimensions of two data points.
 *
 * \f[\displaystyle
 *   d(\bf{x},\bf{x'}) = \sum_{i=1}^{n}\frac{|\bf{x_{i}-\bf{x'_{i}}}|}
 *    {|\bf{x_{i}}|+|\bf{x'_{i}}|} \quad \bf{x},\bf{x'} \in R^{n}
 * \f]
 *
 *  A summation element has range [0,1]. Note that \f$d(x,0)=d(0,x')=n\f$ 
 *  and \f$d(0,0)=0\f$.
 */
class CCanberraMetric: public CSimpleDistance<DREAL>
{
	public:
		/** default constructor */
		CCanberraMetric();

		/** constructor
		 *
		 * @param l features of left-hand side
		 * @param r features of right-hand side
		 */
		CCanberraMetric(CRealFeatures* l, CRealFeatures* r);
		virtual ~CCanberraMetric();

		/** init distance
		 *
		 * @param l features of left-hand side
		 * @param r features of right-hand side
		 * @return if init was successful
		 */
		virtual bool init(CFeatures* l, CFeatures* r);

		/** cleanup distance */
		virtual void cleanup();

		/** load init data from file
		 *
		 * @param src file to load from
		 * @return if loading was successful
		 */
		virtual bool load_init(FILE* src);

		/** save init data to file
		 *
		 * @param dest file to save to
		 * @return if saving was successful
		 */
		virtual bool save_init(FILE* dest);

		/** get distance type we are
		 *
		 * @return distance type CANBERRA
		 */
		virtual EDistanceType get_distance_type() { return D_CANBERRA; }

		/** get name of the distance
		 *
		 * @return name Canberra-Metric
		 */
		virtual const char* get_name() { return "Canberra-Metric"; }

	protected:
		/// compute distance for features a and b
		/// idx_{a,b} denote the index of the feature vectors
		/// in the corresponding feature object
		virtual DREAL compute(int32_t idx_a, int32_t idx_b);
};

#endif /* _CANBERRAMETRIC_H__ */
