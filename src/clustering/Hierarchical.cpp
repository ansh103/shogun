/*
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3 of the License, or
 * (at your option) any later version.
 *
 * Written (W) 2007-2008 Soeren Sonnenburg
 * Copyright (C) 2007-2008 Fraunhofer Institute FIRST and Max-Planck-Society
 */

#include "clustering/Hierarchical.h"
#include "distance/Distance.h"
#include "features/Labels.h"
#include "features/RealFeatures.h"
#include "lib/Mathematics.h"
#include "base/Parallel.h"

#ifndef WIN32
#include <pthread.h>
#endif

struct pair
{
	/** index 1 */
	int32_t idx1;
	/** index 2 */
	int32_t idx2;
};

CHierarchical::CHierarchical()
: CDistanceMachine(), merges(3), dimensions(0), assignment(NULL),
	table_size(0), pairs(NULL), merge_distance(NULL)
{
}

CHierarchical::CHierarchical(int32_t merges_, CDistance* d)
: CDistanceMachine(), merges(merges_), dimensions(0), assignment(NULL),
	table_size(0), pairs(NULL), merge_distance(NULL)
{
	set_distance(d);
}

CHierarchical::~CHierarchical()
{
	delete[] merge_distance;
	delete[] assignment;
	delete[] pairs;
}

bool CHierarchical::train()
{
	ASSERT(distance);
	CFeatures* lhs=distance->get_lhs();
	ASSERT(lhs);

	int32_t num=lhs->get_num_vectors();
	ASSERT(num>0);

	const int32_t num_pairs=num*(num-1)/2;

	delete[] merge_distance;
	merge_distance=new DREAL[num];
	CMath::fill_vector(merge_distance, num, -1.0);

	delete[] assignment;
	assignment=new int32_t[num];
	CMath::range_fill_vector(assignment, num);

	delete[] pairs;
	pairs=new int32_t[2*num];
	CMath::fill_vector(pairs, 2*num, -1);

	pair* index=new pair[num_pairs];
	DREAL* distances=new DREAL[num_pairs];

	int32_t offs=0;
	for (int32_t i=0; i<num; i++)
	{
		for (int32_t j=i+1; j<num; j++)
		{
			distances[offs]=distance->distance(i,j);
			index[offs].idx1=i;
			index[offs].idx2=j;
			offs++;					//offs=i*(i+1)/2+j
		}
		SG_PROGRESS(i, 0, num-1);
	}

	CMath::qsort_index<DREAL,pair>(distances, index, (num-1)*num/2);
	//CMath::display_vector(distances, (num-1)*num/2, "dists");

	int32_t k=-1;
	int32_t l=0;
	for (; l<num && (num-l)>=merges && k<num_pairs-1; l++)
	{
		while (k<num_pairs-1)
		{
			k++;

			int32_t i=index[k].idx1;
			int32_t j=index[k].idx2;
			int32_t c1=assignment[i];
			int32_t c2=assignment[j];

			if (c1==c2)
				continue;
			
			SG_PROGRESS(k, 0, num_pairs-1);

			if (c1<c2)
			{
				pairs[2*l]=c1;
				pairs[2*l+1]=c2;
			}
			else
			{
				pairs[2*l]=c2;
				pairs[2*l+1]=c1;
			}
			merge_distance[l]=distances[k];

			int32_t c=num+l;
			for (int32_t m=0; m<num; m++)
			{
				if (assignment[m] == c1 || assignment[m] == c2)
					assignment[m] = c;
			}
#ifdef DEBUG_HIERARCHICAL
			SG_PRINT("l=%04i i=%04i j=%04i c1=%+04d c2=%+04d c=%+04d dist=%6.6f\n", l,i,j, c1,c2,c, merge_distance[l]);
#endif
			break;
		}
	}

	assignment_size=num;
	table_size=l-1;
	ASSERT(table_size>0);
	delete[] distances;
	delete[] index;
	SG_UNREF(lhs)

	return true;
}

bool CHierarchical::load(FILE* srcfile)
{
	return false;
}

bool CHierarchical::save(FILE* dstfile)
{
	return false;
}
