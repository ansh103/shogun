/*
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3 of the License, or
 * (at your option) any later version.
 *
 * Written (W) 1999-2008 Soeren Sonnenburg
 * Copyright (C) 1999-2008 Fraunhofer Institute FIRST and Max-Planck-Society
 */

#include "lib/common.h"
#include "kernel/Chi2Kernel.h"
#include "features/Features.h"
#include "features/RealFeatures.h"
#include "lib/io.h"

CChi2Kernel::CChi2Kernel(int32_t size, DREAL w)
: CSimpleKernel<DREAL>(size), width(w)
{
}

CChi2Kernel::CChi2Kernel(CRealFeatures* l, CRealFeatures* r, DREAL w, int32_t size)
: CSimpleKernel<DREAL>(size), width(w)
{
	init(l,r);
}

CChi2Kernel::~CChi2Kernel()
{
	cleanup();
}

bool CChi2Kernel::init(CFeatures* l, CFeatures* r)
{
	bool result=CSimpleKernel<DREAL>::init(l,r);
	init_normalizer();
	return result;
}

bool CChi2Kernel::load_init(FILE* src)
{
	return false;
}

bool CChi2Kernel::save_init(FILE* dest)
{
	return false;
}
  
DREAL CChi2Kernel::compute(int32_t idx_a, int32_t idx_b)
{
	int32_t alen, blen;
	bool afree, bfree;

	double* avec=((CRealFeatures*) lhs)->get_feature_vector(idx_a, alen, afree);
	double* bvec=((CRealFeatures*) rhs)->get_feature_vector(idx_b, blen, bfree);
	ASSERT(alen==blen);

	DREAL result=0;
	for (int32_t i=0; i<alen; i++)
	{
		DREAL n=avec[i]-bvec[i];
		DREAL d=avec[i]+bvec[i];
		if (d!=0)
			result+=n*n/d;
	}

	result=exp(-result/width);

	((CRealFeatures*) lhs)->free_feature_vector(avec, idx_a, afree);
	((CRealFeatures*) rhs)->free_feature_vector(bvec, idx_b, bfree);

	return result;
}
